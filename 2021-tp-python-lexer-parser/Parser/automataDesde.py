ESTADO_FINAL = "ESTADO ACEPTADO"
ESTADO_NO_FINAL = "ESTADO NO ACEPTADO"
ESTADO_TRAMPA = "ESTADO TRAMPA"

def automata_desde(cadena):
	estado = 0
	estados_finales = [5]

	for caracter in cadena:
		if estado == 0 and caracter == "d":
			estado = 1
		elif estado == 1 and caracter == "e":
			estado = 2
		elif estado == 2 and caracter == "s":
			estado = 3
		elif estado == 3 and caracter == "d":
			estado = 4
		elif estado == 4 and caracter == "e":
			estado = 5
		else:
			estado = -1
			break

	if estado == -1:
		return ESTADO_TRAMPA 
	if estado in estados_finales:
		return ESTADO_FINAL 
	else:
		return ESTADO_NO_FINAL 

assert automata_desde("desde") == ESTADO_FINAL
assert automata_desde("desd") == ESTADO_NO_FINAL
assert automata_desde("desdee") == ESTADO_TRAMPA