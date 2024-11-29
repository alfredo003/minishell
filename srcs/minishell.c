#include "minishell.h"

static int	g_signal_flag;

void	handle_signal(int signal)
{
	g_signal_flag = signal;
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

/*void	execute_external_command(char **args)
{
	pid_t	pid;
	int	status;

	pid = fork();
	if (pid == 0)  // Processo filho
	{
		if (execve(args[0], args, NULL) == -1) // Executa o comando com o ambiente especificado
			perror("minishell");
		exit(EXIT_FAILURE); // Sai se execve falhar
	}
	else if (pid < 0)  // Erro ao criar o processo filho
		perror("minishell");
	else  // Processo pai
		wait(&status); // Espera o processo filho terminar
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
	else if (ft_strcmp(args[0], "echo") == 0)
	{
		cd_command(args);
		return (1);
	}
	else if (ft_strcmp(args[0], "unset") == 0)
	{
		cd_command(args);
		return (1);
	}
	else if (ft_strcmp(args[0], "env") == 0)
	{
		cd_command(args);
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
}*/

void	execute_command(char *input)
{
	char	**tokens;
	size_t	i;

	i = 0;
	tokens = ft_split_with_quotes_and_vars(input);
	while (tokens[i])
	{
		printf("Token %zu: %s\n", i, tokens[i]);
		i++;
	}
}

int	main(void)
{
	char	*input;

	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		input = readline("minishell> ");
		if (input == NULL)
			break ;
		if (input[0] != '\0')
		{
			add_history(input);
			execute_command(input);
		}
		free(input);
	}
	return (0);
}
