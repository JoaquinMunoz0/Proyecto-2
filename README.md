# The Guardians Battles
## Descripción del Proyecto
Lircay Hub está interesado en desarrollar un piloto de un juego llamado "The Guardians Battles". Este juego se centra en los guardianes, héroes con habilidades únicas, que protegen las últimas ciudades de la humanidad. El objetivo principal es alcanzar uno de los tres codiciados puestos como guardianes del reino, siguiendo las órdenes de Stormbreaker, the judge. El juego se enfoca en la sección de duelos, recorrido por el mundo abierto e inventario de ítems.

# Objetivo del Proyecto
El objetivo es crear un programa en C++ que simule y actualice la información del juego. Se deben implementar las siguientes funcionalidades:
+ Guardar la lista de candidatos: El ranking es la posición en la cual se encuentra un guardián y puede cambiar después de cada batalla.
+ Jerarquía de los guardianes: La relación de maestro y aprendices entre los guardianes.
+ Mapa del mundo: La relación entre los guardianes y las ciudades del reino, así como los rivales en cada viaje.

# Estructuras de Datos
El programa debe contener las siguientes estructuras de datos:
+ Guardianes: Estructura para trabajar con la jerarquía y las ciudades.

# Funcionalidades
## Carga Inicial de Información:
+ Desarrollar la declaración de estructuras para trabajar con los guardianes, considerando la jerarquía y las ciudades.
+ Cargar la información inicial desde archivos de configuración.
## Menú de Opciones:
+ Ver la lista de candidatos.
+ Ver al guardián.
+ Conocer el reino.
+ Presenciar una batalla.
+ Salir.
## Operaciones sobre Estructuras:
+ Árbol binario para el ranking de guardianes: Operaciones de recorrido, búsqueda y eliminación.
+ Árbol general para la jerarquía de guardianes: Operaciones de recorrido, búsqueda y eliminación.
+ Grafo para las ciudades en el reino: Actualización, búsqueda de aristas y detección de caminos.
## Implementación de Algoritmos:
+ Evidenciar cambios en el ranking de los guardianes después de peleas, ítems y recompensas, y el recorrido por el mundo.

# Reglas de Implementación
## Ver la Lista de Candidatos
+ Revisar el ranking para identificar candidatos a guardianes del reino. Solo aquellos con 90 a 99 puntos son catalogados como caballeros candidatos.
## Ver al Guardián
+ Detalles del guardián, incluyendo toda la información relacionada con él.
## Conocer el Reino
+ Viajar a través del reino conocido y realizar nuevas consultas sobre caminos existentes.
## Presenciar una Batalla
+ Seleccionar un guardián, viajar a una ciudad y pelear con campeones locales.
+ El resultado de la batalla varía según el oponente y puede afectar el ranking.
+Actualización en la lista de candidatos después de la batalla.
Contribuciones son bienvenidas. Si encuentras errores o mejoras, por favor, crea un pull request.

# Solucion
Aborde el proyecto en estos 3 pasos a seguir:
+ Identificacion.
+ Implementacion.
+ Ejecucion.
## Identificacion
Lircay Hub esta interesado en desarrollar un piloto del juego asi que como programador tenemos que pensar como implementar lo que nos pide que se resumen en:
+ Utilizar estructuras para la implementacion de arbol general y binario, ademas de la utilizacion de un grafo para dar uso a una matriz de adyacencia.
+ Utilizacion de funciones para recorrer, buscar y eliminar dentro de los arboles seran necesarias para desarrollar el proyecto.

## Implementacion
Este proyecto sera implementado en C++ y utilizara estructuras de datos como grafos para modelar las ciudades y sus conexiones. Los Guardianes se representan mediante una estructura de datos que incluye información sobre su nombre, nivel de poder, maestro, ciudad y aprendices. La interacción con el programa se realiza a través de un menú interactivo que ofrece diversas funcionalidades para gestionar las operaciones de los Guardianes y las ciudades.

## Ejecucion
Durante la ejecucion se podra dar la validacion y la busqueda de errores, todo esto con el fin de llegar a un programa completamente funcional teniendo en cuenta todo
lo pedido anteriormente, obviamente habran errores y podria decir que se vuelve tediosa esta parte ya que se resume en un ciclo de programar y compilar, sin embargo los esfuerzos se hacen notar luego de ver como avanza el proyecto a medida que fallas y vuelves a programar.

## Video Presentacion
https://youtu.be/t4AuGQFSm7Y
