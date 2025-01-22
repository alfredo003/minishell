/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoao <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 12:57:17 by djoao             #+#    #+#             */
/*   Updated: 2025/01/20 12:57:19 by djoao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*error_message(char *path, t_shell *shell)
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

void	redir(t_shell *shell, char *file, char *type)
{
	ft_close(shell->fdout);
	if (ft_strcmp(type, "trunc") == 0)
		shell->fdout = open(file, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	else
		shell->fdout = open(file, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	if (shell->fdout == -1)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(file, STDERR);
		ft_putendl_fd(": No such file or directory", STDERR);
		shell->last_return = 1;
		shell->no_exec = 1;
		return ;
	}
	dup2(shell->fdout, STDOUT);
}
