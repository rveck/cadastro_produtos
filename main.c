/**
 * Aplicação que executa o CRUD de produtos
 * Autor: Rafael Veck dos Santos
 * Data: 28/03/2021
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define NOME_ARQUIVO "dados.bin"
#define NOME_ARQUIVO_TEMPORARIO "temp.bin"
#define TAMANHO_MAX_REGISTRO 220
#define SEPARADOR ','
#define FIM_REGISTRO '|'

/**
 * Retorna o próximo ID de produto de acordo com a lista de produtos cadastrados
 */
int getNextId()
{
    int id = 0;

    //verifica se arquivo existe
    if (access(NOME_ARQUIVO, F_OK) == 0)
    {
        char idBuffer[10];

        FILE *fp;
        char c;
        fp = fopen(NOME_ARQUIVO, "rb");
        int count = 0;

        memset(idBuffer, 0, sizeof(idBuffer));

        while ((c = getc(fp)) != EOF)
        {
            if (c == FIM_REGISTRO)
            {
                count = 0;

                if (atoi(idBuffer) > id)
                {
                    id = atoi(idBuffer);
                }
                memset(idBuffer, 0, sizeof(idBuffer));
            }
            else if (c == SEPARADOR)
            {
                count = count + 1;
            }
            else if (count == 0)
            {
                idBuffer[strlen(idBuffer)] = c;
            }
        }
        fclose(fp);
    }
    return id + 1;
}

/**
 * Apresenta os dados do produto
 */
void apresentarDados(char c, int *contador)
{
    if (*contador == -1)
    {
        printf("ID: ");
        *contador = 0;
    }

    if (c == FIM_REGISTRO)
    {
        printf("\n\n");
        *contador = -1;
    }
    else if (c == SEPARADOR)
    {
        printf("\n");
        *contador = *contador + 1;
        if (*contador == 1)
        {
            printf("Nome: ");
        }
        else if (*contador == 2)
        {
            printf("Descrição: ");
        }
        else if (*contador == 3)
        {
            printf("Valor: ");
        }
        else if (*contador == 4)
        {
            printf("Cor: ");
        }
    }
    else
    {
        printf("%c", c);
    }
}

/*
 * Retorna os dados de um produto a partir do seu ID
 */
void getProdutoById(int idProduto, char retorno[TAMANHO_MAX_REGISTRO])
{
    //verifica se arquivo existe
    if (access(NOME_ARQUIVO, F_OK) == 0)
    {

        char nomeProduto[50];
        char descricao[100];
        double valorProduto;
        char cor[50];

        char valorProdutoBuffer[10];
        char idBuffer[10];

        FILE *fp;
        char c;
        fp = fopen(NOME_ARQUIVO, "rb");
        int count = 0;
        int posicao = 0;
        int countCaracteres = 0;
        memset(idBuffer, 0, sizeof(idBuffer));
        memset(nomeProduto, 0, sizeof(nomeProduto));
        memset(descricao, 0, sizeof(descricao));
        memset(valorProdutoBuffer, 0, sizeof(valorProdutoBuffer));
        memset(cor, 0, sizeof(cor));

        while ((c = getc(fp)) != EOF)
        {
            if (c == FIM_REGISTRO)
            {
                count = 0;

                if (atoi(idBuffer) == idProduto)
                {
                    sprintf(retorno, "%d%c%s%c%s%c%s%c%s%c%s%c", posicao, SEPARADOR, idBuffer, SEPARADOR, nomeProduto, SEPARADOR, descricao, SEPARADOR, valorProdutoBuffer, SEPARADOR, cor, FIM_REGISTRO);
                    return;
                }

                posicao = countCaracteres + 1;

                memset(idBuffer, 0, sizeof(idBuffer));
                memset(nomeProduto, 0, sizeof(nomeProduto));
                memset(descricao, 0, sizeof(descricao));
                memset(valorProdutoBuffer, 0, sizeof(valorProdutoBuffer));
                memset(cor, 0, sizeof(cor));
            }
            else if (c == SEPARADOR)
            {
                count = count + 1;
            }
            else
            {
                switch (count)
                {
                case 0:
                    idBuffer[strlen(idBuffer)] = c;
                    break;
                case 1:
                    nomeProduto[strlen(nomeProduto)] = c;
                    break;
                case 2:
                    descricao[strlen(descricao)] = c;
                    break;
                case 3:
                    valorProdutoBuffer[strlen(valorProdutoBuffer)] = c;
                    break;
                case 4:
                    cor[strlen(cor)] = c;
                    break;
                default:
                    break;
                }
            }
            countCaracteres = countCaracteres + 1;
        }
        fclose(fp);
    }
}

