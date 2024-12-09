/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <mcaquart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:46:37 by mcaquart          #+#    #+#             */
/*   Updated: 2024/10/25 18:33:07 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static void	go_pwd(char *path, t_mini *mini)
{
	char	*current_pwd;
	char	*past_pwd;

	past_pwd = ft_pwd(mini);
	if (chdir(path))
	{
		printf("minishell: cd: %s: No such file or directory\n", path);
		mini->last_return = 1;
	}
	else
	{
		current_pwd = ft_pwd(mini);
		past_pwd = ft_strjoin2("OLDPWD=", past_pwd, 0, 1);
		ft_export(past_pwd, &mini->env, 0, 1);
		ft_free(past_pwd, 1);
		current_pwd = ft_strjoin2("PWD=", current_pwd, 0, 1);
		ft_export(current_pwd, &mini->env, 0, 1);
		ft_free(current_pwd, 1);
		mini->last_return = 0;
	}
}

static int	verifying_arguments(t_mini *mini, char **argument)
{
	int		total_of_arguments;

	total_of_arguments = numb_split(argument);
	if (total_of_arguments > 2)
	{
		ft_putendl_fd("minishell: cd: too many arguments", 1);
		mini->last_return = 1;
		return (0);
	}
	else if (!argument[1] || argument[1][0] == '~' || argument[1][0] == '-')
	{
		ft_putendl_fd("minishell: cd: <relative or absolute path>", 1);
		mini->last_return = 1;
		return (0);
	}
	return (1);
}

void	ft_cd(t_mini *mini, char **argument)
{
	if (verifying_arguments(mini, argument))
		go_pwd(argument[1], mini);
}
