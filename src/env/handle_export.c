#include "minishell.h"

void	handle_export(char **tmp, t_env **env, t_shell *shell)
{
	int	n;

	n = 0;
	while (tmp[++n]) //Começa do segundo argumento (tmp[1]) porque o primeiro é o próprio comando export.
	{
		if (ft_strncmp(tmp[n], "-", 1) == 0) //Verifica se algum argumento começa com o caractere -
		{
			ft_putstr_fd("minishell: export: ", 2); //Exibe o erro "minishell: export: no options required" no erro padrão (FD 2).
			ft_putstr_fd(": no options required\n", 2);
			shell->last_return = 1; //Define shell->last_return como 1 (indicando erro)
			return ; //Interrompe a execução da função.
		}
	}
	n = 0;
	while (tmp[++n]) //Percorre novamente os argumentos (excluindo o comando export).
		ft_export(tmp[n], env, 0, 1); //Para cada argumento válido, chama a função ft_export
	(void)shell;
}
