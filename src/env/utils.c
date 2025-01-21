/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achivela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 12:10:27 by achivela          #+#    #+#             */
/*   Updated: 2025/01/20 12:10:30 by achivela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

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

int	handle_unset(char **tmp, t_env **env)
{
	int	n;

	n = 0;
	if (tmp[++n] && tmp[n + 1] == NULL)
	{
		if (ft_isalpha(tmp[n][0]) || tmp[n][0] == '_')
            ft_unset_non_expanded(tmp[n], env);
        else
            ft_unset_expanded(tmp[n], env);
	}
	return (0);
}

int	ft_is_unclosed_quote(char *str, int i, char quote, t_shell *shell)
{
	if (shell->values.val1 == quote)
		return (0);
	else if (!shell->values.val1)
	{
		while (str[++i])
		{
			if (str[i] == quote)
				return (0);
		}
	}
	return (1);
}

int	ft_is_closed(char *str, int i, char quote)
{
	while (str[++i])
	{
		if (str[i] == quote)
			return (1);
	}
	return (0);
}

int	ft_can_be_add(char *str, int i, t_shell *shell)
{
	if ((str[i] == 34 || str[i] == 39))
	{
		if (str[i] == 34 && ft_is_unclosed_quote(str, i, str[i], shell))
			return (1);
		if (str[i] == 39 && ft_is_unclosed_quote(str, i, str[i], shell))
			return (1);
		if (!shell->values.val1)
			return (0);
		if ((str[i] == 34 && shell->values.val1 == 34))
			return (0);
		if ((str[i] == 39 && shell->values.val1 == 39))
			return (0);
	}
	return (1);
}