/**
 * Edita os campos de um produto
 */
void editar(char registro[TAMANHO_MAX_REGISTRO])
{
    char posicao[10];
    char idBuffer[10];
    char nomeProduto[50];
    char descricao[100];
    char valorProdutoBuffer[10];
    char cor[50];

    memset(posicao, 0, sizeof(posicao));
    memset(idBuffer, 0, sizeof(idBuffer));
    memset(nomeProduto, 0, sizeof(nomeProduto));
    memset(descricao, 0, sizeof(descricao));
    memset(valorProdutoBuffer, 0, sizeof(valorProdutoBuffer));
    memset(cor, 0, sizeof(cor));

    int count = 0;

    for (int i = 0; i < TAMANHO_MAX_REGISTRO; i++)
    {
        char c = registro[i];
        if (c == FIM_REGISTRO)
        {
            break;
        }
        else if (c == SEPARADOR)
        {
            count = count + 1;
        }
        else
        {
            switch (count)
            {
            case 0:
                posicao[strlen(posicao)] = c;
                break;
            case 1:
                idBuffer[strlen(idBuffer)] = c;
                break;
            case 2:
                nomeProduto[strlen(nomeProduto)] = c;
                break;
            case 3:
                descricao[strlen(descricao)] = c;
                break;
            case 4:
                valorProdutoBuffer[strlen(valorProdutoBuffer)] = c;
                break;
            case 5:
                cor[strlen(cor)] = c;
                break;
            default:
                break;
            }
        }
    }

    char novoNomeProduto[50];
    char novadDescricao[100];
    char novoValorProduto[10];
    char novaCor[50];

    printf("Nome do produto: (%s)\n", nomeProduto);
    gets(novoNomeProduto);

    printf("Descrição: (%s)\n", descricao);
    gets(novadDescricao);

    printf("Valor: (%s)\n", valorProdutoBuffer);
    gets(novoValorProduto);

    printf("Cor: (%s)\n", cor);
    gets(novaCor);

    if (strlen(novoNomeProduto) == 0)
    {
        strcpy(novoNomeProduto, nomeProduto);
    }

    if (strlen(novadDescricao) == 0)
    {
        strcpy(novadDescricao, descricao);
    }

    if (strlen(novoValorProduto) == 0)
    {
        strcpy(novoValorProduto, valorProdutoBuffer);
    }

    if (strlen(novaCor) == 0)
    {
        strcpy(novaCor, cor);
    }

    char registroAtualizado[TAMANHO_MAX_REGISTRO];
    memset(registroAtualizado, 0, TAMANHO_MAX_REGISTRO);
    sprintf(registroAtualizado, "%s%c%s%c%s%c%s%c%s%c", idBuffer, SEPARADOR, novoNomeProduto, SEPARADOR, novadDescricao, SEPARADOR, novoValorProduto, SEPARADOR, novaCor, FIM_REGISTRO);

    FILE *fp;
    fp = fopen(NOME_ARQUIVO, "rb+");

    FILE *novo_fp;
    novo_fp = fopen(NOME_ARQUIVO_TEMPORARIO, "ab");

    if (atoi(posicao) > 0)
    {
        int tamanhoInicioArquivo = atoi(posicao) + 1;
        char inicioArquivo[tamanhoInicioArquivo];
        fgets(inicioArquivo, tamanhoInicioArquivo, fp);
        char ch;
        for (int i = 0; i < tamanhoInicioArquivo - 1; i++)
        {
            ch = inicioArquivo[i];
            fputc(ch, novo_fp);
        }
    }

    int antivoTamanhoRegistro = strlen(idBuffer) + strlen(nomeProduto) + strlen(descricao) + strlen(valorProdutoBuffer) + strlen(cor) + 4 + 1; //4 separadores
    int novoTamanhoRegistro = strlen(registroAtualizado);
    int posicaoProximoRegistro = atoi(posicao) + antivoTamanhoRegistro;
    fseek(fp, posicaoProximoRegistro, SEEK_SET);
    int tamanhoFimArquivo = 0;
    char ch;
    while ((ch = getc(fp)) != EOF)
    {
        tamanhoFimArquivo++;
    }

    tamanhoFimArquivo++;
    char fimArquivo[tamanhoFimArquivo];
    fseek(fp, posicaoProximoRegistro, SEEK_SET);

    fgets(fimArquivo, tamanhoFimArquivo, fp);

    fseek(fp, atoi(posicao), SEEK_SET);

    fwrite(registroAtualizado, strlen(registroAtualizado), 1, novo_fp);

    for (int i = 0; i < tamanhoFimArquivo - 1; i++)
    {
        ch = fimArquivo[i];
        fputc(ch, novo_fp);
    }

    fclose(fp);
    fclose(novo_fp);
    remove(NOME_ARQUIVO);
    rename(NOME_ARQUIVO_TEMPORARIO, NOME_ARQUIVO);
}

