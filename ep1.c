/*1º Exercício-programa de Cálculo Numérico 2018.1
Equipe:
-Andersson Cláudio
-Francisco Matheus
-Vinicius Morais
-Jardel Alves
-João Marcelo

*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <locale.h>

#define MARGEM 0.00000001
#define epsilon 0.000001
#define NLIN 16
#define NCOL 16

char mostraMenu();
int conversaoBinario(double valor);
int conversaoOctal(double valor);
int conversaoHexadecimal(double valor);
int lendoMatriz(double **matriz, double **resposta, int *tamanho);
void MostraMatriz(double **matriz, int tamanho);
int metodo_jordan(double **matriz, double *resposta, int tamanho);
int TrocaColuna(int index, double **matriz, double *resposta, int tamanho);
void zera_coluna(double **matriz, int index_coluna, int tamanho);
int verifica_sistema_compativel(double **matriz, int tamanho);
int resultado_jordan(double **matriz, double *resposta, int tamanho);



int main(){

	setlocale(LC_ALL, "Portuguese");
    double *matriz = NULL;
    double *resposta = NULL;
    int tamanho, i;
    char opcao;
    double decimal;

    do{
        opcao = mostraMenu();
        switch(opcao){
            case 'c':
                system("cls");

                printf("Digite o número que deseja converter: ");
                scanf("%lf", &decimal);

                conversaoBinario(decimal);
                conversaoOctal(decimal);
                conversaoHexadecimal(decimal);
                printf("\n");
                break;

            case 's':

            	system("cls");
				lendoMatriz(&matriz, &resposta, &tamanho);


                if(metodo_jordan(&matriz, resposta, tamanho)){
                	printf("\n");
                    for (i = 0;i<tamanho;i++)
                        printf("Var x%d = %.2lf\n",i+1,resposta[i]);
                }else{
                    printf("\n** Sistema Incompatível ** \n");
                }
                printf("\n");
                break;

            case 'e':
                break;

            case 'f':
                printf("\nAté mais!\n");
                break;

            default:
                printf("\nDigite uma opção válida!\n");
        }

        fflush(stdin);
    }while(opcao != 'f');

    return 0;
}

char mostraMenu(){
    char opcao;

    printf("Bem vindo ao programa-exercício.");
    printf("\nPor favor, digite a opção desejada:");
    printf("\nopção 1: Conversão (C);");
    printf("\nopção 2: Sistema Linear (S);");
    printf("\nopção 3: Equação Algébrica (E);");
    printf("\nopção 4: Finalizar (F).");
    printf("\nopção: ");
    scanf("%c", &opcao);
    opcao = tolower(opcao);

    return opcao;
}

int conversaoBinario(double valor)
{
    int contador = 0;
    double parteFracionaria;
    long int parteInteira;
	
	/*aloca uma lista para exibir os valores*/
	
    int *lista = malloc((sizeof(valor)*8) + 1);
    if(lista == NULL)
	{
        printf("Erro ao alocar memória!");
        return -1;
    }
	
	
    parteInteira = (int) valor;
    parteFracionaria = valor - parteInteira;

	/*converte a parte inteira*/
    while(parteInteira>0)
	{
        lista[contador] = (parteInteira % 2);
        parteInteira /= 2;
        contador++;
    }
	
	/*printa os valores ao contrario*/
	printf("Binário: ");
    for(--contador; contador>=0; contador--)
	{
        printf("%d", lista[contador]);
	}

	printf(",");

	/*converte a parte fracionária*/
    contador = 0;
    while(parteFracionaria >= MARGEM && contador < 20)
	{
        printf("%x", (int) fabs(parteFracionaria*2));
        parteFracionaria *= 2;
        parteFracionaria -= (int) (parteFracionaria);
        contador++;
    }

	printf("\n");
    free(lista);
    return 0;
}

