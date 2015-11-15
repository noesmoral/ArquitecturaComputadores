#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <iomanip>
#include <math.h>

using namespace std;

float cuadrado = 0.0F;

//Funcion que calcula
float fy(int i, int n, float h) {
	if (i==0)
	{	
		return 1.0F;
	}
	if (i==(int)n)
	{
		return 0.5F;
	}
	else
	{
		cuadrado = (float)i*h;
		cuadrado = pow(cuadrado, 2);
		return 2*(1.0F/(1.0F+cuadrado));
	}	
}

int main(int argc, char *argv[]) {

	//19 decimales
	cout.setf(ios::fixed);
	cout.precision(19);

	float h= 0.0F;		//Anchura
	float n= 0.0F;		//Divisiones
	float suma = 0.0F;	//Suma total
	float h2 = 0.0f;	//variable para H/2

	clock_t start = clock();	//INICIO contador tiempo

	cout << "Inserte el numero de divisiones con el formato 0.0" << endl;
	cin >> n;
	n = (float)n;

	//calculo de las divisiones
	h = 1.00F / n;

	//calcula H/2 que es el multiplicador
	h2 = h / 2.0F;

	for (size_t i = 0; i < n+1; i++)
	{
		/*suma = suma + (fy(i, n, h));*/
		suma=suma+fy(i, n, h);
	}

	//Multiplicacion del h2
	suma = h2*suma;

	//Multiplicacion 4 cuatro para obtener aproximacion de (pi/4) a pi
	cout << "Resultado" << endl;
	suma = 4.0f*suma;
	cout << suma << endl;

	printf("Tiempo transcurrido: %f", ((double)clock() - start) / CLOCKS_PER_SEC);//muestra contador tiempo
	cout << endl;
	system("pause");		//pause para no cerrar ventana
	return 0;
}

//No funciona bien fallo al aproximarse posible acausa la conversion cast de algunos de los datos