#include <stdio.h>


//inicializamos a função passando a posição (indice) do numero que queremos como parametro
int fibonnaci(int n){
    //caso base 1
    if (n == 0){
        return 0;
      //caso base 2
    } else if (n == 1){
        return 1;
      //recursividade: na sequencia de fibonnaci, temos o numero seguinte somando os 2 anteriores. E para "descobrirmos" quais sao, aplicamos a recursividade até o caso base
    } else {
        int resultado = fibonnaci(n - 1) + fibonnaci(n - 2);
        return resultado;
    }
    
}

int main(){
    int x = 0;
    printf("Insira um número para a sequeência de fibonnaci:");
    scanf("%d",&x);
    int y = fibonnaci(x-1);
    printf("O número é: %d", y);
    return 0;
}