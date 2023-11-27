#include <stdio.h>
#include <string.h>

void rm_value(char *str, char character)
{
	char	*found;
	
	found = strchr(str, character);
	if (found != NULL)
		*found = '\0';
}

int main()
{
	char texto[] = "Esto es una prueba=Eliminar desde el guion";
	char caracter = '=';
	
	printf("Texto original: %s\n", texto);
	
	strchr(texto, caracter);
	rm_value(texto, caracter);
	
	printf("Texto modificado: %s\n", texto);
	
	return 0;
}