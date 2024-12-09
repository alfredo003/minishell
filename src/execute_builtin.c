/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <mcaquart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 00:31:58 by mcaquart          #+#    #+#             */
/*   Updated: 2024/10/09 07:27:43 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../header/minishell.h"

static void	calling_tiny_functions(t_mini *mini, char **args)
{
	if (ft_strcmp(args[0], "echo") == 0)
		ft_echo(args, mini);
	if (ft_strcmp(args[0], "cd") == 0)
		ft_cd(mini, args);
	if (ft_strcmp(args[0], "exit") == 0)
		ft_exit(args, mini);
	if (ft_strcmp(args[0], "unset") == 0)
		handle_unset(args, &mini->env);
}

static void	calling_env_function(t_mini *mini, char **args)
{
	if (ft_strcmp(args[0], "env") == 0)
	{
		if (args[1])
		{
			ft_putstr_fd("minishell: env: ", 2);
			ft_putendl_fd("no option or argument requireds.", 2);
			mini->last_return = 1;
		}
		else
			ft_env(mini->env, 0);
	}
}

static void	calling_pwd_function(t_mini *mini, char **args, int *result)
{
	char	*pwd;

	if (ft_strcmp(args[0], "pwd") == 0)
	{
		if (args[1] && args[1][0] == '-')
		{
			ft_putendl_fd("minishell: pwd: no option requireds.", 2);
			mini->last_return = 2;
			return ;
		}
		pwd = ft_pwd(mini);
		if (pwd)
		{
			ft_putstr_fd(pwd, 1);
			ft_putchar_fd('\n', 1);
			ft_free(pwd, 1);
			(*result) = 0;
		}
	}
}

static void	calling_export_function(t_mini *mini, char **args, int *result)
{
	if (ft_strcmp(args[0], "export") == 0)
	{
		if (args[1])
		{
			(*result) = 0;
			while (args[++(*result)])
			{
				if (!ft_strncmp(args[(*result)], "=",
						ft_strlen(args[(*result)]))
					|| !ft_strncmp(args[(*result)], "=", 1))
				{
					ft_putstr_fd("not a valid identifier\n", 2);
					mini->last_return = 1;
					return ;
				}
			}
			handle_export(args, &mini->env, mini);
		}
		else
			ft_env(mini->env, 1);
	}
}

int	exec_builtin(char **args, t_mini *mini)
{
	int	result;

	result = 0;
	calling_tiny_functions(mini, args);
	calling_env_function(mini, args);
	calling_pwd_function(mini, args, &result);
	calling_export_function(mini, args, &result);
	return (result);
}
