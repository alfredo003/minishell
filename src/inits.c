#include "minishell.h"
 
static void	process_line(t_shell *shell, char *line)
{
	char	*str_heredoc;
	int		verif_heredoc;
	t_token	*tokens;

	line = ft_strtrim(line, " ");
	if (!line || !line[0])
	{
		ft_free(line, 1);
		return ;
	} 
	tokens = get_tokens(shell, line);
	str_heredoc = NULL;
	verif_heredoc = verifying_heredoc(shell, tokens, &str_heredoc);
	dup_tokens(shell, tokens, str_heredoc);
	if (verif_heredoc == 258 || !verifying_argument(shell))
	{
		shell->last_return = 258;
		return ;
	}
	shell->charge = 1;
	redir_and_exec(shell, 0, 0);
	ft_free_tokens(tokens);
	ft_free(line, 1);
}

void	init_struct(t_shell *shell)
{
	shell->fdin = -1;
	shell->fdout = -1;
	shell->pipin = -1;
	shell->pipout = -1;
	shell->pid = -1;
	shell->last_return = 0;
	shell->exit_status = 0;
	shell->no_exec = 0;
	shell->tokens = NULL;
}

void	init_shell(t_shell *shell)
{
	char	*line;
	int		status;

	while (shell->exit_status == 0)
	{ 
		shell->tokens = NULL;
		shell->parent = 1;
		shell->in = dup(STDIN_FILENO);
		shell->out = dup(STDOUT_FILENO);

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
