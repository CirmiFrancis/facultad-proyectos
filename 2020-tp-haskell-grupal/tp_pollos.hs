-------------------------------------------------------------------------------POLLOS
data Pollo = UnPollo {
    nombre :: String,
    diasVivos :: Int,
    peso :: Float, -- en gramos
    artesMarciales :: [String]
    }
    deriving Show

gin :: Pollo
gin = UnPollo {
    nombre = "ginger", 
    diasVivos = 10, 
    peso = 150, 
    artesMarciales = []
    }

roc :: Pollo
roc = UnPollo {
    nombre = "rocky", 
    diasVivos = 1, 
    peso = 3000, 
    artesMarciales = []
    }




--1. Engordar a un pollo una cierta cantidad de gramos

engordarPollo :: Float -> Pollo -> Pollo
engordarPollo gramos pollo = pollo {peso = peso pollo + gramos}




--2. Saber si un pollo es mayor de edad: se dice que un pollo es mayor de edad si tiene más de 6 meses de vida

mayorDeEdad :: Pollo -> Bool
mayorDeEdad pollo = diasVivos pollo > 180




--3. Saber si el último atributo de un pollo es vacío. ¡Ojo! Cuando sepamos qué es esa última lista, el nombre debe cambiar
--(falta cambiar el nombre)

listaVacia :: Pollo -> Bool
listaVacia pollo = artesMarciales pollo == []




--4. Cruzar un conjunto de pollos: dada una lista de pollos, obtener un pollo que es la combinación de todos los anteriores. 
--Inventar una lógica para esto, usando al menos una expresión lambda. 
--(falta la expresion lambda)

pau :: Pollo
pau = UnPollo {
    nombre = "Paula", 
    diasVivos = 2, 
    peso = 300, 
        artesMarciales = ["judo"]
}

cruzar :: [Pollo] -> Pollo

cruzar losPollos = UnPollo {
    nombre = "Super " ++ nombre (head losPollos),
    diasVivos = maximum (map (\pollo -> diasVivos pollo) losPollos),
    peso = minimum (map (\pollo -> peso pollo) losPollos),
    artesMarciales = [] 
}

listaPolluelosLocos :: [Pollo]
listaPolluelosLocos = [gin, pau, gin, roc] --para verificar

-------------------------------------------------------------------------------POLLOS NINJAS
--Ahora necesitamos modelar a los entrenadores, que son capaces de entrenar a un pollo. 




--arguiniano: Engorda 100 gramos al pollo que entrena.

arguiniano :: Pollo -> Pollo
arguiniano = engordarPollo 100




--miyagi: Si no sabe, le enseña karate al pollo.

miyagi :: Pollo -> Pollo
miyagi pollo 
            | elem "karate" (artesMarciales pollo) = pollo
            | otherwise = pollo {artesMarciales = artesMarciales pollo ++ ["karate"]}




--marcelito: Hace que el pollo se olvide todas las artes marciales y después lo manda a aprender de Miyagi.

marcelito :: Pollo -> Pollo
marcelito pollo = pollo {artesMarciales = ["karate","kung fu"]}




--brujaTapita: Alimenta al pollo dándole de comer un ratón. El alimento que provee el ratón se calcula como su peso por su
--altura menos la cantidad de bigotes.

data Raton = UnRaton {
    pesoR :: Float, -- en gramos
    altura :: Float,
    bigotes :: Float
    }
    deriving Show

mikelAyala :: Raton
mikelAyala = UnRaton {
    pesoR = 150, 
    altura = 2, 
    bigotes = 4
    }

brujaTapita :: Raton -> Pollo -> Pollo 
brujaTapita raton pollo = pollo {peso = (peso pollo) + (pesoR raton) * (altura raton) - (bigotes raton)}




--marioBros: Toma al pollo y le agrega al nombre la frase “super mario ”. Le enseña a saltar y una nueva arte marcial que
--también se indica por parámetro, si es que el pollo no sabe hacerlo. Por ejemplo,  marioBros “judo” le podría enseñar a
--rocky judo.

agregar :: Pollo -> String -> [String]
agregar pollo arte
            | not (elem arte (artesMarciales pollo)) = [arte]
            | otherwise = []

