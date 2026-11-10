#include <stdio.h>
#include <string.h>

struct Moto {
   char fabricante[50];
   char modelo[50];
   int cilindrada;
};

struct Circuito {
   char nomec[50];
   char pais[50];
   float km_pista;
};

struct Corrida {
   int posicao;
   float Melhortempo;
   float Velocidademedia;
   int pontos;
   struct Circuito a1;//Circuito tem que ser uma struct aninhada dentro da corrida
};

struct Piloto {
   int numero;
   char nome[50];
   char nacionalidade[50];
   struct Moto moto; //Moto tem q ser um item do piloto
   int Qtdcorridas;
   struct Corrida corridas[6]; // Cada piloto pode participar de ATÉ 6 corridas.
};

int calcularPontos(int posicao) {
    switch (posicao) {
        case 1:
            return 25;
        case 2:
            return 20;
        case 3:
            return 16;
        case 4:
            return 13;
        case 5:
            return 11;
        case 6:
            return 10;
        case 7:
            return 9;
        case 8:
            return 8;
        case 9:
            return 7;
        case 10:
            return 6;
        default:
            return 0;
    }
}

// FUNÇÃO PARA ENCONTRAR A MELHOR POSIÇÃO
int melhorposicao(struct Piloto piloto) {

    int melhor = piloto.corridas[0].posicao;

    for (int i = 1; i < piloto.Qtdcorridas; i++) {
        if (piloto.corridas[i].posicao < melhor) {
            melhor = piloto.corridas[i].posicao;
        }
    }

    return melhor;
}

float melhorvelocidade(struct Piloto piloto) {

    float melhor = piloto.corridas[0].Velocidademedia;

    for (int i = 1; i < piloto.Qtdcorridas; i++) {
        if (piloto.corridas[i].Velocidademedia > melhor) {
            melhor = piloto.corridas[i].Velocidademedia;
        }
    }

    return melhor;
}


int contarVitorias(struct Piloto piloto) {

    int vitorias = 0;

    for (int i = 0; i < piloto.Qtdcorridas; i++) {
        if (piloto.corridas[i].posicao == 1) {
            vitorias++;
        }
    }

    return vitorias;
}

int contarPodios(struct Piloto piloto) {

    int podios = 0;

    for (int i = 0; i < piloto.Qtdcorridas; i++) {
        if (piloto.corridas[i].posicao >= 1 && piloto.corridas[i].posicao <= 3) {
            podios++;
        }
    }

    return podios;
}

int calcularPontosTotais(struct Piloto piloto) {

    int pontosTotais = 0;

    for (int i = 0; i < piloto.Qtdcorridas; i++) {
        pontosTotais += piloto.corridas[i].pontos;
    }

    return pontosTotais;
}

float calcularVelocidadeTemporada(struct Piloto piloto) {

    float soma = 0;

    for (int i = 0; i < piloto.Qtdcorridas; i++) {
        soma += piloto.corridas[i].Velocidademedia;
    }

    if (piloto.Qtdcorridas > 0) {
        return soma / piloto.Qtdcorridas;
    }

    return 0;
}

//Criando novas funções para o relatorio
void salvarDados(struct Piloto pilotos[4]) {

    FILE *arquivo;

    arquivo = fopen("motogp.txt", "w"); //w de write, funciona para escrita.

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    for (int i = 0; i < 4; i++) {
        fprintf(arquivo, "%d;%s;%s;%s;%s;%d;%d\n", //salva os dados dos pilotos
            pilotos[i].numero,
            pilotos[i].nome,
            pilotos[i].nacionalidade,
            pilotos[i].moto.fabricante,
            pilotos[i].moto.modelo,
            pilotos[i].moto.cilindrada,
            pilotos[i].Qtdcorridas);

        for (int j = 0; j < pilotos[i].Qtdcorridas; j++) {

            fprintf(arquivo, "%d;%f;%f;%d;%s;%s;%f\n", //salva as corridas
                pilotos[i].corridas[j].posicao,
                pilotos[i].corridas[j].Melhortempo,
                pilotos[i].corridas[j].Velocidademedia,
                pilotos[i].corridas[j].pontos,
                pilotos[i].corridas[j].a1.nomec,
                pilotos[i].corridas[j].a1.pais,
                pilotos[i].corridas[j].a1.km_pista);
            }
    }

    fclose(arquivo);
}

