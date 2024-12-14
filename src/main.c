#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_shell	shell; 
	(void)argc;
	(void)argv;
	init_struct(&shell,env);
	init_shell(&shell);
	return (shell.last_return); 
}