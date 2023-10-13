ESTADO_FINAL = "ESTADO ACEPTADO"
ESTADO_NO_FINAL = "ESTADO NO ACEPTADO"
ESTADO_TRAMPA = "ESTADO TRAMPA"

def automata_mas(cadena):
	estado = 0
	estados_finales = [1]

	for caracter in cadena:
		if estado == 0 and caracter == "+":
			estado = 1
		else:
			estado = -1
			break

	if estado == -1:
		return ESTADO_TRAMPA
	if estado in estados_finales:
		return ESTADO_FINAL
	else:
		return ESTADO_NO_FINAL

assert automata_mas("+") == ESTADO_FINAL
assert automata_mas("") == ESTADO_NO_FINAL
assert automata_mas(";+") == ESTADO_TRAMPA