void salvarRelatorioTexto(struct Piloto pilotos[4], int lider, int ordem[4]){ //salva todos os resultados do programa no arquivo.txt
    FILE *arquivo;
    arquivo = fopen("relatorio_campeonato.txt", "w");

    if (arquivo == NULL) {

        printf("\nErro ao criar o relatorio em texto!\n");

        return;
    }
    
    fprintf(arquivo,"====== RELATORIO DO CAMPEONATO ======\n");

    for (int i = 0; i < 4; i++) {

        int pontosTotais = calcularPontosTotais(pilotos[i]);
        int melhorPos = melhorposicao(pilotos[i]);
        float melhorVel = melhorvelocidade(pilotos[i]);
        int vitorias = contarVitorias(pilotos[i]);
        int podios = contarPodios(pilotos[i]);
        float velocidadeTemporada = calcularVelocidadeTemporada(pilotos[i]);

        fprintf(arquivo,"\n====== RELATORIO DO PILOTO ======\n"); //Dados dos pilotos

        fprintf(arquivo,"Numero: %d\n",pilotos[i].numero);
        fprintf(arquivo,"Nome: %s\n",pilotos[i].nome);
        fprintf(arquivo,"Nacionalidade: %s\n",pilotos[i].nacionalidade);

        fprintf(arquivo,"\n------ MOTO ------\n");

        fprintf(arquivo,"Fabricante: %s\n",pilotos[i].moto.fabricante);
        fprintf(arquivo,"Modelo: %s\n",pilotos[i].moto.modelo);
        fprintf(arquivo,"Cilindrada: %d cc\n",pilotos[i].moto.cilindrada);


        fprintf(arquivo,"\n------ CORRIDAS ------\n");


        for (int j = 0;j < pilotos[i].Qtdcorridas;j++) {

            fprintf(arquivo,"\nCorrida %d:\n", j + 1);
            fprintf(arquivo,"Circuito: %s\n", pilotos[i].corridas[j].a1.nomec);
            fprintf(arquivo,"Pais: %s\n", pilotos[i].corridas[j].a1.pais);
            fprintf(arquivo,"Km da pista: %.2f km\n", pilotos[i].corridas[j].a1.km_pista);
            fprintf(arquivo,"Posicao: %d\n", pilotos[i].corridas[j].posicao);
            fprintf(arquivo,"Melhor tempo: %.2f\n", pilotos[i].corridas[j].Melhortempo);
            fprintf(arquivo,"Velocidade media: %.2f km/h\n", pilotos[i].corridas[j].Velocidademedia);
            fprintf(arquivo,"Pontos: %d\n", pilotos[i].corridas[j].pontos);
        }

        fprintf(arquivo,"\n------ DESEMPENHO ------\n");

        fprintf(arquivo,"Corridas disputadas: %d\n",pilotos[i].Qtdcorridas);
        fprintf(arquivo,"Pontos totais: %d\n",pontosTotais);
        fprintf(arquivo,"Melhor posicao: %d\n",melhorPos);
        fprintf(arquivo,"Maior velocidade: %.2f km/h\n",melhorVel);
        fprintf(arquivo,"Vitorias: %d\n",vitorias);
        fprintf(arquivo,"Podios: %d\n",podios);
        fprintf(arquivo,"Velocidade media da temporada: %.2f km/h\n",velocidadeTemporada);
    }

    fprintf(arquivo,"====== CLASSIFICACAO DO CAMPEONATO ======\n");//classificacão do campeonato

    for (int i = 0; i < 4; i++) {

        int indice = ordem[i];

        fprintf(arquivo,"%d lugar - %s | Numero: %d | Pontos: %d\n", i + 1, pilotos[indice].nome, pilotos[indice].numero, calcularPontosTotais(pilotos[indice]));
    }

    fprintf(arquivo,"LIDER DA TEMPORADA\n"); //Líder

    fprintf(arquivo,"Piloto: %s\n", pilotos[lider].nome);
    fprintf(arquivo,"Numero: %d\n", pilotos[lider].numero);
    fprintf(arquivo,"Pontos: %d\n", calcularPontosTotais(pilotos[lider]));
    fprintf(arquivo,"========================================\n");

    fclose(arquivo);

    printf("\nRelatorio salvo em relatorio_campeonato.txt!\n");
}

