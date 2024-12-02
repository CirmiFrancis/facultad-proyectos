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
// mensaje para cola de mensaje de 1 registro de ventas
typedef struct msgbuf  {
	long tipo;     /* tipo de msj., debe ser > 0 */
	t_venta venta;
} mensaje;
// mensaje para cola de mensaje de 1 byte
typedef struct msgbuf2 {
	long tipo;     /* tipo de msj., debe ser > 0 */
	char car;
} mensaje1;
// mensaje para cola de mensaje de 12 bytes
typedef struct msgbuf3 {
	long tipo;     /* tipo de msj., debe ser > 0 */
	char msg[12];
} mensaje2;
// genera numeros enteros pseudo-ramdom entre min y max, ambos inclusive
int irnd(int min,int max);
