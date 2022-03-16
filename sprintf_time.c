#include <stdio.h>
#include <time.h>
#include <string.h>

//#define EJ_STRUCTS
#define EJ_SPRINTF_TIME

// Defino un tipo de variable estructura auto_t con sus respectivos miembros
typedef struct{
    char marca[50];
    int anio;
    float kilometraje;
} auto_t;

int main(void)
{
#ifdef EJ_STRUCTS
	auto_t auto1; // Declaro una variable del tipo auto_t
	/*
	Accedo a los miembros de la estructura con un punto y los opero igual que el tipo del
	variable que sean. Por ejemplo auto1.marca sera un puntero a la posicion inicial del vector,
	como para cualquier caso de declaración de vectores.
	*/
	strcpy(auto1.marca, "Ford Fiesta"); 
	auto1.anio = 2015;
	auto1.kilometraje = 12123.87;
	
	printf("%s %d %.2f", auto1.marca, auto1.anio, auto1.kilometraje);
#endif

#ifdef EJ_SPRINTF_TIME
	char tiempo[50];
	unsigned char index = 0;
	time_t rawtime; // Defino una variable time_t (time.h) que almacenera el tiempo POSIX. Tiene un tamaño de 8 bytes
	/* 
	Declaro un puntero a la struct tm cuyos miembros serán los días, horas, minutos, segundos, etc.
	https://www.cplusplus.com/reference/ctime/tm/?kw=struct%20tm
	Se declara un puntero ya que utilizando la funcion localtime(), se le asignará al mismo la dirección de memoria
	de una variable del tipo struct tm interna a la biblioteca time.h que contendrá todos los parámetros temporales
	*/
	struct tm * timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	
	/*
	Para acceder a los miembros de un puntero a una estructura se utiliza el operador ->.
	Es lo mismo que realizar la siguiente operacion: (*timeinfo).tm_mday = timeinfo -> tm_mday
	*/
	/*
	int sprintf ( char * str, const char * format, ... );
	sprintf escribirá sobre el string str lo que nosotros definamos con el formato del printf y devolverá
	la cantidad de caracteres escritos sobre el string, nos sirve para luego poder seguir escribiendo sobre 
	el mismo string desplazandonos este valor desde el puntero inicial para no sobreescribir.
	*/
	index += sprintf(tiempo, "%04d-%02d-%02d %02d:%02d:%02d", timeinfo -> tm_year + 1900, 
															  timeinfo -> tm_mon + 1, 
															  (*timeinfo).tm_mday,
															  timeinfo -> tm_hour, 
															  timeinfo -> tm_min, 
															  timeinfo -> tm_sec);		
    index += sprintf(tiempo + index, " Continuo Escribiendo");
	printf("%s", tiempo);
#endif
}