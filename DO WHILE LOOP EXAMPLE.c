#include <stdio.h>
#include <stdbool.h>

int main(){
    int elemento;
    printf("-----Escolha uma opção-----:\n");
    printf("1 - Fogo\n2 - Agua\n3 - Terra\n");
    printf("Sua opção:");
    scanf("%d", &elemento);
    //inserimos o if para fazer que o codigo entre no laço apenas na condição correta, evitando colocar 
    if (elemento != 1 && elemento != 2 && elemento !=3){
        do {
            printf("Opção inválida!\nInsira outra:");
            scanf("%d", &elemento);
        }while(elemento < 1 || elemento > 3);{
            ;
        }
        }
        
    printf("\nO seu numero do seu elemento é %d", elemento);
    return 0;
     
    }
    
    
