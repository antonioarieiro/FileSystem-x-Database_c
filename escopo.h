#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define ESCOPO_H

/* ---------------------------------------------------------
    Definicao das estruturas:
 ---------------------------------------------------------*/

typedef struct disciplina      /* Estrutura de dados para cadastrar disciplina: */
{                              
    char nomeDisciplina[40];   
    char codigoDisciplina[15]; 
    int chDisciplina;
} tDisciplina;

tDisciplina Disciplina[100];

typedef struct turma           /* Estrutura de dados para cadastrar turma: */
{                              
    int idTurma;
    char turnoTurma[15]; 
    char docenteTurma[15];
    char codigoDisciplina[15];
} tTurma;

tTurma Turma[100];

typedef struct historico /* Estrutura de dados para cadastrar historico de aluno: */
{                        
    int numeroAluno;
    float notaFinal;
    int idTurma;
} tHistorico;

tHistorico Historico[100];
int tam = 100;
int quantDis = 0;
int quantTurma = 0;
int quantHist = 0;

// Função para salvar os dados inseridos no nosso banco simulado 
void salvarArq()
{
    FILE *arq = fopen("Database.dat", "a+"); //abre o arqv database.dat
    int i, j, k;

    if (arq) //verifica se conseguiu abrir o arquivo para salvar os dados
    {
        fprintf(arq, "     DATA BASE UNIVERSITY          \n");
        fprintf(arq, "\nN° R|         DISCIPLINA                  |\n\t|--------------------------------------");
        for (i = 1; i <= quantDis; i++)
        {
            fprintf(arq, "\n\t|\tNome: %s\n", Disciplina[i].nomeDisciplina);
            fprintf(arq, " %d\t|\tCodigo: %s\n", i, Disciplina[i].codigoDisciplina);
            fprintf(arq, "\t|\tCarga Horaria: %d\n", Disciplina[i].chDisciplina);
            fprintf(arq, "\t|--------------------------------------");
        }
        fprintf(arq, "\n\n\nN° R|         TURMA                       |\n\t|--------------------------------------");
        for (j = 1; j <= quantTurma; j++)
        {
            fprintf(arq, "\n\t|\tID da Turma: %d\n", Turma[j].idTurma);
            fprintf(arq, "%d\t|\tTurno: %s\n\t|\tDocente: %s\n", j, Turma[j].turnoTurma, Turma[j].docenteTurma);
            fprintf(arq, "\t|\tCodigo da Turma: %s\n", Turma[j].codigoDisciplina);
            fprintf(arq, "\t|--------------------------------------");
        }
        fprintf(arq, "\n\n\nN° R|         HISTORICO                   |\n\t|--------------------------------------");
        for (k = 1; k <= quantHist; k++)
        {

            fprintf(arq, "\n\t|\tNumero do aluno: %d\n", Historico[k].numeroAluno);
            fprintf(arq, "%d\t|\tID da Turma: %d\n\t|\tNota Final: %.2f\n", k, Historico[k].idTurma, Historico[k].notaFinal);
            fprintf(arq, "\t|--------------------------------------");
        }
        puts("\nSucess: informacoes novas foram salvas em Database.\n");
    }
    else
        printf("ERROR: nao foi possivel abrir o arquivo.\n\n");

    fclose(arq); //fecha o arquivo
}

