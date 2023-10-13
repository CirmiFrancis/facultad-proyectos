ESTADO_FINAL = "ESTADO ACEPTADO"
ESTADO_NO_FINAL = "ESTADO NO ACEPTADO"
ESTADO_TRAMPA = "ESTADO TRAMPA"

def automata_constante(cadena):
	estado = 0
	estados_finales = [2]

	for caracter in cadena:
		if estado == 0 and caracter == "-": 
			estado = 1
		elif estado == 0 and caracter.isnumeric():
			estado = 2
		elif estado == 1 and (caracter.isdigit() and int(caracter) in range(1,10)):
			estado = 2	
		elif estado == 2 and caracter.isnumeric():
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

assert automata_constante("36") == ESTADO_FINAL
assert automata_constante("-10") == ESTADO_FINAL
assert automata_constante("-") == ESTADO_NO_FINAL
assert automata_constante("-0") == ESTADO_TRAMPA
assert automata_constante("98a") == ESTADO_TRAMPA
assert automata_constante("a3") == ESTADO_TRAMPA