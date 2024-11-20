#include "minishell.h"

int exec_external_command(char **token)
{
	extern	char **environ;
    pid_t pid = fork();

    if (pid == 0)
    {
		if (ft_strchr(token[0], '/'))
		{
		    if (execve(token[0], token, environ) == -1)
		    {
				perror("Command execution failed");
				exit(EXIT_FAILURE);
		    }
		}
		else
		{
		    char *path = getenv("PATH");
		    if (path == NULL)
		    {
				perror("PATH not set\n");
				exit(EXIT_FAILURE);
		    }

		    char *path_copy = ft_strdup(path);
		    if (path_copy == NULL)
		    {
				perror("Memory allocation failed");
				exit(EXIT_FAILURE);
		    }

		    char *directory;
		    char *save_ptr;
		    directory = strtok_r(path_copy, ":", &save_ptr);

		    while (directory != NULL)
		    {
				char full_path[1024];
				snprintf(full_path, sizeof(full_path), "%s/%s", directory, token[0]);

				if (access(full_path, X_OK) == 0)
				{
					execve(full_path, token, environ);
					perror("Command execution failed");
					free(path_copy);
					exit(EXIT_FAILURE);
				}
				directory = strtok_r(NULL, ":", &save_ptr);
		    }

		    printf("Command not found: %s\n", token[0]);
		    free(path_copy);
		    exit(EXIT_FAILURE);
		}
	}
	else
	{
		int status;
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		{
		    fprintf(stderr, "Child process exited with error code %d\n", WEXITSTATUS(status));
		}
	}
	return 0;
}

int	exec_internal_command(char **args)
{
	if(!ft_strncmp(args[0],"echo",5))
	{
		//cd_command(args);
		return (1);
	}
	else if (!ft_strncmp(args[0],"cd",3))
	{
		//pwd_command();
		return (1);
	}
	else if (!ft_strncmp(args[0],"export",7))
	{
		//export_command(args);
		return (1);
	}
	else if (!ft_strncmp(args[0],"unset",5))
	{
		//cd_command(args);
		return (1);
	}
	else if (!ft_strncmp(args[0],"env",4))
	{
		//cd_command(args);
		return (1);
	}
	else if (!ft_strncmp(args[0],"exit",5))
		 return (1);
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
	if (!exec_internal_command(args))
			exec_external_command(args);
	while (args[i] != NULL)
	{
		free(args[i]);
		i++;
	}
	free(args);
}