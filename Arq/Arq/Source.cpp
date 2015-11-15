#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <iomanip>

using namespace std;


//Funcion que calcula
float fy(int y, int n, float h) {
	if (y==0)
	{	
		return 1.0F;
	}
	if (y==(int)n)
	{
		return 0.0F;
	}
	else
	{
		return (float)y*h;
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

	//calculo de las divisiones
	h = 1.00F / n;

	//calcula H/2
	h2 = h / 2.0f;


	for (size_t i = 1; i < n-1; i++)
	{
		suma = suma + (h / 2)*(fy(i-1,n,h) + 2 * fy(i, n, h) + fy(i+1, n, h));
		//suma=suma+h2+(fy(i, n, h) + fy(i+1, n, h));
	}

	cout << "Resultado" << endl;
	suma = 4.0f*suma;
	cout << suma << endl;

	printf("Tiempo transcurrido: %f", ((double)clock() - start) / CLOCKS_PER_SEC);//muestra contador tiempo
	system("pause");		//pause para no cerrar ventana
	return 0;
}