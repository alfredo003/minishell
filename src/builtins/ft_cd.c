#include "minishell.h"

static void	go_pwd(char *path, t_shell *shell)
{
	char	*current_pwd;
	char	*past_pwd;

	past_pwd = ft_pwd(shell);
	if (chdir(path))
	{
		printf("minishell: cd: %s: No such file or directory\n", path);
		shell->last_return = 1;
	}
	else
	{
		current_pwd = ft_pwd(shell);
		past_pwd = strjoin_free("OLDPWD=", past_pwd, 0, 1);
		ft_export(past_pwd, &shell->env, 0, 1);
		ft_free(past_pwd, 1);
		current_pwd = strjoin_free("PWD=", current_pwd, 0, 1);
		ft_export(current_pwd, &shell->env, 0, 1);
		ft_free(current_pwd, 1);
		shell->last_return = 0;
	}
}

static int	verifying_arguments(t_shell *shell, char **argument)
{
	int		total_of_arguments;

	total_of_arguments = numb_split(argument);
	if (total_of_arguments > 2)
	{
		ft_putendl_fd("minishell: cd: too many arguments", 1);
		shell->last_return = 1;
		return (0);
	}
	else if (!argument[1] || argument[1][0] == '~' || argument[1][0] == '-')
	{
		ft_putendl_fd("minishell: cd: <relative or absolute path>", 1);
		shell->last_return = 1;
		return (0);
	}
	return (1);
}

void	ft_cd(t_shell *shell, char **argument)
{
	if (verifying_arguments(shell, argument))
		go_pwd(argument[1], shell);
}
