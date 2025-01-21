/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoao <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 12:07:32 by djoao             #+#    #+#             */
/*   Updated: 2025/01/20 12:07:35 by djoao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset_expanded(char *args, t_env **env)
{
	t_env	*env_tmp;
	t_env	*prev;

	env_tmp = *env;
	prev = NULL;
	while (env_tmp)
	{
		if (env_tmp->value && ft_strcmp(env_tmp->value, args) == 0)
		{
			if (!prev)
				*env = env_tmp->next;
			else
				prev->next = env_tmp->next;
			ft_free(env_tmp->key, 1);
			ft_free(env_tmp->value, 1);
			ft_free(env_tmp, 1);
			break ;
		}
		prev = env_tmp;
		env_tmp = env_tmp->next;
	}
}

void	ft_unset_non_expanded(char *args, t_env **env)
{
	t_env	*env_tmp;
	t_env	*prev;

	env_tmp = *env;
	prev = NULL;
	while (env_tmp)
	{
		if (ft_strcmp(env_tmp->key, args) == 0)
		{
			if (!prev)
				*env = env_tmp->next;
			else
				prev->next = env_tmp->next;
			ft_free(env_tmp->key, 1);
			ft_free(env_tmp->value, 1);
			ft_free(env_tmp, 1);
			break ;
		}
		prev = env_tmp;
		env_tmp = env_tmp->next;
	}
}
