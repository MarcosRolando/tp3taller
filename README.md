#### Alumno: Marcos Daniel Rolando
#### Padrón: 102323
#### [Repositorio de Github](https://github.com/MarcosRolando/tp3taller)
# Taller de Programación 1
# TP3 Adivina el Número
### Diseño general

La solución desarrollada para el enunciado del trabajo práctico en 
cuestión consta de dos secciones bien diferenciadas, por un lado 
tenemos la lógica del _Cliente_ y por el otro la lógica del 
_Servidor_. Ambos se encuentran compuestos por un conjunto de clases
con tareas específicas y APIs sencillas para simplificar el desarrollo
de la solución al problema propuesto por el trabajo práctico y lograr
encontrar soluciones a problemas mas pequeños (_Divide and Conquer_).  

A grandes rasgos, la ejecución del Server Side comienza levantando
un servidor en el puerto especificado por el usuario, donde dicho
servidor se encargará de aceptar las _connection requests_ que le 
lleguen de potenciales clientes (esto es, usuarios que quieran 
conectarse a nuestro juego). Una vez aceptada la petición de conexión
del cliente, esta se delegará a una clase ClientHandler la cual
se encargará de iniciar una instancia del juego Adivina el Numero y mantener
la comunicación con nuestro cliente durante la partida.  

Por otro lado, la ejecución del Client Side comenzará levantando un
cliente en la IP y puerto especificados por el usuario y, una vez 
establecida la conexión, se validarán los comandos del usuario y
se intercambiará la información con el servidor como corresponda.  

A continuación se muestran unos diagramas con las clases más importantes
del programa para dar una idea de la estructura del mismo.

![Diagrama de clases del Servidor](/images/server_class_diagram.jpeg)

                                        Diagrama de clases del Servidor  
  
Como se puede ver en el diagrama, la clase Server es el nexo del
_Server side_ y manejará el flujo principal del programa. La clase File
Reader se encarga de leer el archivo con los números y retornarlos en
formato Round Robin cada vez que se le pida el siguiente número.
El Socket engloba la lógica de conexión, envío y recepción de mensajes. 
El ClientHandler maneja la comunicación de un cliente particular mientras
que ServerProtocol se encarga de traducir los mensajes al protocolo
correspondiente, haciendo de traductor para la clase Game la cual maneja
la lógica del juego en sí. Por último, el ServerMonitor se encarga de
_monitorear_ el input por entrada estándar para avisarle al server cuando
deba dejar de aceptar conexiones de nuevos clientes.   
  
![Diagrama de clases del Cliente](/images/client_class_diagram.jpeg)

                          Diagrama de clases del Cliente

Por el lado del cliente, la clase Client es análoga en función a lo que 
es la clase Server, siendo el nexo del _Client side_. Nuevamente la lógica
de conexión, envio y recepción de mensajes se encapsula en el Socket.
La clase User es la encargada de leer el input del usuario por entrada 
estándar mientras que la clase ClientProtocol se encargará de validar y
traducir dicho input (nuevamente, es análoga en función para el 
_Client side_ a lo que es ServerProtocol para el _Server side_). 

![Diagrama de clases del Thread](/images/thread_class_diagram.jpeg)
    
             Diagrama de clases del Thread
  
Este pequeño diagrama representa la relación de **herencia** de las
clases ServerMonitor y ClientHandler con la clase Thread. Dicha clase
Thread se constituye por un método virtual _run_ el cual deberá ser definido
por las clases hijas; dicho método será el ejecutado cuando se invoque
a un nuevo _thread-process_ mediante el **operator()**.

Habiendo explicado en lineas generales el desarrollo del trabajo práctico
para dar una idea conceptual del mismo y comprender su estructura, se 
presentan un par de diagramas de secuencia del programa.

![Diagrama de secuencia de conxeión del Server](/images/server_sequence_diagram.jpeg)

                     Diagrama de secuencia de conexión del Server
                     
![Diagrama de secuencia de ejecución del comando número del Cliente](/images/number_command_sequence_diagram.jpeg)

                   Diagrama de secuencia de ejecución del comando número del Cliente