#include "minishell.h"

static	int g_signal_flag;

void	handle_signal(int signal)
{
	g_signal_flag = signal;
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	initialize_shell(t_shell *shell, char **envp)
{
	shell->env = convert_to_env_list(envp);
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	shell->exit_status = 0;
}

void print_commands(t_command *commands) {
    t_command *current = commands;

    while (current) {
        // Imprime os argumentos
        printf("Command:\n");
        if (current->args) {
            for (int i = 0; current->args[i]; i++) {
                printf("  Arg[%d]: %s\n", i, current->args[i]);
            }
        } else {
            printf("  No arguments\n");
        }

        // Imprime os redirecionamentos
        printf("  Redirections:\n");
        t_redirection *redir = current->redirections;
        while (redir) {
            printf("    Type: %d, File: %s\n", redir->type, redir->file);
            redir = redir->next;
        }

        // Move para o próximo comando
        current = current->next;
        printf("\n");
    }
}

void free_commands(t_command *commands) {
    t_command *current = commands;
    t_command *next_command;

    while (current) {
        next_command = current->next;

        // Libera os argumentos
        if (current->args) {
            for (int i = 0; current->args[i]; i++) {
                free(current->args[i]);
            }
            free(current->args);
        }

        // Libera os redirecionamentos
        t_redirection *redir = current->redirections;
        while (redir) {
            t_redirection *next_redir = redir->next;
            free(redir->file);
            free(redir);
            redir = next_redir;
        }

        // Libera o comando atual
        free(current);

        // Avança para o próximo comando
        current = next_command;
    }
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	t_command	*commands;
	char	*input;
	char	**tokens;

	(void)argc;
	(void)argv;
	initialize_shell(&shell, envp);
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
			break;
		if (*input)
			add_history(input);
		tokens = tokenize_input(input);
		commands = parse_tokens(tokens);
		//execute_commands(commands, &shell);
		//free_commands(commands);
		for (int i = 0; tokens[i] != NULL; i++)
		{
			printf("Token[%d]: %s\n", i, tokens[i]);
			free(tokens[i]);
		}
		print_commands(commands);
		free_commands(commands);
		free(tokens);
		free(input);
	}
	free_env_list(shell.env);
	//cleanup_shell(&shell);
	return (0);
}
