#include "minishell.h"

static void	handle_quotes(t_shell *shell, char *input, int *n)
{
	if (input[*n] == 34 && shell->values.val1 != 39)
	{
		if (shell->values.val1 != 34)
		{
			if (ft_is_closed(input, *n, 34))
				shell->values.val1 = 34;
		}
		else
			shell->values.val1 = 0;
	}
	else if (input[*n] == 39 && shell->values.val1 != 34)
	{
		if (shell->values.val1 != 39)
		{
			if (ft_is_closed(input, *n, 39))
				shell->values.val1 = 39;
		}
		else
			shell->values.val1 = 0;
	}
}

int	ft_get_len_aloc(t_shell *shell, char *input, int in_heredoc)
{
	int		n;
	int		len_aloc;

	n = 0;
	len_aloc = 0;
	shell->values.val1 = 0;
	while (input[n])
	{
		if (input[n] == '$' && input[n + 1] && (shell->values.val1 != 39
				|| in_heredoc))
			len_aloc += get_variable_length(shell, input, &n);
		else
		{
			if (ft_can_be_add(input, n, shell))
				len_aloc++;
			handle_quotes(shell, input, &n);
			n++;
		}
	}
	return (len_aloc);
}

void	handle_variable_expansion(t_shell *shell
		, char *expanded, int *n, int *j)
{
	char	*env_value;
	int		i;

	(*n)++;
	if (ft_strcmp(shell->values.str1, "\"$\"") == 0)
		env_value = ft_strdup("$");
	else
		env_value = get_env_value(shell, shell->values.str1, n);
	if (env_value)
	{
		i = 0;
		while (env_value[i])
			expanded[(*j)++] = env_value[i++];
	}
	ft_free(env_value, 1);
}

void expand_variables_loop(t_shell *shell, char *input, char *expanded, int in_heredoc)
{
    int n = 0;
    int j = 0;

    shell->values.val1 = 0;

    if (!expanded) // Segurança extra, embora não devesse acontecer
        return;

    while (input[n])
    {
        if (input[n] == '$' && input[n + 1] && (shell->values.val1 != 39 || in_heredoc))
        {
            shell->values.str1 = input; // Configura a variável de ambiente
            handle_variable_expansion(shell, expanded, &n, &j);
        }
        else
        {
            if (ft_can_be_add(input, n, shell))
                expanded[j++] = input[n]; // Copia o caractere atual
            handle_quotes(shell, input, &n); // Lida com aspas
            n++;
        }
    }
    expanded[j] = '\0'; // Finaliza a string com '\0'
}

char *expand_variables(t_shell *shell, char *input, int in_heredoc)
{
    char *expanded;
    int len_aloc;

    // Calcula o tamanho necessário para a string expandida
    len_aloc = ft_get_len_aloc(shell, input, in_heredoc);

    // Aloca espaço para a string expandida (+1 para o '\0')
    expanded = (char *)malloc(len_aloc + 1);
    if (!expanded)
    {
        ft_free(input, 1); // Libera o input caso a alocação falhe
        return (NULL);
    }

    // Expande as variáveis e constrói a string
    expand_variables_loop(shell, input, expanded, in_heredoc);

    // Libera a entrada original
    ft_free(input, 1);

    return (expanded);
}
