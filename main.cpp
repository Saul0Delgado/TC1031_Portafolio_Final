#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <unordered_map>

using namespace std;

struct Registro {
    string fecha;
    int dia;
    string hora;
    string ip;
    string mensaje;
};

bool compareRegistros(const Registro& a, const Registro& b) {
    string monthA = a.fecha;
    string monthB = b.fecha;
    
    // Compare the months using the numerical values
    if (months[monthA] != months[monthB]) {
        return months[monthA] < months[monthB];  // Sort by month in ascending order
    }

    return months[a.fecha] < months[b.fecha] || (months[a.fecha] == months[b.fecha] && a.dia < b.dia) || (months[a.fecha] == months[b.fecha] && a.dia == b.dia && a.hora < b.hora) ;
}

void read(vector<Registro>& registros);
void searchAndDisplay(const vector<Registro>& registros, const string& startDate, const string& endDate);
void saveSortedData(const vector<Registro>& registros);

int main() {
    vector<Registro> registros;
    read(registros);
    if (registros.empty()) {
        cout << "No se encontraron registros." << endl;
        return 1;
    }

    // Orden global de los meses
    unordered_map<std::string, int> months = {
        {"Jan", 1}, {"Feb", 2}, {"Mar", 3}, {"Apr", 4},
        {"May", 5}, {"Jun", 6}, {"Jul", 7}, {"Aug", 8},
        {"Sep", 9}, {"Oct", 10}, {"Nov", 11}, {"Dec", 12}
    }; 

    // Ordenar registros por fecha y hora
    sort(registros.begin(), registros.end(), compareRegistros);

    // Solicitar al usuario las fechas de inicio y fin de búsqueda
    string startDate, endDate;
    int startDay, endDay;
    cout << "Ingrese la fecha de inicio (MMM DD): ";
    cin >> startDate >> startDay;
    cout << "Ingrese la fecha de fin (MMM DD): ";
    cin >> endDate >> endDay;

    // Desplegar registros correspondientes a esas fechas
    searchAndDisplay(registros, startDate, endDate);

    // Almacenar en un archivo el resultado del ordenamiento
    saveSortedData(registros);

    system("pause");
    return 0;
}

void read(vector<Registro>& registros) {
    ifstream archivo("bitacora.txt");
    if (!archivo.is_open()) {
        cout << "No se pudo leer el archivo" << endl;
        exit(1);
    }

    string line;
    Registro registro;
    while (getline(archivo, line)) {
        archivo >> registro.fecha >> registro.dia >> registro.hora >> registro.ip;
        // Leer el resto de la línea como el mensaje
        getline(archivo, registro.mensaje);
        registros.push_back(registro);
    }

    archivo.close();
}

void searchAndDisplay(const vector<Registro>& registros, const string& startDate, const string& endDate, const string& startDay, const string& endDay) {
    cout << "Registros entre " << startDate << " y " << endDate << ":" << endl;
    for (const Registro& registro : registros) {
        string entryDate = registro.fecha;
        int entryDay = registro.dia;
        //months[a.fecha] < months[b.fecha] || (months[a.fecha] == months[b.fecha] && a.dia < b.dia)
        if (months[entryDate] >= months[startDate] && months[entryDate] <= months[endDate]) {            
            // AQUI NO HAY ORDEN EN LOS MESES CREO. RECHECK. ALSO MAKE SURE IT COUNTS EVERY DAY IF ITS WITHIN A MONTH THAT WASNT SPECIFIED
            if (entryDay >= startDay && entryDay <= endDay) {
            cout << registro.fecha << " " << registro.dia << " " << registro.hora << " " << registro.ip << " " << registro.mensaje << endl;
            }
        }
    }
}


void saveSortedData(const vector<Registro>& registros) {
    ofstream archivoOrdenado("bitacora_ordenada.txt");
    if (!archivoOrdenado.is_open()) {
        cout << "No se pudo crear el archivo de salida" << endl;
        exit(1);
    }

    for (const Registro& registro : registros) {
        archivoOrdenado << registro.fecha << " " << registro.dia << " " << registro.hora << " " << registro.ip << " " << registro.mensaje << endl;
    }

    archivoOrdenado.close();
}
