#include "minishell.h"

int	main(int ac, char **argv, char **env)
{
	(void)ac;
	(void)argv;
	t_shell	shell;

	dup_env(env, &shell);

	return (shell.last_return);
}
