#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
	if(argc != 2){
		fprintf(stderr, "Numero errado de argumentos");
		return 1;
	}

	char *filename = argv[1];
	FILE *fp = fopen(filename, "r");
	if(fp == NULL){
		fprintf(stderr, "Falha ao abrir o arquivo");
		return 1;
	}

	printf("uhu");

	return 0;
}
