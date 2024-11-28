#include "minishell.h"

void verify_line(t_shell *shell, char *line)
{
    char *str_heredoc;
    int verify_heredoc;
    t_token *tokens;

    line = ft_strtrim(line, " ");
    if (!line || !line[0])
    {
        ft_free(line, 1);
        return ;
    }
    tokens = gettokens(shell, line);
    str_heredoc = NULL;
    verify_heredoc = verifying_heredoc(shell, tokens, &str_heredoc);
    tokens_dup(shell, tokens, str_heredoc);
	if (verify_heredoc == 258 || !verifying_argument(shell))
	{
		shell->last_return = 258;
		return ;
	}
	shell->charge = 1;
	redirect_exec(shell, 0, 0);
	free_tokens(tokens);
	ft_free(line, 1);
}

int ft_readline(t_shell *shell, char **line)
{
    *line = readline("minishell$ ");
    if(!*line)
    {
        shell->exit_status = 1;
        ft_putendl_fd("exit", 2);
        return (0);
    }

    if(**line)
        add_history(*line);
    return(1);
}