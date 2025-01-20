#include "minishell.h"

void verifying_option(char **argument, int *i) {
    // Loop para verificar se o argumento começa com '-n'
    while (argument[*i] && argument[*i][0] == '-') {
        int j = 1;  // Começa após o '-'

        // Verifica se o argumento consiste apenas de 'n's após o '-'
        while (argument[*i][j] == 'n') {
            j++;
        }

        // Se o argumento for apenas uma sequência de '-n's, move para o próximo argumento
        if (argument[*i][j] == '\0') {
            (*i)++;
        } else {
            // Se o argumento contém outros caracteres além de 'n', sai do loop
            break;
        }
    }
}


void ft_echo(char **argument, t_shell *shell) {
    int i = 1;  // Começa no segundo argumento, já que o primeiro é o comando 'echo'
    int put_break = 1;  // Assume que deve imprimir nova linha por padrão
    int n;

    // Chama a função para verificar e ajustar o índice i para o próximo argumento válido
    verifying_option(argument, &i);

    // Se o índice i foi alterado, significa que foi encontrado um '-n' e não deve imprimir nova linha
    put_break = (i == 1) ? 1 : 0;

    // Loop para imprimir os argumentos a partir do índice correto
    while (i < numb_split(argument)) {
        n = 0;
        while (argument[i][n]) {
            ft_putchar_fd(argument[i][n], STDOUT_FILENO);  // Imprime cada caractere
            n++;
        }
        if (argument[i + 1]) {  // Se houver mais argumentos, imprime um espaço
            ft_putchar_fd(' ', STDOUT_FILENO);
        }
        i++;
    }

    // Se put_break for 1, imprime a nova linha no final
    if (put_break == 1) {
        ft_putchar_fd('\n', STDOUT_FILENO);
    }

    // Atualiza o estado do shell
    shell->last_return = 0;
    shell->parent = 1;
}
