#include <iostream>
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

map<string, Guardian> guardiansMap;

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

    while (getline(inputFile, name, ','))
    {
        inputFile >> powerLevel;
        inputFile.ignore();
        getline(inputFile, master, ',');
        getline(inputFile, city);

        guardians.push_back({name, powerLevel, master, city});
    }

    inputFile.close();

    return guardians;
}

vector<City> loadCities(const string& filename)
{
    vector<City> cities;

    ifstream inputFile(filename);

    if (!inputFile.is_open() || inputFile.fail())
    {
        cout << "Error al abrir el archivo de las Ciudades " << filename << endl;
        return cities;
    }

    string cityName, connectedCity;

    while (getline(inputFile, cityName, ','))
    {
        getline(inputFile, connectedCity);

        auto existingCity = find_if(cities.begin(), cities.end(),
            [cityName](const City& city) { return city.name == cityName; });

        if (existingCity == cities.end())
        {
            cities.push_back({cityName, {connectedCity}});
        }
        else
        {
            existingCity->connectedCities.push_back(connectedCity);
        }
    }

    inputFile.close();

    return cities;
}

void showMenu()
{
    cout << "\nMENU PRINCIPAL:" << endl;
    cout << "1. Ver la lista de candidatos." << endl;
    cout << "2. Ver al guardian." << endl;
    cout << "3. Conocer el reino." << endl;
    cout << "4. Presenciar una batalla." << endl;
    cout << "5. Salir." << endl;
}

void printHierarchy(const Guardian& guardian, int indent = 0)
{
    cout << string(indent, ' ') << "Nombre: " << guardian.name << ", Nivel de poder: " << guardian.powerLevel << ", Ciudad: " << guardian.city << endl;

    for (const auto& apprentice : guardian.apprentices)
    {
        printHierarchy(apprentice, indent + 2);
    }
}

bool compareGuardians(const Guardian& a, const Guardian& b)
{
    return a.powerLevel > b.powerLevel;
}

Graph buildGraph(const vector<City>& cities)
{
    Graph graph;
    graph.cities = cities;

    int numCities = cities.size();
    graph.adjacencyMatrix.assign(numCities, vector<int>(numCities, 0));

    for (int i = 0; i < numCities; ++i)
    {
        graph.cityIndices[cities[i].name] = i;
    }

    for (const City& city : cities)
    {
        int cityIndex = graph.cityIndices[city.name];

        for (const string& connectedCity : city.connectedCities)
        {
            int connectedCityIndex = graph.cityIndices[connectedCity];

            graph.adjacencyMatrix[cityIndex][connectedCityIndex] = 1;
        }
    }

    return graph;
}

int main()
{
    vector<Guardian> guardians = loadGuardians("guardians.conf");
    vector<City> cities = loadCities("cities.conf");

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

    Graph cityGraph = buildGraph(cities);

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

    int choice;

    do
    {
        showMenu();
        cout << "Seleccione una opcion: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
			    {
			        cout << "\nLISTA DE CANDIDATOS A GUARDIANES DEL REINO:" << endl;
			        bool candidatosEncontrados = false;
			        int contador = 1;
			
			        for (const auto& guardian : guardians)
			        {
			            if (guardian.powerLevel >= 90 && guardian.powerLevel <= 99)
			            {
			                cout << contador << ". " << guardian.name << ", Nivel de poder: " << guardian.powerLevel << ", Maestro: " << guardian.master << ", Ciudad: " << guardian.city << endl;
			                candidatosEncontrados = true;
			                contador++;
			            }
			        }
			
			        if (!candidatosEncontrados)
			        {
			            cout << "No hay candidatos disponibles en el rango de poder requerido." << endl;
			        }
			    }
			    break;
            case 2:
			    {
			        cout << "LISTA DE GUARDIANES:" << endl;
			        for (int i = 0; i < guardians.size(); ++i)
			        {
			            cout << i + 1 << ". " << guardians[i].name << endl;
			        }
			
			        cout << "Ingrese el numero del guardian que desea ver: ";
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
            case 3:
			    {
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
			    }
			    break;
            case 4:
            	{
	                cout << "Seleccione un guardian para la batalla:" << endl;
	                for(int i = 0; i < guardians.size(); ++i)
					{
	                    cout << i + 1 << ". " << guardians[i].name << endl;
	                }
	                int challengerIndex;
	                cout << "Ingrese el numero del guardian retador: ";
	                cin >> challengerIndex;
	
	                if(challengerIndex >= 1 && challengerIndex <= guardians.size())
					{
	                    Guardian& challenger = guardians[challengerIndex - 1];
	
	                    if(challenger.name == "Stormbreaker" || challenger.master == "Stormbreaker")
						{
	                        cout << "No puedes seleccionar a Stormbreaker o sus aprendices para la batalla." << endl;
	                        break;
	                    }
	
	                    cout << "Seleccione una ciudad para la batalla:" << endl;
	                    for(int i = 0; i < cities.size(); ++i)
						{
	                        cout << i + 1 << ". " << cities[i].name << endl;
	                    }
	                    int cityIndex;
	                    cout << "Ingrese el numero de la ciudad: ";
	                    cin >> cityIndex;
	
	                    if(cityIndex >= 1 && cityIndex <= cities.size())
						{
	                        City& battleCity = cities[cityIndex - 1];
	
	                        // IMPLEMENTAR BATALLA AQUI
	
	                        // ACTUALIZAR INFORMACION
	
	                    }
						else
						{
	                        cout << "Numero de ciudad invalido." << endl;
	                    }
	                }
					else
					{
	                    cout << "Numero de guardian invalido." << endl;
	                }
	            }
                break;
            case 5:
            	cout << "Cerrando el programa..." << endl;
                break;
            default:
                cout << "Opcion Invalida." << endl;
        }

    }while (choice != 5);

    return 0;
}
