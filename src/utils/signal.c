#include "minishell.h"

void	handle_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	sigquit(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 1);
}