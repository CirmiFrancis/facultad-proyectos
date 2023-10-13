import pasteleros.*

class Pastelero {
	var property nombre
	var property nota
}

object jurado {
	const platos = []
	const property participantes = [sonia,marcos,samanta] //es property para el test del Punto 2.3
	var tortaModelo = tortaWollok

	//el pastelero más habilidoso del programa
	method masHabilidoso(){
		return participantes.max{pastelero => pastelero.habilidad()}
	}	
	
	//cuánto más habilidoso es el más habilidoso del programa respecto del menos habilidoso.
	method diferenciaHabilidad(){
		return self.masHabilidoso().habilidad() - self.menosHabilidoso().habilidad()
	}
	
	//el pastelero menos habilidoso del programa
	method menosHabilidoso() {
		return participantes.min{pastelero => pastelero.habilidad()}
	}

	//Punto 2.3
	method masHabilidosoFavorito(){
		return participantes.filter({pastelero => pastelero.puedeHacerPostreFavorito()}).max{pastelero => pastelero.habilidad()}
	}
	
	method presentarTorta(torta){
		platos.add(torta)
	}	
	
	//Punto 3.2
	method realizarPruebaTecnica(){
		participantes.forEach{pastelero => pastelero.pruebaTecnica(tortaModelo)}
	}
	
	//Punto 3.3
	method ganadorPruebaTecnica(){
		return platos.max({plato=>self.puntosPara(plato)}).autor()
	}
	
	method puntosPara(torta){
		return 10 - (torta.pesoTotal()-tortaModelo.pesoTotal()).abs() - (torta.coccion() - tortaModelo.coccion()).abs()
	}
}

//=====================================================================================================================================================

class Torta {
	const property ingredientes = []
	var property coccion 
	var property autor
		
	method agregarIngrediente(nombre, cantidad){
		ingredientes.add(new Ingrediente(nombre = nombre, cantidad = cantidad))
	}
	
	method pesoTotal() = ingredientes.sum{ing => ing.cantidad()}
}

const tortaWollok = new Torta(
	ingredientes = [
		new Ingrediente(nombre = "chocolate", cantidad = 0.5),
		new Ingrediente(nombre = "harina", cantidad = 0.6),
		new Ingrediente(nombre = "azucar", cantidad = 0.3),
		new Ingrediente(nombre = "manteca", cantidad = 0.1)		
	],
	coccion = 50,
	autor = "nadie"
) 
