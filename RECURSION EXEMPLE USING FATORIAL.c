#include <stdio.h>


//A função começa recebendo o número que voce deseja saber o fatorial como parametro
int fatorial(int n){
    //caso base: é o chao, precisa dele para parar a função e é dele que virão as outras respostas para os problemas maiores
    //É 1 ou 0 pois o fatorial de ambos é 1.
    if (n == 0 || n == 1){
        return 1;
    } else {
        //Principio do fatorial, é o numero vezes o seu antecessor. E aqui usamos a recursão chamando a função dela própria
        //Assim "quebramos" até chegar no caso base para, após isso, ir resolvendo-os
        int resultado = n * fatorial(n - 1);
        return resultado;
    }
    
}

int main(){
    int x = 0;
    printf("Insira um número para descobrir o seu fatorial:");
    scanf("%d",&x);
    int y = fatorial(x);
    printf("\nO fatorial é: %d\n", y);
    return 0;
}