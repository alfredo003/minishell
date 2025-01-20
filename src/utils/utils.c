#include "minishell.h"

void	increment_shell_level(t_shell *shell)
{
	char	*str_shell_level;
	char	*tmp;
	int		shell_level;

	str_shell_level = ft_getenv(shell->env, "SHLVL");
	if (!str_shell_level)
		return ;
	else
	{
		shell_level = ft_atoi(str_shell_level);
		shell_level++;
	}
	tmp = strjoin_free("SHLVL=", ft_itoa(shell_level), 0, 1);
	ft_export(tmp, &shell->env, 0, 1);
	ft_free(tmp, 1);
	ft_free(str_shell_level, 1);
}

void	input(t_shell *shell, char *file)
{
	ft_close(shell->fdin);
	shell->fdin = open(file, O_RDONLY, S_IRWXU);
	if (shell->fdin == -1)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(file, STDERR);
		ft_putendl_fd(": No such file or directory", STDERR);
		shell->last_return = 1;
		shell->no_exec = 1;
		return ;
	}
	dup2(shell->fdin, STDIN);
}

char	*my_strndup(const char *s, size_t n)
{
	char	*dup;
	size_t	i;

	if (!s)
		return (NULL);
	dup = (char *)malloc(n + 1);
	if (!dup)
		return (NULL);
	i = -1;
	while (++i < n && s[i] != '\0')
		dup[i] = s[i];
	dup[i] = '\0';
	return (dup);
}

int	numb_split(char **matrix)
{
	int	num;

	num = 0;
	while (matrix[num])
		num++;
	return (num);
}