void salvarBinario(struct Piloto pilotos[4],int lider,int ordem[4]) {

    FILE *arquivo;

    arquivo = fopen("relatorio_final.dat", "wb"); //wb serve exclusivamente para escrita em binário

    if (arquivo == NULL) {

        printf("\nErro ao criar o arquivo binario!\n");

        return;
    }

    //Primeiro grava os 4 pilotos e todas as suas informacoes.
    fwrite(pilotos, sizeof(struct Piloto), 4, arquivo); //fwrite( endereço_dos_dados, tamanho_de_cada_elemento, quantidade_de_elementos, ponteiro_do_arquivo );

    //Depois grava a informacao do lider.
    fwrite(&lider, sizeof(int), 1, arquivo);

    //Depois grava a classificacao final.
    fwrite(ordem, sizeof(int), 4, arquivo);

    //Grava tambem os indicadores calculados de cada piloto.
    for (int i = 0; i < 4; i++) {

        int pontosTotais = calcularPontosTotais(pilotos[i]);
        int melhorPos = melhorposicao(pilotos[i]);
        float melhorVel = melhorvelocidade(pilotos[i]);
        int vitorias = contarVitorias(pilotos[i]);
        int podios = contarPodios(pilotos[i]);
        float velocidadeTemporada = calcularVelocidadeTemporada(pilotos[i]);

        fwrite(&pontosTotais, sizeof(int), 1, arquivo);
        fwrite(&melhorPos, sizeof(int), 1, arquivo);
        fwrite(&melhorVel, sizeof(float), 1, arquivo);
        fwrite(&vitorias, sizeof(int), 1, arquivo);
        fwrite(&podios, sizeof(int), 1, arquivo);
        fwrite(&velocidadeTemporada, sizeof(float), 1, arquivo);
    }

    fclose(arquivo);

    printf("\nRelatorio final salvo em relatorio_final.dat!\n");
}

