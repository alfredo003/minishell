/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <mcaquart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 23:31:31 by mcaquart          #+#    #+#             */
/*   Updated: 2024/10/05 02:06:59 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static void	verifying_option(char **argument, int *i)
{
	int	j;

	j = 0;
	if (argument[1] && (argument[1][j] == '-'))
	{
		while (argument[1][++j])
		{
			if (argument[1][j] != 'n')
			{
				*i = 1;
				break ;
			}
			else
				*i = 2;
		}
	}
}

void	ft_echo(char **argument, t_mini *mini)
{
	int	i;
	int	put_break;
	int	n;

	i = 1;
	verifying_option(argument, &i);
	put_break = i;
	while (i < numb_split(argument))
	{
		n = -1;
		while (argument[i][++n])
			ft_putchar_fd(argument[i][n], STDOUT_FILENO);
		if (argument[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (put_break == 1)
		ft_putchar_fd('\n', STDOUT_FILENO);
	mini->last_return = 0;
	mini->parent = 1;
}
