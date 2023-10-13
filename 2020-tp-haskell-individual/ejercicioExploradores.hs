-- control + D or :q to leave Prelude/Main
-- cd .. to move to previous folder
-- :r to reset
-- git clone ... // git clone "..."
-- stack ghci "archivo.hs" (sin comillas)
-- Ctrl + ç -> comentario
-- :t to know the type, ex: 'a' -> 'a' :: Char  
-- :i to know the info
-- ctrl + c to interrupt a function at console

----------------------------------------------------------------- Primer Punto: Modelado de los planetas

-- De cada planeta conocemos su nombre, su posición en coordenadas PDP (un punto con coordenadas x,y,z) y su porcentaje de agua.

-- Sabemos que al menos existen 3 planetas:
-- Próxima Centauri b, se encuentra orbitando la estrella Próxima Centauri, actualmente en el punto (43.2, 14.2, 8.9). Según nuestros métodos, su porcentaje de agua es 74%. 
-- Alpha Centauri Bb, según nuestros reportes se encuentra actualmente en el punto (17, 31.2, 32) y su porcentaje de agua es realmente bajo, solo 3% de agua.
-- Alpha Centauri Cc, el último planeta descubierto. Se encuentra en la ubicación (42, 42, 42), el agua que detectamos está congelada pero representa un 60% según los reportes.

data Planeta = UnPlaneta {
    nombrePlaneta :: String,
    coordenadas :: [Float],
    porcentajeAgua :: Float
    }
    deriving Show

proxima :: Planeta
proxima = UnPlaneta {nombrePlaneta = "Proxima Centauri b", coordenadas = [43.2, 14.2, 8.9], porcentajeAgua = 0.74}
alphaBb :: Planeta
alphaBb = UnPlaneta {nombrePlaneta = "Alpha Centauri Bb", coordenadas = [17, 31.2, 32], porcentajeAgua = 0.03}
alphaCc :: Planeta
alphaCc = UnPlaneta {nombrePlaneta = "Alpha Centauri Cc", coordenadas = [42, 42, 42], porcentajeAgua = 0.6}

todosPlanetas :: [Planeta]
todosPlanetas = [proxima,alphaBb,alphaCc]

----------------------------------------------------------------- Segundo Punto: Cálculo de distancia estelar

-- Para poder dirigirnos a explorar los diferentes planetas de Alpha Centauri, primero debemos saber a qué distancia estamos de ellos.
-- Para ello es necesario tener una función `distanciaA` que dado un planeta destino y nuestra ubicación (en coordenadas PDP) pueda calcular la distancia al mismo.

-- La fórmula utilizada para calcular la distancia es: dist((x1, y1, z1), (x2, y2, z2)) = x1x2 + 2y1z2 + |y2 - z1|

distanciaA :: Planeta -> [Float] -> Float
distanciaA planeta ubicacion = dist (coordenadas planeta) ubicacion --distanciaA (UnPlaneta _ coordenadas _) ubicacion = dist coordenadas ubicacion

dist :: [Float] -> [Float] -> Float
dist [x1, y1, z1] [x2, y2, z2] = x1 * x2 + 2 * y1 * z2 + abs (y2 - z1) --dist cD cU = head cD * head cU + 2 * cD !! 1 * cU !! 2 + abs (cU !! 1 - cD !! 2)

----------------------------------------------------------------- Tercer Punto: Planetas aptos

-- Ahora que sabemos a qué distancia estamos de cada planeta, necesitamos saber si un planeta es apto. 
-- Esto es, cuando su porcentaje de agua es mayor a 52% y la distancia a él desde nuestra nave es menor a 100.

esApto :: Planeta -> [Float] -> Bool
esApto planeta ubicacion = (porcentajeAgua planeta) > 0.52 && (distanciaA planeta ubicacion) < 100

----------------------------------------------------------------- Cuarto Punto: Próximo destino

-- Por último, debemos cargar el próximo planeta al que se dirigirá la nave, para ello necesitamos primero modelarla.
-- De nuestra nave conocemos su nombre, cantidad de combustible expresada en litros, sus tripulantes y el próximo planeta al que se dirigirá.
-- Inicialmente el planeta destino es Alpha Centauri Bb, pero nos gustaría poder cambiarlo, por lo que deben hacer una función `cargarProximoPlaneta` 
-- que dada una nave y una lista de planetas explorados fije el primer planeta de la lista como próximo destino de la nave.

data Nave = UnaNave {
    nombreNave :: String,
    combustible :: Float, -- en litros
    tripulantes :: [String],
    proximoPlaneta :: Planeta
    }
    deriving Show

navenoide :: Nave
navenoide = UnaNave {nombreNave = "La Navenoide 2000", combustible = 0, tripulantes = [], proximoPlaneta = alphaBb}

cargarProximoPlaneta :: Nave -> [Planeta] -> Nave
cargarProximoPlaneta nave planetasExplorados = nave {proximoPlaneta = head planetasExplorados}

----------------------------------------------------------------- Quinto Punto: Destinos ordenados

-- Por último, necesitamos saber si una lista de planetas está ordenada de menor a mayor distancia. Para ello define una función `estaOrdenada` usando recursión.

estaOrdenada:: [Planeta] -> [Float] -> Bool
estaOrdenada ([]) [_,_,_] = False
estaOrdenada (_:[]) [_,_,_] = True

estaOrdenada (planeta:colaPlanetas) [x,y,z] = ( distanciaA planeta [x,y,z] <= distanciaA (head colaPlanetas) [x,y,z] ) && (estaOrdenada colaPlanetas [x,y,z])

----------------------------------------------------------------- Puntos Adicionales

-- Dada una lista de planetas, calcular:
--  Cuantas son aptas
--  La maxima distancia a la nave
--  Hacer que todos los planetas tengan un 10% más de agua

--cuantasSonAptas :: [Planeta] -> [[Float]] -> Int
--cuantasSonAptas :: [[Float]] -> Planeta -> Int
cuantasSonAptas listaPlanetas ubicacion = length ( filter (esApto ubicacion) listaPlanetas )

--maximaDistancia :: [Planeta] -> [Float] -> 
--maximaDistancia :: [[Float]] -> Planeta -> Float
maximaDistancia listaPlanetas ubicacion = maximum (map (distanciaA ubicacion) listaPlanetas)

aumentarAgua :: Float -> Planeta -> Planeta
aumentarAgua porcentaje planeta = planeta { porcentajeAgua = (porcentajeAgua planeta) * (1+porcentaje) }

--aumentaAguaEnTodos :: [Planeta] -> [Planeta]
--aumentaAguaEnTodos :: Float -> [Planeta] -> [Planeta] 
aumentaAguaEnTodos listaPlanetas = map (aumentarAgua listaPlanetas)