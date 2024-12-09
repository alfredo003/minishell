/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <mcaquart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:46:47 by mcaquart          #+#    #+#             */
/*   Updated: 2024/10/05 08:38:41 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	ft_is_numeric(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

static void	closing_minishell_on_error(t_mini *mini, char **matrix)
{
	printf("minishell: exit: %s: numeric argument required\n", matrix[1]);
	mini->last_return = 2;
	mini->exit_status = 1;
	return ;
}

static void	verifying_exits_arguments(t_mini *mini, char **matrix,
	int *total_of_arguments)
{
	if (*total_of_arguments >= 3)
	{
		if (ft_is_numeric(matrix[1]))
		{
			ft_putendl_fd("minishell: exit: too many arguments", 1);
			mini->last_return = 1;
			return ;
		}
		closing_minishell_on_error(mini, matrix);
		return ;
	}		
	if (*total_of_arguments == 2)
	{
		if (ft_is_numeric(matrix[1]))
		{
			mini->last_return = (ft_atoi(matrix[1]) % 256);
			mini->exit_status = 1;
			return ;
		}
		closing_minishell_on_error(mini, matrix);
		return ;
	}
	mini->exit_status = 1;
	return ;
}

void	ft_exit(char **matrix, t_mini *mini)
{
	int	total_of_arguments;

	total_of_arguments = numb_split(matrix);
	ft_putendl_fd("exit", 1);
	verifying_exits_arguments(mini, matrix, &total_of_arguments);
	return ;
}
