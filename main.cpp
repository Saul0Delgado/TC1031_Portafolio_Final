#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

struct Registro {
    string fecha;
    string hora;
    string ip;
    string mensaje;
};

bool compareRegistros(const Registro& a, const Registro& b) {
    return a.fecha < b.fecha || (a.fecha == b.fecha && a.hora < b.hora);
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

    // Ordenar registros por fecha y hora
    sort(registros.begin(), registros.end(), compareRegistros);

    // Solicitar al usuario las fechas de inicio y fin de búsqueda
    string startDate, endDate;
    cout << "Ingrese la fecha de inicio (MM DD): ";
    cin >> startDate;
    cout << "Ingrese la fecha de fin (MM DD): ";
    cin >> endDate;

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

    Registro registro;
    while (archivo >> registro.fecha >> registro.hora >> registro.ip) {
        // Leer el resto de la línea como el mensaje
        getline(archivo, registro.mensaje);
        registros.push_back(registro);
    }

    archivo.close();
}

void searchAndDisplay(const vector<Registro>& registros, const string& startDate, const string& endDate) {
    cout << "Registros entre " << startDate << " y " << endDate << ":" << endl;
    for (const Registro& registro : registros) {
        if (registro.fecha >= startDate && registro.fecha <= endDate) {
            cout << registro.fecha << " " << registro.hora << " " << registro.ip << " " << registro.mensaje << endl;
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
        archivoOrdenado << registro.fecha << " " << registro.hora << " " << registro.ip << " " << registro.mensaje << endl;
    }

    archivoOrdenado.close();
}
