#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Funcion que calcula
long double fy(int i, int n, float h) {
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
	int n = 0;		//Divisiones
	long double suma = 0.0F;	//Suma total
	long double h2 = 0.0f;	//variable para H/2

	clock_t start = clock();	//INICIO contador tiempo

	n = 10000;

	//calculo de las divisiones
	h = 1.00F / n;

	//calcula H/2 que es el multiplicador
	h2 = h / 2.0F;

	for (size_t i = 0; i < n; i++)
	{
		suma += (fy(i, n, h) + fy(i + 1, n, h));
	}

	

	//Multiplicacion 4 cuatro para obtener aproximacion de (pi/4) a pi
	suma = suma*h2;
	suma = 4.0f*suma;
	printf("El resultado es: %.19Lf \n", suma);

	printf("Tiempo transcurrido: %f \n", ((double)clock() - start) / CLOCKS_PER_SEC);//muestra contador tiempo
	system("pause");		//pause para no cerrar ventana
	return 0;
}