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

static t_signal	g_signal;

void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	if (g_signal.g_redisplay == 1)
		rl_redisplay();
	if (g_signal.g_temp_shell)
	{
		g_signal.g_temp_shell->last_return = 130;
	}
}

void	handle_signals(t_shell *shell)
{
	g_signal.g_temp_shell = shell;
	g_signal.g_redisplay = 1;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	sigquit(int sig)
{
	(void)sig;
}

char	*find_executable(char *cmd, t_shell *shell, int i)
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
		g_signal.g_redisplay = 0;
		waitpid(pid, &status, 0);
		g_signal.g_redisplay = 1;
		signal(SIGQUIT, old_sigquit);
	}
	shell->charge = 0;
	shell->last_return = WEXITSTATUS(status);
}
