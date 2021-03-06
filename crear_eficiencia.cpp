#include <cstdlib> 
#include <iostream> 
#include <chrono>

#include <image.h>

using namespace std; 

auto do_routine(int rows, int cols, int repeats){
    // INICIO PARTE FUERA DEL CRONO
    // ...

    // FIN FUERA DEL CRONO

    // start time
    auto start = chrono::high_resolution_clock::now();

    // INICIO PARTE DENTRO DEL CRONO
    for (int j=0; j<repeats; j++){
        Image im(rows,cols);
        im.ShuffleRows();
    }
    //FIN PARTE DENTRO DEL CRONO

    // end time
    auto stop = chrono::high_resolution_clock::now();
    // microseconds count
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start).count();
    // return elapsed microseconds
    return duration;
}

int main (int argc, char ** argv) {

    int REPEATS = 10;

    cout << "SIZE\tROWS\tCOLS\tELAPSED\n";
    for (int rows=100; rows<=2000; rows+=200){
        for (int cols=100; cols<=2000; cols+=200){
            cout << rows*cols << "\t" << rows << "\t" << cols << "\t" << do_routine(rows,cols,REPEATS) << endl;
        }
    }

}


