from automataAceptar import automata_aceptar
from automataConstante import automata_constante
from automataDesde import automata_desde
from automataEntonces import automata_entonces
from automataHasta import automata_hasta
from automataIdentificador import automata_identificador
from automataIgual import automata_igual
from automataLlaveAbrir import automata_llaveAbrir
from automataLlaveCerrar import automata_llaveCerrar
from automataMas import automata_mas
from automataMostrar import automata_mostrar
from automataPara import automata_para
from automataParentesisAbrir import automata_parentesisAbrir
from automataParentesisCerrar import automata_parentesisCerrar
from automataPor import automata_por
from automataPuntoComa import automata_puntoComa
from automataSi import automata_si
from automataSino import automata_sino

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

    candidates = [] #la lista "candidatos" es vacia (se le asigna tipo_token)
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