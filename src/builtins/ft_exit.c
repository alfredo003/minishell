#include "./minishell.h"

static int	ft_is_numeric(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

static void	closing_minishell_on_error(t_shell *shell, char **matrix)
{
	printf("shellshell: exit: %s: numeric argument required\n", matrix[1]);
	shell->last_return = 2;
	shell->exit_status = 1;
	return ;
}

static void	verifying_exits_arguments(t_shell *shell, char **matrix, int *total_of_arguments)
{
	if (*total_of_arguments >= 3)
	{
		if (ft_is_numeric(matrix[1]))
		{
			ft_putendl_fd("minishell: exit: too many arguments", 1);
			shell->last_return = 1;
			return ;
		}
		closing_minishell_on_error(shell, matrix);
		return ;
	}		
	if (*total_of_arguments == 2)
	{
		if (ft_is_numeric(matrix[1]))
		{
			shell->last_return = (ft_atoi(matrix[1]) % 256);
			shell->exit_status = 1;
			return ;
		}
		closing_minishell_on_error(shell, matrix);
		return ;
	}
	shell->exit_status = 1;
	return ;
}

void	ft_exit(char **matrix, t_shell *shell)
{
	int	total_of_arguments;

	total_of_arguments = numb_split(matrix);
	ft_putendl_fd("exit", 1);
	verifying_exits_arguments(shell, matrix, &total_of_arguments);
	return ;
}
