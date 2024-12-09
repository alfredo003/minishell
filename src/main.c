#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_shell	shell; 
	(void)argc;
	(void)argv;
	init_struct(&shell);
	str_dup_env(env, &shell, 0);
	handle_signals();
	init_shell(&shell);
	return (shell.last_return); 
}