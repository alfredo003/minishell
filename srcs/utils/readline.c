#include "minishell.h"

void verify_line(t_shell *shell, char *line)
{
    char *str_heredoc;
    int verify_heredoc;
    t_token *token;

    line = ft_strtrim(line, " ");
    if (!line || !line[0])
    {
        ft_free(line, 1);
        return ;
    }
    tokens = gettokens(shell, line);
    str_heredoc = NULL;
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