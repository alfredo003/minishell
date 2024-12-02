#include "minishell.h"

t_env	*add_env(char *env_name, char *env_value, int equal)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(env_name);
	if (!new->key)
	{
		free(new);
		return (NULL);
	}

	new->value = ft_strdup(env_value);
	if (!new->value)
	{
		free(new->key);
		free(new);
		return (NULL);
	}
	new->equal = equal;
	new->next = NULL;

	return (new);
}

void	dup_env(char **env, t_shell *shell)
{
	t_env	*current;
	char	**my_env;
	int		i;
	int		equal;

	if (!env || !shell)
		return;
	i = 0;
	current = NULL;
	while (env[i])
	{
		my_env = ft_split(env[i], '=');
		equal = (ft_strchr(env[i], '=') != NULL);

		t_env *new_env = add_env(my_env[0], my_env[1], equal);

		if (!current)
		{
			shell->env = new_env;
			shell->env_copy = new_env;
		}
		else
		{
			current->next = new_env;
		}
		current = new_env;

		free_matrix(my_env);
		i++;
	}
}