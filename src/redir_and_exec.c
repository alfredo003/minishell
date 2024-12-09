/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_and_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <mcaquart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 00:17:11 by mcaquart          #+#    #+#             */
/*   Updated: 2024/10/09 06:56:47 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
   
static int	is_builtin(char *command)
{
	return (!ft_strcmp(command, "echo")
		|| !ft_strcmp(command, "cd")
		|| !ft_strcmp(command, "pwd")
		|| !ft_strcmp(command, "env")
		|| !ft_strcmp(command, "export")
		|| !ft_strcmp(command, "unset")
		|| !ft_strcmp(command, "exit"));
}

void	ft_execute(t_mini *mini, int *pos_token)
{
	char	**cmd;

	if (mini->charge == 0)
		return ;
	cmd = cmd_tab(mini->tokens, pos_token);
	if (!cmd[0])
		return ;
	if (is_builtin(cmd[0]))
		exec_builtin(cmd, mini);
	else
		execute_cmd(mini, cmd);
	ft_free_matrix(cmd);
	ft_close(mini->pipin);
	ft_close(mini->pipout);
	mini->pipin = -1;
	mini->pipout = -1;
	mini->charge = 0;
}

void	redir_and_exec(t_mini *mini, int pos_token, int pipe)
{
	t_token	prev;

	prev.str = NULL;
	if (pos_token > 0)
		prev = mini->tokens[pos_token - 1];
	if (is_type(prev, 'R'))
		redir(mini, mini->tokens[pos_token].str, "trunc");
	else if (is_type(prev, 'T'))
		redir(mini, mini->tokens[pos_token].str, "append");
	else if (is_type(prev, 'I'))
		input(mini, mini->tokens[pos_token].str);
	else if (is_type(prev, 'P'))
		pipe = minipipe(mini);
	if (mini->tokens[(pos_token + 1)].str && pipe != 1)
		redir_and_exec(mini, (pos_token + 1), 0);
	if ((!prev.str || is_type(prev, 'P')) && pipe != 1 && mini->no_exec == 0)
		ft_execute(mini, &pos_token);
}
