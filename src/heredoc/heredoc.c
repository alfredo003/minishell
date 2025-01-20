#include "minishell.h"

static char	*get_trimmed_line(t_shell *shell, char *delimiter)
{
	char	*line;
	char	*tmp;

	line = readline("> ");
	if (line == NULL)
	{
		ft_putstr_fd("minishell: warning: here-document"
			"delimited by end-of-file (wanted `", 2);
		ft_putstr_fd(delimiter, 2);
		ft_putstr_fd("')\n", 2);
		exit(1);
	}
	tmp = ft_strtrim(line, " ");
	tmp = expand_variables(shell, tmp, 1);
	ft_free(line, 1);
	return (tmp);
}

char	*heredoc(t_shell *shell, char *delimiter)
{
	char	*tmp;
	char	*str;

	str = ft_strdup("");
	while (1)
	{
		tmp = get_trimmed_line(shell, delimiter);
		if (tmp == NULL)
			return (NULL);
		if (ft_strcmp(tmp, delimiter) == 0)
		{
			ft_free(tmp, 1);
			break ;
		}
		else
		{
			str = strjoin_free(str, tmp, 1, 1);
			str = strjoin_free(str, "\n", 1, 0);
		}
	}
	return (str);
}
