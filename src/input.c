/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:41:51 by mcaquart          #+#    #+#             */
/*   Updated: 2024/10/07 15:41:53 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	input(t_mini *mini, char *file)
{
	ft_close(mini->fdin);
	mini->fdin = open(file, O_RDONLY, S_IRWXU);
	if (mini->fdin == -1)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(file, STDERR);
		ft_putendl_fd(": No such file or directory", STDERR);
		mini->last_return = 1;
		mini->no_exec = 1;
		return ;
	}
	dup2(mini->fdin, STDIN);
}
