#include "minishell.h"

static void	verifying_option(char **argument, int *i)
{
	int	j;

	j = 0;
	if (argument[1] && (argument[1][j] == '-'))
	{
		while (argument[1][++j])
		{
			if (argument[1][j] != 'n')
			{
				*i = 1;
				break ;
			}
			else
				*i = 2;
		}
	}
}

void	ft_echo(char **argument, t_shell *shell)
{
	int	i;
	int	put_break;
	int	n;

	i = 1;
	verifying_option(argument, &i);
	put_break = i;
	while (i < numb_split(argument))
	{
		n = -1;
		while (argument[i][++n])
			ft_putchar_fd(argument[i][n], STDOUT_FILENO);
		if (argument[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (put_break == 1)
		ft_putchar_fd('\n', STDOUT_FILENO);
	shell->last_return = 0;
	shell->parent = 1;
}
