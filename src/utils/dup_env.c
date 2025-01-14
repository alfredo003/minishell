#include "minishell.h"

t_env	*add_env(char *env_name, char *env_value, int equal)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(env_name);
	new->equal = equal;
	new->value = ft_strdup(env_value);
	new->next = NULL;
	return (new);
}

void	dup_env(char **env, t_shell *shell, int equal)
{
	t_env	*new;
	char	**current_env;
	int		i;

	i = -1;
	new = NULL;
	while (env[++i])
	{
		current_env = ft_split(env[i], '=');
		equal = 0;
		if (ft_strchr(env[i], '='))
			equal = 1;
		if (!new)
		{
			new = add_env(current_env[0], current_env[1], equal);
			shell->env = new;
			shell->env_copy = new;
		}
		else
		{
			new->next = add_env(current_env[0], current_env[1], equal);
			new = new->next;
		}
		ft_free_matrix(current_env);
	}
}