int conversaoOctal(double valor)
{
    int contador = 0;
    double parteFracionaria;
    long int parteInteira;

    int *lista = malloc((sizeof(valor)*8) + 1);
    if(lista == NULL)
	{
        printf("Erro ao alocar memória!");
        return -1;
    }

    parteInteira = (int) valor;
    parteFracionaria = valor - parteInteira;
	
	/*converte a parte inteira*/
    while(parteInteira>0)
	{
        lista[contador] = (parteInteira % 8);
        parteInteira /= 8;
        contador++;
    }
	
	/*printa os valores ao contrario*/
	printf("Octal: ");
    for(--contador; contador>=0; contador--)
	{
        printf("%d", lista[contador]);
	}
    printf(",");
	
	/*converte a parte fracionária*/
    contador = 0;
    while(parteFracionaria >= MARGEM && contador < 20
	){
        printf("%x", (int) fabs(parteFracionaria*8));
        parteFracionaria *= 8;
        parteFracionaria -= (int) (parteFracionaria);
        contador++;
    }

	printf("\n");
    free(lista);
    return 0;
}

int conversaoHexadecimal(double valor)
{
    int aux = 0;
	int contador = 0;
    double parteFracionaria;
    long int parteInteira;

    int *lista = malloc((sizeof(valor)*8) + 1);
    if(lista == NULL)
	{
        printf("Erro ao alocar memória!");
        return -1;
    }

    parteInteira = (int) valor;
    parteFracionaria = valor - parteInteira;
	
	/*converte a parte inteira*/
    while(parteInteira>0)
	{
        lista[contador] = (parteInteira % 16);
        if(lista[contador] < 10)
        	lista[contador] += 48;
        else
        	lista[contador] += 55;
        parteInteira /= 16;
        contador++;
    }
	
	/*printa os valores ao contrario*/
	printf("Hexadecimal: ");
    for(--contador; contador>=0; contador--)
	{
		printf("%c", lista[contador]);
	}
    printf(".");
	
	/*converte a parte fracionária*/
    contador = 0;
    while(parteFracionaria >= MARGEM && contador < 20)
	{
        aux = (parteFracionaria * 16);
        if(aux < 10)
        	aux += 48;
        else
        	aux += 55;
		printf("%c", aux);
        parteFracionaria *= 16;
        parteFracionaria -= (int) (parteFracionaria);
        contador++;
    }A

	printf("\n");
    free(lista);
    return 0;
}

int lendoMatriz(double **matriz, double **resposta, int *tamanho){

	int  i, j;
	char nomedoArquivo[10];

	/* Pede o nome do arquivo que contém o sistema linear em forma de matriz */

	printf("Digite o nome do arquivo que possui o sistema linear: ");
	scanf("%s", &nomedoArquivo);

	/* Abre o arquivo */
    FILE *arquivo = fopen(nomedoArquivo, "r");

    /* Verifica se o arquivo está vazio*/

	if(arquivo == NULL)
        return 0;

    /*lê o tamanho da matriz*/
	fscanf(arquivo, "%d", tamanho);

    *matriz = malloc(sizeof(double * ) * (*tamanho));
    if ( matriz == NULL )
        return -1;

    for ( i = 0 ; i < (*tamanho) ; i++ ){
        matriz[i]  = (double *) malloc(sizeof(double) * ((*tamanho)+1));
        if ( matriz[i] == NULL )
            return -1;
    }

    for ( i = 0 ; i < (*tamanho) ; i++ ){
        for ( j = 0 ; j < ((*tamanho)+1) ; j++ ){
            fscanf (arquivo, "%lf", &matriz[i][j]);
        }
    }

    return carrega_resposta(resposta, *tamanho);

    }


int carrega_resposta(double **resposta, int tamanho){

    int i;
    *resposta =  malloc( sizeof(double) * tamanho );

    if (resposta == NULL)
        return -1;

    /* Inicializa indice com posição corresponde da matriz, para os swaps de coluna*/
    for (i = 0;i<tamanho;i++)
        (*resposta)[i] = (int)i;

    return 1;

}

void MostraMatriz(double **matriz, int tamanho){

    int i,j;
    for (i = 0;i<tamanho;i++){
        for (j = 0;j<tamanho+1;j++)
            printf("%.2lf ",matriz[i][j]);
        printf("\n");
    }
}

