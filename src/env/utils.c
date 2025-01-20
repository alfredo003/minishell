#include "minishell.h"

t_env	*add_envirenoment(char *env_name, char *env_value, int equal)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	new->key = ft_strdup(env_name);
	new->equal = equal;
	new->value = ft_strdup(env_value);
	new->next = NULL;
	return (new);
}

int	handle_unset(char **tmp, t_env **env)
{
	int	n;

	n = -1;
	while (tmp[++n])
		ft_unset(tmp[n], env);
	return (0);
}

int	ft_is_unclosed_quote(char *str, int i, char quote, t_shell *shell)
{
	if (shell->values.val1 == quote)
		return (0);
	else if (!shell->values.val1)
	{
		while (str[++i])
		{
			if (str[i] == quote)
				return (0);
		}
	}
	return (1);
}

int	ft_is_closed(char *str, int i, char quote)
{
	while (str[++i])
	{
		if (str[i] == quote)
			return (1);
	}
	return (0);
}

int	ft_can_be_add(char *str, int i, t_shell *shell)
{
	if ((str[i] == 34 || str[i] == 39))
	{
		if (str[i] == 34 && ft_is_unclosed_quote(str, i, str[i], shell))
			return (1);
		if (str[i] == 39 && ft_is_unclosed_quote(str, i, str[i], shell))
			return (1);
		if (!shell->values.val1)
			return (0);
		if ((str[i] == 34 && shell->values.val1 == 34))
			return (0);
		if ((str[i] == 39 && shell->values.val1 == 39))
			return (0);
	}
	return (1);
}

int	handle_return_value(t_shell *shell, int *n, int *len_aloc)
{
	shell->values.str1 = ft_itoa(shell->last_return);
	*len_aloc += ft_strlen(shell->values.str1);
	ft_free(shell->values.str1, 1);
	(*n)++;
	return (*len_aloc);
}

int	get_variable_length(t_shell *shell, char *input, int *n)
{
	char	*env_name;
	int		i;
	int		len_aloc;
	char	*env_value;

	i = 0;
	len_aloc = 0;
	(*n)++;
	if (input[*n] == '?')
		return (handle_return_value(shell, n, &len_aloc));
	env_name = malloc(ft_strlen(input) + 1);
	if (!env_name)
		return (0);
	while (input[*n] && (ft_isalnum(input[*n]) || input[*n] == '_'))
		env_name[i++] = input[(*n)++];
	env_name[i] = '\0';
	env_value = ft_getenv(shell->env, env_name); //Obtém o valor da variável de ambiente correspondente
	if (env_value)
		len_aloc += ft_strlen(env_value); //Calcula o seu comprimento
	ft_free(env_name, 1); //Libera a memória
	ft_free(env_value, 1);
	return (len_aloc);
}
