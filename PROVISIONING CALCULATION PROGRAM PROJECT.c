#include <stdio.h>
#include <stdlib.h>

double pdd(double x, double y, double z, double a, double k){
    double provisionamento = x - y + z - a;
    double liquido = (provisionamento/k) * 100.0;
    return liquido;
}

int main (){
    double rec_prejuizo_liquida;
    double descontos;
    double outros;
    double bruta;
    double carteira;
    double resultado;
    
    printf("Insira a recuperação de prejuízo líquida:");
    scanf(" %lf", &rec_prejuizo_liquida);
    
    printf("\nInsira o total de desconto aplicado no mês:");
    scanf(" %lf", &descontos);
    
    printf("\nInsira outras despesas caso tenha:");
    scanf(" %lf", &outros);
    
    printf("\nInsira o valor da PDD bruta:");
    scanf(" %lf", &bruta);
    
    printf("\nInsira o valor liquida da carteira:");
    scanf("%lf", &carteira);
    
    resultado = pdd(rec_prejuizo_liquida,descontos,outros,bruta,carteira);
    printf("\nO resultado é %.2lf:", resultado);
    return 0;
}