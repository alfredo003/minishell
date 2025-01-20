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

static void	closing_minishell_on_error(t_shell *shell, char **args)
{
	(void)args;
	shell->last_return = 2;
	shell->exit_status = 1;
	return ;
}

static void	verifying_exits_arguments(t_shell *shell, char **args, int *total_of_arguments)
{
	if (*total_of_arguments >= 3)
	{
		if (ft_is_numeric(args[1]))
		{
			ft_putendl_fd("minishell: exit: too many arguments", 1);
			shell->last_return = 1;
			return ;
		}
		closing_minishell_on_error(shell, args);
		return ;
	}		
	if (*total_of_arguments == 2)
	{
		if (ft_is_numeric(args[1]))
		{
			shell->last_return = (ft_atoi(args[1]) % 256);
			shell->exit_status = 1;
			return ;
		}
		closing_minishell_on_error(shell, args);
		return ;
	}
	shell->exit_status = 1;
	return ;
}

void	ft_exit(char **args, t_shell *shell)
{
	int	total_of_arguments;

	total_of_arguments = numb_split(args);
	ft_putendl_fd("exit", 1);
	verifying_exits_arguments(shell, args, &total_of_arguments);
	return ;
}