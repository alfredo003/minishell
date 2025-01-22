/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoao <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 12:56:58 by djoao             #+#    #+#             */
/*   Updated: 2025/01/20 12:57:03 by djoao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	g_redisplay = 1;

void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	if (g_redisplay == 1)
		rl_redisplay();
}

static char	*error_message(char *path, t_shell *shell)
{
	DIR	*folder;
	int	fd;

	fd = open(path, O_WRONLY);
	folder = opendir(path);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(path, 2);
	if (ft_strchr(path, '/') == NULL)
		ft_putendl_fd(": command not found", 2);
	else if (fd == -1 && folder == NULL)
		ft_putendl_fd(": No such file or directory", 2);
	else if (fd == -1 && folder != NULL)
		ft_putendl_fd(": is a directory", 2);
	else if (fd != -1 && folder == NULL)
		ft_putendl_fd(": Permission denied", 2);
	if (ft_strchr(path, '/') == NULL || (fd == -1 && folder == NULL))
		shell->last_return = 127;
	else
		shell->last_return = 126;
	if (folder)
		closedir(folder);
	ft_close(fd);
	return (NULL);
}

static char	*find_executable(char *cmd, t_shell *shell, int i)
{
	struct stat	buffer;
	char		**path_dirs;
	char		*full_path;

	if (cmd[0] == '/' || cmd[0] == '.')
		if (stat(cmd, &buffer) == 0)
			return (ft_strdup(cmd));
	shell->values.str1 = ft_getenv(shell->env, "PATH");
	if (!shell->values.str1)
		return (NULL);
	path_dirs = ft_split(shell->values.str1, ':');
	ft_free(shell->values.str1, 1);
	while (path_dirs[++i])
	{
		full_path = strjoin_free(ft_strjoin(path_dirs[i], "/"), cmd, 1, 0);
		if (full_path && stat(full_path, &buffer) == 0)
		{
			ft_free_matrix(path_dirs);
			return (full_path);
		}
		ft_free(full_path, 1);
	}
	ft_free_matrix(path_dirs);
	return (NULL);
}

void	handle_child(t_shell *shell, char **cmd)
{
	char	*cmd_path;
	char	**env_matrix;

	cmd_path = find_executable(cmd[0], shell, -1);
	if (cmd_path)
	{
		env_matrix = env_to_matrix(shell->env, 0, 0);
		execve(cmd_path, cmd, env_matrix);
		ft_free_matrix(env_matrix);
	}
	else
	{
		error_message(cmd[0], shell);
		shell->parent = 0;
	}
	ft_free(cmd_path, 1);
}

void	execute_cmd(t_shell *shell, char **cmd)
{
	int		status;
	sig_t	old_sigquit;
	pid_t	pid;

	status = 0;
	if (shell->charge == 0)
		return ;
	old_sigquit = signal(SIGQUIT, sigquit);
	pid = fork();
	if (pid == 0)
	{
		handle_child(shell, cmd);
		exit(shell->last_return);
	}
	else
	{
		g_redisplay = 0;
		waitpid(pid, &status, 0);
		g_redisplay = 1;
		signal(SIGQUIT, old_sigquit);
	}
	shell->charge = 0;
	shell->last_return = WEXITSTATUS(status);
}
