import wollok.game.*
import puntero.*
import numeros.*
import configuracion.*


//profe
class Jugada {
    const numeros
    const nroJugada

    method realizar() {
        self.cargarNumeros()
        self.cargarResultados()
    }

    method cargarNumeros() {
        4.times{x=> self.cargarNumero(x) }
    }

    method cargarNumero(nro){
        new Numero(
                num = numeros.get(nro-1),
                position = game.at(nro, self.fila()),
                color="rojo"
        ).mostrarse()
    }
    
    	method cargarResultados() {
        new Numero(
            num = pc.cantidadNyP(numeros),
            position = game.at(juego.columnaNyP(), self.fila()),
            color="rojo"
        ).mostrarse()

        new Numero(
            num = pc.cantidadN(numeros),
            position = game.at(juego.columnaSoloN(), self.fila()),
            color="rojo"
        ).mostrarse()
    }
    
    method fila() = juego.filaInicial() - nroJugada
}

object pc {
	const numero = []
    
    //nuevo{
    
    method cantidadNyP(numeros) {
    	var numeroYPosicion = 0
    	4.times( { x => 
						if ( self.numero().contains(numeros.get(x-1)) )
							{
							if ( self.numero().get(x-1) == numeros.get(x-1) )
								numeroYPosicion += 1
							}
				})
		return numeroYPosicion				
    }
    
    method cantidadN(numeros) {
    	var soloNumero = 0
    	4.times( { x => 
						if ( self.numero().contains(numeros.get(x-1)) )
							{
							if ( self.numero().get(x-1) != numeros.get(x-1) )
								soloNumero += 1
							}
    			})
    			
    	return soloNumero
    }
    //nuevo}
    
    //metodo para mostrar el numero de la pc
	method numeroVisual() {
	 	var xVisual = 7
    	numero.forEach({ nu => self.mostrarNumero(nu, xVisual) xVisual = xVisual + 1})
	}
	
	method mostrarNumero(num, x) {
		new Numero
			(
		  		num = num,
                color = "blanco",
                position = game.at(x, 2)
            ).mostrarse()
	}
	
	//se genera el numero a adivinar
	method generarNumero() {
		const posibles = [0,1,2,3,4,5,6,7,8,9]
		numero.clear()
		4.times{i=>self.agregarNumero(posibles)}
	}
	
	//metodo auxiliar para generar el numero a adivinar
	method agregarNumero(auxi) {
		const nro = auxi.anyOne()
		numero.add(nro)
		auxi.remove(nro)
	}
	
	//getter del numero de la pc
	method numero() {
		return numero
	}
}

object juego {
	const posicionesPuntero = [1,2,3,4]
	var auxiliarEnter = false
	var nro_Jugada = 0
	const numeros = []
	const nrosIngresados = []
	const posOcupadas = []
	
	method columnaNyP() {
		return 10
	}
	
	method columnaSoloN() {
		return 7
	}
//nuevo{	
	
	method cargarNumeros() {
		numeros.clear()
		4.times{x=>numeros.add(game.getObjectsIn(game.at(x,1)).last().num())}
		4.times{x=>game.removeVisual(game.getObjectsIn(game.at(x,1)).last())}
	}

	method filaInicial() {
		return 13
	}
//nuevo}    	
	method tieneNum(posX, posY) {
		return not game.getObjectsIn(game.at(posX,posY)).isEmpty()
	}
	
	method jugadaIngresada() = posicionesPuntero.all { pos => self.tieneNum(pos, 1) }
	method partidaPerdida() = self.ultimaRonda() && not self.partidaGanada()
    method finDelJuego() = self.partidaGanada() or self.partidaPerdida()
    
    //nuevo{
    method ultimaRonda() = ((new Jugada(numeros = numeros , nroJugada = nro_Jugada)).fila()) == 3
    
    method partidaGanada(){
    	  if (numeros == []){
    		return false
    	  }
    	  else
    	 		return pc.cantidadNyP(numeros) == 4
    }
    //nuevo}
     
	method registrarJugada() 
			{
			//nuevo{
			nro_Jugada += 1
			self.cargarNumeros()
			new Jugada(numeros = numeros , nroJugada = nro_Jugada).realizar()
			//nuevo}
			self.actualizarRondas()
			}
		
