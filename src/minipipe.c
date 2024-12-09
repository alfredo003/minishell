/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minipipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:47:00 by mcaquart          #+#    #+#             */
/*   Updated: 2024/10/07 14:47:02 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	minipipe(t_mini *mini)
{
	pid_t	pid;
	int		pipefd[2];

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		ft_close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		mini->pipin = pipefd[0];
		mini->no_exec = 0;
		mini->parent = 0;
		return (2);
	}
	else
	{
		ft_close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		mini->pipout = pipefd[1];
		return (1);
	}
}
