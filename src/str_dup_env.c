/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_dup_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <mcaquart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:17:53 by mcaquart          #+#    #+#             */
/*   Updated: 2024/10/25 18:31:46 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	str_dup_env(char **env, t_mini *mini, int equal)
{
	t_env	*new;
	char	**my_env;
	int		i;

	i = -1;
	new = NULL;
	while (env[++i])
	{
		my_env = ft_split(env[i], '=');
		equal = 0;
		if (ft_strchr(env[i], '='))
			equal = 1;
		if (!new)
		{
			new = add_envirenoment(my_env[0], my_env[1], equal);
			mini->env = new;
			mini->env_copy = new;
		}
		else
		{
			new->next = add_envirenoment(my_env[0], my_env[1], equal);
			new = new->next;
		}
		ft_free_matrix(my_env);
	}
}