int metodo_jordan(double **matriz, double *resposta, int tamanho)
{
    int i,j,k;


    printf("\nMetodo de Jordan\n");
    printf("Matriz de %d linhas\n",tamanho);
    MostraMatriz(matriz, tamanho);
    printf("\n");


      /* Linhas */
    for (i = 0;i<tamanho;i++){
        double pivo = matriz[i][i];

        printf("\nPivo[%d][%d] = %lf \n",i,i,pivo);


        /* troca de Coluna se o pivo for 0*/
        if ( pivo == 0 ){
            if(TrocaColuna(i, matriz, resposta, tamanho))
                i--; /*Troca efetuada, repetir linha*/
            else{
                zera_coluna(matriz, i, tamanho);    /*Variavel livre, zerar coluna*/
            }
             continue;
        }

        /*Percorre linhas */
        for (k = 0; k<tamanho; k++) {
            /* Exceto a linha do pivo */
            if (k == i) continue;

            /* Valor a ser zerado na linha */
            double valorAlvo = matriz[k][i];

            /* Linha Auxiliar*/
            double *auxLinha = malloc( sizeof( double ) * ( tamanho + 1 ) );
            if (auxLinha == NULL) return -1;

            /* Preenche linha aux com valores a serem somados com os da linha atual*/
            for (j = 0;j<tamanho+1;j++)
                auxLinha[j] = matriz[i][j] * (valorAlvo/pivo);

            printf("Linha %d - (",k);
            for (j = 0;j<tamanho+1;j++)
                printf("%.2lf ",auxLinha[j]);
            printf(")\n");

            /* Subtrai auxLinha do valor da linha corrente da matriz*/
            for (j = 0;j<tamanho+1;j++)
                matriz[k][j] -= auxLinha[j];

            free(auxLinha);

            printf("Matriz\n");
            MostraMatriz(matriz, tamanho);

        }
    }

    /*Calcula resultado da matriz*/
    return resultado_jordan(matriz, resposta, tamanho);
}



int TrocaColuna(int index, double **matriz, double *resposta, int tamanho)
{
    int j,k,temp;
    /*k < j = n*/
    for ( j = index; j<tamanho ; j++ ){
        /*ak,j != 0*/
        if ( matriz[index][j] != 0 ){
            /* troca */
            for ( k = 0 ; k<tamanho ; k++ ){
                temp = matriz[k][index];
                matriz[k][index]= matriz[k][j];
                matriz[k][j] = temp;
            }


            printf("\nPivo igual a 0!\nTrocando coluna %d por %d\n",index,j);
            MostraMatriz(matriz, tamanho);
            printf("\n");


            /* faz troca do marcador de variaveis */
            temp = (int) resposta[index];
            resposta[index] = resposta[j];
            resposta[j] = temp;

            return 1;
        }
    }
    /*Variavel livre*/
    return 0;
}



void zera_coluna(double **matriz, int index_coluna, int tamanho){
	
	/*seta os valores da coluna index para zero*/
    int j;
    for (j=0; j<tamanho; j++) {
        matriz[j][index_coluna] = 0;
    }
}


int verifica_sistema_compativel(double **matriz, int tamanho){
	
	/*verifica se a matriz é incompativel se todos os termos de uma linha k for 0, menos o termo independente*/
    int i;
    for (i=0;i<tamanho;i++){
        if (matriz[i][i] == 0 && matriz[i][tamanho] != 0)
            return 0;
    }
    return 1;
}

int resultado_jordan(double **matriz, double *resposta, int tamanho){

    int i;
    int *indexAux = malloc(sizeof(int)*tamanho);
    if (indexAux == NULL)
        return -1;

    /*Recebe valor referente ao indice de cada posicao*/
    for (i=0; i<tamanho; i++)
        indexAux[i] = (int)resposta[i];


    if(verifica_sistema_compativel(matriz, tamanho)){
    	printf("\n");
        for (i=0; i<tamanho; i++) {
            if(matriz[indexAux[i]][indexAux[i]] != 0){
                resposta[indexAux[i]] = matriz[indexAux[i]][tamanho] / matriz[indexAux[i]][indexAux[i]];

                printf("x%d = %.2lf\n", indexAux[i], resposta[indexAux[i]]);
            }else{
                resposta[indexAux[i]] = 0;

                printf("x%d = Livre\n", indexAux[i]);

            }
        }
        free(indexAux);
        return 1;
    }

    free(indexAux);
    return 0;
}




