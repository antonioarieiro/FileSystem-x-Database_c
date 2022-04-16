#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "escopo.h"

int main(void)
{
    int op;

    do
    {
        puts("\n---------- MENU ----------");
        printf("|\t\t\t |");
        puts("\n| 0 - Sair\t\t |\n| 1 - Cadastrar\t\t |\n| 2 - Remover Registro\t\t |\n| 3 - Alterar Registro\t |\t\t\n| 4 - Imprimir\t |");
        printf("|\t\t\t |\n");
        puts("--------------------------");
        scanf("%d", &op);

        switch (op)
        {
        case 0:
            puts("Saindo...\n");
            break;
        case 1:
            cadastrar();
            break;
        case 2:
         remover();
            break;
        case 3:
            altera();
            break;
        case 4:
          imprimiVetor();
            break;
        default:
            puts("Opção Invalida.\n\n");
        }
    } while (op != 0);

    return 0;
}
