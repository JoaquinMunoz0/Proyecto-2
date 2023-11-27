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

