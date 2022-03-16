#include <stdio.h>
#include <string.h>

//#define EJ_STRINGS_1
//#define EJ_STRNCPY
#define EJ_STRCHR

int main(void)
{
	#ifdef EJ_STRINGS_1
	// El string consiste de una cadena de caracteres (char o unsigned char)
	char a[10] = "Hola";
	// Todos los strings serán terminados con el caracter de terminacion '\0'
	// strlen(char* a) devuelve el largo de un string
	printf("String -> %s\n", a); // Puedo usar %s para imprimir un string directo
	printf("Caracter de terminacion -> %d", a[strlen(a) + 1]);
	
	#endif
	
	#ifdef EJ_STRNCPY
	char a[10] = "Hola";
	char b[10];
	//char * strcpy ( char * destination, const char * source );
	//char * strncpy ( char * destination, const char * source, size_t num );
	/*
	strncpy copiará num elementos del string de origen al destino, si num es mayor
	al largo del vector, copiará solo el largo del vector. Siempre controlar no copiar
	más caracteres que el tamaño.
	*/
	strncpy(b, a, 8);
	printf("A: %s\nB: %s", a, b);
	#endif
	
	#ifdef EJ_STRCHR
	char a[50] = "Hola como estan";
	// char * strchr ( char * str, int character );
	/*
	La funcion devolverá un puntero a la primera posición en la que encuentre el
	caracter pedido
	*/
	char* b = strchr(a, 's');
	printf("String A: %s", a);
	printf("\nPosicion 's': %lu , %c", b - a, *b);
	#endif
}