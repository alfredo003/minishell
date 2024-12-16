#include "minishell.h"

t_env	*create_env_node(const char *env_var)
{
	t_env	*node;
	char	*equal_sign;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	equal_sign = ft_strchr(env_var, '=');
	if (equal_sign)
	{
		node->key = ft_strndup(env_var, equal_sign - env_var);
		node->value = ft_strdup(equal_sign + 1);
	}
	else
	{
		node->key = ft_strdup(env_var);
		node->value = NULL;
	}
	node->next = NULL;
	return (node);
}

void	free_env_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

t_env	*convert_to_env_list(char **envp)
{
	t_env	*head;
	t_env	*current;
	t_env	*new_node;
	int	i;

	i = 0;
	head = NULL;
	current = NULL;
	while (envp[i] != NULL)
	{
		new_node = create_env_node(envp[i]);
		if (!new_node)
		{
			free_env_list(head);
			return (NULL);
		}
		if (!head)
			head = new_node;
		else
			current->next = new_node;
		current = new_node;
		i++;
	}
	return (head);
}
