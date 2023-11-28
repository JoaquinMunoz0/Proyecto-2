#include <iostream>
#include <functional>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <map>

using namespace std;

struct City
{
    string name;
    vector<string> connectedCities;
};

struct Graph
{
    vector<City> cities;
    vector<vector<int>> adjacencyMatrix;
    map<string, int> cityIndices;
};

struct Guardian
{
    string name;
    int powerLevel;
    string master;
    string city;
    vector<Guardian> apprentices;
};

// Un mapa que almacena a los guardianes por nombre, lo cual facilita el acceso rapido a los datos del guardian dado su nombre.
map<string, Guardian> guardiansMap;

// LAS SIGUIENTES FUNCIONES CARGAN LA INFORMACION DE LOS GUARDIANES Y CIUDADES DESDE ARCHIVOS Y DEVUELVEN SUS VECTORES CORRESPONDIENTES

// Crea guardiansMap la cual se utiliza para almacenar informacion detallada de los guardianes del reino De esta manera,
// puedes acceder a la informacion de un guardian especifico utilizando su nombre como clave
vector<Guardian> loadGuardians(const string& filename)
{
    vector<Guardian> guardians;

    ifstream inputFile(filename);

    if (!inputFile.is_open() || inputFile.fail())
    {
        cout << "No se puede abrir el archivo de los Guardianes " << filename << endl;
        return guardians;
    }

    string name, master, city;
    int powerLevel;
    bool hasGuardianWithMaxPower = false;  // Variable para rastrear si ya se encontro un guardian con 100 puntos de experiencia.

    while (getline(inputFile, name, ','))
    {
        inputFile >> powerLevel;
        inputFile.ignore();
        getline(inputFile, master, ',');
        getline(inputFile, city);

        if (powerLevel == 100 && hasGuardianWithMaxPower)
        {
            cout << "Error: Solo puede haber un guardian con 100 puntos de experiencia.\nEl guardian '" << name << "' no cumple con esta restriccion." << endl;
        }
        else
        {
            guardians.push_back({name, powerLevel, master, city});
            if (powerLevel == 100)
            {
                hasGuardianWithMaxPower = true;
            }
        }
    }

    inputFile.close();

    return guardians;
}


// La funcion loadCities tiene como objetivo cargar la informacion de las ciudades desde un archivo y devolver un vector en el cual cada elemento representa una ciudad.
vector<City> loadCities(const string& filename)
{
    vector<City> cities; // Vector que almacenara la informacion de las ciudades

    ifstream inputFile(filename); // abre el archivo especifico para la carga

	// Verifica si el archivo se abrio correctamente
    if (!inputFile.is_open() || inputFile.fail())
    {
        cout << "Error al abrir el archivo de las Ciudades " << filename << endl;
        return cities;
    }

    string cityName, connectedCity;

	// Se lee el archivo linea por linea y procesa la informacion
    while (getline(inputFile, cityName, ','))
    {
        getline(inputFile, connectedCity);

		// Busca si ya existe en el vector una ciudad con el mismo nombre
        auto existingCity = find_if(cities.begin(), cities.end(),
            [cityName](const City& city) { return city.name == cityName; });
		
		// si la ciudad no existe se agrega al vector
        if (existingCity == cities.end())
        {
            cities.push_back({cityName, {connectedCity}});
        }
        //Si la ciudad ya existe, agrega solo la ciudad conectada
        else
        {
            existingCity->connectedCities.push_back(connectedCity);
        }
    }

	// cierra el archivo para liberar memoria
    inputFile.close();

	// Devuelve el vector de ciudades lleno
    return cities;
}