// Função para cadastrar novos dados
int cadastrar()
{
    int op;
    int len;

    puts("\n------ CADASTRO -----");
    printf("|\t\t\t |");
    printf("\n| Oque deseja cadastrar:\t |\n|\t\t\t |\n| 1 - Nova Disciplinma\t |\n| 2 -Nova Turma\t\t |\n| 3 -Novo Historico\t\t |\n| 0 - Sair\t\t |\n");
    puts("--------------------------");
    scanf("%d", &op);

    switch (op)
    {

    case 1:

        if (quantDis < tam)
        {
            fflush(stdin);

            tDisciplina Dis;
            puts("----- CADASTRO DE NOVA DISCIPLINA -----\n\nPress enter");
            scanf("%*c");
            printf("Nome da Disciplina: ");
            fgets(Dis.nomeDisciplina, 40, stdin);
            len = strlen(Dis.nomeDisciplina);
            if (Dis.nomeDisciplina[len - 1] == '\n')
                Dis.nomeDisciplina[len - 1] = '\0';
            printf("Digite o Codigo da Disciplina: ");
            scanf("%s", &Dis.codigoDisciplina);
            printf("Digite a carga horaria: ");
            scanf("%d", &Dis.chDisciplina);
            quantDis++;
            Disciplina[quantDis] = Dis;
            puts("--------------------------");
            salvarArq();
            return 1;
        }
        else
        {
            printf("ERROR: Vetor Cheio...\n");
            return 0;
        }
        break;

    case 2:

        if (quantTurma < tam)
        {
            puts("----- CADASTRO DE NOVA TURMA -----");
            tTurma Tur;
            puts("");
            scanf("%*c");
            printf("ID da Turma: ");
            scanf("%d", &Tur.idTurma);
            printf("Codigo da Disciplina: ");
            scanf("%s", &Tur.codigoDisciplina);
            printf("Professor Responsavel: ");
            scanf("%s", Tur.docenteTurma);
            printf("Turno da turma: ");
            scanf("%s", Tur.turnoTurma);
            quantTurma++;
            Turma[quantTurma] = Tur;
            puts("--------------------------");
            salvarArq();
            return 1;
        }
        else
        {
            printf("ERROR: Capacidade maxima de armazenamento atingido...\n");
            return 0;
        }
        break;

    case 3:

        if (quantHist < tam)
        {
            puts("----- CADASTRAR NOVO HISTORICO -----");
            tHistorico His;
            scanf("%*c");
            puts("");
            printf("Numero do estudante: ");
            scanf("%d", &His.numeroAluno);
            printf("ID da Turma: ");
            scanf("%d", &His.idTurma);
            printf("Nota final: ");
            scanf("%f", &His.notaFinal);
            quantHist++;
            Historico[quantHist] = His;
            puts("--------------------------");
            salvarArq();
            return 1;
        }
        else
        {
            printf("ERROR: Capacidade maxima de armazenamento atingido...\n");
            return 0;
        }
        break;
    case 0:
        puts("Voltando para o MENU");
        break;
    default:
        puts("Opcao invalida");
    }
}

// Função para alterar os dados do arquivo Database.dat
int altera()
{
    int op;

    puts("\n------ ALTERACOES ----");
    printf("|\t\t\t |");
    printf("\n|  Selecione o que Deseja alterar:\t |\n|\t\t\t |\n| 1 -Alterar Disciplina\t |\n| 2 -Alterar Turma\t\t |\n| 3 -Alterar Historico\t\t |\n| 0 - Sair\t\t |\n");
    puts("--------------------------");
    scanf("%d", &op);

    switch (op)
    {

        int num, op2;
    case 1:
        puts("Alterar Disciplina:");
        printf("Qual registro deseja alterar: ");
        scanf("%d", &num);
        if (num > quantDis)
        {
            printf("Disciplina nao encontrada.\n");
            break;
        }
        printf("Qual campo deseja alterar :\n1 - Nome\n2 - Codigo\n3 - Carga horaria\n\n");
        scanf("%d", &op2);

        if (op2 == 1)
        {
            printf("Digite o novo nome para a Disciplina: ");
            scanf("%s", &Disciplina[num].nomeDisciplina);
        }
        else if (op2 == 2)
        {
            printf("Digite o Codigo Atualizado: ");
            scanf("%s", &Disciplina[num].codigoDisciplina);
        }
        else if (op2 == 3)
        {
            printf("Digite a Carga Horaria Atualizada: ");
            scanf("%d", &Disciplina[num].chDisciplina);
        }
        else
        {
            puts("Opcao invalida!");
        }
        salvarArq();
        break;
    case 2:
        puts("Alterar Turma: ");
        printf("Qual registro deseja alterar: ");
        scanf("%d", &num);
        if (num > quantTurma)
        {
            printf("Turma nao encontrada.\n");
            break;
        }
        printf("Deseja alterar qual campo:\n1 - ID\n2 - Codigo\n3 - Turno\n4 - Docente\n\n");
        scanf("%d", &op2);

        if (op2 == 1)
        {
            printf("Id da Turma atualizado: ");
            scanf("%d", &Turma[num].idTurma);
        }
        else if (op2 == 2)
        {

            tTurma Tur;
            printf("Codigo da Turma atualizado: ");
            scanf("%s", &Turma[num].codigoDisciplina);
        }
        else if (op2 == 3)
        {
            printf("Turno da Turma atualizado: ");
            scanf("%s", &Turma[num].turnoTurma);
        }
        else if (op2 == 4)
        {
            printf("Docente da Turma atualizado: ");
            scanf("%s", &Turma[num].docenteTurma);
        }
        else
        {
            puts("Opcao invalida!");
        }
        salvarArq();
        break;
    case 3:
        puts("Alterar Historico:");
        printf("Qual registro deseja alterar: ");
        scanf("%d", &num);
        if (num > quantHist)
        {
            printf("Historico nao encontrado.\n");
            break;
        }
        printf("Deseja alterar qual campo:\n 1 - N° do aluno\n2 - ID\n3 - Nota final\n\n");
        scanf("%d", &op2);

        if (op2 == 1)
        {
            printf("Numero do aluno atualizado: ");
            scanf("%d", &Historico[num].numeroAluno);
        }
        else if (op2 == 2)
        {
            printf("ID da turma atualizado: ");
            scanf("%d", &Historico[num].idTurma);
        }
        else if (op2 == 3)
        {
            printf("Nota final atualiza: ");
            scanf("%f", &Historico[num].notaFinal);
        }
        else
        {
            puts("Opcao invalida!");
        }
        salvarArq();
        break;
    case 0:
        puts("Voltando para o MENU");
    default:
        puts("Opção invalida!");
        return 1;
        break;
    }

    return 0;
}

