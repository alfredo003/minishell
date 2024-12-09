/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   increment_shell_level.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <mcaquart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:48:44 by mcaquart          #+#    #+#             */
/*   Updated: 2024/10/25 18:34:06 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	increment_shell_level(t_mini *mini)
{
	char	*str_shell_level;
	char	*tmp;
	int		shell_level;

	str_shell_level = ft_getenv(mini->env, "SHLVL");
	if (!str_shell_level)
		return ;
	else
	{
		shell_level = ft_atoi(str_shell_level);
		shell_level++;
	}
	tmp = ft_strjoin2("SHLVL=", ft_itoa(shell_level), 0, 1);
	ft_export(tmp, &mini->env, 0, 1);
	ft_free(tmp, 1);
	ft_free(str_shell_level, 1);
}