	method realizarJugada(){
		if ( self.jugadaIngresada() and not self.ultimaRonda() and not self.finDelJuego() and (not auxiliarEnter)) 
            {
            self.registrarJugada()
            nrosIngresados.clear()
            posOcupadas.clear()
            }
        if ( self.finDelJuego() )
        	{
        	auxiliarEnter = true
            pc.numeroVisual()
            game.schedule( 3000, {self.finalizar()} ) 
            }
    }
    
	method finalizar(){
		if (self.partidaGanada())
			self.resultado(pantallaGanaste)
		if (self.partidaPerdida())
			self.resultado(pantallaPerdiste)
	}
	
	method resultado(pantalla){
		game.clear()
		keyboard.x().onPressDo{game.stop()}
		game.addVisual(pantalla)
	}
	
	method actualizarRondas() {
		const nroJugada = 13 - ((new Jugada(numeros = numeros , nroJugada = nro_Jugada)).fila())
		game.removeVisual(game.getObjectsIn(game.at(9,1)).last())
		if ( nroJugada < 10 )
			new Numero(
						num = nroJugada,
						color = "dorado",
						position = game.at(9,1)
					  ).mostrarse()
		else
			{
			game.removeVisual(game.getObjectsIn(game.at(8,1)).last())
			new Numero(
						num = 1,
						color = "dorado",
						position = game.at(8,1)
					  ).mostrarse()
					  
			new Numero(
						num = nroJugada % 10,
						color = "dorado",
						position = game.at(9, 1)
					  ).mostrarse()
			}
	}
	method borrar() {
		if (self.posicionOcupada() and nrosIngresados.contains(game.getObjectsIn(game.at(puntero.position().x(),1)).last().num()))
			{
			nrosIngresados.remove(game.getObjectsIn(game.at(puntero.position().x(),1)).last().num())
			posOcupadas.remove(puntero.position().x())
			}
		game.at(puntero.position().x(), 1).clear()
	}
	
	method mostrarNro(nro) {
		if ( self.yaEstaIngresado(nro) )
			{
			if (self.posicionOcupada() and not self.esElMismo(nro))
				self.desocuparPosicion()
			self.modificarPosicion(nro)
			}
		else
			{
			if (self.posicionOcupada())
				{
				self.cambiarNumero(nro)
				}
			else
				{
				self.agregarRealmente(nro)
				}
			}
	}
	
	method agregarRealmente(nro) {
		nrosIngresados.add(nro)
		posOcupadas.add(puntero.position().x())
		new Numero(num = nro, color = "rojo", position = game.at(puntero.position().x(),1)).mostrarse()
	}
	
	method cambiarNumero(numeroNuevo) {
		const numeroActual = game.getObjectsIn(game.at(puntero.position().x(),1)).last().num()
		game.getObjectsIn(game.at(puntero.position().x(),1)).last().num(numeroNuevo)
		nrosIngresados.remove(numeroActual)
		nrosIngresados.add(numeroNuevo)
	}
	
	method desocuparPosicion() {
		nrosIngresados.remove(game.getObjectsIn(game.at(puntero.position().x(), 1)).last().num())
		posOcupadas.remove(puntero.position().x())
		game.at(puntero.position().x(), 1).clear()
	}
	
	method modificarPosicion(nro) {
		const posicionActual = self.posicionActual(nro)
		const posicionNueva = puntero.position().x()
		game.getObjectsIn(game.at(posicionActual,1)).last().position(game.at(posicionNueva,1))
		posOcupadas.remove(posicionActual)
		posOcupadas.add(posicionNueva)
	}
	
	method posicionActual(nro) {
		return posOcupadas.find{x => game.getObjectsIn(game.at(x,1)).last().num() == nro}
	}
	
	method esElMismo(nro) {
		return game.getObjectsIn(game.at(puntero.position().x(),1)).last().num() == nro
	}
	
	method yaEstaIngresado(nro) {
		return nrosIngresados.contains(nro)
	}
	
	method posicionOcupada() {
		return posOcupadas.contains(puntero.position().x())
	}
}