class Planeta {
	
	var property habitantes = []

	method agregarHabitante(hab){
		habitantes.add(hab)
	}
	
	method removerHabitante(hab){
		habitantes.remove(hab)
	}

	method sumatoriaPoder(){
		return habitantes.sum{hab => hab.poder()}
	}
	
	method habitantesMasPoderosos(){
		return habitantes.sortedBy{hab1, hab2 => hab1.poder() > hab2.poder()}.take(3)
	}
	
	method sumatoriaPoder2(){
		return self.habitantesMasPoderosos().sum{hab => hab.poder()}
	}
	
	method existeOrden(){
		return self.sumatoriaPoder2() > self.sumatoriaPoder() / 2
	}
}

class Habitante{

	const inteligencia
	const valentia
	
	method poder() {
		return valentia + inteligencia
	}
}

class Soldado inherits Habitante {  //stormtrooper, droides, clones y los demás personajes que combaten
	
	const property arma = [] //new Equipamiento(nombre = "pistola", potencia = 20)
	
	method agregarArma(equipamiento){
		arma.add(equipamiento)
	}
	
	method removerArma(equipamiento){
		arma.remove(equipamiento)
	}
	
	method encontrarArma(nombre){
		return arma.find({ a => a == nombre })
	}
	
	method armasUtiles(){
		return arma.filter{ a => a.armaUtil() }
	}
	
	override method poder(){
		return super() + self.armasUtiles().sum({ a => a.potencia() })
	}		
}

class Maestro inherits Habitante {
	const midiclorianos
	const sableDeLuz
	var property lado
	
	
	override method poder(){
		return super() + midiclorianos/1000 + lado.poderSable(sableDeLuz)
	}
	
	method vivirSuceso(suceso) {
		lado.vivirSuceso(suceso, self)
	}	
}

class Lado {
	
	var tiempo = 0
	
	method pasarTiempo(){
		tiempo += 1
	}
	
	method vivirSuceso(suceso, maestro) {
		self.pasarTiempo()
		self.aceptarSuceso(suceso, maestro)	
	}
	
	method aceptarSuceso(suceso, maestro)
	
	method poderSable(energiaSable)
}

class Jedi inherits Lado {
	
	var property pazInterior = 100
	
	override method aceptarSuceso(suceso, maestro){
		pazInterior += suceso.cargaEmocional()
		if (self.verificarPaz())
			maestro.lado(new Sith())
	}
	
	method verificarPaz(){
		return pazInterior <= 0
	}
	
	override method poderSable(sable){
		return sable*tiempo
	}
	
}

class Sith inherits Lado {
	
	var property odio = 100
	
	override method aceptarSuceso(suceso, maestro){
		if (suceso.cargaEmocional() > odio)
			maestro.lado(new Jedi())
		else
			odio = odio * 1.1
	}
	
	override method poderSable(sable){
		return sable*2 + tiempo
	}
}

class Suceso {
	const property cargaEmocional
}

class Equipamiento {
	
	var property potencia //si lo dejo constante, no lo leen los metodos de la clase soldado
	var property buenEstado = true //si lo dejo constante, no se puede cambiar la durabilidad ni usar el getter
	
	//la durabilidad tomaba valores "integers" pero lo cambie a "booleans"
	
	method reparar(){
		buenEstado = true
	}
	
	method usar(){
		buenEstado = false
	}	
	
	method armaUtil(){
		return potencia > 10 and buenEstado
	}

}
