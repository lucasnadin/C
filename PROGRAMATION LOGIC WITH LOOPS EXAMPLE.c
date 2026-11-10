#include <stdio.h>
//necessário importar essa biblioteca pois o C nativo não tem a opção de booleano
#include <stdbool.h>

int main(){
    int opcao;
    int opcaonova;
    //define uma variavel igual a 0 que tem o mesmo valor de False em C
    int erro = 0;
    printf("1 - Matutino\n2 - Vespertino\n3 - Noturno\n");
    printf("Escolha sua opcao:");
    scanf("%d", &opcao);
    
    //Na linguagem C, o and é representado por && 
    if (opcao != 1 && opcao != 2 && opcao != 3){
        while(!erro){
            printf("Insira uma opcao válida\n");
            printf("Opção:");
            scanf("%d", &opcaonova);
            opcao = opcaonova;
            //Na linguagem C, o or é representado por ||
            if (opcao == 1 || opcao == 2 || opcao ==3){
                //define a variavel False para True alterando o valor dela de 0 pra 1
                erro = 1;
            }
            
            
        }
    }
    
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
    }
    return 0;
}