marioBros :: String -> Pollo -> Pollo
marioBros arteMarcial pollo = pollo {
    nombre = "super mario " ++ nombre pollo, 
    artesMarciales = artesMarciales pollo ++ agregar pollo arteMarcial
    }




--1. Hacer que un entrenador entrene a un pollo.

entrenar :: (Pollo -> Pollo) -> Pollo -> Pollo
entrenar unEntrenador pollo = unEntrenador pollo -- Es una función trivial, pero responde a la consigna. De aquí en adelante
                                                 -- vamos a usar directamente a los entrenadores, no a la función "entrenar".




--2. Dados dos entrenadores y un pollo, averiguar cuál de los dos entrenadores lo entrena mejor, es decir, lo deja con más artes
--marciales aprendidas.

cantidadArtesMarciales :: Pollo -> Int
cantidadArtesMarciales pollo = length(artesMarciales pollo)

quienEntrenaMejor :: (Pollo -> Pollo) -> (Pollo -> Pollo) -> Pollo -> Pollo -> Pollo
quienEntrenaMejor entrenador1 entrenador2 pollo
    |length(artesMarciales (entrenador1 pollo)) > length(artesMarciales (entrenador2 pollo)) = entrenador1
    |otherwise = entrenador2




-------------------------------------------------------------------------------POLLOS NINJAS ESPACIALES
data Planeta = UnPlaneta {
    entrenador :: Pollo -> Pollo,
    habitantes :: [Pollo]
    }




--1. elMejorPollo: un pollo es el mejor pollo de un planeta si es el que más artes marciales sabe.

artesMarcialesDeUnPlaneta :: Planeta -> [[String]]
artesMarcialesDeUnPlaneta planeta = map (artesMarciales) (habitantes planeta)

cantidadArtesMarcialesDeUnPlaneta :: Planeta -> [Int]
cantidadArtesMarcialesDeUnPlaneta planeta= map (length) (artesMarcialesDeUnPlaneta planeta)

mayorCantidadDeArtesMarcialesDeUnPlaneta :: Planeta -> Int
mayorCantidadDeArtesMarcialesDeUnPlaneta planeta = maximum (cantidadArtesMarcialesDeUnPlaneta planeta)

elMejorPollo :: Planeta -> [Pollo]
elMejorPollo planeta = filter (\pollo -> cantidadArtesMarciales pollo == mayorCantidadDeArtesMarcialesDeUnPlaneta planeta) (habitantes planeta)




--2. esDebil: Un planeta es débil si ninguno de sus pollos adultos sabe más de 2 artes marciales o si al menos dos de sus
--pollos no saben ningún arte marcial.

pollosAdultosDeUnPlaneta :: Planeta -> [Pollo]
pollosAdultosDeUnPlaneta planeta = filter (mayorDeEdad) (habitantes planeta)

artesMarcialesDeUnaLista :: [Pollo] -> [[String]]
artesMarcialesDeUnaLista listaDePollos = map (artesMarciales) listaDePollos

sabeMasDeDosArtesMarciales :: Pollo -> Bool
sabeMasDeDosArtesMarciales pollo = length (artesMarciales pollo) >= 2

esDebil :: Planeta -> Bool
esDebil planeta = not(any (\pollo -> sabeMasDeDosArtesMarciales pollo) (pollosAdultosDeUnPlaneta planeta))




--3. entrenarP: Recibe un planeta y hace que su entrenador haga lo correspondiente con todos los pollos del planeta. Devuelve el planeta
--con todos sus pollos entrenados.

entrenarP :: Planeta -> Planeta
entrenarP planeta = planeta {
                        habitantes = map (entrenador planeta) (habitantes planeta)
                        }




--4. entrenamientoKaio: dado dos planetas los pollos del primer planeta son entrenados por su entrenador asignado y después por el entrenador
-- del segundo planeta, devolviendo el planeta con los pollos entrenados.

entrenamientoKaio :: Planeta -> Planeta -> Planeta
entrenamientoKaio planeta1 planeta2 = planeta1 {
                                        habitantes = map (entrenador planeta2) (habitantes planeta1)
                                        } 




