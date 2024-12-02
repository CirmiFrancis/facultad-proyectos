// mensaje para cola de mensaje de 64 bytes maximo para chat
typedef struct msgbuf {
	long tipo;     /* tipo de msj., debe ser > 0 */
	char msg[64];
} mensaje;
