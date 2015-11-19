#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define n 10000	//Definicion del numero de divisiones
#define nh 1	//numero de hebras

//Funcion que calcula
long double fy(int i, float h) {
	if (i == 0)
	{
		return 1.0F;
	}
	if (i == (int)n)
	{
		return 0.5F;
	}
	else
	{
		return (long double)(1.0 / (1 + (i*h)*(i*h)));
	}
}

int main(int argc, char *argv[]) {

	long double h = 0.0F;		//Anchura
	int i = 0, nb = 0;			//Divisiones
	long double suma = 0.0F;	//Suma total
	long double h2 = 0.0f;		//variable para H/2

	clock_t start = clock();	//INICIO contador tiempo

								//calculo de las divisiones
	h = 1.00F / n;

	//calulo del numero de bloques por hebra
	nb = n / nh;

	//calcula H/2 que es el multiplicador
	h2 = h / 2.0F;

	//Bucle que realiza las sumas
	for (i = 0; i < n; i++)
	{
		suma += (fy(i, h) + fy(i + 1, h));
	}

	//Multiplicacion 4 cuatro para obtener aproximacion de (pi/4) a pi
	suma = suma*h2;
	suma = 4.0f*suma;
	printf("El resultado es: %.19Lf \n", suma);

	printf("Tiempo transcurrido: %f \n", ((double)clock() - start) / CLOCKS_PER_SEC);//muestra contador tiempo
	system("pause");
	return 0;
}

/* Para el paralelismo la idea es que cada una de las hebras realiza un pedazo del codigo individual(aunque no es el mejor metodo) y despues de eso que guarden de forma ordenada(mutex) en el contador total y terminen, una vez terminados todos el principal hace la multiplicacion y muestra el resultado*/
