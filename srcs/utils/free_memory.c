#include "minishell.h"

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return ;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
	matrix = NULL;
}

void	free_tokens(t_token *tokens)
{
	int	i;

	if (tokens == NULL)
		return ;
	i = 0;
	while (tokens[i].str)
	{
		ft_free(tokens[i].str, 1);
		i++;
	}
	ft_free(tokens, 1);
}

void	ft_free(void *ptr, int free_ptr)
{
	if (!free_ptr)
		return ;
	if (ptr)
		free(ptr);
	ptr = NULL;
}
