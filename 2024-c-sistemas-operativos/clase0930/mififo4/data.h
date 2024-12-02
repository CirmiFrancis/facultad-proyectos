#include <time.h>

typedef struct t_fecha {
	int dia;
	int mes;
	int anio;
} t_fecha;

typedef struct t_venta {
	t_fecha fecha;
	int sucursal; // 1 .. 10
	double monto;
} t_venta;

// genera numeros enteros pseudo-ramdom entre min y max, ambos inclusive
int irnd(int min,int max);
