/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <mcaquart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:14:58 by mcaquart          #+#    #+#             */
/*   Updated: 2024/10/25 18:34:51 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static char	*format_env_value(char *key, char *value, int equal, int type)
{
	char	*tmp;

	tmp = ft_strdup(key);
	if (value && equal == 1)
	{
		tmp = ft_strjoin2(tmp, "=", 1, 0);
		if (type == 1)
		{
			tmp = ft_strjoin2(tmp, "\"", 0, 0);
			tmp = ft_strjoin2(tmp, value, 1, 0);
			tmp = ft_strjoin2(tmp, "\"", 0, 0);
		}
		else
			tmp = ft_strjoin2(tmp, value, 1, 0);
	}
	return (tmp);
}

static int	get_env_count(t_env *env)
{
	int		count;
	t_env	*env_tmp;

	count = 0;
	env_tmp = env;
	while (env_tmp)
	{
		count++;
		env_tmp = env_tmp->next;
	}
	return (count);
}

char	**env_to_matrix(t_env *env, int i, int type)
{
	t_env	*env_tmp;
	char	**matrix;

	env_tmp = env;
	i = get_env_count(env);
	matrix = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env_tmp)
	{
		if (type == 1 && ft_strncmp(env_tmp->key, "_", 1) == 0)
		{
			env_tmp = env_tmp->next;
			continue ;
		}
		matrix[i] = format_env_value(env_tmp->key, env_tmp->value,
				env_tmp->equal, type);
		if (matrix[i])
			i++;
		env_tmp = env_tmp->next;
	}
	matrix[i] = NULL;
	return (matrix);
}
