#include "minishell.h"

int	main(void)
{
	char	*input;

	//signal(SIGINT, handle_signal);
	//signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		input = readline("minishell$ ");
		if (input == NULL)
			break ;
		if (input[0] != '\0')
		{
			add_history(input);
			execute_command(input); 
		}
		free(input);
	}
	return EXIT_SUCCESS;
}