--5. hacerViajeEspiritual: hace que un pollo se transforme en The Chicken One (el Pollo Elegido). Hacer un viaje espiritual es entrenar a
--un pollo con todos los entrenadores de la lista que se recibe como argumento. Realizar los cambios necesarios para que las funciones de
--la primera parte sigan funcionando.

entrenamientoConVariosEntrenadores :: Pollo -> [Pollo -> Pollo] -> [String]
entrenamientoConVariosEntrenadores pollo (unEntrenador:listaDeEntrenadores) = 
    artesMarciales (unEntrenador pollo) ++ entrenamientoConVariosEntrenadores pollo listaDeEntrenadores
entrenamientoConVariosEntrenadores _ [] = []

hacerViajeEspiritual :: [Pollo -> Pollo] -> Pollo -> Pollo
hacerViajeEspiritual listaDeEntrenadores pollo= pollo {
                                                    nombre = (nombre pollo) ++ " The Chicken One",
                                                    artesMarciales = entrenamientoConVariosEntrenadores pollo listaDeEntrenadores
                                                    }




--6. planetaDebilEntrenado: saber si un planeta queda débil incluso después de hacer que todos sus pollos hagan un viaje espiritual con ciertos
--entrenadores

planetaDebilEntrenado :: Planeta -> [Pollo -> Pollo] -> Bool
planetaDebilEntrenado planeta listaDeEntrenadores = esDebil(planeta {
                                                            habitantes = map (hacerViajeEspiritual listaDeEntrenadores) (habitantes planeta)
                                                            })



--Definir varios algunos pollos y planetas y hacer pruebas contemplando las variantes mencionadas.

marte :: Planeta
marte = UnPlaneta {entrenador = arguiniano, habitantes = [gin, roc, pau, pedro]}

tierra :: Planeta
tierra = UnPlaneta {entrenador = marcelito, habitantes = [roc,pau,pau]}

venus :: Planeta
venus = UnPlaneta {entrenador = miyagi, habitantes = [pau, roc]}

jupiter :: Planeta
jupiter = UnPlaneta {entrenador = brujaTapita mikelAyala, habitantes = [pau, roc]}

saturno :: Planeta
saturno = UnPlaneta {entrenador = marioBros "kung fu", habitantes = [pau, roc]}

pedro :: Pollo
pedro = UnPollo {
    nombre = "pedro",
    diasVivos = 181,
    peso = 8,
    artesMarciales = ["karate","kung fu","taekwondo"]
    }

auxi :: [Pollo -> Pollo]
auxi = [miyagi, marioBros "kung fu", marioBros "karate", brujaTapita mikelAyala]

-------------------------------------------------------------------------------POLLOS NINJAS ESPACIALES MUTANTES
--1. chickenNorris Es un pollo mutante que pesa 100 kilos, tiene 9000000 días y sabe TODOS los niveles de 
--karate. "karate1", "karate2", "karate3", etc. (Sabe infinitas artes marciales) Mostrar ejemplos de invocación para entrenar a 
--chickenNorris con diferentes entrenadores. ¿Con cuáles se lo puede entrenar y con cuáles no? Justificar. Mostrar ejemplos de 
--invocación y respuesta con diferentes entrenadores.

chickenNorris :: Pollo
chickenNorris = UnPollo {
    nombre = "Chicken Norris",
    diasVivos = 9000000,
    peso = 100000,
    artesMarciales = ["karate1","karate2","karate3"]
    }

--arguiniano: Engorda 100 gramos al pollo que entrena. Puede entrenar a chickenNorris ya que no tiene ninguna restricción para hacerlo.
entrenarChickenNorrisConArguiniano :: Pollo
entrenarChickenNorrisConArguiniano = arguiniano chickenNorris -- peso chickenNorris == 100100

--miyagi: Si no sabe, le enseña karate al pollo. En rigor puede entrenarlo. Pero teniendo en cuenta que chickenNorris "sabe TODOS los 
--niveles de karate " (inclusive "karate"), no provocará ningun cambio en chickenNorris.

entrenarChickenNorrisConMiyagi :: Pollo
entrenarChickenNorrisConMiyagi = miyagi chickenNorris -- No lo afecta en nada.

