#include "minishell.h"

int main(void)
{
	char	*input;

	while (1)
	{
		input = readline("mini_shell> ");
		if (input[0] != '\0')
			add_history(input);// Adiciona ao histórico
		if (input == NULL)
			break ;
		free(input);  // Liberar a memória alocada por readline()
	}
	return 0;
}
