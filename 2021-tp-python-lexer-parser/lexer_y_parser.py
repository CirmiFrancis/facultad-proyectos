#------------------------------------------------------------------------------------AUTOMATAS------------------------------------------------------------------------------------

ESTADO_FINAL = "ESTADO ACEPTADO"
ESTADO_NO_FINAL = "ESTADO NO ACEPTADO"
ESTADO_TRAMPA = "ESTADO TRAMPA"

def automata_aceptar(cadena):
	estado = 0
	estados_finales = [7]

	for caracter in cadena:
		if estado == 0 and caracter == "a":
			estado = 1
		elif estado == 1 and caracter == "c":
			estado = 2
		elif estado == 2 and caracter == "e":
			estado = 3
		elif estado == 3 and caracter == "p":
			estado = 4
		elif estado == 4 and caracter == "t":
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

assert automata_aceptar("aceptar") == ESTADO_FINAL
assert automata_aceptar("acep") == ESTADO_NO_FINAL
assert automata_aceptar("aceptr") == ESTADO_TRAMPA

#---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

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

#---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

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

#---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

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

#---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ESTADO_FINAL = "ESTADO ACEPTADO"
ESTADO_NO_FINAL = "ESTADO NO ACEPTADO"
ESTADO_TRAMPA = "ESTADO TRAMPA"

def automata_hasta(cadena):
	estado = 0
	estados_finales = [5]

	for caracter in cadena:
		if estado == 0 and caracter == "h":
			estado = 1
		elif estado == 1 and caracter == "a":
			estado = 2
		elif estado == 2 and caracter == "s":
			estado = 3
		elif estado == 3 and caracter == "t":
			estado = 4
		elif estado == 4 and caracter == "a":
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

assert automata_hasta("hasta") == ESTADO_FINAL
assert automata_hasta("has") == ESTADO_NO_FINAL
assert automata_hasta("hastta") == ESTADO_TRAMPA

#---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

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

#---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ESTADO_FINAL = "ESTADO ACEPTADO"
ESTADO_NO_FINAL = "ESTADO NO ACEPTADO"
ESTADO_TRAMPA = "ESTADO TRAMPA"

def automata_igual(cadena):
	estado = 0
	estados_finales = [1]

	for caracter in cadena:
		if estado == 0 and caracter == "=":
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

assert automata_igual("=") == ESTADO_FINAL
assert automata_igual("") == ESTADO_NO_FINAL
assert automata_igual("==") == ESTADO_TRAMPA

#---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ESTADO_FINAL = "ESTADO ACEPTADO"
ESTADO_NO_FINAL = "ESTADO NO ACEPTADO"
ESTADO_TRAMPA = "ESTADO TRAMPA"

def automata_llaveAbrir(cadena):
	estado = 0
	estados_finales = [1]

	for caracter in cadena:
		if estado == 0 and caracter == "{":
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

assert automata_llaveAbrir("{") == ESTADO_FINAL
assert automata_llaveAbrir("") == ESTADO_NO_FINAL
assert automata_llaveAbrir("a{") == ESTADO_TRAMPA

#---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ESTADO_FINAL = "ESTADO ACEPTADO"
ESTADO_NO_FINAL = "ESTADO NO ACEPTADO"
ESTADO_TRAMPA = "ESTADO TRAMPA"

def automata_llaveCerrar(cadena):
	estado = 0
	estados_finales = [1]

	for caracter in cadena:
		if estado == 0 and caracter == "}":
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

assert automata_llaveCerrar("}") == ESTADO_FINAL
assert automata_llaveCerrar("") == ESTADO_NO_FINAL
assert automata_llaveCerrar("}a") == ESTADO_TRAMPA

#---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

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

#---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

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

#---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

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

#---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ESTADO_FINAL = "ESTADO ACEPTADO"
ESTADO_NO_FINAL = "ESTADO NO ACEPTADO"
ESTADO_TRAMPA = "ESTADO TRAMPA"

def automata_parentesisAbrir(cadena):
	estado = 0
	estados_finales = [1]

	for caracter in cadena:
		if estado == 0 and caracter == "(":
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

assert automata_parentesisAbrir("(") == ESTADO_FINAL
assert automata_parentesisAbrir("") == ESTADO_NO_FINAL
assert automata_parentesisAbrir("k(") == ESTADO_TRAMPA

