#include <stdio.h>
#include <string.h>

#define EJ_REFERENCIA
//#define EJ_MEM_CPY
//#define EJ_MEM_CMP
//#define EJ_MEM_SET

#ifdef EJ_REFERENCIA
// Paso un puntero para poder recibir un vector y operarlo
void funcion(int* a, int largo)
{
    for(int i = 0; i < largo; i++)
	    a[i] += 5;
}
#endif

int main(void)
{
	#ifdef EJ_REFERENCIA
	int a[5] = {1,2,3,4,5};
	printf("A original: ");
	for(int i = 0; i < sizeof(a) / sizeof(int); i++)
		printf("%d ", a[i]);
	funcion(a, sizeof(a) / sizeof(int));
	printf("\nA modificado: ");
	for(int i = 0; i < sizeof(a) / sizeof(int); i++)
		printf("%d ", a[i]);
	#endif
	
	#ifdef EJ_MEM_CPY
	int a[5] = {1,2,3,4,5};
	int b[5] = {6,7,8,9,10};
	/*
	Para encontrar el tamaño del vector puedo utilizar la funcion sizeof,
	la cual devolverá el valor total en memoria ocupado por el vector. Entonces,
	para obtener la cantidad neta de elementos, divido por el tamaño del tipo de 
	la variable que sea el vector.
	*/
	printf("A original: ");
	for(int i = 0; i < sizeof(a) / sizeof(int); i++)
		printf("%d ", a[i]);
	printf("\nB original: ");
	for(int i = 0; i < sizeof(b) / sizeof(int); i++)
		printf("%d ", b[i]);
	
	// void * memcpy ( void * destination, const void * source, size_t num );
	// memcpy copia num posiciones de memoria desde el puntero source a destination
	memcpy(b, a, sizeof(a)); // Copio a en b y utilizo sizeof para el tamaño total,

	printf("\nB modificado: ");
	for(int i = 0; i < sizeof(b) / sizeof(int); i++)
		printf("%d ", b[i]);
	#endif
	
	#ifdef EJ_MEM_CMP
	int a[5] = {1,2,3,4,5};
	int b[5] = {6,7,8,9,10};
	int c[5] = {1,2,3,4,5};
	
	// int memcmp ( const void * ptr1, const void * ptr2, size_t num );
	/*
	memcmp compara posicion por posicion si los contenidos son iguales y devuelve:
	0: contenidos iguales
	!0: contenidos distintos
	
	Si quiero comparar solo n posiciones:
	n * sizeof(tipo);
	
	*/
	if(!memcmp(a, b, sizeof(a))) // memcmp(a, b, sizeof(a)) == 0
		printf("a y b tienen el mismo contenido\n");
	else
		printf("a y b no tienen el mismo contenido\n");
	
	if(!memcmp(a, c, sizeof(a)))
		printf("a y c tienen el mismo contenido\n");
	else
		printf("a y c no tienen el mismo contenido\n");
	#endif
	
	#ifdef EJ_MEM_SET
	int a[5] = {1,2,3,4,5};
	printf("A original: ");
	for(int i = 0; i < sizeof(a) / sizeof(int); i++)
		printf("%d ", a[i]);
	
	//void * memset ( void * ptr, int value, size_t num );
	// Defino un valor en num posiciones de memoria desde ptr
	memset(a, 0, sizeof(a));
	/*
		OJO
		Setea el valor en TODAS las posiciones de memoria, entonces no puedo definir
		valores para variables de mas de 1 byte porque tendría mas de un byte de la variable
		en x valor.
	*/
	printf("A modificado: \n");
	for(int i = 0; i < sizeof(a) / sizeof(int); i++)
		printf("%d ", a[i]);
	#endif
}