//
// Created by Morad on 05/10/2021.
//
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <image.h>

using namespace std;

int main (int argc, char *argv[]) {

    char *fich_orig, *fich_rdo; // nombres de los ficheros
    Image image;
    int fila, col, lado;

// Comprobar validez de la llamada
    if (argc != 6) {
        cerr << "Error: Numero incorrecto de parametros.\n";
        cerr << "Uso: zoom <FichImagenOriginal> <FichImagenDestino> <fila> <columna> <lado>\n";
        exit(1);
    }

// Obtener argumentos
    fich_orig = argv[1];
    fich_rdo = argv[2];
    fila = atoi(argv[3]);
    col = atoi(argv[4]);
    lado = atoi(argv[5]);
// Leer la imagen del fichero de entrada
    if (!image.Load(fich_orig)){
        cerr << "Error: No pudo leerse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        return 1;
    }

// Mostrar los parametros de la Imagen
    cout << endl;
    cout << "Dimensiones de " << fich_orig << ":" << endl;
    cout << "   Imagen   = " << image.get_rows()  << " filas x " << image.get_cols() << " columnas " << endl;

// Recortamos la imagen que queremos hacer zoom
    image = image.Crop(fila, col, lado, lado);

    Image zoom(2*lado - 1, 2*lado - 1);

    zoom = image.Zoom2X();

// Guardar la imagen resultado en el fichero
    if (zoom.Save(fich_rdo))
        cout  << "La imagen se guardo en " << fich_rdo << endl;
    else{
        cerr << "Error: No pudo guardarse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        return 1;
    }

}



