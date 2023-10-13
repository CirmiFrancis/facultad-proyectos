/*
paquete(Paquete, CiudadOrigen, CiudadDestino, Tamanio). 
horarioEntrega(Paquete, Dia, HoraInicio, HoraFin).
sucursal(Nombre, Ciudad).
mensajero(Nombre, Sucursal, Dia, HoraInicio, HoraFin).
*/

paquete(paquete01, zarate, campana, 1).
paquete(paquete02, zarate, zarate, 3).
paquete(paquete03, campana, zarate, 2).
paquete(paquete04, campana, campana, 2).
paquete(paquete05, lima, lima, 5).
horarioEntrega(paquete01, lunes, 9, 13).
horarioEntrega(paquete02, lunes, 14, 18).
horarioEntrega(paquete03, lunes, 9, 13).
horarioEntrega(paquete04, lunes, 14, 18).
horarioEntrega(paquete05, viernes, 15, 19).
sucursal(correoZarate, zarate).
sucursal(correoCampana, campana).
sucursal(ocampana, campana).
mensajero(francis, correoZarate, lunes, 9, 13).
mensajero(cirmi, correoZarate, lunes, 9, 13).
mensajero(cirmi, ocampana, lunes, 14, 17).
mensajero(nahuel, correoCampana, lunes, 14, 17).
mensajero(nahuel, ocampana, lunes, 9, 13).

%% 1) Envíos express 
envioExpress(Paquete):-
    paquete(Paquete, Ciudad, Ciudad, Tamanio),
    Tamanio =< 3.

envioExpress(Paquete):-
    paquete(Paquete, CiudadOrigen, CiudadDestino, 1),
    CiudadOrigen \= CiudadDestino.

% Un predicado es inversible cuando admite consultas con variables libres para sus argumentos;
% en el caso de envioExpress si hacemos la consulta con una variable: envioExpress(Paquete). --> Paquete = paquete01
% pero en el caso que elijamos un paquete determinado: envioExpress(paquete01). --> true.

%% 2) Multiempleo
multiempleo(Nombre):-
    mensajero(Nombre, Sucursal1, _, _, _),
    mensajero(Nombre, Sucursal2, _, _, _),
    sucursal(Sucursal1, Ciudad),
    sucursal(Sucursal2, Ciudad),
    Sucursal1 \= Sucursal2.

%% 3) Entregas
entregas(Nombre,Paquete):-
    mensajero(Nombre, Sucursal, Dia, HoraInicio, HoraFin),
    sucursal(Sucursal, Ciudad),
    paquete(Paquete, _, Ciudad, _),
    horarioEntrega(Paquete, Dia, HoraInicioEntrega, HoraFinEntrega),
    HoraInicio < HoraFinEntrega,
    HoraFin > HoraInicioEntrega.

%entregas(Nombre,Paquete):-
%    mensajero(Nombre, Sucursal, Dia, HoraInicio, HoraFin),
%    sucursal(Sucursal, Ciudad),
%    paquete(Paquete, _, Ciudad, _),
%    horarioEntrega(Paquete, Dia, HoraInicioEntrega, HoraFinEntrega),
%    hayHoraEnComun(HoraInicio, HoraFin, HoraInicioEntrega, HoraFinEntrega).

%hayHoraEnComun(Inicio1, Fin1, Inicio2, Fin2):-
%    between(Inicio1,Fin1, HORAINTERMEDIA),
%    between(Inicio2,Fin2, HORAINTERMEDIA).

%% 4) Calificación de paquetes
paqueteImposible(Paquete):-
    paquete(Paquete, _, _, _),
    not(entregas(_, Paquete)).

paqueteIndiscutido(Paquete):-
    paquete(Paquete, _, _, _),
    not(paqueteImposible(Paquete)),
    not(paqueteDisputado(Paquete)).

paqueteDisputado(Paquete):-
    paquete(Paquete, _, _, _),
    entregas(Nombre1,Paquete),
    entregas(Nombre2,Paquete),
    Nombre1 \= Nombre2.

%Todos los empleados de una misma sucursal de la ciudad destino pueden entregarlo.
paqueteComunDeSucursal(Paquete):-
    paquete(Paquete, _, CiudadDestino, _),
    sucursal(Sucursal, CiudadDestino),
    forall(mensajero(Nombre, Sucursal, _, _, _), entregas(Nombre, Paquete)).

%Todos los empleados de cualquiera de las sucursales de la ciudad destino pueden entregarlo.
paqueteEntregablePorTodos(Paquete):-
    paquete(Paquete, _, CiudadDestino, _),
    forall( mensajeroDeCiudad(Nombre, CiudadDestino), entregas(Nombre, Paquete) ).

