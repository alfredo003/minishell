#include "minishell.h"

char	*ft_getenv(t_env *env, char *var)
{
	t_env	*env_tmp;

	env_tmp = env;
	while (env_tmp)
	{
		if (ft_strcmp(env_tmp->key, var) == 0)
		{
			if (env_tmp->equal == 1 && env_tmp->value)
				return (ft_strdup(env_tmp->value));
			else
				return (NULL);
		}
		env_tmp = env_tmp->next;
	}
	return (NULL);
}

char	*get_env_value(t_shell *shell, char *input, int *n)
{
	char	*env_name;
	char	*env_value;
	int		i;

	i = 0;
	if (input[*n] == '?')
	{
		env_value = ft_itoa(shell->last_return);
		(*n)++;
	}
	else
	{
		env_name = malloc(1000);
		if (!env_name)
			return (NULL);
		while (input[*n] && (ft_isalnum(input[*n]) || input[*n] == '_'))
			env_name[i++] = input[(*n)++];
		env_name[i] = '\0';
		env_value = ft_getenv(shell->env, env_name);
		ft_free(env_name, 1);
	}
	return (env_value);
}

int	is_separator(char c)
{
	return ((c == '|' || c == '>' || c == '<'));
}

char	type_str(char *str, int in_quotes)
{
	if (in_quotes == 1)
		return ('A');
	else if (ft_strcmp(str, ">>") == 0)
		return ('T');
	else if (ft_strcmp(str, ">") == 0)
		return ('R');
	else if (ft_strcmp(str, "<<") == 0)
		return ('H');
	else if (ft_strcmp(str, "<") == 0)
		return ('I');
	else if (ft_strcmp(str, "|") == 0)
		return ('P');
	return ('A');
}

int	is_type(t_token token, char type)
{
	if (token.str && token.str[0]
		&& token.type == type)
		return (1);
	return (0);
}

char	*get_separator(char *line, int *i)
{
	int		total_of_strings;
	char	*str;

	total_of_strings = 1;
	if (line[*i] == '>' && line[*i + 1] == '>')
		total_of_strings = 2;
	else if (line[*i] == '<' && line[*i + 1] == '<')
		total_of_strings = 2;
	str = (char *)malloc(sizeof(char) * (total_of_strings + 1));
	if (!str)
		return (NULL);
	str[0] = line[*i];
	if (total_of_strings == 2)
		str[1] = line[*i + 1];
	str[total_of_strings] = '\0';
	*i += total_of_strings;
	return (str);
}