import jurado.*

class Ingrediente {
	var property nombre
	var property cantidad = 0 // en kg
	
	method aumentarCantidad(unaCantidad) {
		cantidad += unaCantidad
	}
}

//=====================================================================================================================================================

//MARCOS
object marcos {
	var property experiencia = 0
	const ingredientes = 
	[
		new Ingrediente(nombre = "chocolate", cantidad = 1.2),
		new Ingrediente(nombre = "azucar", cantidad = 0.3),
		new Ingrediente(nombre = "harina", cantidad = 0.4)
	]
	
	//calcular y devolver la habilidad
	method habilidad() {
		return experiencia + self.totalCantidad()
	}
	
	//cantidad total de kg
	method totalCantidad() {
		return ingredientes.sum({ ing => ing.cantidad() })
	}
	
	//agregar ingrediente
	method agregarIngrediente(nombre,cantidad) {
		ingredientes.add(new Ingrediente(nombre = nombre, cantidad = cantidad))
	}
	
//	//existe ingrediente
//	method anyIngrediente(unNombre) {
//		return ingredientes.any({ing => ing.nombre() == unNombre})
//	}
//	
//	//encontrar ingrediente
//	method findIngrediente(unNombre) {
//		return ingredientes.find({ing => ing.nombre() == unNombre})
//	}
	
	//Punto 2: Postre favorito
	method tieneSuficiente(nombre, cantidad) {
		return ingredientes.any({ i => i.nombre() == nombre && i.cantidad() >= cantidad})
	}
	
	method tieneBuenDia() {
		return self.habilidad() > 5
	}
	
	method puedeHacerPostreFavorito() {
		return ingredientes.size().even() && self.tieneSuficiente("azucar", 0.1) && self.tieneBuenDia()
	}
	
	//Punto 3: Prueba técnica
	
	method pruebaTecnica(tortaModelo){
		const nuevaTorta = new Torta(coccion = tortaModelo.coccion(), autor = self)
		tortaModelo.ingredientes().forEach({ing => self.colocarIngrediente(nuevaTorta,ing)})
		jurado.presentarTorta(nuevaTorta)
	}

	method colocarIngrediente(torta, ingrediente) {
		torta.agregarIngrediente(ingrediente.nombre(),
			ingrediente.cantidad().min(self.cuantoTieneDe(ingrediente.nombre()))
		) 
	}
	
	method cuantoTieneDe(producto){
		if(ingredientes.any({ing => ing.nombre() == producto}))
			return ingredientes.find({ing => ing.nombre() == producto}).cantidad()
		else 
			return 0
	}
}

//=====================================================================================================================================================

//SONIA
object sonia {
	
	//hacer esta variable "property", hace que el ingrediente se reemplace siempre por el nuevo, para solo tener un único
	var property ingrediente = new Ingrediente(nombre = "chocolate", cantidad = 1)
	var property instrumento = cuadernoDeRecetas
	
	//calcular y devolver la habilidad
	method habilidad() {
		return (1 + ingrediente.cantidad() + instrumento.suerte()).min(10)
	}
	
	method agregarCantidad(cantidad) {
		ingrediente.aumentarCantidad(cantidad) 
	}
	
	//Punto 2: Postre favorito
	method puedeHacerPostreFavorito() {
		return self.tieneChocolate() && instrumento.suerte() > 5
	}
	
	method tieneChocolate() {
		return ingrediente.nombre() == "chocolate"
	}
	
	//Punto 3: Prueba técnica
	method pruebaTecnica(tortaModelo){
		jurado.presentarTorta(
			new Torta(
				coccion = tortaModelo.coccion() * 10 / self.habilidad(),
			    ingredientes = [new Ingrediente(
			    	nombre = ingrediente.nombre(), 
			    	cantidad = tortaModelo.pesoTotal()
			    )],
			    autor = self
			)
		)
	}
}

//INSTRUMENTOS
object cuchara {

	method suerte() {
		return 2
	}
}

object cuadernoDeRecetas {
	var property paginas = 3

	method suerte() {
		return paginas
	}
}

//Punto 1.2
object cucharon {

	method suerte() {
		return 6
	}
}

//=====================================================================================================================================================

//SAMANTA
object samanta {
	
	//calcular y devolver la habilidad
	method habilidad() {
		return 9
	}
	
	//Punto 2: Postre favorito
	method puedeHacerPostreFavorito() { //method puedeHacerPostreFavorito() = false
		return false
	}
	
	//Punto 3: Prueba técnica
	method pruebaTecnica(tortaModelo){
		jurado.presentarTorta(new Torta(coccion = 30, autor = self))
	}
}

//=====================================================================================================================================================

//Punto 1.3
object francis {
	var property buenHumor = false
	var property habilidad = 3
	
	//no usé el método "habilidad()" (polimorfismo) porque no se requiere
	method calcularHabilidadActual() {
		if (buenHumor)
			habilidad += 2
		else
			habilidad -= 2
	}
	
	//Punto 2: Postre favorito
	method puedeHacerPostreFavorito() {
		return habilidad >= 5
	}
	
	//Punto 3: Prueba técnica
	method pruebaTecnica(tortaModelo){
		jurado.presentarTorta(new Torta(coccion = 0, autor = self))
	}
}

//=====================================================================================================================================================

//Punto 4: Preguntas Teóricas

//Identificar usos de polimorfismo. ¿Qué condición es necesaria para poder tratar a los objetos de manera polimórfica?
///"habilidad()", "puedeHacerPostreFavorito()", "hornear()", "presentarTorta()", "hacerTortaWollok()", ...
///Que entiendan el mismo mensaje (método)

//¿Que ventaja tiene el uso de clases? ¿En qué casos no justifica su uso?
///Evita la programación innecesaria o repetida, con lo cual, un mismo código puede ser usado en aquellos objetos que posean la misma estructura
///No se debe de usar cuando los objetos poseen un comportamiento diferente (por más leve que sea)

//Punto 5: Bonus

//No lo hice