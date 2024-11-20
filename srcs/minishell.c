#include "minishell.h"

int	main(int ac, char **argv, char **env)
{
	(void)ac;
	(void)argv;
	t_shell	shell;

	//reset_fds(&mini);
	/*str_dup_env(env, &mini, 0);
	mini.last_return = 0;
	mini.exit_status = 0;
	mini.no_exec = 0;
	mini.tokens = NULL;
	handle_signals();*/
	main_loop(&shell);
	return (shell.last_return);
}
