#include <stdio.h>

int main(){
    
    int opcao;
    printf("(1)manha\n(2)noite\n");
    printf("Escolha a sua opção:");
    scanf("%d", &opcao);
    if (opcao == 1){
        printf("manha");
    }
    else if (opcao == 2){
        printf("noite");
    }
    else{
        printf("Escolha uma opcao valida");
    }
    
    return 0;
}