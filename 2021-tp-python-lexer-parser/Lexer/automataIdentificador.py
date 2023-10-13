ESTADO_FINAL = "ESTADO ACEPTADO"
ESTADO_NO_FINAL = "ESTADO NO ACEPTADO"
ESTADO_TRAMPA = "ESTADO TRAMPA"

def automata_identificador(cadena):
	estado = 0
	estados_finales = [1]

	for caracter in cadena:
		if estado == 0 and caracter.isalpha():
			estado = 1
		elif estado == 1 and caracter.isalnum():
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

assert automata_identificador("fdgdf45g") == ESTADO_FINAL
assert automata_identificador("") == ESTADO_NO_FINAL
assert automata_identificador("4as3") == ESTADO_TRAMPA