#---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ESTADO_FINAL = "ESTADO ACEPTADO"
ESTADO_NO_FINAL = "ESTADO NO ACEPTADO"
ESTADO_TRAMPA = "ESTADO TRAMPA"

def automata_parentesisCerrar(cadena):
	estado = 0
	estados_finales = [1]

	for caracter in cadena:
		if estado == 0 and caracter == ")":
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

assert automata_parentesisCerrar(")") == ESTADO_FINAL
assert automata_parentesisCerrar("") == ESTADO_NO_FINAL
assert automata_parentesisCerrar("()") == ESTADO_TRAMPA

#---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ESTADO_FINAL = "ESTADO ACEPTADO"
ESTADO_NO_FINAL = "ESTADO NO ACEPTADO"
ESTADO_TRAMPA = "ESTADO TRAMPA"

def automata_por(cadena):
	estado = 0
	estados_finales = [1]

	for caracter in cadena:
		if estado == 0 and caracter == "*":
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

assert automata_por("*") == ESTADO_FINAL
assert automata_por("") == ESTADO_NO_FINAL
assert automata_por("***") == ESTADO_TRAMPA

#---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ESTADO_FINAL = "ESTADO ACEPTADO"
ESTADO_NO_FINAL = "ESTADO NO ACEPTADO"
ESTADO_TRAMPA = "ESTADO TRAMPA"

def automata_puntoComa(cadena):
	estado = 0
	estados_finales = [1]

	for caracter in cadena:
		if estado == 0 and caracter == ";":
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

assert automata_puntoComa(";") == ESTADO_FINAL
assert automata_puntoComa("") == ESTADO_NO_FINAL
assert automata_puntoComa(".;") == ESTADO_TRAMPA

#---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

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

#---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ESTADO_FINAL = "ESTADO ACEPTADO"
ESTADO_NO_FINAL = "ESTADO NO ACEPTADO"
ESTADO_TRAMPA = "ESTADO TRAMPA"

def automata_sino(cadena):
	estado = 0
	estados_finales = [4]

	for caracter in cadena:
		if estado == 0 and caracter == "s":
			estado = 1
		elif estado == 1 and caracter == "i":
			estado = 2
		elif estado == 2 and caracter == "n":
			estado = 3
		elif estado == 3 and caracter == "o":
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

assert automata_sino("sino") == ESTADO_FINAL
assert automata_sino("sin") == ESTADO_NO_FINAL
assert automata_sino("siño") == ESTADO_TRAMPA

#------------------------------------------------------------------------------------LEXER------------------------------------------------------------------------------------

ESTADO_FINAL = "ESTADO ACEPTADO"
ESTADO_NO_FINAL = "ESTADO NO ACEPTADO"
ESTADO_TRAMPA = "ESTADO TRAMPA"

TOKENS_POSIBLES = [
  ("aceptar", automata_aceptar),
  ("cte", automata_constante),
  ("desde", automata_desde),
  ("entonces", automata_entonces),
  ("hasta", automata_hasta),
  ("=", automata_igual),
  ("{", automata_llaveAbrir),
  ("}", automata_llaveCerrar),
  ("+", automata_mas),
  ("mostrar", automata_mostrar),
  ("para", automata_para),
  ("(", automata_parentesisAbrir),
  (")", automata_parentesisCerrar),
  ("*", automata_por),
  (";", automata_puntoComa),
  ("si", automata_si),
  ("sino", automata_sino),
  ("id", automata_identificador)]