// Função para imprimir a tabela Disciplina
void showDisciplina()
{
    int o, i;

    do
    {
        puts("Mostrar a tabela completa - 1\nMostrar 1 atributo - 2\nMostrar 2 atributos - 3\nSair - 0");
        scanf("%d", &o);
        if (quantDis == 0)
        {
            puts("----------------");
            printf("Tabela Vazia!\n");
            puts("----------------\n");
            break;
        }
        switch (o)
        {
        case 1:
            printf("---------- Tabela Disciplina Todos Atributos ----------\n");
            for (i = 1; i <= quantDis; i++)
            {
                printf("\nNumero do Registro Disciplina: %d\n", i);
                printf("Nome: %s\nCodigo: %s\nCarga Horaria: %d\n\n", Disciplina[i].nomeDisciplina, Disciplina[i].codigoDisciplina, Disciplina[i].chDisciplina);
                printf("---------------------------------\n");
            }
            break;
        case 2:
            printf("---------- Tabela Disciplina 1 Atributo ----------\n");
            for (i = 1; i <= quantDis; i++)
            {
                printf("\nNumero do Registro Disciplina: %d\n", i);
                printf("Nome: %s", Disciplina[i].nomeDisciplina);
                printf("---------------------------------\n");
            }
            break;
        case 3:
            printf("---------- Tabela Disciplina 2 Atributos ----------\n");
            for (i = 1; i <= quantDis; i++)
            {
                printf("\nNumero do Registro Disciplina: %d\n", i);
                printf("Nome: %s", Disciplina[i].nomeDisciplina);
                printf("Codigo: %s\n", Disciplina[i].codigoDisciplina);
                printf("---------------------------------\n");
            }
            break;
        case 0:
            puts("Voltando para o menu 'Imprimir'\n");
            break;
        default:
            puts("Opcao invalida!");
            break;
        }
    } while (o != 0);
}

// Função para imprimir a tabela Turma
void showTTurma()
{
    int op, j;
    do
    {
        puts("Mostrar a tabela completa - 1\nMostrar 1 atributo - 2\nMostrar 2 atributos - 3\nMostrar 3 atributos - 4\nSair - 0");
        scanf("%d", &op);
        if (quantTurma == 0)
        {
            puts("----------------");
            printf("Tabela Vazia!\n");
            puts("----------------\n");
            break;
        }
        switch (op)
        {
            if (quantTurma == 0)
                printf("Tabela Vazia!\n");
        case 1:
            puts("------------ Tabela Turma Todos Atributos----------\n");
            for (j = 1; j <= quantTurma; j++)
            {

                printf("Numero do Registro de Turma: %d\n", j);
                printf("ID da Turma: %d\n", Turma[j].idTurma);
                printf("Codigo da Turma: %s\n", Turma[j].codigoDisciplina);
                printf("Docente: %s\nTurno: %s\n", Turma[j].docenteTurma, Turma[j].turnoTurma);

                printf("---------------------------------\n\n");
            }
            break;
        case 2:
            puts("------------- Tabela Turma 1 Atributos ---------");
            for (j = 1; j <= quantTurma; j++)
            {
                printf("Numero do Registro de Turma: %d\n", j);
                printf("ID da Turma: %d\n", Turma[j].idTurma);
                printf("---------------------------------\n");
            }
            break;
        case 3:
            puts("------------ Tabela Turma 2 Atributos ------------");
            for (j = 1; j <= quantTurma; j++)
            {

                printf("Numero do Registro de Turma: %d\n", j);
                printf("ID da Turma: %d\n", Turma[j].idTurma);
                printf("Turno: %s\n", Turma[j].turnoTurma);

                printf("---------------------------------\n");
            }
            break;
        case 4:
            puts("------------ Tabela Turma 3 Atributos ----------");
            for (j = 1; j <= quantTurma; j++)
            {

                printf("Numero do Registro de Turma: %d\n", j);
                printf("ID da Turma: %d\n", Turma[j].idTurma);
                printf("Turno: %s\nDocente: %s\n", Turma[j].turnoTurma, Turma[j].docenteTurma);
                printf("---------------------------------\n");
            }
        case 0:
            puts("Voltando para o menu 'Imprimir'\n");
            break;
        default:
            puts("\nOpcao invalida!\n");
        }
    } while (op != 0);
}

