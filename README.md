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

A continuacion se muestran unos diagramas con las clases mas importantes
del programa para dar una idea de la estructura del mismo.

![Diagrama de clases del Servidor](/images/server_class_diagram.jpeg)

                                        Diagrama de clases del Servidor  
  
Como se puede ver en el diagrama, la clase Server es el nexo del
_Server side_ y manejara el flujo principal del programa. La clase File
Reader se encarga de leer el archivo con los numeros y retornarlos en
formato Round Robin cada vez que se le pida el siguiente numero.
El Socket engloba la logica de conexion, envio y recepcion de mensajes. 
El ClientHandler maneja la comunicacion de un cliente particular mientras
que ServerProtocol se encarga de traducir los mensajes al protocolo
correspondiente, haciendo de traductor para la clase Game la cual maneja
la logica del juego en si. Por ultimo, el ServerMonitor se encarga de
_monitorear_ el input por entrada estandar para avisarle al server cuando
deba dejar de aceptar conexiones de nuevos clientes.   
  
![Diagrama de clases del Cliente](/images/client_class_diagram.jpeg)

                          Diagrama de clases del Cliente

Por el lado del cliente, la clase Client es analoga en funcion a lo que 
es la clase Server, siendo el nexo del _Client side_. Nuevamente la logica
de conexion, envio y recepcion de mensajes se encapsula en el Socket.
La clase User es la encargada de leer el input del usuario por entrada 
estandar mientras que la clase ClientProtocol se encargara de validar y
traducir dicho input (nuevamente, es analoga en funcion para el 
_Client side_ a lo que es ServerProtocol para el _Server side_). 

![Diagrama de clases del Thread](/images/thread_class_diagram.jpeg)
    
             Diagrama de clases del Thread
  
Este pequenio diagrama representa la relacion de **herencia** de las
clases ServerMonitor y ClientHandler con la clase Thread. Dicha clase
Thread se constituye por un metodo virtual _run_ el cual debera ser definido
por las clases hijas; dicho metodo sera el ejecutado cuando se invoque
a un nuevo _thread-process_ mediante el **operator()**.

Habiendo explicado en lineas generales el desarrollo del trabajo practico
para dar una idea conceptual del mismo y comprender su estructura, se 
presentan un par de diagramas de secuencia del programa.

![Diagrama de secuencia de conxeion del Server](/images/server_sequence_diagram.jpeg)

                     Diagrama de secuencia de conexion del Server
                     
![Diagrama de secuencia de ejecucion del comando numero del Cliente](/images/number_command_sequence_diagram.jpeg)

        Diagrama de secuencia de ejecucion del comando numero del Cliente