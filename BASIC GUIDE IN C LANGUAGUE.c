#include <stdio.h>
//Importa a biblioteca básica que diz ao compilador o que ele irá fazer
//COISAS PARA NÃO ESQUECER: 
// \n --> Pula a linha do cursor
// ; --> Extremamente necessário no final das linhas
// %x --> O % especifica o tipo da variavel escolhida anteriormente (exemplo: int numeros, float numeros e etc)
// tipos de % --> Agora, os mais importantes tipos do % são int (%d), float (%f) e string (%s) 
// & --> Obtem o endereço de memoria da variavel declarada antes e manda o scanf guardar a informação lá 
// & é indispensavel para int e float mas não utilizá-lo em strings


//define como int pois é o padrão recomendado e define o bloco de codigo main. indispensavel (LEMBRAR DE COLOCAR O {})
int main(){
    //declara a variável que é estritamente necessário
    int numero;
    int cubo;
    printf("Bem vindo ao programa que calcula o cubo dos números\n");
    printf("Insira o número:");
    //funciona + ou - como o input mas ele n imprime nada no terminal. Toda vez que utilizá-lo é necessário identificar o tipo e usar o & para...
    //...guardar a informação na memória da variavel (nesse caso, a variavel numero)
    scanf("%d" , &numero);
    //necessario colocar o tipo da variavel (%d) e colocar a variavel normalmente como em python
    printf("Seu número é %d \n", numero);
    //nao possui operador nativo de potenciação, então faremos a multiplicação 3 vezes
    cubo = numero * numero * numero;
    printf("O cubo do número escolhido é:%d", cubo);
    return 0;
}