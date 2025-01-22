/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoao <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 12:08:37 by djoao             #+#    #+#             */
/*   Updated: 2025/01/20 12:08:40 by djoao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void verifying_option(char **argument, int *i)
{
    int j;

    while (argument[*i] && argument[*i][0] == '-')
    {
        j = 1;
        while (argument[*i][j] == 'n')
            j++;
        if (argument[*i][j] == '\0')
            (*i)++;
        else
            break;
    }
}

void	verify_break(int i, int *put_break)
{
	if (i == 1)
		*put_break = 1;
	else
		*put_break = 0;
}

void ft_echo(char **argument, t_shell *shell)
{
    int i;
    int put_break;

    i = 1;
    put_break = 1;

    verifying_option(argument, &i);
	verify_break(i,&put_break);
    while (argument[i])
    {
        ft_putstr_fd(argument[i], STDOUT_FILENO);
        if (argument[i + 1])
            ft_putchar_fd(' ', STDOUT_FILENO);
        i++;
    }
    if (put_break == 1)
        ft_putchar_fd('\n', STDOUT_FILENO);
    shell->last_return = 0;
    shell->parent = 1;
}

