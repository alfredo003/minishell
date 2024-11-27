#include "minishell.h"

void	process_separator(char *line, int *i, t_token *matrix, int *j)
{
	char	*str;

	if (is_separator(line[*i]))
	{
		str = get_separator(line, i);
		if (str && str[0])
		{
			if (*j > 0 && matrix[*j - 1].str && is_type(matrix[*j - 1], 'P'))
			{
				matrix[(*j)].str = ft_strdup("echo");
				matrix[(*j)].type = 'A';
				(*j)++;
			}
			matrix[(*j)].str = str;
			matrix[(*j)].type = type_str(str, 0);
			(*j)++;
		}
	}
}

int	ft_quote_is_closed(char *str, int i, int quote)
{
	while (str[++i])
	{
		if (str[i] == quote)
			return (1);
	}
	return (0);
}

static void	return_str_auxilary(int *single_quote, int *double_quote,
	char *ptr, int *i)
{
	if (ptr[*i] == 34)
	{
		if (*double_quote == 0)
		{
			if (ft_quote_is_closed(ptr, *i, 34))
				*double_quote ^= 1;
		}
		else
			*double_quote = 0;
	}
	else if (ptr[*i] == 39)
	{
		if (*single_quote == 0)
		{
			if (ft_quote_is_closed(ptr, *i, 39))
				*single_quote ^= 1;
		}
		else
			*single_quote = 0;
	}
}

char	*get_substr(char *ptr, int *i, int *in_quotes)
{
	char	*str;
	int		n;
	int		single_quote;
	int		double_quote;

	str = (char *)malloc(sizeof(char) * 100000);
	if (!str)
		return (NULL);
	n = 0;
	single_quote = 0;
	double_quote = 0;
	*in_quotes = 0;
	while (ptr[*i])
	{
		return_str_auxilary(&single_quote, &double_quote, ptr, i);
		if (double_quote == 1 || single_quote == 1)
			*in_quotes = 1;
		if (double_quote == 0 && single_quote == 0
			&& (is_separator(ptr[*i]) || ptr[*i] == ' '))
			break ;
		str[n++] = ptr[(*i)++];
	}
	str[n] = '\0';
	return (str);
}