int main() {

   struct Piloto pilotos[4];

   int lider = 0;
   
   for (int i = 0; i < 4; i++) {//cadastro dos pilotos

      printf("\n========== CADASTRO DO PILOTO %d ==========\n", i + 1);
      printf("Digite seu numero de competidor: ");
      scanf("%d", &pilotos[i].numero);
      printf("Digite seu nome: ");
      scanf("%s", pilotos[i].nome);
      printf("Qual sua nacionalidade: ");
      scanf("%s", pilotos[i].nacionalidade);

      // Cadastro da moto

      printf("\n====== CADASTRO DA MOTO ======\n");
      printf("Digite o fabricante da sua moto: ");
      scanf("%s", pilotos[i].moto.fabricante);
      printf("Digite o modelo da sua moto: ");
      scanf("%s", pilotos[i].moto.modelo);
      printf("Digite as cilindradas da sua moto: ");
      scanf("%d", &pilotos[i].moto.cilindrada);

      printf("\n====== QUANTIDADE DE CIRCUITOS ======\n");
      printf("Digite quantos circuitos o piloto irá participar: ");
      scanf("%d", &pilotos[i].Qtdcorridas);
      while(pilotos[i].Qtdcorridas > 6 || pilotos[i].Qtdcorridas < 1){
          printf("\nDigite quantos circuitos o piloto irá participar: ");
          scanf("%d", &pilotos[i].Qtdcorridas);
      }

      // Cadastro das corridas

      for (int j = 0; j < pilotos[i].Qtdcorridas; j++) {

        printf("\n====== CADASTRO DA CORRIDA %d ======\n", j + 1);
        printf("Digite a posicao: ");
        scanf("%d", &pilotos[i].corridas[j].posicao);
        printf("Digite o melhor tempo: ");
        scanf("%f", &pilotos[i].corridas[j].Melhortempo);
        printf("Digite a velocidade media: ");
        scanf("%f", &pilotos[i].corridas[j].Velocidademedia);   

        printf("Digite o nome do circuito: ");
        scanf("%s", pilotos[i].corridas[j].a1.nomec);
        printf("Digite o pais do circuito: ");
        scanf("%s", pilotos[i].corridas[j].a1.pais);
        printf("Digite os km da pista: ");
        scanf("%f", &pilotos[i].corridas[j].a1.km_pista);
        
        pilotos[i].corridas[j].pontos = calcularPontos(pilotos[i].corridas[j].posicao);

      }
   }

   salvarDados(pilotos); //Salva todos os dados dos pilotos em arquivo de texto

   // calculo das estatisticas

   for (int i = 0; i < 4; i++) {
        int pontosTotais = calcularPontosTotais(pilotos[i]);
        int melhorPos = melhorposicao(pilotos[i]);
        float melhorVel = melhorvelocidade(pilotos[i]);
        int vitorias = contarVitorias(pilotos[i]);
        int podios = contarPodios(pilotos[i]);
        float velocidadeTemporada = calcularVelocidadeTemporada(pilotos[i]);

        printf("\n======RELATORIO DO PILOTO======\n"); //Escreve esse relatório no terminal

        printf("Numero: %d\n", pilotos[i].numero);
        printf("Nome: %s\n", pilotos[i].nome);
        printf("Nacionalidade: %s\n", pilotos[i].nacionalidade);

        printf("\n------ MOTO ------\n");

        printf("Fabricante: %s\n",pilotos[i].moto.fabricante);
        printf("Modelo: %s\n",pilotos[i].moto.modelo);
        printf("Cilindrada: %d cc\n",pilotos[i].moto.cilindrada);

        // informacoes das corridas

        printf("\n------ CORRIDAS ------\n");

        for (int j = 0; j < pilotos[i].Qtdcorridas; j++) {
            printf("\nCorrida %d:\n", j + 1);
            printf("Circuito: %s\n",pilotos[i].corridas[j].a1.nomec);
            printf("Pais: %s\n",pilotos[i].corridas[j].a1.pais);
            printf("Km da pista: %.2f km\n",pilotos[i].corridas[j].a1.km_pista);
            printf("Posicao: %d\n",pilotos[i].corridas[j].posicao);
            printf("Melhor tempo: %.2f\n",pilotos[i].corridas[j].Melhortempo);
            printf("Velocidade media: %.2f km/h\n",pilotos[i].corridas[j].Velocidademedia);
            printf("Pontos: %d\n",pilotos[i].corridas[j].pontos);
        }

        // desempenho

        printf("\n------ DESEMPENHO ------\n");
        printf("Corridas disputadas: %d\n",pilotos[i].Qtdcorridas);
        printf("Pontos totais: %d\n",pontosTotais);
        printf("Melhor posicao: %d\n",melhorPos);
        printf("Maior velocidade: %.2f km/h\n",melhorVel);
        printf("Vitorias: %d\n",vitorias);
        printf("Podios: %d\n",podios);
        printf("Velocidade media da temporada: %.2f km/h\n",velocidadeTemporada);

   }

   // encontrar lider

   for (int i = 1; i < 4; i++) {
        if (calcularPontosTotais(pilotos[i]) >calcularPontosTotais(pilotos[lider])) {
            lider = i;
        }
   }

   // classificacao geral

   int ordem[4] = {0, 1, 2, 3};

   for (int i = 0; i < 3; i++) {
       for (int j = i + 1; j < 4; j++) {

           if (calcularPontosTotais(pilotos[ordem[j]]) > calcularPontosTotais(pilotos[ordem[i]])) {
               int temp = ordem[i];
               ordem[i] = ordem[j];
               ordem[j] = temp;
           }
       }
   }

   printf("\n======CLASSIFICACAO DO CAMPEONATO======\n");//Escreve a classificação e quem foi o líder no terminal

   for (int i = 0; i < 4; i++) {
       int indice = ordem[i];
       printf("%d lugar - %s | Numero: %d | Pontos: %d\n",
              i + 1,
              pilotos[indice].nome,
              pilotos[indice].numero,
              calcularPontosTotais(pilotos[indice]));

   }

   printf("LIDER DA TEMPORADA\n");
   printf("Piloto: %s\n",pilotos[lider].nome);
   printf("Numero: %d\n",pilotos[lider].numero);
   printf("Pontos: %d\n",calcularPontosTotais(pilotos[lider]));
   printf("========================================\n");

    salvarRelatorioTexto(pilotos, lider, ordem);
    salvarBinario(pilotos, lider, ordem);


    printf("\nCampeonato encerrado!\n");

    printf("\nArquivos gerados:\n");
    printf("- motogp.txt\n");
    printf("- relatorio_campeonato.txt\n");
    printf("- relatorio_final.dat\n");


   return 0;
}