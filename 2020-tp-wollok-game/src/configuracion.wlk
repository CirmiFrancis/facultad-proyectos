import wollok.game.*
import numeros.*
import puntero.*
import logica.*

class Interfaz{
	const position = game.origin()
	const image
	
	method position() {
		return position
	}
	
	method image() {
		return image
	}
}

const pantallaInicial = new Interfaz(position = game.origin(),image = "interfazInicial.png")
const pantallaJuego = new Interfaz(position = game.origin(),image = "fondonegro.png")

const pantallaInstrucciones = new Interfaz(position = game.origin(),image = "instrucciones.png")

const rondaInicial = new Numero(num = 0, color = "dorado", position = game.at(8,1) )
const rondaInicial2 = new Numero(num = 0, color = "dorado", position = game.at(9,1) )

const pantallaGanaste = new Interfaz(position = game.origin(),image = "ganaste" + (1..5).anyOne() + ".jpg")
const pantallaPerdiste = new Interfaz(position = game.origin(),image = "perdiste" + (1..6).anyOne() + ".jpg")

const guionesEnX = [1, 2, 3, 4, 7, 10]
const guionesEnY = [3, 4, 5, 6, 7, 8, 9, 10, 11, 12]

class Guion {
	var property position
	const image = "-.png"
	
	method mostrarse() {
		game.addVisual(self)
	}
	
	method image() {
		return image
	}
}

object agregar {
	method guiones() {
		guionesEnY.forEach( { y => guionesEnX.forEach( { x => new Guion(position = game.at(x, y)).mostrarse() } ) } )
	}
}

// x: (1..4), 7, 10
// y: (2..12)

object configuracion {	
	var auxActivarJuego = false //variable auxiliar que se coloca como "global" porque en el método se reiniciaría y no se mantendría el "activarElJuego = true" 
	//var nroParaElTeclado = 0..9
	
	method activarInicio() {
		game.title("CODE")
		game.width(14)
		game.height(14)
		game.addVisual(pantallaInicial)
		keyboard.p().onPressDo{self.activarJuego()}
		keyboard.x().onPressDo{game.stop()}
		keyboard.i().onPressDo{self.instrucciones()}
	}
	
	method instrucciones(){
		if (game.hasVisual(pantallaInstrucciones))
			game.removeVisual(pantallaInstrucciones)
		else
			game.addVisual(pantallaInstrucciones)
	}
	
	method activarJuego() {
		
		if (not auxActivarJuego) //si es "false" se activa el juego
			{
			auxActivarJuego = true //al settearlo "true" no se puede volver a activar el método
			pc.generarNumero()
			game.removeVisual(pantallaInicial)
			game.addVisual(pantallaJuego)
			game.addVisual(puntero)
			game.addVisual(rondaInicial)
			game.addVisual(rondaInicial2)
			agregar.guiones()
			keyboard.left().onPressDo{puntero.mover(puntero.position().left(1))}
			keyboard.right().onPressDo{puntero.mover(puntero.position().right(1))}
			10.times({ i => keyboard.num(i-1).onPressDo{juego.mostrarNro(i-1)}})
			
			keyboard.space().onPressDo{juego.borrar()}
			keyboard.enter().onPressDo{juego.realizarJugada()}
			}
		}
	}