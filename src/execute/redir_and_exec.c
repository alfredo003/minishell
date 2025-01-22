/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_and_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoao <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 12:57:46 by djoao             #+#    #+#             */
/*   Updated: 2025/01/20 12:57:48 by djoao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**cmd_tab(t_token *tokens, int *pos_token)
{
	char	**tab;
	int		i;
	int		j;

	if (!tokens)
		return (NULL);
	i = *pos_token;
	j = 0;
	while (tokens[i].str && is_type(tokens[i], 'A'))
	{
		i++;
		j++;
	}
	tab = malloc(sizeof(char *) * (j + 1));
	if (!tab)
		return (NULL);
	ft_memset(tab, 0, sizeof(char *) * (j + 1));
	i = 0;
	while (tokens[*pos_token].str && is_type(tokens[*pos_token], 'A'))
	{
		tab[i++] = ft_strdup(tokens[*pos_token].str);
		*pos_token += 1;
	}
	tab[i] = NULL;
	return (tab);
}

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

void	ft_execute(t_shell *shell, int *pos_token)
{
	char	**cmd;

	if (shell->charge == 0)
		return ;
	cmd = cmd_tab(shell->tokens, pos_token);
	if (!cmd[0])
		return ;
	if (ft_strlen(cmd[0]) == 0)
	{
		ft_putstr_fd("minishell: command '' not found\n", STDERR);
		shell->no_exec = 1;
		shell->last_return = 127;
		ft_free_matrix(cmd);
		return ;
	}
	if (is_builtin(cmd[0]))
		exec_builtin(cmd, shell);
	else
		execute_cmd(shell, cmd);
	ft_free_matrix(cmd);
	ft_close(shell->pipin);
	ft_close(shell->pipout);
	shell->pipin = -1;
	shell->pipout = -1;
	shell->charge = 0;
}

void	redir_and_exec(t_shell *shell, int pos_token, int pipe)
{
	t_token	prev;

	prev.str = NULL;
	if (pos_token > 0)
		prev = shell->tokens[pos_token - 1];
	if (is_type(prev, 'R'))
		redir(shell, shell->tokens[pos_token].str, "trunc");
	else if (is_type(prev, 'T'))
		redir(shell, shell->tokens[pos_token].str, "append");
	else if (is_type(prev, 'I'))
		input(shell, shell->tokens[pos_token].str);
	else if (is_type(prev, 'P'))
		pipe = minipipe(shell);
	if (shell->tokens[(pos_token + 1)].str && pipe != 1)
		redir_and_exec(shell, (pos_token + 1), 0);
	if ((!prev.str || is_type(prev, 'P')) && pipe != 1 && shell->no_exec == 0)
		ft_execute(shell, &pos_token);
}