mensajeroDeCiudad(Nombre, CiudadDestino):-
    mensajero(Nombre, Sucursal, _, _, _),
    sucursal(Sucursal, CiudadDestino).

%% 5) Empleado Modelo
horasTrabajadas(Nombre,Dia,Horas):-
    mensajero(Nombre, _, Dia, HoraInicio, HoraFin),
    Horas is HoraFin - HoraInicio.

horasTrabajadas(Nombre,Dia,Horas):-
    mensajero(Nombre, Sucursal1, Dia, HoraInicio1, HoraFin1),
    mensajero(Nombre, Sucursal2, Dia, HoraInicio2, HoraFin2),
    Sucursal1 \= Sucursal2,
    Horas1 is HoraFin1 - HoraInicio1,
    Horas2 is HoraFin2 - HoraInicio2,
    Horas is Horas1 + Horas2.

empleadoModelo(Nombre,Dia,Horas):-
    mensajero(Nombre, _, _, _, _),
    horasTrabajadas(Nombre, Dia, Horas),
    forall(horasTrabajadas(_, _, OtrasHoras), Horas >= OtrasHoras).

%============================================================================================================================================

/*

================PUNTO 1================
envioExpress(Paquete).
Paquete = paquete02 ;
Paquete = paquete04 ;
Paquete = paquete01.

envioExpress(paquete03). 
false.

================PUNTO 2================

multiempleo(Nombre).
Nombre = nahuel ;
Nombre = nahuel ;
false.

multiempleo(francis).  
false.

================PUNTO 3================

entregas(Nombre,Paquete).
Nombre = francis,
Paquete = paquete03 ;
Nombre = cirmi,
Paquete = paquete03 ;
Nombre = cirmi,
Paquete = paquete04 ;
Nombre = nahuel,
Paquete = paquete04 ;
Nombre = nahuel,
Paquete = paquete01 ;
false.

entregas(francis,paquete02). 
false.

================PUNTO 4================

paqueteImposible(Paquete).
Paquete = paquete02 ;
Paquete = paquete05.

paqueteIndiscutido(Paquete).
Paquete = paquete01 ;
false.

paqueteDisputado(Paquete).
Paquete = paquete03 ;
Paquete = paquete03 ;
Paquete = paquete04 ;
Paquete = paquete04 ;
false.

paqueteComunDeSucursal(Paquete).
Paquete = paquete01 ;
Paquete = paquete03 ;
Paquete = paquete04 ;
Paquete = paquete04 ;
false.

paqueteEntregablePorTodos(Paquete).
Paquete = paquete03 ;
Paquete = paquete04 ;
Paquete = paquete05.

mensajeroDeCiudad(Nombre, CiudadDestino).
Nombre = francis,
CiudadDestino = zarate ;
Nombre = cirmi,
CiudadDestino = zarate ;
Nombre = cirmi,
CiudadDestino = campana ;
Nombre = nahuel,
CiudadDestino = campana ;
Nombre = nahuel,
CiudadDestino = campana.

================PUNTO 5================

horasTrabajadas(Nombre,Dia,Horas).
Nombre = francis,
Dia = lunes,
Horas = 4 ;
Nombre = cirmi,
Dia = lunes,
Horas = 4 ;
Nombre = cirmi,
Dia = lunes,
Horas = 3 ;
Nombre = nahuel,
Dia = lunes,
Horas = 3 ;
Nombre = nahuel,
Dia = lunes,
Horas = 4 ;
Nombre = cirmi,
Dia = lunes,
Horas = 7 ;
Nombre = cirmi,
Dia = lunes,
Horas = 7 ;
Nombre = nahuel,
Dia = lunes,
Horas = 7 ;
Nombre = nahuel,
Dia = lunes,
Horas = 7 ;
false.

empleadoModelo(Nombre,Dia,Horas).
Nombre = cirmi,
Dia = lunes,
Horas = 7 ;
Nombre = cirmi,
Dia = lunes,
Horas = 7 ;
Nombre = cirmi,
Dia = lunes,
Horas = 7 ;
Nombre = cirmi,
Dia = lunes,
Horas = 7 ;
Nombre = nahuel,
Dia = lunes,
Horas = 7 ;
Nombre = nahuel,
Dia = lunes,
Horas = 7 ;
Nombre = nahuel,
Dia = lunes,
Horas = 7 ;
Nombre = nahuel,
Dia = lunes,
Horas = 7 ;
false.

*/