#include "minishell.h"

void init_params(char **env, t_shell shell)
{
    dup_env(env, &shell);
	shell.last_return = 0;
    shell.exit_status = 0;
	shell.tokens = NULL;
}

void	init_shell(t_shell *shell)
{
    char    *line;
  //  int status;

    while(shell->exit_status == 0)
    {
        shell->tokens = NULL;
        if (!ft_readline(shell, &line))
            break ;
    }
}