#include "minishell.h"

void	handle_export(char **tmp, t_env **env, t_shell *shell)
{
	int	n;

	n = 0;
	while (tmp[++n])
	{
		if (ft_strncmp(tmp[n], "-", 1) == 0)
		{
			ft_putstr_fd("minishell: export: ", 2);
			ft_putstr_fd(": no options required\n", 2);
			shell->last_return = 1;
			return ;
		}
	}
	n = 0;
	while (tmp[++n])
		ft_export(tmp[n], env, 0, 1);
	(void)shell;
}
