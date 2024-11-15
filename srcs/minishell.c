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
			perror("mini_shell");
		exit(EXIT_FAILURE); // Sai se execve falhar
	}
	else if (pid < 0)  // Erro ao criar o processo filho
		perror("mini_shell");
	else  // Processo pai
		wait(&status); // Espera o processo filho terminar
}

int	execute_internal_command(char **args)
{
	if (ft_strcmp(args[0], "cd") == 0)
	{
		if (args[1] == NULL)
			ft_printf("mini_shell: waiting for \"cd dir_name\"\n");
		else
		{
			if (chdir(args[1]) != 0)
				perror("mini_shell");
		}
		return (1);
	}
	if (ft_strcmp(args[0], "exit") == 0)
		exit(0);
	return (0);
}

void	execute_command(char *input)
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
