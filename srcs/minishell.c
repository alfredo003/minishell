#include "minishell.h"
#include <sys/types.h>
#include <sys/wait.h>

static	int g_signal_flag;  //Variável para armazenar sinais recebidos

void	handle_signal(int signal)
{
	g_signal_flag = signal;  //Registrar apenas o número do sinal
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line(); //Informa ao readline que uma nova linha está sendo iniciada
		rl_replace_line("", 0); //Limpa o conteúdo atual da linha
		rl_redisplay(); //Atualiza o prompt e exibe o prompt limpo
	}
}

int	execute_internal_command(char **args)
{
	if (ft_strcmp(args[0], "cd") == 0)
	{
		cd_command(args);
		return (1);
	}
	else if (ft_strcmp(args[0], "pwd") == 0)
	{
		pwd_command();
		return (1);
	}
	else if (ft_strcmp(args[0], "export") == 0)
	{
		export_command(args);
		return (1);
	}
	/*else if (ft_strcmp(args[0], "echo") == 0)
	{
		cd_command(args);
		return (1);
	}*/
	/*else if (ft_strcmp(args[0], "unset") == 0)
	{
		cd_command(args);
		return (1);
	}*/
	else if (ft_strcmp(args[0], "env") == 0)
	{
		cd_command(args);
		return (1);
	}
	else if (ft_strcmp(args[0], "exit") == 0)
		exit(0);
	return (0);
}

/*void	execute_external_command(char **args)
{
	pid_t	pid;
	int	status;

	pid = fork();
	if (pid == 0)  // Processo filho
	{
		if (execve(args[0], args, NULL) == -1) // Executa o comando com o ambiente especificado
			perror("my_shell");
		exit(EXIT_FAILURE); // Sai se execve falhar
	}
	else if (pid < 0)  // Erro ao criar o processo filho
		perror("my_shell");
	else  // Processo pai
		wait(&status); // Espera o processo filho terminar
}*/

/*void	execute_command(char *input)
{
	char	**args;
	int	i;

	args = ft_split(input, ' ');
	i = 0;
	if (args[i] == NULL)
	{
		free(args);
		return ;
	}
	if (!execute_internal_command(args))
		execute_external_command(args);
	while (args[i] != NULL)
	{
		free(args[i]);
		i++;
	}
	free(args);
}*/

void	execute_command(char *input, int last_exit_code)
{
	char	**tokens;
	size_t	i;

	i = 0;
	tokens = ft_split_with_quotes_and_vars(input, last_exit_code);
	while (tokens[i])
	{
		printf("Token %zu: %s\n", i, tokens[i]);
		i++;
	}
}

int	main(void)
{
	char	*input;
	int	last_exit_code;

	last_exit_code = 0;
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);  /*Ignorar Ctrl-\*/
	while (1)
	{
		input = readline("my_shell> ");
		if (input == NULL)
			break ;  //Sai ao receber EOF (Ctrl-D)
		if (input[0] != '\0')
		{
			add_history(input);  //Adiciona ao histórico
			execute_command(input, last_exit_code);
		}
		free(input);  //Liberar a memória alocada por readline()
	}
	return (0);
}
