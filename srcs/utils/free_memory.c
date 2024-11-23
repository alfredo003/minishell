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

void	ft_free(void *ptr, int free_ptr)
{
	if (!free_ptr)
		return ;
	if (ptr)
		free(ptr);
	ptr = NULL;
}
