/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoao <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:28:05 by djoao             #+#    #+#             */
/*   Updated: 2025/01/20 13:28:08 by djoao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_readline(t_shell *shell, char **line)
{
	*line = readline("minishell$ ");
	if (!*line)
	{
		shell->exit_status = 1;
		ft_putendl_fd("exit", 2);
		return (0);
	}
	if (**line)
		add_history(*line);
	return (1);
}
