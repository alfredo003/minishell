#include "minishell.h"

static int	is_builtin(char *cmd)
{
	return (!ft_strcmp(cmd, "echo")
		|| !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "exit"));
}

void	ft_execute(t_shell *shell, int *pos_token)
{
	char	**cmd;

	if (shell->charge == 0)
		return ;
	cmd = cmd_tab(shell->tokens, pos_token);
	if (!cmd[0])
		return ;
	if (is_builtin(cmd[0]))
		printf("is builtin");
	else
		execute_cmd(shell, cmd);
	free_matrix(cmd);
	/*ft_close(shell->pipin);
	ft_close(shell->pipout);
	shell->pipin = -1;
	shell->pipout = -1;*/
	shell->charge = 0;
}

void	redirect_exec(t_shell *shell, int pos_token, int pipe)
{
	t_token	prev;

	prev.str = NULL;
	if (pos_token > 0)
		prev = shell->tokens[pos_token - 1];
	
	if ((!prev.str || is_type(prev, 'P')) && pipe != 1 && shell->no_exec == 0)
		ft_execute(shell, &pos_token);
}
