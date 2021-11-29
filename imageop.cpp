/**
 * @file imageop.cpp
 * @brief Fichero con definiciones para el resto de métodos de la clase Image
 */

#include <iostream>
#include <cmath>
#include <image.h>
#include <cassert>

Image Image::Crop(int nrow, int ncol, int height, int width) const
{
    Image recortada(height,width);

    for (int i = 0, k = nrow; i < height && k < get_rows(); i++, k++)
        for(int j = 0, l = ncol; j < width && l < get_cols(); j++, l++ )
            recortada.set_pixel(i,j, get_pixel(k,l));

    return recortada;
}

void Image::AdjustContrast(byte in1, byte in2, byte out1, byte out2)
{
    byte a, b, min, max, pixel_ajus;
    double exp,pixel;
    byte pixel_orig;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {

            pixel_orig = get_pixel(i,j);

            if (pixel_orig >= 0  && pixel_orig < in1){
                a = 0;
                b = (int) in1;
                min = 0;
                max = (int) out1;
            }
            else if(pixel_orig >= in1 && pixel_orig <= in2){
                a = (int) in1;
                b = (int) in2;
                min = (int) out1;
                max = (int) out2;
            }
            else if (pixel_orig > in2 && pixel_orig <= 255){
                a = (int) in2;
                b = 255;
                min = (int)out2;
                max = 255;
            }

            exp = (max - min) * 1.0/ (b-a) * 1.0;

            pixel = min + (exp * (pixel_orig - a));


            pixel_ajus = round(pixel);

            set_pixel(i,j,pixel_ajus);

        }
    }
}

Image Image::Subsample(int factor) const
{
    Image icono(get_rows()/factor,get_cols()/factor);
    int x = 0, y = 0;
    byte pixel;

    if(icono.get_rows() == 1) {
        pixel = (byte) round(Mean(0, 0, get_rows(), get_cols()));
        icono.set_pixel(0, 0, pixel);
    }
    else {
        for (int i = 0; i < icono.get_rows(); i++) {
            for (int j = 0; j < icono.get_cols(); j++) {
                pixel = (byte) round(Mean(x, y, factor, factor));
                icono.set_pixel(i, j, pixel);
                y += factor;
            }
            x += factor;
            y = 0;
        }
    }
    return icono;
}

double Image::Mean(int i, int j, int height, int width) const
{
    int suma_pixels = 0;
    double media;

    for (int l = i; l < i + height; l++)
        for (int k = j; k < j + width; k++)
            suma_pixels += this->get_pixel(l,k);

    media = (suma_pixels*1.0)/((height * width)* 1.0);

    return media;
}

Image Image::Zoom2X() const
{
    int x,y;
    int media, pixel_ant, pixel_post, pixel_ant1, pixel_post1;
    Image zoom(2*cols - 1, 2*cols - 1);

    for (int i = 0; i < cols; i++)
        for (int j = 0; j < cols; j++)
            zoom.set_pixel(i*2,j*2,get_pixel(i,j));

    for (int k = 1; k < cols; k++){
        for (int l = 0; l < zoom.get_cols(); l++){

            x = 2*k-1;
            y = l;

            if ((x+y) % 2 == 0){
                pixel_ant = zoom.get_pixel(x-1,y-1);
                pixel_ant1 = zoom.get_pixel(x+1,y-1);
                pixel_post = zoom.get_pixel(x-1,y+1);
                pixel_post1 = zoom.get_pixel(x+1,y+1);

                media = round(((pixel_post+pixel_post1+pixel_ant+pixel_ant1)*1.0)/(4*1.0));

                zoom.set_pixel(x,y,media);
            }
            else{
                pixel_ant = zoom.get_pixel(x-1,y);
                pixel_post = zoom.get_pixel(x+1,y);

                media = round(((pixel_ant + pixel_post)*1.0)/(2*1.0));

                zoom.set_pixel(x,y,media);

            }
        }
    }


    for (int i = 0; i < cols; i++){
        for(int j = 1; j < cols; j++ ){

            x = 2 * i;
            y = (2 * j) - 1;

            pixel_ant = zoom.get_pixel(x,y-1);
            pixel_post = zoom.get_pixel(x,y+1);

            media = round(((pixel_ant + pixel_post)*1.0)/(2*1.0));

            zoom.set_pixel(x,y,media);

        }
    }

    return zoom;
}
void Image::Invert()
{
    for (int i=0; i<size(); i++)
        set_pixel(i,255-get_pixel(i));
}

void Image::ShuffleRows()
{
    const int p = 9973;
    int newr;
    byte * a = &img[0][0];

    for (int r=0; r<rows; r++){
        newr = (r*p)%(rows);
        img[r] = a+newr*cols;
    }
}

    /*
    const int p = 9973;
    Image temp(rows,cols);
    int newr;
    for (int r=0; r<rows; r++){
        newr = (r*p)%rows;
        for (int c=0; c<cols;c++)
            temp.set_pixel(r,c,get_pixel(newr,c));
    }
    Copy(temp);
}*/



