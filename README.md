#### Alumno: Marcos Daniel Rolando
#### Padrón: 102323
#### [Repositorio de Github](https://github.com/MarcosRolando/tp3taller)
# Taller de Programacion 1
# TP3 Adivina el Numero
### Disenio general

La solucion desarrollada para el enunciado del trabajo practico en 
cuestion consta de dos secciones bien diferenciadas, por un lado 
tenemos la logica del _Cliente_ y por el otro la logica del 
_Servidor_. Ambos se encuentran compuestos por un conjunto de clases
con tareas especificas y APIs simples para simplificar el desarrollo
de la solucion al problema propuesto por el trabajo practico y lograr
encarar soluciones a problemas mas pequenios (_Divide and Conquer_).  

A grandes rasgos, la ejecucion del Server Side comienza levantando
un servidor en el puerto especificado por el usuario, donde dicho
servidor se encargara de aceptar las connection requests que le 
lleguen de potenciales clientes (esto es, usuarios que quieran 
conectarse a nuestro juego). Una vez aceptada la peticion de conexion
del cliente, esta se delegara a una clase ClientHandler la cual
se encargara de iniciar una instancia del juego Adivina el Numero y mantener
la comunicacion con nuestro cliente durante la partida.  

Por otro lado, la ejecucion del Client Side comenzara levantando un
cliente en la IP y puerto especificados por el usuario y, una vez 
establecida la conexion, se validaran los comandos del usuario y
se intercambiara la informacion con el servidor como corresponda.  

A continuacion se muestra un diagrama con las clases mas importantes
del programa para dar una idea de la estructura del mismo.

![Diagrama de clases del Servidor](/images/server_class_diagram.jpeg)

                                             Diagrama de clases del Servidor

![Diagrama de clases del Cliente](/images/client_class_diagram.jpeg)


    
