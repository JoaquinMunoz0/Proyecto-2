#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>

using namespace std;

struct City
{
    string City;
    vector<string> ConnectedCities;
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
    vector<Guardian> guardians; //vector donde se almacenan los guardianes

    // se abre el archivo
    ifstream inputFile(filename);
	
    // Verficacion
    if(!inputFile.is_open() || inputFile.fail())
	{
        cout << "No se puede abrir el archivo de los Guardianes" << filename << endl;
        return guardians; //Returna vacio en caso de que ocurra
    }

    // Variables temporales para almacenar los datos mientras se leen
    string name, master, city;
    int powerLevel;

    //Se lee el archivo linea por linea
    while(getline(inputFile, name, ','))
	{
        inputFile >> powerLevel;
        inputFile.ignore();
        getline(inputFile, master, ',');
        getline(inputFile, city);

        // Se crea un guardian con la informacion leida y se aagrega al vector
        guardians.push_back({name, powerLevel, master, city});
    }

	//Se cierra el archivo
    inputFile.close();

    return guardians; //se retornan los vectores
}

//La logica es la misma que la de los guardianes
vector<City> loadCities(const string& filename)
{
    vector<City> cities;

    ifstream inputFile(filename);

    if (!inputFile.is_open() || inputFile.fail())
	{
        cout << "Error al abrir el archivo de las Ciudades" << filename << endl;
        return cities;
    }
    
    string city, connectedCity;
    
    while(getline(inputFile, city, ','))
	{
        getline(inputFile, connectedCity);
        cities.push_back({city, {connectedCity}});
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

int main()
{
	
	vector<Guardian> guardians = loadGuardians("guardians.conf");
	vector<City> cities = loadCities("cities.conf");
	
	//Construccion Arbol de jerarquia
	for (Guardian& guardian : guardians)
	{
	    for (const Guardian& possibleApprentice : guardians)
		{
	        if(guardian.name != possibleApprentice.name && guardian.name == possibleApprentice.master)
			{
	            guardian.apprentices.push_back(possibleApprentice);
	        }
	    }
	
	    //Si el guardian no tiene aprendices el valor se toma como none
	    if(guardian.apprentices.empty())
		{
	        guardian.apprentices.push_back({"none", 0, "", ""});
	    }
	}
	
	// Mostrar los datos de los guardianes con sus aprendices
	cout << "DATOS GUARDIANES CARGADOS EXITOSAMENTE" << endl;
	for(const auto& guardian : guardians)
	{
	    cout << "Name: " << guardian.name << ", PowerLevel: " << guardian.powerLevel << ", Master: " << guardian.master << ", City: " << guardian.city << ", Apprentices: ";
	    for(const auto& apprentice : guardian.apprentices)
		{
	        cout << apprentice.name << " ";
	    }
	    cout << endl;
	}
    
	cout << "\nDATOS CIUDADES CARGADOS EXITOSAMENTE" << endl;
	for (const auto& city : cities)
	{
        cout << "City: " << city.City << ", Connected Cities: ";
        for(const auto& connectedCity : city.ConnectedCities)
		{
            cout << connectedCity << " ";
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
	            // IMPLEMENTAR
	            break;
	        case 2:
	            // IMPLEMENTAR
	            break;
	        case 3:
	            // IMPLEMENTAR
	            break;
	        case 4:
	            // IMPLEMENTAR
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
