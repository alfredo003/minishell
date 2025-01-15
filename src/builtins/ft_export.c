#include "minishell.h"

static char	*get_env_values(char **args_split)
{
	int		i;
	char	*env_value;

	i = 1;
	env_value = NULL;
	while (args_split[i])
	{
		if (i == 1)
			env_value = ft_strdup(args_split[i]);
		else
			env_value = strjoin_free(env_value, args_split[i], 1, 0);
		if (args_split[i + 1])
			env_value = strjoin_free(env_value, "=", 1, 0);
		i++;
	}
	return (env_value);
}

static int	ft_modify_env(t_env *env, char *env_name, char *env_value,
	int equal)
{
	if (ft_strcmp(env->key, env_name) == 0)
	{
		if (equal == 1)
		{
			ft_free(env->value, 1);
			env->value = ft_strdup(env_value);
			env->equal = 1;
		}
		return (0);
	}
	return (1);
}

void	ft_export(char *args, t_env **env, int equal, int new_env)
{
	t_env	*env_tmp;
	char	*env_name;
	char	*env_value;
	char	**args_split;

	env_tmp = *env;
	args_split = ft_split_advanced(args, "=");
	env_name = args_split[0];
	env_value = get_env_values(args_split);
	if (ft_strchr(args, '='))
		equal = 1;
	new_env = 1;
	while (env_tmp && env_tmp->next)
	{
		new_env = ft_modify_env(env_tmp, env_name, env_value, equal);
		if (new_env == 0)
			break ;
		env_tmp = env_tmp->next;
	}
	if (new_env == 1)
		new_env = ft_modify_env(env_tmp, env_name, env_value, equal);
	if (new_env == 1)
		env_tmp->next = add_envirenoment(env_name, env_value, equal);
	ft_free_matrix(args_split);
	ft_free(env_value, 1);
}
