
// Created by Morad on 04/10/2021.

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <image.h>

using namespace std;

int main(int argc, char *argv[]){
    char *fich_orig,  *fich_rdo;
    int fila, col, filas_sub, cols_sub;
    Image image_orig, image_rdo;

   if (argc != 7){
        cerr << "Error: Numero incorrecto de argumentos." << endl;
        cerr << "Uso: subimagen <fich_orig> <fila> <col> <filas_sub> <cols_sub> <fich_rdo> " << endl;
        exit(1);
   }


    fich_orig  = argv[1];
    fich_rdo = argv[2];
    fila = atoi(argv[3]);
    col = atoi(argv[4]);
    filas_sub = atoi(argv[5]);
    cols_sub = atoi(argv[6]);

    cout << "Fichero origen: " << fich_orig << endl;
    cout << "Fichero resultado: " << fich_rdo << endl;

    if (!image_orig.Load(fich_orig)){
        cerr << "Error: No pudo leerse la imagen." << endl;
        cerr << "Terminando la ejecución del programa." << endl;
        return 1;
    }

    cout << "Dimensiones de " << fich_orig << ":" << endl;
    cout << "Imagen  = " << image_orig.get_rows() << " filas x " << image_orig.get_cols() << " columnas " << endl;

    image_rdo = image_orig.Crop(fila,col,filas_sub,cols_sub);

    if(image_rdo.Save(fich_rdo))
        cout << "La imagen se guardo en " << fich_rdo << endl;
    else{
        cerr <<"Error: No pudo guardarse la imagen" << endl;
        cerr << "Terminando la ejecucion del programam" << endl;
        return 1;
    }

    return 0;




}
