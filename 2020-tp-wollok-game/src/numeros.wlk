import wollok.game.*
import puntero.*
import logica.*

class Numero {
  	var property num
  	const color
  	var property position = game.origin()
  
  	method image() {
  		return "num" + num + color + ".jpg"
  	}
	
	method remover() {
		game.removeVisual(self)
	}
	
	method color() {
		return color
	}
	
	method mostrarse() {
		game.addVisual(self)
	}
}