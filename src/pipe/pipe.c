#include "minishell.h"

static int	checker_pipe(char **arg)
{
	int	i;

	i = 0;
	if (matrixlen(arg) == 1)
	{
		printf("syntax error - \"%s\"\n", arg[i]);
		return (-1);
	}
	while (arg[i])
	{
		if (!ft_strcmp(arg[i], "|"))
		{
			if (*arg[i] == '|' && *(arg[i] + 1) == '|')
			{
				printf("syntax error - \"%s\"\n", arg[i]);
				return (-1);
			}
		}
		i++;
	}
	return (0);
}

static void	process_comunic(int *fd, char **process, int forks, int *i)
{
	if (forks == 0)
	{
		close(fd[0]);
		if ((process[(*i) + 1]) != NULL)
			dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		exit(start_shell(process[*i]));
	}
	if (forks > 0)
	{
		close(fd[1]);
		if (process[*i + 1] != NULL)
			dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
}

int	layer_3(char *line, char **arg)
{
	int	pid;
	int	status;

	status = 0;
	if (checker_pipe(arg))
		return (2);
	pid = fork();
	if (pid == 0)
		pip_process(line);
	if (pid > 0)
		waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}

void	pip_process(char *line)
{
	char	**process;
	int		status;
	int		i;
	int		fd[2];
	int		*forks;

	free(forks);
	status = 0;
	process = split_pip(line, '|');
	forks = malloc(sizeof(int) * matrixlen(process));
	i = 0;
	while (process[i])
	{
		pipe(fd);
		forks[i] = fork();
		process_comunic(fd, process, forks[i], &i);
		i++;
	}
	i = 0;
	while (i < matrixlen(process))
		waitpid(forks[i++], &status, 0);
	free(forks);
	ft_free_matrix(process);
	exit(WEXITSTATUS(status));
}
