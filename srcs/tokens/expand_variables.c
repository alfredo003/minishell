static void	handle_quotes(t_mini *mini, char *input, int *n)
{
	if (input[*n] == 34 && mini->values.val1 != 39)
	{
		if (mini->values.val1 != 34)
		{
			if (ft_is_closed(input, *n, 34))
				mini->values.val1 = 34;
		}
		else
			mini->values.val1 = 0;
	}
	else if (input[*n] == 39 && mini->values.val1 != 34)
	{
		if (mini->values.val1 != 39)
		{
			if (ft_is_closed(input, *n, 39))
				mini->values.val1 = 39;
		}
		else
			mini->values.val1 = 0;
	}
}

int	ft_get_len_aloc(t_mini *mini, char *input, int in_heredoc)
{
	int		n;
	int		len_aloc;

	n = 0;
	len_aloc = 0;
	mini->values.val1 = 0;
	while (input[n])
	{
		if (input[n] == '$' && input[n + 1] && (mini->values.val1 != 39
				|| in_heredoc))
			len_aloc += get_variable_length(mini, input, &n);
		else
		{
			if (ft_can_be_add(input, n, mini))
				len_aloc++;
			handle_quotes(mini, input, &n);
			n++;
		}
	}
	return (len_aloc);
}

void	handle_variable_expansion(t_mini *mini
		, char *expanded, int *n, int *j)
{
	char	*env_value;
	int		i;

	(*n)++;
	if (ft_strcmp(mini->values.str1, "\"$\"") == 0)
		env_value = ft_strdup("$");
	else
		env_value = get_env_value(mini, mini->values.str1, n);
	if (env_value)
	{
		i = 0;
		while (env_value[i])
			expanded[(*j)++] = env_value[i++];
	}
	ft_free(env_value, 1);
}

void	expand_variables_loop(t_mini *mini, char *input, char *expanded,
	int in_heredoc)
{
	int		n;
	int		j;

	n = 0;
	j = 0;
	mini->values.val1 = 0;
	if (!expanded)
		return ;
	while (input[n])
	{
		if (input[n] == '$' && input[n + 1]
			&& (mini->values.val1 != 39 || in_heredoc))
		{
			mini->values.str1 = input;
			handle_variable_expansion(mini, expanded, &n, &j);
		}
		else
		{
			if (ft_can_be_add(input, n, mini))
				expanded[j++] = input[n];
			handle_quotes(mini, input, &n);
			n++;
		}
	}
	expanded[j] = '\0';
}

char	*expand_variables(t_mini *mini, char *input, int in_heredoc)
{
	char	*expanded;
	int		len_aloc;

	len_aloc = ft_get_len_aloc(mini, input, in_heredoc);
	expanded = (char *)malloc(len_aloc + 100);
	expand_variables_loop(mini, input, expanded, in_heredoc);
	ft_free(input, 1);
	return (expanded);
}
