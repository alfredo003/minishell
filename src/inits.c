/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achivela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:42:30 by achivela          #+#    #+#             */
/*   Updated: 2025/01/20 16:42:36 by achivela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void	process_and_validate_line(t_shell *shell,
					char *line, t_token **tokens)
{
	char	*str_heredoc;
	int		verif_heredoc;

	str_heredoc = NULL;
	verif_heredoc = verifying_heredoc(shell, *tokens, &str_heredoc);
	dup_tokens(shell, *tokens, str_heredoc);
	if (verif_heredoc == 258 || !verifying_argument(shell))
	{
		shell->last_return = 258;
		ft_free_tokens(*tokens);
		return ;
	}
}

static void	process_line(t_shell *shell, char *line)
{
	t_token	*tokens;

	line = ft_strtrim(line, " ");
	if (!line || !line[0])
	{
		ft_free(line, 1);
		return ;
	}
	tokens = gettokens(shell, line);
	if (!tokens)
	{
		ft_free(line, 1);
		shell->last_return = 1;
		return ;
	}
	process_and_validate_line(shell, line, &tokens);
	if (shell->last_return == 258)
	{
		ft_free(line, 1);
		return ;
	}
	shell->charge = 1;
	redir_and_exec(shell, 0, 0);
	ft_free_tokens(tokens);
	ft_free(line, 1);
}

void	init_struct(t_shell *shell, char **env)
{
	reset_fds(shell);
	dup_env(env, shell, 0);
	shell->last_return = 0;
	shell->exit_status = 0;
	shell->no_exec = 0;
	shell->tokens = NULL;
	handle_signals();
}

void	init_shell(t_shell *shell)
{
	char	*line;
	int		status;

	while (shell->exit_status == 0)
	{
		shell->parent = 1;
		shell->in = dup(STDIN_FILENO);
		shell->out = dup(STDOUT_FILENO);
		shell->tokens = NULL;
		if (!ft_readline(shell, &line))
			break ;
		process_line(shell, line);
		ft_free(line, 1);
		reset_std(shell);
		close_fds(shell);
		reset_fds(shell);
		waitpid(-1, &status, 0);
		shell->no_exec = 0;
		if (shell->parent == 0)
			exit(0);
		ft_free_tokens(shell->tokens);
	}
	free_env(shell->env);
}
