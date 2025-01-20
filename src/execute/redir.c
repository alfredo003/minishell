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