// Função para imprimir a tabela Histórico
void showTHistorico()
{
    int op, k;
    do
    {
        puts("\nMostrar a tabela completa - 1\nMostrar 1 atributo - 2\nMostrar 2 atributos - 3\nSair - 0");
        scanf("%d", &op);
        if (quantHist == 0)
        {
            puts("----------------");
            printf("Tabela Vazia!\n");
            puts("----------------\n");
            break;
        }
        switch (op)
        {
            if (quantHist == 0)
                printf("Tabela Vazia!\n");

        case 1:
            printf("--------- Tabela Historico Todos Atributos -----------\n");
            for (k = 1; k <= quantHist; k++)
            {

                printf("Numero do Registro de Historico: %d\nID da Turma: %d\n", k, Historico[k].idTurma);
                printf("Numero do aluno: %d\n", Historico[k].numeroAluno);
                printf("Nota Final: %.2f\n\n", Historico[k].notaFinal);
                printf("------------------------------------\n");
            }
            break;
        case 2:
            printf("--------- Tabela Historico 1 Atributo -----------\n");
            for (k = 1; k <= quantHist; k++)
            {

                printf("Numero do Registro de Historico: %d\n", k);
                printf("Numero do aluno: %d\n", Historico[k].numeroAluno);
                printf("------------------------------------\n");
            }
            break;
        case 3:
            printf("--------- Tabela Historico 2 Atributos -----------\n");
            for (k = 1; k <= quantHist; k++)
            {

                printf("Numero do Registro de Historico: %d\n", k);
                printf("Numero do aluno: %d\n", Historico[k].numeroAluno);
                printf("ID da Turma: %d\n\n", Historico[k].idTurma);
                printf("------------------------------------\n");
            }
            break;
        case 0:
            puts("Voltando para o menu 'Imprimir'\n");
            break;
        default:
            puts("Opcao invalida!");
        }
    } while (op != 0);
}

// Função para imprimir as tabelas
void imprimiVetor()
{
    int i, j, k;
    int op, o;

    do
    {
        puts("----- IMPRIMIR ------");
        printf("|\t\t\t |");
        printf("\n|   Deseja Vizualizar:\t |\n|\t\t\t |\n| 1 - Disciplinas\t |\n| 2 - Turmas\t\t |\n| 3 - Historicos\t |\n| 0 - sair\t\t |\n");
        puts("--------------------------");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            showDisciplina();
            break;
        case 2:
            showTTurma();
            break;
        case 3:
            showTHistorico();
            break;
        case 0:
            puts("Voltando para o MENU");
            break;
        default:
            puts("Opcao invalida");
            break;
        }
    } while (op != 0);
}

// Função para excluir registros de tabelas
void remover()
{
    FILE *arq = fopen("Database.dat", "a+");

    if (arq)
    {
        puts("----- REMOVER ------");
        printf("|\t\t\t |");
        printf("\n|   Deseja Remover:\t |\n|\t\t\t |\n| 1 - Disciplinas\t |\n| 2 - Turmas\t\t |\n| 3 - Historicos\t |\n| 0 - sair\t\t |\n");
        puts("--------------------------");
        int numeroRegistro;
        int i, op;
        tDisciplina Dis;
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            puts("Insira o numero do registro a ser removido: ");
            scanf("%d", &numeroRegistro);
            if (numeroRegistro > quantDis)
            {
                puts("Registro de Disciplina nao encontrado!");
            }
            else
            {
                for (i = 1; i <= quantDis - 1; i++)
                {
                    if (i >= numeroRegistro)
                    {
                        Disciplina[i] = Disciplina[i + 1];
                    }
                }
                quantDis--;
                salvarArq();
            }
            break;
        case 2:
            puts("Insira o numero do registro a ser removido: ");
            scanf("%d", &numeroRegistro);
            if (numeroRegistro > quantDis)
            {
                puts("Registro de Turma nao encontrado!");
            }
            else
            {
                for (i = 1; i <= quantDis - 1; i++)
                {
                    if (i >= numeroRegistro)
                    {
                        Turma[i] = Turma[i + 1];
                    }
                }
                quantTurma--;
                salvarArq();
            }
            break;
        case 3:
            puts("Insira o numero do registro a ser removido: ");
            scanf("%d", &numeroRegistro);
            if (numeroRegistro > quantDis)
            {
                puts("Registro de Historico nao encontrado!");
            }
            else
            {
                for (i = 1; i <= quantDis - 1; i++)
                {
                    if (i >= numeroRegistro)
                    {
                        Historico[i] = Historico[i + 1];
                    }
                }
                quantHist--;
                salvarArq();
            }
            break;
        case 0:
            puts("Voltando para o MENU");
            break;
        default:
            puts("Opcao invalida");
            break;
        }
    }
}