// Esta funcion construye el grafo de ciudades a partir de la informacion cargada de las ciudades y sus conexiones utilizando una matriz de adyacencia para representar
// la conexion entre ciudades en un grarfo
Graph buildGraph(const vector<City>& cities)
{
    Graph graph; // Estructura que representa el grafo
    graph.cities = cities; // Asigna el vector de ciudades a la estructura del grafo

    int numCities = cities.size(); // Se obtiene el numero de las ciudades
    graph.adjacencyMatrix.assign(numCities, vector<int>(numCities, 0)); // inicia la matriz de adyacencia con 0
    
	// Les asigna indices a cada ciudad en el grafo
    for (int i = 0; i < numCities; ++i)
    {
        graph.cityIndices[cities[i].name] = i;
    }
	
	// Itera sobre las ciudades y sus conexiones para construir la matriz
    for (const City& city : cities)
    {
        int cityIndex = graph.cityIndices[city.name];

        for (const string& connectedCity : city.connectedCities)
        {
            int connectedCityIndex = graph.cityIndices[connectedCity];
			
			// Establece las conexiones en la matriz de adyacencia
            graph.adjacencyMatrix[cityIndex][connectedCityIndex] = 1;
        }
    }

    return graph; // Devuelve la estructura del grafo construida
}

// Esta funcion muestra el menu principal del programa.
void showMenu()
{
    cout << "\nMENU PRINCIPAL:" << endl;
    cout << "1. Ver la lista de candidatos." << endl;
    cout << "2. Ver al guardian." << endl;
    cout << "3. Conocer el reino." << endl;
    cout << "4. Presenciar una batalla." << endl;
    cout << "5. Salir." << endl;
}