def calcCandidates(source): #funcion "calcular candidatos" que recibe una cadena de caracteres y devuelve una tupla con un booleano y el tipo_token. EJEMPLO: "calcCandidates("hola")", devuelve "(False, 'id')"

  allTrapped = True #variable "todos atrapados" asignada por defecto con un booleano, en este caso, True. Hace referencia al estado trampa
  candidates = [] #variable tipo lista de "candidatos" que guarda el tipo_token de la cadena de caracteres (si es que algun automata lo acepta)

  for (token_kind, automata) in TOKENS_POSIBLES: #para todos los "(tipo_token, automata_x)" en la lista "tokens_posibles"
    result = automata(source) #a la variable "result" se le asigna un automata con la cadena de caracteres que se ingreso al principio

    if result == ESTADO_FINAL: #si ese automata acepta la cadena, "estado aceptado"
      allTrapped = False #la variable "todos atrapados" es Falsa
      candidates.append(token_kind) #adjunta a la lista "candidatos" el tipo_token de la cadena
      
    if result == ESTADO_NO_FINAL: #si ese automata NO acepta la cadena, "estado no aceptado"
      allTrapped = False #la variable "todos atrapados" es Falsa

  if len(candidates) == 0: #teniendo en cuenta que esto esta fuera del ciclo, si la longitud de "candidatos" es igual a 0, significa que la cadena no es aceptada por ningun automata...
    return (allTrapped, []) #...por lo tanto, devuelve el booleano False (variable "todos atrapados") y la lista vacía
  else: #de lo contrario
    return (allTrapped, candidates[0]) #devuelve el booleano True (variable "todos atrapados") y el primer elemento de la lista "candidatos" (el tipo_token de la cadena)

assert calcCandidates("hola") == (False, 'id')
assert calcCandidates("3") == (False, 'cte')
assert calcCandidates(" ") == (True, [])
assert calcCandidates(".") == (True, [])
assert calcCandidates("") == (False, []) #Funciona diferente, no se ingresa ninguna cadena y no se lo toma como estado trampa

'''
Función "Principal" del LEXER: 
  Recibe un STRING como INPUT y devuelve una LISTA DE TUPLAS,
  Cada TUPLA se llama "TOKEN",
    El primer elemento del TOKEN es el TIPO DE TOKEN, 
    El segundo elemento del TOKEN es el LEXEME.

El LEXEME es una palabra que está contenida en el INPUT,
El TIPO DE TOKEN es la clasificación que le corresponde a esa palabra según la gramática dada.
'''

def lexer(source):
  source += " " #variable "source" que contiene...
  index = 0 #variable "indice" que contiene la posicion del caracter de la cadena al que se apunta
  tokens = [] #variable tipo lista de "tokens" que contiene...

  while index < len(source): #mientras "indice" sea MENOR a la longitud de la cadena ingresada como parametro en la funcion...
    if source[index] == " ": #si el caracter de la cadena apuntado es igual a un "espacio"
      index += 1 #se le suma 1 al indice, y
      continue #se omite las demas condiciones externas y vuelve al ciclo principal (es decir, vuelve a la linea de codigo 86)

    candidates = [] #la lista "candidatos" es vacia
    start = index #a la variable "start" le asignamos el "indice" actual

    while True: #mientras sea True...
      next = calcCandidates(source[start:index + 1]) #a la variable "next" le asignamos el resultado de la funcion "calcCandidates" que recibe el parametro del principio DESDE el numero asignado a "start" HASTA el "indice + 1" 
      #EJEMPLO: 
        #calcCandidates("3hola"[0:1]) == (False, 'cte')
        #calcCandidates("3hola"[0:2]) == (True, [])
      #Esto ocurre ya que en el primer caso, solo se tiene cuenta el caracter "3", en cambio, en la segunda se tiene en cuenta "3h"
      
      if next[0]: #teniendo en cuenta que la variable "next" recibe una tupla, solo se tiene en cuenta el primer elemento de la misma, el booleano, es decir, si True...
        break #rompe el ciclo while de la linea de codigo 94

      candidates = next[1] #a la variable "candidatos" se le asigna el segundo elemento de la tupla "next", es decir, el tipo_token
      
      index += 1 #se le suma uno al "indice"

    if len(candidates) == 0: #si la longitud de "candidatos" es igual a "0"
      candidates = "TOKEN_DESCONOCIDO" #a la variable "candidatos" se le asigna el string especificado
      break #rompe el ciclo while de la linea de codigo 86

    token_kind = candidates #a la variable "tipo_token" se le asigna lo que contiene la variable "candidatos"
    lexeme = source[start:index] #a la variable "lexeme" se le asigna la cadena de caracteres ingresada al principio, desde "start" hasta "indice"
    token = (token_kind, lexeme) #a la variable "token" se le asigna una tupla con las variables "tipo_token" y "lexeme"

    tokens.append(token) #a la lista "tokens" se le adjunta la variable "token"

  # Agrego un último TOKEN que siempre debe estar en la LISTA DE TOKEN: ("EOF", "EOF")
  tokens.append(("EOF", "EOF"))
  # Muestra por CONSOLA, la LISTA DE TOKENS que devuelve cada LLAMADA a la FUNCIÓN "lexer", es decir, cada ASSERT.
  #print(tokens)    
  return tokens

