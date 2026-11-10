#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_AMOSTRAS 100
/* Nome 1: Lucas Nadin Fumagali RA:10769708
Nome 2: Ericles Eloy Camargo RA:10732924 */




void inicializarMatrizes(double velocidades[][2], double sensores_frontais[][3],
                          double sensores_laterais[][2], int quantidade) {
    int i;
    for (i = 0; i < quantidade; i++) {
        velocidades[i][0] = (rand() % 1500) / 10.0;       
        velocidades[i][1] = (rand() % 1500) / 10.0;

        sensores_frontais[i][0] = (rand() % 2000) / 10.0; 
        sensores_frontais[i][1] = (rand() % 2000) / 10.0; 
        sensores_frontais[i][2] = (rand() % 2000) / 10.0; 

        sensores_laterais[i][0] = (rand() % 200) / 100.0; 
        sensores_laterais[i][1] = (rand() % 200) / 100.0; 
    }
}

int inserirAmostra(double velocidades[][2], double sensores_frontais[][3],
                    double sensores_laterais[][2], int num_amostras,
                    double velAtual, double velFrente, double radar,
                    double lidar, double camera, double faixaEsq, double faixaDir) {
    if (num_amostras >= MAX_AMOSTRAS) {
        return num_amostras;
    }

    velocidades[num_amostras][0] = velAtual;
    velocidades[num_amostras][1] = velFrente;

    sensores_frontais[num_amostras][0] = radar;
    sensores_frontais[num_amostras][1] = lidar;
    sensores_frontais[num_amostras][2] = camera;

    sensores_laterais[num_amostras][0] = faixaEsq;
    sensores_laterais[num_amostras][1] = faixaDir;

    return num_amostras + 1;
}

double medianaDeTres(double a, double b, double c) {
    if (a > b && a < c){
        return a;
    } else if (b > a && b < c){
        return b;
    } else {
        return c;
    }
}

void fusaoSensores(double sensores_frontais[][3], double processamento[][2], int num_amostras) {
    int i;
    for (i = 0; i < num_amostras; i++) {
        processamento[i][0] = medianaDeTres(sensores_frontais[i][0],
                                             sensores_frontais[i][1],
                                             sensores_frontais[i][2]);
    }
}

void calcularDistanciaSegura(double velocidades[][2], double processamento[][2],
                              int num_amostras, int sensibilidade, double atrito) {
    int i;
    double tempoReacao;
    double v_ms;

    if (sensibilidade == 1) {
        tempoReacao = 1.0;
    } else if (sensibilidade == 2) {
        tempoReacao = 1.5;
    } else {
        tempoReacao = 2.0;
    }

    for (i = 0; i < num_amostras; i++) {
        v_ms = velocidades[i][0] / 3.6;
        processamento[i][1] = (v_ms * tempoReacao) + (v_ms * v_ms) / (2.0 * atrito * 9.81);
    }
}

void analisarRiscoFrontal(double velocidades[][2], double processamento[][2],
                           int status[][3], int num_amostras) {
    int i;
    double velRelativa, validada, segura;

    for (i = 0; i < num_amostras; i++) {
        velRelativa = velocidades[i][0] - velocidades[i][1];

        if (velRelativa <= 0) {
            status[i][0] = 0;
        } else {
            validada = processamento[i][0];
            segura = processamento[i][1];

            if (validada >= segura) {
                status[i][0] = 0;
            } else if (validada >= 0.5 * segura) {
                status[i][0] = 1;
            } else {
                status[i][0] = 2;
            }
        }
    }
}

void analisarFaixaDinamica(double velocidades[][2], double sensores_laterais[][2],
                            int status[][3], int num_amostras) {
    int i;
    double margemDinamica, zonaAtencao, velAtual;

    for (i = 0; i < num_amostras; i++) {
        velAtual = velocidades[i][0];

        margemDinamica = 0.50;
        if (velAtual > 80.0) {
            margemDinamica += 0.01 * (velAtual - 80.0);
        }

        zonaAtencao = margemDinamica + 0.20;

        if (sensores_laterais[i][0] < margemDinamica) {
            status[i][1] = 2;
        } else if (sensores_laterais[i][0] < zonaAtencao) {
            status[i][1] = 1;
        } else {
            status[i][1] = 0;
        }

        if (sensores_laterais[i][1] < margemDinamica) {
            status[i][2] = 2;
        } else if (sensores_laterais[i][1] < zonaAtencao) {
            status[i][2] = 1;
        } else {
            status[i][2] = 0;
        }
    }
}


