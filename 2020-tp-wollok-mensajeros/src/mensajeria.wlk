import mensajeros.*

object mensajeria {
	
	//Lista o colección vacía, pueden ser variables o constantes, ya que el contenido no se ve afectado
	const mensajeros = []
	var enviados = []
	var pendientes = []
	var paquetes = []
	
	//2.1 Contratar a un mensajero
	method contratar(alguien) {
		mensajeros.add(alguien)
	}
	
	//2.2 Despedir a un mensajero
	method despedir(alguien) {
		mensajeros.remove(alguien)
	}
	
	//2.3 Despedir a todos los mensajeros
	method despedirATodos() {
		mensajeros.clear()
	}
	
	//2.4 Analizar si la mensajeria es grande (si tiene mas de dos mensajeros)
	method esGrande() {
		return mensajeros.size() > 2
	}
	
	//2.5 Consultar si el paquete puede ser entregado por el primer empleado de la la empresa de mensajería.
	method elPrimeroPuedeEntregarlo() {
		return paquete.puedeSerEntregadoPor(mensajeros.first())
	}
	
	//2.6 Saber el peso del último mensajero de la empresa.
	method pesoDelUltimoMensajero() {
		return mensajeros.last().peso()
	}
	
	//Lo agregué yo
	method elPrimerMensajero() {
		return mensajeros.first()
		
	}
	
	method mensajeros() {
		return mensajeros
	}
	
	//3.1 Averiguar si un paquete puede ser entregado por la empresa de mensajería, es decir, si al menos uno de sus mensajeros puede entregar el paquete.
	method puedeEntregarse(algo){
		return mensajeros.any({ mensajero => algo.puedeSerEntregadoPor(mensajero) })
	}
	
	//3.2 Obtener todos los mensajeros que pueden llevar un paquete dado.
	method candidatosPara(algo){
		return mensajeros.filter({ mensajero => algo.puedeSerEntregadoPor(mensajero) })
	}
	
	method paqueteFacil(algo){
		return mensajeros.any({ mensajero => algo.puedeSerEntregadoPor(mensajero) })
	}
	
	//3.3 Saber si una mensajería tiene sobrepeso. Esto sucede si el promedio del peso de los mensajeros es superior a 500 Kg.
	method tieneSobrepeso(){
		if (mensajeros.isEmpty()) return false
		return mensajeros.sum({ men => men.peso() }) / mensajeros.size() > 500
	}
	
	//3.4 Hacer que la empresa de mensajería envíe un paquete. Para ello elige cualquier mensajero entre los que pueden enviarlo y si no puede lo agrega a los paquetes pendientes.
	method enviar(algo){
		if(self.puedeEntregarse(algo))
			self.registrarEnvio(algo)
		else
			self.registrarPendiente(algo)
	}
	
	method registrarEnvio(algo) {
		enviados.add(algo)
	}
	
	method enviados(){
		return enviados
	}
	
	method registrarPendiente(algo) {
		pendientes.add(algo)
	}
	
	method pendientes(){
		return pendientes
	}
	
	method limpiarPendientes(){
		pendientes.clear()
	}
	
	//3.5 Conocer la facturación de la empresa, que es el total ganado por los paquetes enviados.
	method facturacion() {
		return enviados.sum({ en => en.precio() })
	}
	
	//3.6 Dado un conjunto de paquetes, enviarlos a todos.		
	method enviarATodos(){
		paquetes.forEach({ p =>
			p.pagar()
			self.enviar(p)
		})
		paquetes.clear()
	}
	
	method agregarPaquete(paquetoide){
		paquetes.add(paquetoide)
	}
	
	method paquetes(){
		return paquetes.size()
	}
	
	//3.7 Encontrar el paquete pendiente más caro y enviarlo, actualizando los pendientes en caso de haberlo podido enviar.
	method pendienteMasCaro(){
		return pendientes.max({ p=>p.precio() })
	}
		
	method enviarMasCaro(){	
		if(self.puedeEntregarse(self.pendienteMasCaro()))
		{
			self.enviar(self.pendienteMasCaro())
			pendientes.remove(self.pendienteMasCaro())
		}
	}
}
