ESTADO_FINAL = "ESTADO ACEPTADO"
ESTADO_NO_FINAL = "ESTADO NO ACEPTADO"
ESTADO_TRAMPA = "ESTADO TRAMPA"

def automata_entonces(cadena):
	estado = 0
	estados_finales = [8]

	for caracter in cadena:
		if estado == 0 and caracter == "e":
			estado = 1
		elif estado == 1 and caracter == "n":
			estado = 2
		elif estado == 2 and caracter == "t":
			estado = 3
		elif estado == 3 and caracter == "o":
			estado = 4
		elif estado == 4 and caracter == "n":
			estado = 5
		elif estado == 5 and caracter == "c":
			estado = 6
		elif estado == 6 and caracter == "e":
			estado = 7
		elif estado == 7 and caracter == "s":
			estado = 8
		else:
			estado = -1
			break

	if estado == -1:
		return ESTADO_TRAMPA
	if estado in estados_finales:
		return ESTADO_FINAL
	else:
		return ESTADO_NO_FINAL

assert automata_entonces("entonces") == ESTADO_FINAL
assert automata_entonces("enton") == ESTADO_NO_FINAL
assert automata_entonces("entnnces") == ESTADO_TRAMPA