#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char proprietario[50];
    char combustivel[20];
    char modelo[50];
    char chassi[17];
    char cor[20];
    int ano;
    char placa[8];
} Veiculo;

typedef struct No {
    Veiculo veiculo;
    struct No* proximo;
} NoLista;

NoLista* adicionarVeiculo(NoLista* lista, Veiculo veiculo) {
    NoLista* novoNo = (NoLista*)malloc(sizeof(NoLista));
    if (novoNo == NULL) {
        printf("Erro ao alocar memoria.\n");
        exit(1);
    }

    novoNo->veiculo = veiculo;
    novoNo->proximo = lista;

    return novoNo;
}

void listarProprietariosDiesel2010(NoLista* lista) {
    printf("\nProprietarios de carros do ano de 2010 ou posterior e movidos a diesel:\n");
    while (lista != NULL) {
        if (lista->veiculo.ano >= 2010 && strcmp(lista->veiculo.combustivel, "diesel") == 0) {
            printf("- %s\n", lista->veiculo.proprietario);
        }
        lista = lista->proximo;
    }
}

void listarPlacasJ(NoLista* lista) {
    printf("\nPlacas que começam com 'J' e terminam com 0, 2, 4 ou 7 e seus respectivos proprietarios:\n");
    while (lista != NULL) {
        if (lista->veiculo.placa[0] == 'J' &&
            (lista->veiculo.placa[7] == '0' || lista->veiculo.placa[7] == '2' ||
             lista->veiculo.placa[7] == '4' || lista->veiculo.placa[7] == '7')) {
            printf("- Placa: %s, Proprietario: %s\n", lista->veiculo.placa, lista->veiculo.proprietario);
        }
        lista = lista->proximo;
    }
}

void listarModeloCorVogalSomaPar(NoLista* lista) {
    printf("\nModelo e cor dos veiculos com placas que possuem como segunda letra uma vogal e soma dos valores numericos e par:\n");
    while (lista != NULL) {
        char segundaLetraPlaca = lista->veiculo.placa[1];
        int somaValoresNumericos = 0;
        for (int i = 3; i < 7; i++) {
            somaValoresNumericos += lista->veiculo.placa[i] - '0';
        }

        if ((segundaLetraPlaca == 'A' || segundaLetraPlaca == 'E' ||
             segundaLetraPlaca == 'I' || segundaLetraPlaca == 'O' ||
             segundaLetraPlaca == 'U') && somaValoresNumericos % 2 == 0) {
            printf("- Modelo: %s, Cor: %s\n", lista->veiculo.modelo, lista->veiculo.cor);
        }

        lista = lista->proximo;
    }
}

void trocarProprietarioSemDigitoZero(NoLista* lista, const char* novoProprietario, const char* chassi) {
    while (lista != NULL) {
        int temDigitoZero = 0;
        for (int i = 0; i < 8; i++) {
            if (lista->veiculo.placa[i] == '0') {
                temDigitoZero = 1;
                break;
            }
        }

        if (!temDigitoZero && strcmp(lista->veiculo.chassi, chassi) == 0) {
            strcpy(lista->veiculo.proprietario, novoProprietario);
            printf("\nTroca de proprietario realizada com sucesso!\n");
            return;
        }

        lista = lista->proximo;
    }

    printf("\nVeiculo com chassi '%s' nao encontrado ou possui digito zero na placa.\n", chassi);
}

void liberarLista(NoLista* lista) {
    while (lista != NULL) {
        NoLista* proximo = lista->proximo;
        free(lista);
        lista = proximo;
    }
}

int main() {
    NoLista* lista = NULL;
    Veiculo novoVeiculo;

    char continuarCadastro;
    do {
        printf("\nInforme os dados do veiculo:\n");

        printf("Proprietario: ");
        scanf("%s", novoVeiculo.proprietario);

        printf("Combustivel (alcool, diesel, gasolina): ");
        scanf("%s", novoVeiculo.combustivel);

        printf("Modelo: ");
        scanf("%s", novoVeiculo.modelo);

        printf("Chassi: ");
        scanf("%s", novoVeiculo.chassi);

        printf("Cor: ");
        scanf("%s", novoVeiculo.cor);

        printf("Ano: ");
        scanf("%d", &novoVeiculo.ano);

        printf("Placa (XXX1234): ");
        scanf("%s", novoVeiculo.placa);

        lista = adicionarVeiculo(lista, novoVeiculo);

        printf("Deseja cadastrar outro veiculo? (s/n): ");
        scanf(" %c", &continuarCadastro);

    } while (continuarCadastro == 's' || continuarCadastro == 'S');

    listarProprietariosDiesel2010(lista);
    listarPlacasJ(lista);
    listarModeloCorVogalSomaPar(lista);

    char chassiTroca[17];
    printf("\nInforme o chassi do veiculo para troca de proprietario: ");
    scanf("%s", chassiTroca);
    trocarProprietarioSemDigitoZero(lista, "Novo Proprietario", chassiTroca);

    liberarLista(lista);

    return 0;
}