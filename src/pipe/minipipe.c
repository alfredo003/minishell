/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minipipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoao <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 12:01:26 by djoao             #+#    #+#             */
/*   Updated: 2025/01/20 12:01:28 by djoao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minipipe(t_shell *shell)
{
	pid_t	pid;
	int		pipefd[2];

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		ft_close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		shell->pipin = pipefd[0];
		shell->no_exec = 0;
		shell->parent = 0;
		return (2);
	}
	else
	{
		ft_close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		shell->pipout = pipefd[1];
		return (1);
	}
}
