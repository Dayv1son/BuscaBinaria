#include <stdio.h>
#include <string.h>


typedef struct _Endereco Endereco;

// registroCEP = struct.Struct("72s72s72s72s2s8s2s")

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2]; // Ao Espaço no final da linha + quebra de linha
};

int main()
{
	
	FILE *f;
	Endereco e;
	
	f = fopen("cep_ordenado.dat","r");
	

	int inicio = 0;
	int meio;

	fseek(f,0,SEEK_END);
	int fim = ftell(f);
	fim = fim/sizeof(Endereco) -1;


	int tentativas = 0;
	int achei = 0;
	char procura[8]; 
	

	printf("Digite um cep: ");
	scanf("%s", procura);

	while(inicio <= fim){
		tentativas++;

		meio = (inicio+fim)/2;
		fseek(f, meio * sizeof(Endereco), SEEK_SET);
		fread(&e,sizeof(Endereco),1,f);
		
		
		if(strncmp(procura, e.cep, 8) == 0){
			achei = 1;
			inicio = fim + 1;
			printf("Achei o cep com %d tentativas\n", tentativas);
			printf("%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n",e.logradouro,e.bairro,e.cidade,e.uf,e.sigla,e.cep);
		}else if(strncmp(procura, e.cep, 8) > 0){
			inicio = meio + 1;
		}else if(strncmp(procura, e.cep, 8) < 0){
			fim = meio - 1;
		}
	}

	if(achei == 0){
		printf("Nao achei o cep digitado. Percorri um total de %d tentativas", tentativas);
	}
	fclose(f);
}

