#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
void listado(char list[], char ruta[]);
int contadorArchivos(void);
void parseador(char ruta[], int n_archivos);

int main()
{
	int n_archivos = 0;
	char ruta[200], list[200];

	printf("Indica la ruta completa donde se encuentran los archivos a parsear:\n");
	gets(ruta);
	ruta[strlen(ruta)] = 92;

	listado(list, ruta);
	n_archivos = contadorArchivos();
	printf("En dicha ruta hay %d archivos.\n", n_archivos);
	system("pause");
	system("cls");
	printf("Parseando, por favor espera... ");
	parseador(ruta, n_archivos);
	printf("OK\nTodos los archivos han sido parseados correctamente\n");
	system("del archivos.txt");
	return 0;
}

void listado(char list[], char ruta[]) {
	strcpy(list, "dir /b \"");
	strcat(list, ruta);
	strcat(list, "\" > archivos.txt");
	system(list);
}

int contadorArchivos() {

	int cont = 0;
	char ch;
	FILE *archivos;
	archivos = fopen("archivos.txt", "rt");
	while ((ch = fgetc(archivos)) != EOF)
		if (ch == '\n')
			cont++;
	fclose(archivos);
	return cont;
}

void parseador(char ruta[], int n_archivos) {
	FILE *listado;
	char nombre[100], nombreCorregido[100], ren[200];
	int i, j, k;
	listado = fopen("archivos.txt", "rt");

	for (i = 0; i < n_archivos; i++) {
		j = -1;
		do {
			j++;
			nombre[j] = fgetc(listado);
		} while (nombre[j] != '\n');
		nombre[j] = 0;
		for (j = 0; nombre[j] != '_'; j++) {
			if (nombre[j]==0) break;
			nombreCorregido[j] = nombre[j];
		}
		nombreCorregido[j] = ' ';
		for (k = j + 10; nombre[k] != 0; k++) {
			nombreCorregido[j] = nombre[k];
			j++;
		}
		nombreCorregido[j] = 0;
		strcpy(ren, "rename ");
		strcat(ren, "\"");
		strcat(ren, ruta);
		strcat(ren, nombre);
		strcat(ren, "\"");
		strcat(ren, " ");
		strcat(ren, "\"");
		strcat(ren, nombreCorregido);
		strcat(ren, "\"");
		system(ren);
		printf("%s\n", ren);
		for (j = 0; j < 100; j++) {
			nombreCorregido[j] = 0;
			nombre[j] = 0;
		}
		for (j = 0; j < 200; j++)
			ren[j] = 0;
	}
	fclose(listado);

}