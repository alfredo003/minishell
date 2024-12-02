#include "minishell.h"

static int	verifying_next_type(t_shell *shell, int i)
{
	if (is_type(shell->tokens[i], 'R') || is_type(shell->tokens[i], 'T')
		|| is_type(shell->tokens[i], 'I'))
	{
		if (!shell->tokens[i + 1].str
			|| (is_type(shell->tokens[i + 1], 'R')
				|| is_type(shell->tokens[i + 1], 'T')
				|| is_type(shell->tokens[i + 1], 'I')
				|| is_type(shell->tokens[i + 1], 'P')))
		{
			ft_putstr_fd("minishell: "
				"syntax error near unexpected token1", 2);
			if (shell->tokens[i + 1].str)
				ft_putstr_fd(shell->tokens[i + 1].str, 2);
			else
				ft_putstr_fd("newline", 2);
			ft_putstr_fd("'\n", 2);
			shell->last_return = 258;
			return (0);
		}
	}
	return (1);
}

static int	verifying_previous_type(t_shell *shell, int i)
{
	if (is_type(shell->tokens[i], 'P'))
	{
		if (!shell->tokens[i + 1].str || !shell->tokens[i - 1].str
			|| is_type(shell->tokens[i - 1], 'R')
			|| is_type(shell->tokens[i - 1], 'T')
			|| is_type(shell->tokens[i - 1], 'I')
			|| is_type(shell->tokens[i - 1], 'P'))
		{
			ft_putstr_fd("shellshell: "
				"syntax error near unexpected token ", 2);
			ft_putstr_fd(shell->tokens[i].str, 2);
			ft_putstr_fd("'\n", 2);
			shell->last_return = 258;
			return (0);
		}
	}
	return (1);
}

int	verifying_argument(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->tokens[i].str)
	{
		if (!verifying_next_type(shell, i)
			|| !verifying_previous_type(shell, i))
			return (0);
		i++;
	}
	return (1);
}