/**
 * Exclui um produto
 */
void excluir(char registro[TAMANHO_MAX_REGISTRO])
{
    char posicao[10];
    char idBuffer[10];
    char nomeProduto[50];
    char descricao[100];
    char valorProdutoBuffer[10];
    char cor[50];

    memset(posicao, 0, sizeof(posicao));
    memset(idBuffer, 0, sizeof(idBuffer));
    memset(nomeProduto, 0, sizeof(nomeProduto));
    memset(descricao, 0, sizeof(descricao));
    memset(valorProdutoBuffer, 0, sizeof(valorProdutoBuffer));
    memset(cor, 0, sizeof(cor));

    int count = 0;

    for (int i = 0; i < TAMANHO_MAX_REGISTRO; i++)
    {
        char c = registro[i];
        if (c == FIM_REGISTRO)
        {
            break;
        }
        else if (c == SEPARADOR)
        {
            count = count + 1;
        }
        else
        {
            switch (count)
            {
            case 0:
                posicao[strlen(posicao)] = c;
                break;
            case 1:
                idBuffer[strlen(idBuffer)] = c;
                break;
            case 2:
                nomeProduto[strlen(nomeProduto)] = c;
                break;
            case 3:
                descricao[strlen(descricao)] = c;
                break;
            case 4:
                valorProdutoBuffer[strlen(valorProdutoBuffer)] = c;
                break;
            case 5:
                cor[strlen(cor)] = c;
                break;
            default:
                break;
            }
        }
    }

    char registroAtualizado[TAMANHO_MAX_REGISTRO];
    memset(registroAtualizado, 0, TAMANHO_MAX_REGISTRO);
    sprintf(registroAtualizado, "%s%c%s%c%s%c%s%c%s%c", idBuffer, SEPARADOR, nomeProduto, SEPARADOR, descricao, SEPARADOR, valorProdutoBuffer, SEPARADOR, cor, FIM_REGISTRO);

    FILE *fp;
    fp = fopen(NOME_ARQUIVO, "rb+");

    FILE *novo_fp;
    novo_fp = fopen(NOME_ARQUIVO_TEMPORARIO, "ab");

    if (atoi(posicao) > 0)
    {
        int tamanhoInicioArquivo = atoi(posicao) + 1;
        char inicioArquivo[tamanhoInicioArquivo];
        fgets(inicioArquivo, tamanhoInicioArquivo, fp);
        char ch;
        for (int i = 0; i < tamanhoInicioArquivo - 1; i++)
        {
            ch = inicioArquivo[i];
            fputc(ch, novo_fp);
        }
    }

    int antivoTamanhoRegistro = strlen(idBuffer) + strlen(nomeProduto) + strlen(descricao) + strlen(valorProdutoBuffer) + strlen(cor) + 4 + 1; //4 separadores
    int posicaoProximoRegistro = atoi(posicao) + antivoTamanhoRegistro;
    fseek(fp, posicaoProximoRegistro, SEEK_SET);
    int tamanhoFimArquivo = 0;
    char ch;
    while ((ch = getc(fp)) != EOF)
    {
        tamanhoFimArquivo++;
    }

    tamanhoFimArquivo++;
    char fimArquivo[tamanhoFimArquivo];
    fseek(fp, posicaoProximoRegistro, SEEK_SET);

    fgets(fimArquivo, tamanhoFimArquivo, fp);

    fseek(fp, atoi(posicao), SEEK_SET);

    for (int i = 0; i < tamanhoFimArquivo - 1; i++)
    {
        ch = fimArquivo[i];
        fputc(ch, novo_fp);
    }

    fclose(fp);
    fclose(novo_fp);
    remove(NOME_ARQUIVO);
    rename(NOME_ARQUIVO_TEMPORARIO, NOME_ARQUIVO);
}

