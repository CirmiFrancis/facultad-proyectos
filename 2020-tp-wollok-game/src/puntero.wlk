import wollok.game.*

object puntero {
	var property position = game.at(1, 0)

	method image() = "puntero.png"
	
	method mover(unaPosicion) {
		if (unaPosicion.x().between(1,4) )
			position = unaPosicion
	}
}