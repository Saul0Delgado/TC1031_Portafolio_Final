#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <regex>

using namespace std;

struct Registro {
    string fecha;
    int dia;
    string hora;
    string ip;
    string mensaje;
};

bool compareRegistrosDate(const Registro& a, const Registro& b) {
    // Orden de los meses
    unordered_map<std::string, int> months = {
        {"Jan", 1}, {"Feb", 2}, {"Mar", 3}, {"Apr", 4},
        {"May", 5}, {"Jun", 6}, {"Jul", 7}, {"Aug", 8},
        {"Sep", 9}, {"Oct", 10}, {"Nov", 11}, {"Dec", 12}
    }; 

    string monthA = a.fecha;
    string monthB = b.fecha;

    // Compare the months using the numerical values
    if (months[monthA] != months[monthB]) {
        return months[monthA] < months[monthB];  // Sort by month in ascending order
    }

    return months[a.fecha] < months[b.fecha] || (months[a.fecha] == months[b.fecha] && a.dia < b.dia) || (months[a.fecha] == months[b.fecha] && a.dia == b.dia && a.hora < b.hora) ;
}

bool compareRegistrosIp(const Registro& a, const Registro& b) {
       // Divide las direcciones IP en componentes numéricos
    istringstream a_stream(a.ip);
    istringstream b_stream(b.ip);

    int a1, a2, a3, a4, b1, b2, b3, b4;
    char dot;

    a_stream >> a1 >> dot >> a2 >> dot >> a3 >> dot >> a4;
    b_stream >> b1 >> dot >> b2 >> dot >> b3 >> dot >> b4;

    if (a1 != b1) return a1 < b1;
    if (a2 != b2) return a2 < b2;
    if (a3 != b3) return a3 < b3;
    return a4 < b4;
}

void read(vector<Registro>& registros);
void searchAndDisplayDate(const vector<Registro>& registros);
void searchAndDisplayIp(const vector<Registro>& registros);
void saveSortedData(const vector<Registro>& registros);

int main() {
    vector<Registro> registros;
    read(registros);
    if (registros.empty()) {
        cout << "No se encontraron registros." << endl;
        return 1;
    }

    int choice;

    cout << "Selecciona por que factor quiere ordenar (por su numero) :\n1) Fecha\n2) IP" << endl;
    cin >> choice;

    switch(choice) {
        case 1:
            // Ordenar registros por fecha y hora
            sort(registros.begin(), registros.end(), compareRegistrosDate);

            // Desplegar registros correspondientes a esas fechas
            searchAndDisplayDate(registros);

            // Almacenar en un archivo el resultado del ordenamiento
            saveSortedData(registros);

            system("pause");
            break;

        case 2:

             // Ordenar registros por Ip
            sort(registros.begin(), registros.end(), compareRegistrosIp);

            // Desplegar registros correspondientes a estas Ip
            searchAndDisplayIp(registros);

            // Almacenar en un archivo el resultado del ordenamiento
            saveSortedData(registros);

            system("pause");
            break;
    }
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

void searchAndDisplayDate(const vector<Registro>& registros) {
    // Solicitar al usuario las fechas de inicio y fin de búsqueda
    string startMonth, endMonth;
    int startDay, endDay;

    cout << "Ingrese el mes de inicio (MMM): ";
    cin >> startMonth;
    cout << "\nIngrese el dia de inicio: ";
    cin >> startDay;

    cout << "\nIngrese el mes de fin (MMM): ";
    cin >> endMonth;
    cout << "\nIngrese el dia de fin: ";
    cin >> endDay;

    cout << "\nRegistros entre " << startMonth << " " << startDay << " y " << endMonth << " " << endDay << ":" << endl;

    // Orden de los meses
    unordered_map<std::string, int> months = {
        {"Jan", 1}, {"Feb", 2}, {"Mar", 3}, {"Apr", 4},
        {"May", 5}, {"Jun", 6}, {"Jul", 7}, {"Aug", 8},
        {"Sep", 9}, {"Oct", 10}, {"Nov", 11}, {"Dec", 12}
    }; 

    for (const Registro& registro : registros){
        string entryMonth = registro.fecha;
        int entryDay = registro.dia;

        if ((months[entryMonth] > months[startMonth] || (months[entryMonth] == months[startMonth] && entryDay >= startDay)) && 
            (months[entryMonth] < months[endMonth] || (months[entryMonth] == months[endMonth] && entryDay <= endDay))) {         
            cout << registro.fecha << " " << registro.dia << " " << registro.hora << " " << registro.ip << " " << registro.mensaje << endl;
        }
    }
}

void searchAndDisplayIp(const vector<Registro>& registros) {
    // Solicitar al usuario las Ips de inicio y fin de búsqueda
    string startIp, endIp;
    cout << "Ingrese la IP de inicio : ";
    cin >> startIp;
    cout << "Ingrese la IP de fin : ";
    cin >> endIp;

    cout << "Registros entre " << startIp << " y " << endIp << ":" << endl;

    for (const Registro& registro : registros){

        string entryIp = registro.ip;

        if ((entryIp >= startIp) && (entryIp <= endIp)) {         
            cout << registro.ip << " " << registro.fecha << " " << registro.dia << " " << registro.hora  << " " << registro.mensaje << endl;
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