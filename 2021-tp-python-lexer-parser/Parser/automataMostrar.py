ESTADO_FINAL = "ESTADO ACEPTADO"
ESTADO_NO_FINAL = "ESTADO NO ACEPTADO"
ESTADO_TRAMPA = "ESTADO TRAMPA"

def automata_mostrar(cadena):
	estado = 0
	estados_finales = [7]

	for caracter in cadena:
		if estado == 0 and caracter == "m":
			estado = 1
		elif estado == 1 and caracter == "o":
			estado = 2
		elif estado == 2 and caracter == "s":
			estado = 3
		elif estado == 3 and caracter == "t":
			estado = 4
		elif estado == 4 and caracter == "r":
			estado = 5
		elif estado == 5 and caracter == "a":
			estado = 6
		elif estado == 6 and caracter == "r":
			estado = 7
		else:
			estado = -1
			break

	if estado == -1:
		return ESTADO_TRAMPA
	if estado in estados_finales:
		return ESTADO_FINAL
	else:
		return ESTADO_NO_FINAL

assert automata_mostrar("mostrar") == ESTADO_FINAL
assert automata_mostrar("mos") == ESTADO_NO_FINAL
assert automata_mostrar("mossstrar") == ESTADO_TRAMPA