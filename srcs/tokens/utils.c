#include "minishell.h"

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