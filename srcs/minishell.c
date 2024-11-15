#include "minishell.h"
#include <sys/types.h>
#include <sys/wait.h>

void	execute_external_command(char **args)
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
}

void	execute_command(char *input)
{
	char	**args;

	args = ft_split(input, ' ');
	if (args[0] == NULL)
	{
		free(args);
		return ;
	}
	execute_external_command(args);
}


int	main(void)
{
	char	*input;

	while (1)
	{
		input = readline("mini_shell> ");
		if (input == NULL)
			break ;
		if (input[0] != '\0')
		{
			add_history(input); // Adiciona ao histórico
			execute_command(input);
		}
		free(input);  // Liberar a memória alocada por readline()
	}
	return 0;
}
