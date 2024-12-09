/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_envirenoment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:17:11 by mcaquart          #+#    #+#             */
/*   Updated: 2024/10/07 15:17:13 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_env	*add_envirenoment(char *env_name, char *env_value, int equal)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	new->key = ft_strdup(env_name);
	new->equal = equal;
	new->value = ft_strdup(env_value);
	new->next = NULL;
	return (new);
}
