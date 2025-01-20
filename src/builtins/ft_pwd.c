/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoao <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 12:07:16 by djoao             #+#    #+#             */
/*   Updated: 2025/01/20 12:07:19 by djoao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_pwd(t_shell *shell)
{
	char	*cwd;

	cwd = malloc(PATH_MAX);
	if (cwd == NULL)
	{
		perror("malloc failed");
		shell->last_return = 1;
		return (NULL);
	}
	if (getcwd(cwd, PATH_MAX) != NULL)
	{
		shell->last_return = 0;
		return (cwd);
	}
	else
	{
		ft_free(cwd, 1);
		shell->last_return = 1;
		return (NULL);
	}
}
