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
