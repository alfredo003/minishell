#include "minishell.h"

static int	g_redisplay = 1;

void	sigint_handler(int sig) //Essa função é um manipulador para o sinal SIGINT (geralmente disparado ao pressionar Ctrl+C no terminal).
{
	(void)sig; //Ignora o argumento sig porque ele não é necessário na implementação.
	write(1, "\n", 1); //Escreve um caractere de nova linha (\n) no terminal.
	rl_on_new_line(); //Chama rl_on_new_line() para indicar ao Readline que a linha atual foi concluída.
	rl_replace_line("", 0); //Substitui a linha atual por uma string vazia usando rl_replace_line().
	if (g_redisplay == 1)
		rl_redisplay(); //Se a variável global g_redisplay for 1, redisplay a linha de entrada com rl_redisplay (actualiza e redesenha o que é exibido na tela).
}

static char	*error_message(char *path, t_shell *shell) //Essa função exibe mensagens de erro apropriadas ao tentar executar um comando ou acessar um caminho.
{
	DIR	*folder;
	int	fd;

	fd = open(path, O_WRONLY); //Abre o arquivo especificado pelo path em modo de escrita usando open()
	folder = opendir(path); //Tenta abrir o diretório especificado usando opendir()
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(path, 2);
	if (ft_strchr(path, '/') == NULL)
		ft_putendl_fd(": command not found", 2);  //Caso o path não contenha /, exibe command not found
	else if (fd == -1 && folder == NULL)
		ft_putendl_fd(": No such file or directory", 2); //Se o arquivo ou diretório não existir, exibe a mensagem
	else if (fd == -1 && folder != NULL)
		ft_putendl_fd(": is a directory", 2); //Se o path for um diretório, exibe a mensagem
	else if (fd != -1 && folder == NULL)
		ft_putendl_fd(": Permission denied", 2); //Se o arquivo existir, mas não for acessível, exibe Permission denied
	if (ft_strchr(path, '/') == NULL || (fd == -1 && folder == NULL))
		shell->last_return = 127; //Retorna 127 para comandos não encontrados ou arquivos inexistentes
	else
		shell->last_return = 126; //Retorna 126 para diretórios ou permissões negadas
	if (folder)
		closedir(folder); //Fecha o descritor de diretório (se aberto) e o arquivo (se aberto)
	ft_close(fd); //fecha o fd se ainda estiver aberto
	return (NULL);
}

static char	*find_executable(char *cmd, t_shell *shell, int i) //Essa função encontra o caminho completo de um executável
{
	struct stat	buffer;
	char		**path_dirs;
	char		*full_path;

	if (cmd[0] == '/' || cmd[0] == '.') //Verifica se o comando (cmd) já é um caminho absoluto ou relativo
		if (stat(cmd, &buffer) == 0) //Usa stat(fornece um retrato completo do arquivo do ponto de vista do S.O) para verificar se o arquivo existe
			return (ft_strdup(cmd)); //Se existir, retorna uma cópia do caminho
	shell->values.str1 = ft_getenv(shell->env, "PATH"); //Recupera a variável de ambiente PATH usando ft_getenv()
	if (!shell->values.str1)
		return (NULL);
	path_dirs = ft_split(shell->values.str1, ':'); //Divide os diretórios de PATH usando ft_split()
	ft_free(shell->values.str1, 1);
	while (path_dirs[++i])
	{
		full_path = strjoin_free(ft_strjoin(path_dirs[i], "/"), cmd, 1, 0); //Concatena cada diretório com o comando (cmd) e verifica com stat() se o arquivo existe
		if (full_path && stat(full_path, &buffer) == 0) //Se encontrar, libera a matriz de diretórios e retorna o caminho completo
		{
			ft_free_matrix(path_dirs); 
			return (full_path);
		}
		ft_free(full_path, 1);
	}
	ft_free_matrix(path_dirs); //Caso não encontre, libera a matriz de diretórios e retorna NULL
	return (NULL); 
}

void	handle_child(t_shell *shell, char **cmd) //Essa função executa o comando no processo filho
{
	char	*cmd_path;
	char	**env_matrix;

	cmd_path = find_executable(cmd[0], shell, -1); //Obtém o caminho do executável chamando find_executable()
	if (cmd_path) //Se o caminho for encontrado:
	{
		env_matrix = env_to_matrix(shell->env, 0, 0); //Converte as variáveis de ambiente em uma matriz usando env_to_matrix
		execve(cmd_path, cmd, env_matrix); //Executa o comando com execve()
		ft_free_matrix(env_matrix); //Libera a matriz de variáveis de ambiente
	}
	else //Se o caminho não for encontrado:
	{
		error_message(cmd[0], shell); //para exibir a mensagem de erro apropriada
		shell->parent = 0; //Define como 0 para indicar que o processo filho foi gerenciado
	}
	ft_free(cmd_path, 1);
}

void	execute_cmd(t_shell *shell, char **cmd) //Função responsável por criar um processo filho para executar o comando
{
	int		status;
	sig_t	old_sigquit;
	pid_t	pid;

	status = 0;
	if (shell->charge == 0) //Se o shell não está preparado para executar (shell->charge == 0), retorna imediatamente
		return ;
	old_sigquit = signal(SIGQUIT, sigquit); //Define um manipulador de sinal temporário para SIGQUIT usando signal()
	pid = fork(); //Cria um processo filho com fork(cria um novo processo duplicando-o, chamdado de filho)
	if (pid == 0) //No processo filho
	{
		handle_child(shell, cmd); //Chama handle_child() para executar o comando
		exit(shell->last_return); //Sai com o código de retorno apropriado
	}
	else //No processo pai:
	{
		g_redisplay = 0; //Define g_redisplay como 0 para evitar conflitos com o prompt
		waitpid(pid, &status, 0); //Aguarda o término do processo filho com waitpid(aguarda pela terminação de um processo filho especifico)
		g_redisplay = 1;
		signal(SIGQUIT, old_sigquit); //Restaura o manipulador original de SIGQUIT
	}
	shell->charge = 0;
	shell->last_return = WEXITSTATUS(status); //Atualiza o código de retorno do shell (shell->last_return) com o status do processo filho
}