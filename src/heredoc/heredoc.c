/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <mcaquart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:05:38 by mcaquart          #+#    #+#             */
/*   Updated: 2024/10/09 05:39:08 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static char	*get_trimmed_line(t_mini *mini, char *delimiter)
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
	tmp = expand_variables(mini, tmp, 1);
	ft_free(line, 1);
	return (tmp);
}

char	*heredoc(t_mini *mini, char *delimiter)
{
	char	*tmp;
	char	*str;

	str = ft_strdup("");
	while (1)
	{
		tmp = get_trimmed_line(mini, delimiter);
		if (tmp == NULL)
			return (NULL);
		if (ft_strcmp(tmp, delimiter) == 0)
		{
			ft_free(tmp, 1);
			break ;
		}
		else
		{
			str = ft_strjoin2(str, tmp, 1, 1);
			str = ft_strjoin2(str, "\n", 1, 0);
		}
	}
	return (str);
}