--marcelito: Hace que el pollo se olvide todas las artes marciales y después lo manda a aprender de Miyagi. Puede entrenarlo perfectamente,
--no tiene ninguna restricción para hacerlo.

entrenarChickenNorrisConMarcelito :: Pollo
entrenarChickenNorrisConMarcelito = marcelito chickenNorris --artesMarciales chickenNorris == ["karate"].

--brujaTapita: Alimenta al pollo dándole de comer un ratón. El alimento que provee el ratón se calcula como su peso por su
--altura menos la cantidad de bigotes. Puede entrenarlo perfectamente, ya que no tiene ninguna restricción para hacerlo.

entrenarChickenNorrisConBrujaTapita1 :: Pollo
entrenarChickenNorrisConBrujaTapita1 = brujaTapita mikelAyala chickenNorris --Afecta al peso

entrenarChickenNorrisConBrujaTapita2 :: Raton -> Pollo
entrenarChickenNorrisConBrujaTapita2 raton = brujaTapita raton chickenNorris --Afecta al peso (si, para el raton, su peso por su
                                                                             --altura menos la cantidad de bigotes != 0)

--marioBros: Toma al pollo y le agrega al nombre la frase “super mario ”. Le enseña a saltar y una nueva arte marcial que
--también se indica por parámetro, si es que el pollo no sabe hacerlo. Por ejemplo,  marioBros “judo” le podría enseñar a
--rocky judo. Puede entrenarlo perfectamente, teniendo en cuenta que si el arte marcial que se le pasa por parametro es "karate",
--entrenarlo con marioBros solo afectará a su nombre.

entrenarChickenNorrisConMarioBros1 :: Pollo
entrenarChickenNorrisConMarioBros1 = marioBros "karate" chickenNorris -- Afecta solo al nombre

entrenarChickenNorrisConMarioBros2 :: Pollo
entrenarChickenNorrisConMarioBros2 = marioBros "judo" chickenNorris -- Afecta al nombre y a la lista de artes marciales

entrenarChickenNorrisConMarioBros3 :: String -> Pollo
entrenarChickenNorrisConMarioBros3 arteMarcial = marioBros arteMarcial chickenNorris -- Afecta al nombre y a la lista de artes 
                                                                                     --marciales (si arteMarcial != "karate")


                                                                    -- NOTA: Las respuestas que contienen en su desarrollo algo del estilo 
                                                                    --"funcionX chickenNorris == Y", dicho Y se refiere al valor que
                                                                    --resulta de haberle aplicado la función que corresponde al comentario
                                                                    --de la respuesta.




--2. Graduar al mejor pollo de un planeta, mutándolo a entrenador: hacer una función que dado un planeta, permita obtener un nuevo 
--entrenador, en base al pollo que más artes marciales sabe de ese planeta, con un comportamiento que consista es enseñar 
--todas sus artes marciales.

graduarPollo :: Planeta -> [Pollo]
graduarPollo planeta = elMejorPollo planeta --Es una función trivial, pero resulta más expresiva en este contexto.

aprenderArtesMarciales :: [String] -> [String] -> [String]
aprenderArtesMarciales (arteMarcial:listaDeArtesMarciales) otraListaDeArtesMarciales = 
    (otraListaDeArtesMarciales ++ [arteMarcial]) ++ aprenderArtesMarciales listaDeArtesMarciales otraListaDeArtesMarciales
aprenderArtesMarciales [] _ = []

entrenamientoPolloGraduado :: Planeta -> Pollo -> [String]
entrenamientoPolloGraduado planeta = ((aprenderArtesMarciales.(artesMarciales.(head.graduarPollo))) planeta).artesMarciales

entrenadorPolloGraduado :: Planeta -> Pollo -> Pollo
entrenadorPolloGraduado planeta pollo = pollo {
                                            artesMarciales = entrenamientoPolloGraduado planeta pollo
                                            }




--3. Defiir a marceñano como la mutación de dos entrenadores: marcelito y arguiñano en un nuevo entrenador que combina sucesivamente el
--entrenamiento de ambos. 

marcenianio :: Pollo -> Pollo
marcenianio = marcelito.arguiniano