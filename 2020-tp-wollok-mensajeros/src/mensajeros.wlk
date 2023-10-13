// Mensajeros de pelicula, primera parte

object roberto {
	var peso = 90
	var transporte = camion

	method peso() {
		return peso + transporte.peso()
	}

	method transporte(vehiculo) {
		transporte = vehiculo
	}

	method tieneCredito() {
		return false
	}
}

// object neo {}
object neo {
     var tieneCredito = false
    
     method peso() {
         return 0
     }
     
     method tieneCredito(unBooleano) {
         tieneCredito = unBooleano
     }
     
     method tieneCredito() {
         return  tieneCredito
     }
     
}
 
// object chuck (visto del profe: puedeLlamar -> tieneCredito)
object chuck {
	
	method peso() {
		return 900
	}
	
	method tieneCredito() {
		return true
	}
}

object camion {
	var acoplados = 2

	method peso() {
		return acoplados * 500
	}

	method acoplados(cantAcoplados) {
		acoplados = cantAcoplados
	}
	
	method agrandar() {
		acoplados = acoplados + 1
	}
}

object bicicleta {
	var peso = 1
	
	method peso() {
		return peso
	}
	
	method agrandar() {
		peso = peso * 2
	}
}

object brooklyn {

	method dejarPasar(mensajero) {
		return mensajero.peso() < 1000
	}
}

// object matrix
object matrix {
	method dejarPasar(mensajero) {
		return mensajero.tieneCredito()
	}
}

object paquete {
	var pago = false
	var destino = brooklyn
	var precio = 50

	method pagar() {
		pago = true
	}

	method estaPago() {
		return pago
	}

	method destino(lugar) {
		destino = lugar
	}

	method puedeSerEntregadoPor(mensajero) {
		return destino.dejarPasar(mensajero) and self.estaPago()
	}
	
	method precio(){
		return precio
	}
}

object paquetito {

	method puedeSerEntregadoPor(mensajero) {
		return true
	}
	
	method precio(){
		return 0
	}
	
	method pagar(){
		return true
	}
}

object paquetonViajero {
	const destinos = []
	var monto = 0

	method puedeSerEntregadoPor(mensajero){
		return self.estaPago() && self.puedePasarPorTodos(mensajero)
	}

	method agregarDestino(lugar){
       destinos.add(lugar)
    }

	method precio (){
		return destinos.size() * 100
	}
	
	method pagar(cantidad){
		monto = monto + cantidad
	}
	
	method estaPago(){
		return monto >= self.precio()
	}

	method puedePasarPorTodos(mensajero){
		return destinos.all({ destino => destino.dejarPasar(mensajero) })
	}
}

//3.9 Agregar un nuevo mensajero y un nuevo paquete y garantizar que todo siga funcionando.
object elLocoJorge {
	
	method peso() {
         return 0
     }
     
	method tieneCredito() {
		return true
	}
}

object paquetito2 {
	
	method puedeSerEntregadoPor(mensajero) {
		return true
	}
	
	method precio(){
		return 0
	}
	
	method pagar(){
		return true
	}
}

