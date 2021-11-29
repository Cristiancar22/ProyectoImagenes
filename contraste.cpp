//
// Created by Morad on 07/10/2021.
//

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <image.h>

using namespace std;

int main (int argc, char *argv[]){
    char *fich_orig, *fich_rdo; // nombre de los ficheros
    int e1, e2, s1, s2;
    Image image;

    // Comprobar validez de la llamada
    if(argc != 7){
        cerr << "Error: Numero incorrecto de argumentos.\n";
        cerr << "Uso: contraste <fich_orig> <fich_rdo> <e1> <e2> <s1> <s2>\n";
        exit (1);
    }

    // Obtener argumentos
    fich_orig = argv[1];
    fich_rdo = argv[2];
    e1 = atoi(argv[3]);
    e2 = atoi(argv[4]);
    s1 = atoi(argv[5]);
    s2 = atoi(argv[6]);

    // Mostrar argumentos
    cout << "Fichero origen: " << fich_orig << endl;
    cout << "Fichero resultado: " << fich_rdo << endl;
    cout << "e1: " << e1 << endl;
    cout << "e2: " << e2 << endl;
    cout << "s1: " << s1 << endl;
    cout << "s2: " << s2 << endl;

    // Leer imagen del fichero de entrada
    if(!image.Load(fich_orig)){
        cerr << "Error: No pudo leerse la imagen." << endl;
        cerr << "Terminando la ejecución del programa." << endl;
        return 1;
    }

    // Mostrar los parametros de la imagen
    cout << "Dimensiones de " << fich_orig << ":" << endl;
    cout << "Imagen = " << image.get_rows() << " filas x " << image.get_cols() << " columnas" << endl;

    // Convertir en bytes los valores int
    byte E1 = (byte) e1;
    byte E2 = (byte) e2;
    byte S1 = (byte) s1;
    byte S2 = (byte) s2;

    // Realizar el contraste de la imagen
    image.AdjustContrast(E1,E2,S1,S2);

    // Guardar la imagen resultado en el fichero
    if(image.Save(fich_rdo))
        cout << "La imagen se guardo en " << fich_rdo << endl;
    else{
        cerr <<"Error: No pudo guardarse la imagen " << endl;
        cerr << "Terminando la ejecucion del programa" << endl;
        return 1;
    }

    return 0;
}