assert lexer("hola } 32") == [('id','hola'), ('}', '}'), ('cte', '32'), ("EOF", "EOF")]
assert lexer("2 + 2 = 4") == [('cte','2'), ('+', '+'),('cte','2'), ('=', '='), ('cte', '4'), ("EOF", "EOF")]
assert lexer("(hola}") == [('(','('), ('id', 'hola'), ('}', '}'), ("EOF", "EOF")]
assert lexer("para; y desde") == [('para','para'), (';',';'), ('id', 'y'), ('desde', 'desde'), ("EOF", "EOF")]
assert lexer("2 * 4 = 8") == [('cte','2'), ('*', '*'), ('cte', '4'), ('=', '='), ('cte', '8'), ("EOF", "EOF")]
assert lexer("entonces;hasta cuando") == [('entonces','entonces'), (';', ';'), ('hasta', 'hasta'), ('id', 'cuando'), ("EOF", "EOF")]
assert lexer("francisss;si") == [('id','francisss'), (';', ';'), ('si', 'si'), ("EOF", "EOF")]
assert lexer("hola23+") == [('id','hola23'), ('+', '+'), ("EOF", "EOF")]
assert lexer("{=}") == [('{','{'), ('=', '='), ('}', '}'), ("EOF", "EOF")]
assert lexer("(chau)") == [("(","("), ("id","chau"), (")",")"), ("EOF", "EOF")]

#------------------------------------------------------------------------------------PARSER------------------------------------------------------------------------------------

no_terminales = ['Programa', 'Asignacion', 'Estructura', 'Valor', 'Expresion', 'Expresion*', 'Termino', 'Termino*','Factor', 'ListaExpresiones'] #Se guarda, en una variable, todos los no_terminales de la gramática, incluyendo los añadidos 'Expresion*' y 'Termino*'.
terminales =  ['aceptar', 'cte', 'desde', 'entonces', 'hasta', '=', '{', '}', '+', 'mostrar', 'para', '(', ')', '*', ';', 'si', 'sino', 'id'] #No es la salida del lexer, sino los que determinamos.
#terminales =  lexer.TOKENS_POSIBLES (esto estaba mal, ya que TOKENS_POSIBLES era una tupla)

producciones = { #Estructura de diccionarios: llaves/claves y valores asignados a esa llave/clave. Hay que poner las producciones de los no terminales.
	'Programa': [
				['Asignacion', 'Programa'], #Esta produccion se pone primero porque es la de mayor longitud y sirve para evitar errores impredecibles.
				['Asignacion'], #se agregó para reemplazar al "lambda". 49:40
				['Estructura', 'Programa'], #Esta produccion se pone primero porque es la de mayor longitud y sirve para evitar errores impredecibles.
				['Estructura'] #se agregó para reemplazar al "lambda". 49:40
				#[] Para este algoritmo, la gramática no tiene que tener recursividad izquierda ni símbolos anulables, por lo que "lambda" se arregla con las líneas de código 11 y 13.
	], 
	#producciones['Programa'][1] --> ['Asignacion', 'Programa'].
	
	'Asignacion': [
				  ['id', '=', 'Expresion']
	],
	
	'Estructura': [
				  ['para', 'id', 'desde', 'Valor', 'hasta', 'Valor', '{', 'Programa', '}'], 
				  ['si', 'Expresion', 'entonces', '{', 'Programa', '}', 'sino', '{', 'Programa', '}'], 
				  ['si', 'Expresion', 'entonces', '{', 'Programa', '}'], 
				  ['mostrar', 'ListaExpresiones'], 
				  ['aceptar', 'id']
	],

	'Valor': [
			 ['id'],
			 ['cte']
	],	
	
	'Expresion': [
				 ['Termino', 'Expresion*'], #'Expresion*' es necesario para eliminar la recursividad izquierda. 
				 ['Termino']
	],

	'Expresion*': [
				  ['+', 'Termino', 'Expresion*'], #Esta produccion se pone primero porque es la de mayor longitud y sirve para evitar errores impredecibles.
				  ['+', 'Termino'] #Con esta produccion se reemplaza el "lambda".			  
				  #[]
	],

	'Termino': [
			   ['Factor', 'Termino*'], #'Termino*' es necesario para eliminar la recursividad izquierda. 
			   ['Factor']
	],

	'Termino*': [
				['*', 'Factor', 'Termino*'], #Esta produccion se pone primero porque es la de mayor longitud y sirve para evitar errores impredecibles.
				['*', 'Factor'] #Con esta produccion se reemplaza el "lambda".
				#[]
	],

	'Factor': [
			  ['(', 'Expresion', ')'],
			  ['id'],
			  ['cte']
	],

	'ListaExpresiones': [
			  ['Expresion', ';', 'ListaExpresiones'],
			  ['Expresion']
	]
}

