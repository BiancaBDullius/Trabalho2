#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void push(void *pilha, char *letra);
void pop(void *pilha, void *metadePilha);

int main()
{
    char letra[1];
    int programa = 1;
    void *metadePilha;
    void *pilha = (void *)malloc(sizeof(int));
    int *topo;
    int *limite;

    topo = pilha;
    limite = (pilha + sizeof(int));

    *topo = 0;
    *limite = 0;
    while (programa != 0)
    {
        printf("Digite uma letra: \n");
        scanf("%s", &letra);

        if (strcmp(letra, "x") == 0)
        {
            break;
        }

        pilha = (void *)realloc(pilha, (sizeof(int) * 2) + (sizeof(char) * (*((int *)(pilha + sizeof(int))) + 2)));

        push(pilha, letra);
    }

    if ((*((int *)(pilha + sizeof(int)))) % 2 != 0)
    {
        printf("A sequencia digitada nao eh um palindromo.");
        return 0;
    }

    int metade;
    metade = *((int *)(pilha + sizeof(int)));
    metadePilha = (void *)malloc((sizeof(int) * 2) + sizeof(char) * ((metade / 2) + 1));
    *((int *)(metadePilha)) = 0;
    *((int *)(metadePilha + sizeof(int))) = 0;

    for (int i = 0; i < (metade / 2); i++)
    {
        pop(pilha, metadePilha);
    }

    if (strcmp(((char *)(pilha + sizeof(int) * 2)), ((char *)(metadePilha + sizeof(int) * 2))) == 0)
    {
        printf("Eh palindromo.");
    }
    else
    {
        printf("Nao eh palindromo.");
    }

    free(pilha);
    free(metadePilha);
    return 0;
}

void push(void *pilha, char *letra)
{
    char *caracter;
    caracter = letra;
    char *string;
    string = (pilha + sizeof(int) * 2 + sizeof(char) * (*((int *)(pilha + sizeof(int)))) + 1);
    *string = *caracter;

    *((int *)(pilha)) = *((int *)(pilha)) + 1;

    *((int *)(pilha + sizeof(int))) = *((int *)(pilha + sizeof(int))) + 1;
}

void pop(void *pilha, void *metadePilha)
{
    char *letra;
    letra = (((pilha + sizeof(int) * 2) + sizeof(char) * ((*((int *)(pilha + sizeof(int)))))));
    push(metadePilha, letra);

    *((int *)(pilha)) = *((int *)(pilha)) - 1;
    *((int *)(pilha + sizeof(int))) = *((int *)(pilha + sizeof(int))) - 1;

    pilha = realloc(pilha, (sizeof(int) * 2) + sizeof(char) * (*((int *)(pilha + sizeof(int)))));
}