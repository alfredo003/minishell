#include "minishell.h"

t_command	*create_new_command(void)
{
	t_command	*new_command;

	new_command = malloc(sizeof(t_command));
	if (!new_command)
	{
		perror("malloc failed");
		return (NULL);
	}
	ft_memset(new_command, 0, sizeof(t_command));
	return (new_command);
}

void	add_argument(t_command *command, const char *arg)
{
	int	argc;

	argc = 0;
	while (command->args && command->args[argc])
		argc++;
	command->args = realloc(command->args, sizeof(char *) * (argc + 2));
	if (!command->args)
	{
		perror("realloc failed");
		return ;
	}
	command->args[argc] = ft_strdup(arg);
	command->args[argc + 1] = NULL;
}

void	add_redirection(t_command *command, int type, const char *file)
{
	t_redirection	*redir;

	redir = malloc(sizeof(t_redirection));
	if (!redir)
	{
		perror("malloc failed");
		return ;
	}
	redir->type = type;
	redir->file = ft_strdup(file);
	redir->next = command->redirections;
	command->redirections = redir;
}

t_command	*initialize_command(t_command **head, t_command *current)
{
	if (!current)
	{
		current = create_new_command();
		if (!current)
			return (NULL);
		if (!*head)
			*head = current;
	}
	return (current);
}

t_command	*handle_pipe(t_command *current)
{
	current->next = create_new_command();
	if (!current->next)
	{
		perror("malloc failed");
		return (NULL);
	}
	return (current->next);
}

int	get_redirection_type(const char *token)
{
	if (ft_strcmp(token, ">") == 0)
		return (1);
	else if (ft_strcmp(token, ">>") == 0)
		return (2);
	else if (ft_strcmp(token, "<") == 0)
		return (0);
	return (-1);
}

int	handle_redirection(t_command *current, char **tokens)
{
	int	type;

	type = get_redirection_type(*tokens);
	if (type == -1)
	{
		printf("Unknown redirection: %s\n", *tokens);
		return (-1);
	}
	tokens++;
	if (!*tokens)
	{
		printf("Syntax error: expected file after '%s'\n", *tokens - 1);
		return (-1);
	}
	add_redirection(current, type, *tokens);
	return (0);
}

t_command	*check_command_allocation(t_command *current)
{
	if (!current)
	{
		perror("Command allocation failed");
		return (NULL);
	}
	return (current);
}

t_command	*parse_tokens(char **tokens)
{
	t_command	*head;
	t_command	*current;

	head = NULL;
	current = NULL;
	while (*tokens)
	{
		current = initialize_command(&head, current);
		current = check_command_allocation(current);
		if (ft_strcmp(*tokens, "|") == 0)
		{
			current = handle_pipe(current);
			current = check_command_allocation(current);
		}
		else if (ft_strcmp(*tokens, "<") == 0 || ft_strcmp(*tokens, ">") == 0 || ft_strcmp(*tokens, ">>") == 0)
		{
			if (handle_redirection(current, tokens) == -1)
				return (NULL);
			tokens++;
		}
		else
			add_argument(current, *tokens);
		tokens++;
	}
	return (head);
}
