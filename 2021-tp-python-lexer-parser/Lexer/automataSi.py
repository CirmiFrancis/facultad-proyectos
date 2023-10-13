ESTADO_FINAL = "ESTADO ACEPTADO"
ESTADO_NO_FINAL = "ESTADO NO ACEPTADO"
ESTADO_TRAMPA = "ESTADO TRAMPA"

def automata_si(cadena):
	estado = 0
	estados_finales = [2]

	for caracter in cadena:
		if estado == 0 and caracter == "s":
			estado = 1
		elif estado == 1 and caracter == "i":
			estado = 2
		else:
			estado = -1
			break

	if estado == -1:
		return ESTADO_TRAMPA
	if estado in estados_finales:
		return ESTADO_FINAL
	else:
		return ESTADO_NO_FINAL

assert automata_si("si") == ESTADO_FINAL
assert automata_si("s") == ESTADO_NO_FINAL
assert automata_si("sssssi") == ESTADO_TRAMPA