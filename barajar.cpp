//
// Created by Morad on 13/10/2021.
//
#include "image.h"
#include "imageIO.h"
#include <iostream>

using namespace  std;

int main(int argc, char ** argv)
{
    char *fich_orig, *fich_rdo; // nombre de los ficheros
    Image image;

    fich_orig = argv[1];
    fich_rdo = argv[2];

    if(!image.Load(fich_orig)){
        cerr << "Error: No pudo leerse la imagen." << endl;
        cerr << "Terminando la ejecución del programa." << endl;
        return 1;
    }

    image.ShuffleRows();

    if(image.Save(fich_rdo))
        cout << "La imagen se guardo en " << fich_rdo << endl;
    else{
        cerr <<"Error: No pudo guardarse la imagen " << endl;
        cerr << "Terminando la ejecucion del programa" << endl;
        return 1;
    }

    return 0;
}