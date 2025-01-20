/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achivela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:45:15 by achivela          #+#    #+#             */
/*   Updated: 2025/01/14 17:45:18 by achivela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	init_struct(&shell, env);
	init_shell(&shell);
	return (shell.last_return);
}
