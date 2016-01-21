#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define BUFSIZE 128			//Informacion y parametros para las entradas y las llamadas MPI
#define TAG 0
#define INTERVALO 5.0			//Valor del intervalo 
#define ValorPi 3.14159265358979323846	//Valor real de pi hasta el decimal 20

/*Realizacion de la integra para cada uno de los procesos en el rango establecido*/
double Trap(int mi_rango, int local_n, double h, int n) {
	double integral=0.0; 	// Para almacenar el resultado
	double exp1=0.0;		
	double return_val=0.0;
	double x = 0.0;	 	//Variables para los calculos
	double y = 0.0;
	int i;			//variable del bucle
	int j;
		
	for(i=local_n*mi_rango;i<local_n*(mi_rango+1);i++){
		x=(-INTERVALO+(i*h));
		for(j=0;j<n;j++){
			y=(-INTERVALO+(j*h));
			exp1 = -((x*x+y*y)/2);
			return_val = (h*h)*pow(M_E,exp1);
			integral = integral + return_val;
		}
	}
	return integral;
}

//funcion para calcular los parametros para cada uno de los procesos
double calcula(int mi_rango, int numprocs) {

	double b= INTERVALO; /* Extremos de la integracion */
	int n = 100; /* Numero de divisiones */
	double h; /* Base de cada trapecio */
	int local_n; /* Numero de trapecios para mi calculo */
	double integral; /* Resultado de la integral en mi intervalo */

	/* Obtener siguiente numero a comprobar */
	h = (2*b)/n; /* h es el mismo para todos los procesos, es el ancho de cada division*/

	local_n = n/numprocs; /* numero de intervalos para cada uno */

	/* Calculo la integral pasando el numero del que lo realiza el numero de intervalos  anchura y numero de divisiones para el alto*/
	integral = Trap(mi_rango, local_n, h, n);

	/*Impresion de la informacion del calculo de cada uno de los procesos y su resultado*/
	printf("Integral del %d es = %f\n", mi_rango, integral);

	return integral;
}

/*Programa principal*/
int main(int argc, char *argv[]) {

	int mi_rango = 0;
	int numprocs = 0;
	double total_parcial = 0.0;
	double total = 0.0;
	double tmpinic = 0.0;
	double tmpfin = 0.0;

	/*Obtencion de la informacion de cada uno*/
	MPI_Init(&argc, &argv); /* todos los programas MPI comienzan con MPI_Init; los 'N' procesos comienzan tras él */
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs); /* averigua como de grande es la palabra SPMD */
	MPI_Comm_rank(MPI_COMM_WORLD, &mi_rango); /* y los rangos del proceso */

	/* indicamos si es la maquina cero y cogemos tiempo actual */
	if (mi_rango==0) {
		fprintf(stdout,"Procesando...\n");
		tmpinic=MPI_Wtime();	//Inicializamos el contador global con 0 que es el primero en empezar
	}
	
	//Calculamos el valor de la integra para cada uno
	total_parcial = calcula(mi_rango,numprocs);

	//Usamos el MPI_Reduce para recolectar la infomracion cuando hemos terminado de operar
	MPI_Reduce(&total_parcial, &total, 1, MPI_DOUBLE, MPI_SUM, TAG, MPI_COMM_WORLD);

	//Si soy el 0 Imprimo el valor de la cuenta total
	if (mi_rango == 0){
		//Impresion de la informacion del calculo y la diferencia
		printf("Suma TOTAL es: %.20lf\n", total);
		printf("Error cometido en la resolucion numerica: %.20lf\n", total-(2*ValorPi));
		//Calculamos el tiempo final y lo imprimomos
		tmpfin=MPI_Wtime();
		printf("%.48lf Tiempo total en segundos para realizar el calculo.\n", tmpfin-tmpinic);
	}
	printf("\n");
	/*Finalizamos todos los MPI para evitar errores*/
	MPI_Finalize();
	return 0;
}
