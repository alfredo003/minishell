#include "minishell.h"

int main(void)
{
	char	*input;

	while (1)
	{
		input = readline("minishell> ");
		if (input[0] != '\0')
			add_history(input);
		if (input == NULL)
			break ;
		free(input);
	}
	return 0;
}