int main()
{
	// Se carga la informacion de los guardianes y las ciudades desde el archivo
    vector<Guardian> guardians = loadGuardians("guardians.conf");
    vector<City> cities = loadCities("cities.conf");

	// Se establecen los aprendices entre los guardianes
    for (Guardian& guardian : guardians)
    {
        for (const Guardian& possibleApprentice : guardians)
        {
            if (guardian.name != possibleApprentice.name && guardian.name == possibleApprentice.master)
            {
                guardian.apprentices.push_back(possibleApprentice);
            }
        }

        if (guardian.apprentices.empty())
        {
            guardian.apprentices.push_back({"none", 0, "", ""});
        }
    }

	// Construccion del grafo de ciudades
    Graph cityGraph = buildGraph(cities);
	
	
	// Se imprime la informacion sobre los guardianes, las ciudades y la matriz de adyacencia del grafo
    cout << "DATOS GUARDIANES CARGADOS EXITOSAMENTE" << endl;
    for (const auto& guardian : guardians)
    {
        cout << "Nombre: " << guardian.name << ", Nivel de poder: " << guardian.powerLevel << ", Maestro: " << guardian.master << ", Ciudad: " << guardian.city << ", Aprendices: ";
        for (const auto& apprentice : guardian.apprentices)
        {
            cout << apprentice.name << " ";
        }
        cout << endl;
    }

    cout << "\nDATOS CIUDADES CARGADOS EXITOSAMENTE" << endl;
    for (const auto& city : cities)
    {
        cout << "Ciudad: " << city.name << endl;
    }

    cout << "\nMATRIZ DE ADYACENCIA:" << endl;
    for (const auto& row : cityGraph.adjacencyMatrix)
    {
        for (int value : row)
        {
            cout << value << " ";
        }
        cout << endl;
    }
    
    // Simplemente una pausa antes de refrescar la terminal
    cout << "\nPresiona Enter para continuar..." << endl;
    cin.get();
	system("cls");
	
    int choice;
	
	// Menu principal
    do
    {
        showMenu();
        cout << "Seleccione una opcion: ";
        cin >> choice;
        system("cls");

        switch (choice)
        {
            case 1: // Este case esta destinado a ver detalles de la lista de candidatos, verifica los candidatos encontrados, utiliza contadores para numerar los candidatos en una lista.
				{
				    cout << "\nLISTA DE CANDIDATOS A GUARDIANES DEL REINO:" << endl;
				    bool candidatosEncontrados = false;
				    int contador = 1;
				
				    for (const auto& guardian : guardians)
				    {
				        if (guardian.powerLevel < 90)
				        {
				            cout << contador << ". " << guardian.name << ", Nivel de poder: " << guardian.powerLevel << ", Maestro: " << guardian.master << ", Ciudad: " << guardian.city << endl;
				            candidatosEncontrados = true;
				            contador++;
				        }
				    }
				}
				break;
            case 2: // Este case esta destinado a ver detalles de un guardian especifico, muestra la clasificacion de los guardianes, visualizacion de listas y muestra detalles del guardian seleccionado
			    {
			        vector<Guardian> grandMasters;
				    vector<Guardian> guardiansOfTheRealm;
				    vector<Guardian> guardianCandidates;
				
				    // Clasificar guardianes en las listas correspondientes
				    for (const auto& guardian : guardians)
				    {
				        if (guardian.powerLevel == 100)
				        {
				            grandMasters.push_back(guardian);
				        }
				        else if (guardian.powerLevel >= 90 && guardian.powerLevel <= 99)
				        {
				            guardiansOfTheRealm.push_back(guardian);
				        }
				        else
				        {
				            guardianCandidates.push_back(guardian);
				        }
				    }
				
				    // Mostrar las listas de guardianes
				    cout << "-----------------------\nGran Maestro:" << endl;
				    for (const auto& grandMaster : grandMasters)
				    {
				        cout << "1. " << grandMaster.name << endl;
				    }
				
				    cout << "-----------------------\nGuardianes Del Reino:" << endl;
				    int index = 2;
				    for (const auto& guardianOfTheRealm : guardiansOfTheRealm)
				    {
				        cout << index << ". " << guardianOfTheRealm.name << endl;
				        index++;
				    }
				
				    cout << "-----------------------\nCandidatos a Guardian:" << endl;
				    for (const auto& guardianCandidate : guardianCandidates)
				    {
				        cout << index << ". " << guardianCandidate.name << endl;
				        index++;
				    }
					cout << "-----------------------";
			        cout << "\nIngrese el numero del guardian que desea ver: ";
			        int guardianIndex;
			        cin >> guardianIndex;
			
			        if (guardianIndex >= 1 && guardianIndex <= guardians.size())
			        {
			            auto guardianIt = guardians.begin() + guardianIndex - 1;
			
			            cout << "\nDETALLES DEL GUARDIAN:" << endl;
			            cout << "Nombre: " << guardianIt->name << endl;
			            cout << "Nivel de poder: " << guardianIt->powerLevel << endl;
			            cout << "Maestro: " << guardianIt->master << endl;
			            cout << "Ciudad: " << guardianIt->city << endl;
			            cout << "Aprendices: ";
			            for (const auto& apprentice : guardianIt->apprentices)
			            {
			                cout << apprentice.name << " ";
			            }
			            cout << endl;
			        }
			        else
			        {
			            cout << "Numero de guardian invalido." << endl;
			        }
			    }
			    break;
            case 3: // Este case maneja las operaciones relacionadas con las ciudades dentro del menu principal
			    {
			    	cout << "1. Viajar entre ciudades." << endl;
				    cout << "2. Crear un nuevo camino entre ciudades." << endl;
				    cout << "3. Consultar la existencia de rutas entre ciudades." << endl;
				    cout << "4. Volver al menu principal." << endl;
				
				    int subChoice;
				    cout << "Seleccione una opcion: ";
				    cin >> subChoice;
				
				    switch (subChoice)
				    {
				        case 1:
				            cout << "LISTA DE GUARDIANES Y DONDE SE ENCUENTRAN:" << endl;
					        for (int i = 0; i < guardians.size(); ++i)
					        {
					            cout << i + 1 << ". " << guardians[i].name << ", " << guardians[i].city << endl;
					        }
					
					        cout << "\nIngrese el numero del guardian con el que quieres viajar: ";
					        int guardianIndex;
					        cin >> guardianIndex;
					
					        if (guardianIndex >= 1 && guardianIndex <= guardians.size())
					        {
					            auto guardianIt = guardians.begin() + guardianIndex - 1;
					
					            cout << "Te encuentras en " << guardianIt->city << ". Puedes viajar a las siguientes ciudades:" << endl;
					
					            int guardianCityIndex = cityGraph.cityIndices[guardianIt->city];
					            for (int i = 0; i < cityGraph.adjacencyMatrix[guardianCityIndex].size(); ++i)
					            {
					                if (cityGraph.adjacencyMatrix[guardianCityIndex][i] == 1)
					                {
					                    cout << i + 1 << ". " << cities[i].name << endl;
					                }
					            }
					
					            int choice;
					            cout << "Ingrese el numero de la ciudad a la que desea viajar: ";
					            cin >> choice;
					
					            if (choice >= 1 && choice <= cities.size())
					            {
					                int selectedCityIndex = choice - 1;
					                City& selectedCity = cities[selectedCityIndex];
					                guardianIt->city = selectedCity.name;
					
					                cout << "Viajando a " << selectedCity.name << endl;
					            }
					            else
					            {
					                cout << "Numero de ciudad invalido. Volviendo al menu." << endl;
					            }
					        }
					        else
					        {
					            cout << "Numero de guardian invalido." << endl;
					        }
				            break;
				         case 2:
				            {
				                cout << "LISTA DE CIUDADES DISPONIBLES:" << endl;
				                for (int i = 0; i < cities.size(); ++i)
				                {
				                    cout << i + 1 << ". " << cities[i].name << endl;
				                }
				
				                int originIndex, destinationIndex;
				                cout << "Ingrese el numero de la ciudad de origen: ";
				                cin >> originIndex;
				
				                // Validar la entrada del usuario
				                if (originIndex >= 1 && originIndex <= cities.size())
				                {
				                    cout << "Ingrese el numero de la ciudad de destino: ";
				                    cin >> destinationIndex;
				
				                    // Validar la entrada del usuario
				                    if (destinationIndex >= 1 && destinationIndex <= cities.size())
				                    {
				                        int originCityIndex = originIndex - 1;
				                        int destinationCityIndex = destinationIndex - 1;
				
				                        // Verificar si ya existe un camino entre estas ciudades
				                        if (cityGraph.adjacencyMatrix[originCityIndex][destinationCityIndex] == 1)
				                        {
				                            cout << "Ya existe un camino entre " << cities[originCityIndex].name << " y " << cities[destinationCityIndex].name << "." << endl;
				                        }
				                        else
				                        {
				                            // Crear un nuevo camino
				                            cityGraph.adjacencyMatrix[originCityIndex][destinationCityIndex] = 1;
				                            cout << "Se ha creado un nuevo camino entre " << cities[originCityIndex].name << " y " << cities[destinationCityIndex].name << "." << endl;
				                        }
				                    }
				                    else
				                    {
				                        cout << "Numero de ciudad de destino invalido. Volviendo al menu." << endl;
				                    }
				                }
				                else
				                {
				                    cout << "Numero de ciudad de origen invalido. Volviendo al menu." << endl;
				                }
				            }
				            break;
						case 3:
							{
							    cout << "LISTA DE CIUDADES DISPONIBLES:" << endl;
							    for (int i = 0; i < cities.size(); ++i)
							    {
							        cout << i + 1 << ". " << cities[i].name << endl;
							    }
							
							    int originIndex, destinationIndex;
							    cout << "Ingrese el numero de la ciudad de origen: ";
							    cin >> originIndex;
							
							    // Validar la entrada del usuario
							    if (originIndex >= 1 && originIndex <= cities.size())
							    {
							        cout << "Ingrese el numero de la ciudad de destino: ";
							        cin >> destinationIndex;
							
							        // Validar la entrada del usuario
							        if (destinationIndex >= 1 && destinationIndex <= cities.size())
							        {
							            int originCityIndex = originIndex - 1;
							            int destinationCityIndex = destinationIndex - 1;
							
							            // Utilizaremos el algoritmo de búsqueda en profundidad DFS para encontrar el camino entre ciudades
							            vector<bool> visited(cities.size(), false);
							            vector<int> path;
							            bool pathFound = false;
							
							            // Función DFS recursiva para buscar el camino
							            function<void(int)> dfs = [&](int current) {
							                visited[current] = true;
							                path.push_back(current);
							
							                if (current == destinationCityIndex) {
							                    pathFound = true;
							                    return;
							                }
							
							                for (int neighbor = 0; neighbor < cities.size(); ++neighbor) {
							                    if (cityGraph.adjacencyMatrix[current][neighbor] == 1 && !visited[neighbor]) {
							                        dfs(neighbor);
							                    }
							                }
							
							                if (!pathFound) {
							                    path.pop_back();
							                }
							            };
							
							            // Iniciar la búsqueda en profundidad desde la ciudad de origen
							            dfs(originCityIndex);
							
							            // Mostrar el resultado
							            if (pathFound) {
							                cout << "Existe una ruta entre " << cities[originCityIndex].name << " y " << cities[destinationCityIndex].name << ".\n";
							                cout << "Ruta a seguir: ";
							                for (int cityIndex : path) {
							                    cout << cities[cityIndex].name << ", ";
							                }
							                cout << endl;
							            } else {
							                cout << "No existe una ruta entre " << cities[originCityIndex].name << " y " << cities[destinationCityIndex].name << ".\n";
							            }
							        }
							        else
							        {
							            cout << "Numero de ciudad de destino invalido. Volviendo al menu." << endl;
							        }
							    }
							    else
							    {
							        cout << "Numero de ciudad de origen invalido. Volviendo al menu." << endl;
							    }
							}
							break;
				        case 4:
				            cout << "Volviendo al menu principal..." << endl;
				            break;
				        default:
				            cout << "Opcion Invalida." << endl;
				    }
			    }
			    break;
            case 4: // Este bloque maneja la batalla entre guardianes dentro del menú principal.
				{
				    // Mostrar los guardianes disponibles para la batalla
				    cout << "Seleccione un guardian para la batalla:" << endl;
				    for (int i = 0; i < guardians.size(); ++i)
				    {
				        if (guardians[i].powerLevel < 90)
				        {
				            cout << i + 1 << ". Nombre: " << guardians[i].name << ", Nivel de Poder: " << guardians[i].powerLevel << endl;
				        }
				    }
				
				    int challengerIndex;
				    cout << "\nIngrese el numero del guardian retador: ";
				    cin >> challengerIndex;
				
				    // Se valida el indice del guardian seleccionado
				    if (challengerIndex >= 1 && challengerIndex <= guardians.size() && guardians[challengerIndex - 1].powerLevel < 90)
				    {
				        Guardian& challenger = guardians[challengerIndex - 1];
				
				        // Se obtienen los oponentes de la ciudad del guardian seleccionado en caso de haber.
				        vector<Guardian> opponents;
				        for (const Guardian& opponent : guardians)
				        {
				            if (opponent.city == challenger.city && opponent.name != challenger.name)
				            {
				                opponents.push_back(opponent);
				            }
				        }
				
				        if (opponents.empty())
				        {
				            cout << "No hay oponentes en la misma ciudad. La batalla no puede ocurrir." << endl;
				        }
				        else
				        {
				            // Se muestran los oponentes disponibles
				            cout << "Oponentes en la misma ciudad:" << endl;
				            for (int i = 0; i < opponents.size(); ++i)
				            {
				                cout << i + 1 << ". " << opponents[i].name << endl;
				            }
				
				            int opponentIndex;
				            cout << "Seleccione el numero del oponente: ";
				            cin >> opponentIndex;
				
				            // Se Valida el indice del oponente
				            if (opponentIndex >= 1 && opponentIndex <= opponents.size())
				            {
				                Guardian& opponent = opponents[opponentIndex - 1];
				
				                // Probabilidad de ganar para el retador
				                double challengerWinProbability = 0.4;
				
				                // Generar un numero aleatorio para el resultado de la batalla
				                double randomValue = (double)rand() / RAND_MAX;
				
				                if (randomValue < challengerWinProbability)
				                {
				                    // El retador gana la batalla
				                    cout << "Victoria, " << challenger.name << " ha ganado la batalla contra " << opponent.name << "." << endl;
				
				                    // Actualizar puntajes
				                    challenger.powerLevel += (opponent.master == challenger.name) ? 5 : 3;
				                    opponent.powerLevel--;
				
				                    // Verificar si el retador supera al maestro y lo reemplaza
				                    if (challenger.powerLevel > guardiansMap[challenger.master].powerLevel)
				                    {
				                        cout << challenger.name << " ha superado a su maestro " << challenger.master << " y lo reemplaza en su rol." << endl;
				                        guardiansMap[challenger.master].master = challenger.name;
				                    }
				                }
				                else
				                {
				                    cout << "No puede ser... " << challenger.name << " ha perdido la batalla contra " << opponent.name << "." << endl;
				
				                    // Actualizar el puntaje
				                    challenger.powerLevel--;
				
				                    // Verificar si el retador tiene aprendicez y su puntaje es menor al que ellos, asi su aprendiz toma su rol
				                    if (challenger.powerLevel <= 0)
				                    {
				                        cout << challenger.name << " ha sido derrotado y pierde su rol como guardian." << endl;
				
				                        // El retador pierde su rol y es reemplazado por uno de sus aprendices si tiene
				                        if (!challenger.apprentices.empty())
				                        {
				                            cout << "Su aprendiz " << challenger.apprentices[0].name << " lo reemplaza como nuevo maestro." << endl;
				                            challenger.city = challenger.apprentices[0].city;
				                            guardiansMap[challenger.apprentices[0].name] = challenger.apprentices[0];
				                        }
				                        // Agregue tambien que si no tiene aprendicez este sea eliminado del reino, tipo exiliado
				                        else
				                        {
				                            cout << "Al no tener aprendices, " << challenger.name << " es exiliado del reino." << endl;
				                            guardiansMap.erase(challenger.name);
				                        }
				                    }
				                }
				                
				                // MOSTRAR LA LISTA DE CANDIDATOS ACTUALIZADA
				                cout << "\nLISTA DE CANDIDATOS A GUARDIANES DEL REINO DESPUES DE LA BATALLA:" << endl;
				                int contador = 1;
				
				                for (const auto& guardian : guardians)
				                {
				                    if (guardian.powerLevel < 90)
				                    {
				                        cout << contador << ". " << guardian.name << ", Nivel de poder: " << guardian.powerLevel << ", Maestro: " << guardian.master << ", Ciudad: " << guardian.city << endl;
				                        contador++;
				                    }
				                }
				
				                if (contador == 1)
				                {
				                    cout << "No hay candidatos disponibles en el rango de poder requerido." << endl;
				                }
				            }
				            else
				            {
				                cout << "Numero de oponente invalido. Volviendo al menu." << endl;
				            }
				        }
				    }
				    else
				    {
				        cout << "Numero de guardian retador invalido o nivel de poder mayor a 90. Volviendo al menu." << endl;
				    }
				}
				break;
            case 5:
            	cout << "Cerrando el programa..." << endl;
                break;
            default:
                cout << "Opcion Invalida." << endl;
        }

    }while(choice != 5);

    return 0;
}