#include "minishell.h"

char	*ft_pwd(t_shell *shell)
{
	char	*cwd;

	cwd = malloc(PATH_MAX);
	if (cwd == NULL)
	{
		perror("malloc failed");
		shell->last_return = 1;
		return (NULL);
	}
	if (getcwd(cwd, PATH_MAX) != NULL)
	{
		shell->last_return = 0;
		return (cwd);
	}
	else
	{
		ft_free(cwd, 1);
		shell->last_return = 1;
		return (NULL);
	}
}
