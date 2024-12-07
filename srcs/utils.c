#include "minishell.h"

char *ft_strcpy(char *dest, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strndup(const char *s, size_t n)
{
	size_t	len;
	char	*dup;
	size_t	i;

	len = 0;
	i = 0;
	while (s[len] && len < n)
		len++;
	dup = (char *)malloc(len + 1);
	if (!dup)
		return NULL;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int	process_quote(char **str)
{
	char	quote;

	quote = **str;
	(*str)++;
	while (**str && **str != quote)
		(*str)++;
	if (!**str)
	{
		printf("Error: Unterminated quote\n");
		return (-1);
	}
	(*str)++;
	return (1);
}

int	size_token(char *str)
{
	int	size;

	size = 0;
	while (*str)
	{
		while (*str == ' ')
			str++;
		if (*str == '"' || *str == '\'')
		{
			if (process_quote(&str) == -1)
				return (-1);
			size++;
		}
		else if (*str && *str != ' ')
		{
			size++;
			while (*str && *str != ' ')
				str++;
		}
	}
	return (size);
}

t_split_state	initialize_split_state(char *input)
{
	t_split_state	state;

	state.i = 0;
	state.token_pos = 0;
	state.token_count = 0;
	state.in_single_quotes = 0;
	state.in_double_quotes = 0;
	state.tokens = malloc((size_token(input) + 1) * sizeof(char *));
	if (!state.tokens)
	{
		perror("Allocation Error\n");
		exit(EXIT_FAILURE);
	}
	state.token = malloc(ft_strlen(input) + 1);
	if (!state.token)
	{
		free(state.tokens);
		perror("Allocation Error\n");
		exit(EXIT_FAILURE);
	}
	return (state);
}
