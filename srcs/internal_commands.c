#include "minishell.h"

void	cd_command(char **args)
{
	if (args[1] == NULL)
		printf("my_shell: waiting for \"cd dir_name\"\n");
	else
	{
		if (chdir(args[1]) != 0)
			perror("my_shell");
	}
}

void	pwd_command(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0); // Aloca dinamicamente o buffer necessário
	if (cwd != NULL)
	{
		printf("%s\n", cwd);
		free(cwd); // Libera a memória alocada
	}
	else
		perror("my_shell");
}

void	export_command(char **args)
{
	char	**var_val;

	if (args[1] == NULL)
	{
		printf("my_shell: export VAR=VAL\n");
		return ;
	}
	var_val = ft_split(args[1], '=');
	if (!var_val || !var_val[0] || !var_val[1])
	{
		printf("my_shell: invalid use of export: %s\n", args[1]);
		if (var_val)
			free(var_val);
		return ;
	}
	if (setenv(var_val[0], var_val[1], 1) != 0)
		perror("my_shell: Error setting environment variable");
	free(var_val[0]);
	free(var_val[1]);
	free(var_val);
}
