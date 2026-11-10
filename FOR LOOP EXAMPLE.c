#include <stdio.h>
#include <stdbool.h>

int main(){
    int n;
    printf("Insira um número:");
    scanf("%d", &n);
    printf("Os número pares menores que %d são:\n", n);
    int i;
    //Em C, dentro do for vc coloca: Inicialização(i = 0), Condição(Se i for menor que n) e Incremento(add 2 na variavel i)
    for (i = 0; i < n; i += 2){
        printf("%d", i);
    }
    
    printf("\n");
    printf("Fim");
    return 0;
}