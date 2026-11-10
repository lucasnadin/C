#include <stdio.h>

int main(){
    int opcao;
    printf("1 - Matutino\n2 - Vespertino\n3 - Noturno\n");
    printf("Escolha sua opcao:");
    scanf("%d", &opcao);
    switch (opcao){
        case 1:
            printf("Matutino");
            break;
        case 2:
            printf("Vespertino");
            break;
        case 3:
            printf("Noturno");
            break;
        default:
            printf("Insira uma opcao valida");
            break;
    }
    return 0;
}