#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>

using namespace std;

void read();
int main(){
    read();

    system("pause");
    return 0;

}

void read(){
    ifstream archivo;
    string texto;

    archivo.open("bitacora.txt",ios::in);

    if(archivo.fail()){
        cout<<"No se puedo leer el archivo";
        exit(1);
    }

    while (!archivo.eof()){
        getline(archivo,texto);

        cout<<texto<<endl;
    }

    archivo.close();
}