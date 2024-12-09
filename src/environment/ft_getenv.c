/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:07:15 by mcaquart          #+#    #+#             */
/*   Updated: 2024/10/07 14:07:17 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*ft_getenv(t_env *env, char *var)
{
	t_env	*env_tmp;

	env_tmp = env;
	while (env_tmp)
	{
		if (ft_strcmp(env_tmp->key, var) == 0)
		{
			if (env_tmp->equal == 1 && env_tmp->value)
				return (ft_strdup(env_tmp->value));
			else
				return (NULL);
		}
		env_tmp = env_tmp->next;
	}
	return (NULL);
}
