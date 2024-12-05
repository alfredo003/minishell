#include "minishell.h"

int	expand_variable(char *input, size_t *i, char *token, size_t *token_pos)
{
	size_t	start;
	size_t	var_len;
	char	*var_name;
	char	*value;

	start = *i + 1;
	var_len = 0;
	while (ft_isalnum(input[start]) || input[start] == '_')
	{
		start++;
		var_len++;
	}
	if (var_len > 0)
	{
		var_name = ft_strndup(&input[*i + 1], var_len);
		value = getenv(var_name);
		free(var_name);
		if (value)
		{
			ft_strcpy(&token[*token_pos], value);
			*token_pos += ft_strlen(value);
		}
		*i = start;
		return (1);
	}
	return (0);
}

void	expand_all_args(size_t *i, char *token, size_t *token_pos)
{
	size_t	start;
	char	*value;

	start = *i + 1;
	value = getenv("ALL_ARGUMENTS");
	if (value)
	{
		ft_strcpy(&token[*token_pos], value);
		*token_pos += ft_strlen(value);
	}
	*i = start;
}

void	expand_last_exit_code(size_t *i, char *token, size_t *token_pos, int last_exit_code)
{
	char	*exit_code_str;
	size_t	len;

	exit_code_str = ft_itoa(last_exit_code);
	len = ft_strlen(exit_code_str);
	ft_strcpy(&token[*token_pos], exit_code_str);
	*token_pos += len;
	free(exit_code_str);
	*i += 2;
}
