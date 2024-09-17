#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INGREDIENTES 100
#define MAX_NOME 50
#define ARQUIVO_INGREDIENTES "ingredientes.txt"

typedef struct {
    char nome[MAX_NOME];
    float preco;
    int quantidade;
} Ingrediente;

Ingrediente ingredientes[MAX_INGREDIENTES];
int total_ingredientes = 0;

void salvarIngredientes() {
    FILE *arquivo = fopen(ARQUIVO_INGREDIENTES, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar os dados!\n");
        return;
    }

    // Cabeçalho da tabela
    fprintf(arquivo, "NOME\t\tPREÇO\t\tQUANTIDADE\n");
    fprintf(arquivo, "---------------------------------------------\n");

    float custo_total = 0;

    // Loop para salvar os ingredientes
    for (int i = 0; i < total_ingredientes; i++) {
        fprintf(arquivo, "%-15s\t%.2f\t\t%d\n", ingredientes[i].nome, ingredientes[i].preco, ingredientes[i].quantidade);
        custo_total += ingredientes[i].preco * ingredientes[i].quantidade;
    }

    // Exibe o valor total ao final da lista
    fprintf(arquivo, "\n---------------------------------------------\n");
    fprintf(arquivo, "Custo total:\t\t%.2f\n", custo_total);

    fclose(arquivo);
    printf("Dados salvos com sucesso!\n");
}

void carregarIngredientes() {
    FILE *arquivo = fopen(ARQUIVO_INGREDIENTES, "r");
    if (arquivo == NULL) {
        printf("Nenhum arquivo encontrado. Começando um novo cadastro.\n");
        return;
    }

    while (fscanf(arquivo, "%s %f %d", ingredientes[total_ingredientes].nome, 
            &ingredientes[total_ingredientes].preco, 
            &ingredientes[total_ingredientes].quantidade) != EOF) {
        total_ingredientes++;
    }

    fclose(arquivo);
    printf("Dados carregados com sucesso!\n");
}

void adicionarIngrediente() {
    if (total_ingredientes >= MAX_INGREDIENTES) {
        printf("Limite de ingredientes atingido!\n");
        return;
    }

    Ingrediente novo;
    printf("Digite o nome do ingrediente: ");
    scanf("%s", novo.nome);
    printf("Digite o preco do ingrediente: ");
    scanf("%f", &novo.preco);
    printf("Digite a quantidade do ingrediente: ");
    scanf("%d", &novo.quantidade);

    ingredientes[total_ingredientes] = novo;
    total_ingredientes++;

    salvarIngredientes();
    printf("Ingrediente adicionado com sucesso!\n");
}

void listarIngredientes() {
    if (total_ingredientes == 0) {
        printf("Nenhum ingrediente registrado.\n");
        return;
    }

    printf("\nLista de Ingredientes:\n");
    for (int i = 0; i < total_ingredientes; i++) {
        printf("%d. Nome: %s, Preco: %.2f, Quantidade: %d\n",
               i + 1, ingredientes[i].nome, ingredientes[i].preco, ingredientes[i].quantidade);
    }
}

void editarIngrediente() {
    int index;
    listarIngredientes();
    printf("Digite o número do ingrediente que deseja editar: ");
    scanf("%d", &index);

    if (index < 1 || index > total_ingredientes) {
        printf("Ingrediente inválido!\n");
        return;
    }

    index--;  // Ajusta o índice para começar em 0
    printf("Editar nome (%s): ", ingredientes[index].nome);
    scanf("%s", ingredientes[index].nome);
    printf("Editar preco (%.2f): ", ingredientes[index].preco);
    scanf("%f", &ingredientes[index].preco);
    printf("Editar quantidade (%d): ", ingredientes[index].quantidade);
    scanf("%d", &ingredientes[index].quantidade);

    salvarIngredientes();
    printf("Ingrediente editado com sucesso!\n");
}

void excluirIngrediente() {
    int index;
    listarIngredientes();
    printf("Digite o número do ingrediente que deseja excluir: ");
    scanf("%d", &index);

    if (index < 1 || index > total_ingredientes) {
        printf("Ingrediente inválido!\n");
        return;
    }

    index--;  // Ajusta o índice para começar em 0

    for (int i = index; i < total_ingredientes - 1; i++) {
        ingredientes[i] = ingredientes[i + 1];
    }

    total_ingredientes--;
    salvarIngredientes();
    printf("Ingrediente excluído com sucesso!\n");
}

void buscarIngrediente() {
    char nome_busca[MAX_NOME];
    int encontrado = 0;

    printf("Digite o nome do ingrediente que deseja buscar: ");
    scanf("%s", nome_busca);

    for (int i = 0; i < total_ingredientes; i++) {
        if (strcmp(ingredientes[i].nome, nome_busca) == 0) {
            printf("Ingrediente encontrado: Nome: %s, Preco: %.2f, Quantidade: %d\n",
                   ingredientes[i].nome, ingredientes[i].preco, ingredientes[i].quantidade);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Ingrediente não encontrado.\n");
    }
}

void calcularCustoTotal() {
    float custo_total = 0;

    for (int i = 0; i < total_ingredientes; i++) {
        custo_total += ingredientes[i].preco * ingredientes[i].quantidade;
    }

    printf("Custo total de todos os ingredientes: %.2f\n", custo_total);
}

void menu() {
    int opcao;

    do {
        printf("\nSistema de Gerenciamento de Ingredientes\n");
        printf("1. Adicionar Ingrediente\n");
        printf("2. Listar Ingredientes\n");
        printf("3. Editar Ingrediente\n");
        printf("4. Excluir Ingrediente\n");
        printf("5. Buscar Ingrediente\n");
        printf("6. Calcular Custo Total\n");
        printf("7. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
        case 1:
            adicionarIngrediente();
            break;
        case 2:
            listarIngredientes();
            break;
        case 3:
            editarIngrediente();
            break;
        case 4:
            excluirIngrediente();
            break;
        case 5:
            buscarIngrediente();
            break;
        case 6:
            calcularCustoTotal();
            break;
        case 7:
            printf("Saindo...\n");
            break;
        default:
            printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 7);
}

int main() {
    carregarIngredientes();
    menu();
    return 0;
}
