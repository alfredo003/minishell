/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 02:19:28 by mcaquart          #+#    #+#             */
/*   Updated: 2024/10/05 02:24:13 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*ft_pwd(t_mini *mini)
{
	char	*cwd;

	cwd = malloc(PATH_MAX);
	if (cwd == NULL)
	{
		perror("malloc failed");
		mini->last_return = 1;
		return (NULL);
	}
	if (getcwd(cwd, PATH_MAX) != NULL)
	{
		mini->last_return = 0;
		return (cwd);
	}
	else
	{
		ft_free(cwd, 1);
		mini->last_return = 1;
		return (NULL);
	}
}
