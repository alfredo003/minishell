#include "minishell.h"

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

void	ft_close(int fd)
{
	if (fd > 0)
		close(fd);
}

void	reset_std(t_shell *shell)
{
	dup2(shell->in, STDIN);
	dup2(shell->out, STDOUT);
}
 
void	close_fds(t_shell *shell)
{
	ft_close(shell->fdin);
	ft_close(shell->fdout);
	ft_close(shell->pipin);
	ft_close(shell->pipout);
}

void	free_env(t_env *head)
{
	t_env	*tmp;

	if (!head)
		return ;
	while (head)
	{
		tmp = head;
		head = head->next;
		if (tmp->key)
			ft_free(tmp->key, 1);
		if (tmp->value)
			ft_free(tmp->value, 1);
		ft_free(tmp, 1);
	}
}

void	ft_free_matrix(char **matrix)
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