void exibirRelatorio(double velocidades[][2], double sensores_frontais[][3],
                      double sensores_laterais[][2], double processamento[][2],
                      int status[][3], int num_amostras) {
    int i;
    const char *statusFrontalTexto;
    const char *statusFaixaEsqTexto;
    const char *statusFaixaDirTexto;

    printf("\n===================== RELATORIO DE RISCOS - SAFEDRIVE =====================\n");

    for (i = 0; i < num_amostras; i++) {
        printf("\n---------------------------- Amostra %3d ----------------------------\n", i + 1);

        printf("[Dados de entrada]\n");
        printf("  Velocidade atual: %.2f km/h | Velocidade do veiculo a frente: %.2f km/h\n",
               velocidades[i][0], velocidades[i][1]);
        printf("  Radar: %.2f m | Lidar: %.2f m | Camera: %.2f m\n",
               sensores_frontais[i][0], sensores_frontais[i][1], sensores_frontais[i][2]);
        printf("  Faixa esquerda: %.2f m | Faixa direita: %.2f m\n",
               sensores_laterais[i][0], sensores_laterais[i][1]);

        printf("[Dados processados]\n");
        printf("  Distancia validada: %.2f m | Distancia segura exigida: %.2f m\n",
               processamento[i][0], processamento[i][1]);

        if (status[i][0] == 0) {
            statusFrontalTexto = "SEGURO";
        } else if (status[i][0] == 1) {
            statusFrontalTexto = "ATENCAO";
        } else {
            statusFrontalTexto = "RISCO DE COLISAO (AEB ACIONADO)";
        }

        if (status[i][1] == 0) {
            statusFaixaEsqTexto = "NORMAL";
        } else if (status[i][1] == 1) {
            statusFaixaEsqTexto = "ATENCAO";
        } else {
            statusFaixaEsqTexto = "PERIGO DE INVASAO";
        }

        if (status[i][2] == 0) {
            statusFaixaDirTexto = "NORMAL";
        } else if (status[i][2] == 1) {
            statusFaixaDirTexto = "ATENCAO";
        } else {
            statusFaixaDirTexto = "PERIGO DE INVASAO";
        }

        printf("[Status e alertas]\n");
        printf("  Status frontal: %s\n", statusFrontalTexto);
        printf("  Faixa esquerda: %s | Faixa direita: %s\n", statusFaixaEsqTexto, statusFaixaDirTexto);

        printf("[Decisao geral do sistema]\n");
        if (status[i][0] == 2 || status[i][1] == 2 || status[i][2] == 2) {
            printf("  >>> STATUS GERAL: INTERVENCAO CRITICA EXIGIDA <<<\n");
        } else if (status[i][0] == 1 || status[i][1] == 1 || status[i][2] == 1) {
            printf("  >>> STATUS GERAL: ATENCAO <<<\n");
        } else {
            printf("  >>> STATUS GERAL: NORMAL <<<\n");
        }
    }

    printf("\n=============================================================================\n");
}


int main(void) {
    double velocidades[MAX_AMOSTRAS][2];
    double sensores_frontais[MAX_AMOSTRAS][3];
    double sensores_laterais[MAX_AMOSTRAS][2];
    double processamento[MAX_AMOSTRAS][2];
    int status[MAX_AMOSTRAS][3];

    int num_amostras = 0;
    int opcao;
    int sensibilidade;
    double atrito;

    srand((unsigned int) time(NULL));

    printf("=== SafeDrive - Simulador de Telemetria ADAS ===\n\n");

    printf("Informe o atrito da via (ex: 0.7): ");
    scanf("%lf", &atrito);

    do {
        printf("Informe a sensibilidade do ADAS (1-Esportivo, 2-Normal, 3-Seguro): ");
        scanf("%d", &sensibilidade);
    } while (sensibilidade < 1 || sensibilidade > 3);

    do {
        printf("\n----------------- MENU -----------------\n");
        printf("1. Carregar dados iniciais (50 registros)\n");
        printf("2. Inserir nova amostra\n");
        printf("3. Processar e exibir relatorio de riscos\n");
        printf("4. Sair\n");
        printf("Amostras armazenadas: %d/%d\n", num_amostras, MAX_AMOSTRAS);
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                inicializarMatrizes(velocidades, sensores_frontais, sensores_laterais, 50);
                if (num_amostras < 50) {
                    num_amostras = 50;
                }
                printf("\n50 registros iniciais carregados com sucesso.\n");
                break;
            }
            case 2: {
                if (num_amostras >= MAX_AMOSTRAS) {
                    printf("\nLimite maximo de %d amostras atingido. Nao e possivel inserir nova amostra.\n", MAX_AMOSTRAS);
                    break;
                }

                double velAtual, velFrente, radar, lidar, camera, faixaEsq, faixaDir;

                printf("\n--- Insercao de nova amostra (instante %d) ---\n", num_amostras);
                printf("Velocidade atual (km/h): ");
                scanf("%lf", &velAtual);
                printf("Velocidade do veiculo a frente (km/h): ");
                scanf("%lf", &velFrente);
                printf("Leitura do radar (m): ");
                scanf("%lf", &radar);
                printf("Leitura do lidar (m): ");
                scanf("%lf", &lidar);
                printf("Leitura da camera (m): ");
                scanf("%lf", &camera);
                printf("Distancia da faixa esquerda (m): ");
                scanf("%lf", &faixaEsq);
                printf("Distancia da faixa direita (m): ");
                scanf("%lf", &faixaDir);

                num_amostras = inserirAmostra(velocidades, sensores_frontais, sensores_laterais,
                                               num_amostras, velAtual, velFrente, radar, lidar,
                                               camera, faixaEsq, faixaDir);

                printf("Amostra inserida com sucesso.\n");
                break;
            }
            case 3: {
                if (num_amostras == 0) {
                    printf("\nNenhuma amostra registrada ainda. Carregue os dados iniciais ou insira uma amostra.\n");
                    break;
                }
                fusaoSensores(sensores_frontais, processamento, num_amostras);
                calcularDistanciaSegura(velocidades, processamento, num_amostras, sensibilidade, atrito);
                analisarRiscoFrontal(velocidades, processamento, status, num_amostras);
                analisarFaixaDinamica(velocidades, sensores_laterais, status, num_amostras);
                exibirRelatorio(velocidades, sensores_frontais, sensores_laterais, processamento, status, num_amostras);
                break;
            }
            case 4:
                printf("\nEncerrando o simulador. Ate logo!\n");
                break;
            default:
                printf("\nOpcao invalida. Tente novamente.\n");
        }

    } while (opcao != 4);

    return 0;
}