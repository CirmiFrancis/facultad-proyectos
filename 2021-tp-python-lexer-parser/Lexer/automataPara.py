ESTADO_FINAL = "ESTADO ACEPTADO"
ESTADO_NO_FINAL = "ESTADO NO ACEPTADO"
ESTADO_TRAMPA = "ESTADO TRAMPA"

def automata_para(cadena):
	estado = 0
	estados_finales = [4]

	for caracter in cadena:
		if estado == 0 and caracter == "p":
			estado = 1
		elif estado == 1 and caracter == "a":
			estado = 2
		elif estado == 2 and caracter == "r":
			estado = 3
		elif estado == 3 and caracter == "a":
			estado = 4
		else:
			estado = -1
			break

	if estado == -1:
		return ESTADO_TRAMPA
	if estado in estados_finales:
		return ESTADO_FINAL
	else:
		return ESTADO_NO_FINAL

assert automata_para("para") == ESTADO_FINAL
assert automata_para("par") == ESTADO_NO_FINAL
assert automata_para("parra") == ESTADO_TRAMPA