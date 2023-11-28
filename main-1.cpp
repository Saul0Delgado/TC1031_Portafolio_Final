#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>


using namespace std;

struct resDom { // estructura guarda informacion de cada uno
    int numAccesos;
    int numConexiones;
    vector<string> iPs;
};

void read(string &line, unordered_map<string, resDom> &registroHash) {

    ifstream archivo("bitacora.txt");
    if (!archivo.is_open()) {
        cout << "No se pudo leer el archivo" << endl;
        exit(1);
    }

    while (getline(archivo, line)) {
        istringstream iss(line);
        string mes, dia, hora, ip, mensaje;
        iss >> mes >> dia >> hora >> ip;

        size_t pos = ip.find(':');
        if (pos != string::npos){
            ip = ip.substr(0, pos);
        }

        iss.ignore(256, ' ');
        getline(iss, mensaje);

        pos = ip.rfind('.');
        if (pos != string::npos){
            string dominio = ip.substr(0, pos);

            if (registroHash.find(dominio) == registroHash.end()) {

                resDom newRes;
                newRes.numAccesos = 1;
                newRes.numConexiones = 1;
                newRes.iPs.push_back(ip);
                registroHash[dominio] = newRes;

            } else {

                registroHash[dominio].numAccesos++;

                bool ipExists = false;
                for (const auto &existingIP : registroHash[dominio].iPs){
                    if (existingIP == ip){
                        ipExists = true;
                        break;
                    }
                }

            if (!ipExists) {

                registroHash[dominio].numConexiones++;
                registroHash[dominio].iPs.push_back(ip);
                }

            }

        }

    }
    archivo.close();
}

void buscadorDom(const string &dominio, const unordered_map<string, resDom> &registroHash){
    auto it = registroHash.find(dominio);
    if (it != registroHash.end()) {

        cout << "Dominio: " << dominio << ";" << endl;
        cout << "Accesos: " << it->second.numAccesos << ";" << endl;
        cout << "Conexiones Unicas: " << it->second.numConexiones << ";" << endl;
        cout << "Direcciones IP: " << endl;
        for (const auto &ip : it->second.iPs) {
            cout << "- " << ip << endl;
        }

    } else {

        cout << "Dominio " << dominio << " no existe." << endl;

    }
}

int main () {

    string line;
    unordered_map<string, resDom> registroHash;
    read(line, registroHash);

    string dominioBuscado;
    cout << "Inserta los primeros tres segmentos del IP para buscar el dominio y la informacion: ";
    cin >> dominioBuscado;

    buscadorDom(dominioBuscado, registroHash);

    return 0;

}