/**
 * Cria um novo registro de produto
 */
void criar(char nomeProduto[50], char descricao[100], double valorProduto, char cor[50])
{
    int id = getNextId();
    char registro[TAMANHO_MAX_REGISTRO];
    sprintf(registro, "%d%c%s%c%s%c%0.2f%c%s%c", id, SEPARADOR, nomeProduto, SEPARADOR, descricao, SEPARADOR, valorProduto, SEPARADOR, cor, FIM_REGISTRO);
    printf("Salvado: %s", registro);
    FILE *fp;
    fp = fopen(NOME_ARQUIVO, "ab");
    fputs(registro, fp);
    fclose(fp);
    printf("\n\nProduto cadastrado com sucesso!\n\n");
}

/**
 * Lista todos os produtos cadastrados
*/
void listar()
{
    //verifica se arquivo existe
    if (access(NOME_ARQUIVO, F_OK) == 0)
    {
        FILE *fp;
        fp = fopen(NOME_ARQUIVO, "rb");
        char c;
        int contador = -1;
        while ((c = getc(fp)) != EOF)
        {
            apresentarDados(c, &contador);
        }
        fclose(fp);
    }
    else
    {
        printf("Não há produtos para serem listados");
    }
}

/**
 * Captura os dados de um novo produto a partir do terminal
*/
void getDadosProduto()
{
    char nomeProduto[50];
    char descricao[100];
    double valorProduto;
    char cor[50];

    printf("Nome do produto:\n");
    gets(nomeProduto);

    printf("Descrição:\n");
    gets(descricao);

    char valorProdudoStr[10];
    printf("Valor:\n");
    gets(valorProdudoStr);
    valorProduto = strtod(valorProdudoStr, NULL);

    printf("Cor:\n");
    gets(cor);

    char opcao[1];
    printf("\n\nNome: %s\nDescricao: %s\nValor: %.2f \nCor: %s \n\nTem certeza que deseja cadastrar um novo produto com os seguintes dados? (y/f)\n", nomeProduto, descricao, valorProduto, cor);

    gets(opcao);
    if (strcmp(opcao, "y") == 0)
    {
        criar(nomeProduto, descricao, valorProduto, cor);
    }
}

/**
 * Função principal da aplicação
*/
int main()
{
    char opcao[1];

    printf("Menu: \n\n1. Cadastrar produto \n2. Editar produto \n3. Excluir produto \n4. Listar produtos \n5. Buscar pelo ID \n");
    gets(opcao);

    printf("Opção escolhida : %s\n\n", opcao);

    if (strcmp(opcao, "1") == 0)
    {
        getDadosProduto();
    }
    else if (strcmp(opcao, "4") == 0)
    {
        listar();
    }
    else if (strcmp(opcao, "2") == 0)
    {
        char idProduto[10];
        printf("ID do produto:\n");
        gets(idProduto);
        char retorno[TAMANHO_MAX_REGISTRO];
        getProdutoById(atoi(idProduto), retorno);
        if ((strlen(retorno) - 5) == 0) //5 separadores
        {
            printf("\nProduto não encontrado");
        }
        else
        {
            printf("%lu", strlen(retorno));
            editar(retorno);
        }
    }
    else if (strcmp(opcao, "3") == 0)
    {
        char idProduto[10];
        printf("ID do produto:\n");
        gets(idProduto);
        char retorno[TAMANHO_MAX_REGISTRO];
        getProdutoById(atoi(idProduto), retorno);
        if ((strlen(retorno) - 5) == 0) //5 separadores
        {
            printf("\nProduto não encontrado");
        }
        else
        {
            printf("%lu", strlen(retorno));
            excluir(retorno);
        }
    }
    else if (strcmp(opcao, "5") == 0)
    {
        char idProduto[10];
        printf("ID do produto:\n");
        gets(idProduto);
        char retorno[TAMANHO_MAX_REGISTRO];
        getProdutoById(atoi(idProduto), retorno);
        printf("%s", retorno);
    }

    return 0;
}