def parser(lista_tokens): #lista_tokens es la salida del lexer, lista_tokens = lexer(codigo_fuente). Es la "w".
	datos_parser = {
		'tokens': lista_tokens,
		'posicion_indice': 0, #es la "t", seria en que posicion de la cadena de entrada estoy apuntando, es decir, una posicion dentro de nuestra lista_tokens
		'error': False, #variable que controla el funcionamiento del parser, se pone en "false", asumiendo que no hay ningun error en el procesamiento. Si llega a haber un error, es decir que es "true", la cadena no pertenece
	}

	def principal():
		pni('Programa') #pni hace referencia al simbolo distinguido de la gramatica con la posicion
		token_actual = datos_parser['tokens'][datos_parser['posicion_indice']][0]
		if token_actual != 'EOF' or datos_parser['error']:
			print('La cadena no pertenece al lenguaje')
			return False

		return True

	def pni(no_terminal):
		for parteDerecha in producciones[no_terminal]: #parteDerecha es una variable que se refiere a c/u de las "listitas" de las producciones.
			posicion_a_retroceder = datos_parser['posicion_indice'] #"marca" de retroceso en el arbol, por si no se puede continuar por un camino, para regresar y continuar por el otro.
			procesar(parteDerecha)
			if datos_parser['error'] == True:
				datos_parser['posicion_indice'] = posicion_a_retroceder #si hay un error, es decir, si no se puede continuar por el camino, se vuelve a la "marca".
			else:
				break #si no hay error, no hace falta controlar las otras porque ya encontre una que funciona.

	def procesar(parteDerecha):
		for simbolo in parteDerecha:
			token_actual = datos_parser['tokens'][datos_parser['posicion_indice']][0]
			datos_parser['error'] = False
			if simbolo in terminales: #si el simbolo es un terminal...
				if simbolo == token_actual:
					datos_parser['posicion_indice'] += 1 #si son iguales, avanza
				else:
					datos_parser['error'] = True 
					break #sino se pone la variable en error y se corta el ciclo

			elif simbolo in no_terminales: #en cambio, si el simbolo es un no terminal...
				pni(simbolo) #llama recursivamente a pni
				if datos_parser['error']:
					break #si hay un error, se corta el ciclo porque no hace falta seguir probando lo de ese no_terminal 

	return principal()

#Para probar el parser podemos:

# Hacer una variable que guarde la salida del lexer (el símbolo de fin de cadena ya está incluido) para luego parsearla, como por ejemplo:
	#cadena = lexer("variable = 123")
	#parser(cadena)

# O simplemente llamar a la función lexer dentro del parser:
	#parser(lexer(cadena))

assert(parser(lexer('variable = 123')))
assert(parser(lexer('para id1 desde 0 hasta 10 { aceptar saludo }')))
assert(parser(lexer('hola = 2 + 2')))
assert(parser(lexer('var1 = var1 var2 = var2 aceptar hola aceptar chau')))
assert(parser(lexer("mientras = ( 2 + 3 * 5 )")))
assert(parser(lexer("probando = ( hola + chau )")))
assert(parser(lexer("si 2 + 5 entonces { resultado = 7 } sino { resultado = distintoA7 }")))
assert(parser(lexer("si ( 2 * 2 ) entonces { resultado = 4 }")))
assert(parser(lexer("mostrar hola ; 3 + 3")))
assert(parser(lexer("comenzar = ( 2 * 5 ) + hola * ( 10 )")))

#IMPORTANTE: asegurarse que las cadenas pertenezcan al lenguaje para que no tire error.