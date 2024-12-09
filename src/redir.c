/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 17:20:02 by mcaquart          #+#    #+#             */
/*   Updated: 2024/10/05 17:20:18 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	redir(t_mini *mini, char *file, char *type)
{
	ft_close(mini->fdout);
	if (ft_strcmp(type, "trunc") == 0)
		mini->fdout = open(file, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	else
		mini->fdout = open(file, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	if (mini->fdout == -1)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(file, STDERR);
		ft_putendl_fd(": No such file or directory", STDERR);
		mini->last_return = 1;
		mini->no_exec = 1;
		return ;
	}
	dup2(mini->fdout, STDOUT);
}
