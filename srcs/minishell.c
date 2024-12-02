#include "minishell.h"

int	main(int ac, char **argv, char **env)
{
	(void)ac;
	(void)argv;
	t_shell	shell;

	init_params(env, shell);
	init_shell(&shell);
	return (shell.last_return);
}
