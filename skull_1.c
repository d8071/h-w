#include "lodepng.h"
#include "lodepng.c"
#include <stdio.h>
#include <stdlib.h>


char* loadPng(const char* filename, int* width, int* height) {

  unsigned char* image = NULL;
 // unsigned int width, height;

  int error = lodepng_decode32_file(&image, width, height, filename);
  if(error)
  {
    printf("error %u: %s\n", error, lodepng_error_text(error));
  }

  return (image);
}

void writePng(const char* filename, const unsigned char* image, unsigned width, unsigned height) {
  unsigned error;
  unsigned char* png;
  size_t pngsize;
  LodePNGState state;

  lodepng_state_init(&state);
  /*optionally customize the state*/

  error = lodepng_encode(&png, &pngsize, image, width, height, &state);
  if(!error) lodepng_save_file(png, pngsize, filename);

  /*if there's an error, display it*/
  if(error) printf("error %u: %s\n", error, lodepng_error_text(error));

  lodepng_state_cleanup(&state);
  free(png);
}


void GaussFilter(unsigned char * picture, unsigned char * result, int w, int height) {
    int i,j;
    for(i = 1; i < 4*height - 1; i++)
    for (j = 1; j < w - 1; j++)
        result[i * w + j] = 0.0924 * picture[(i-1) * w + (j-1)] + 0.1192 * picture[(i-1) * w + j] + 0.0924 * picture[(i-1) * w + (j+1)] + 0.1192 * picture[i * w + (j-1)] + 0.1538 * picture[i * w + j] + 0.1192 * picture[i * w + (j+1)] + 0.0924 * picture[(i+1) * w + (j-1)] + 0.1192 * picture[(i+1) * w + j] + 0.0924 * picture[(i+1) * w + (j+1)];
    return;
}


int main() {

    char * filename = "skull.png";
    int w, h;
    int i,j;

    unsigned char * picture = loadPng(filename, &w, &h);
    if (picture == NULL){
        printf("I can not read the picture from the file %s. Error.\n", filename);
        return -1;
    }

    unsigned char * picture1 = (unsigned char*)malloc(w*h*sizeof(unsigned char));
    unsigned char * picture2 = (unsigned char*)malloc(w*h*sizeof(unsigned char));
    unsigned char * picture3 = (unsigned char*)malloc(4*w*h*sizeof(unsigned char));

    picture1 = picture;

    int r,g,b;
    for (i = 0; i < h; i++)
    for (j = 0; j < w; j++) {
        r = picture[4 * w * i + 4 * j + 0];
        g = picture[4 * w * i + 4 * j + 1];
        b = picture[4 * w * i + 4 * j + 2];

        picture1[4 * w * i + 4 * j + 0] = 0.3*r + 0.59*g + 0.1*b;
        picture1[4 * w * i + 4 * j + 1] = 0.3*r + 0.59*g + 0.1*b;
        picture1[4 * w * i + 4 * j + 2] = 0.3*r + 0.59*g + 0.1*b;
    }
    /*int k = 0;
    for (i=0; i < 4*w*h; i++)
        picture1[k++] = (picture[i] + picture[i+1] + picture[i+2])/3;

    /*for (i=0; i < 4*h; i++)
    for (j=0; j < w; j++) {
        if (picture1[i * w + j] < 100) picture1[i * w + j] = 0;
        if (picture1[i * w + j] > 150) picture1[i * w + j] = 255;
    }
*/

    for (i = 0; i < h; i++)
    for (j = 0; j < w; j++) {
        r = picture[4 * w * i + 4 * j + 0];
        g = picture[4 * w * i + 4 * j + 1];
        b = picture[4 * w * i + 4 * j + 2];

        if ((r + g + b) / 3 < 110) {
            picture1[4 * w * i + 4 * j + 0] = 0;
            picture1[4 * w * i + 4 * j + 1] = 0;
            picture1[4 * w * i + 4 * j + 2] = 0;
        }

        if ((r + g + b) / 3 > 150) {
            picture1[4 * w * i + 4 * j + 0] = 255;
            picture1[4 * w * i + 4 * j + 1] = 255;
            picture1[4 * w * i + 4 * j + 2] = 255;
        }
    }

    picture2 = picture1;

    //GaussFilter(picture1,picture2,w,h);

    /*for(i = 4; i < 4*h-4; i++)
    for (j = 0; j < w; j++) {
        picture2[i * w + j] = (-2) * picture1[(i-4) * w + (j-1)];
        picture2[i * w + j] += (-1) * picture1[(i-4) * w + j];
        picture2[i * w + j] += (-2) * picture1[(i-4) * w + (j+1)];
        picture2[i * w + j] += (-1) * picture1[i * w + (j-1)];
        picture2[i * w + j] += (17) * picture1[i * w + j];
        picture2[i * w + j] += (-1) * picture1[i * w + (j+1)];
        picture2[i * w + j] += (-2) * picture1[(i+4) * w + (j-1)];
        picture2[i * w + j] += (-1) * picture1[(i+4) * w + j];
        picture2[i * w + j] += (-2) * picture1[(i+4) * w + (j+1)];
    }*/

    /*for(i = 4; i < 4*h-4; i++)
    for (j = 0; j < w; j++) {
        picture2[i * w + j] = (0.0924) * picture1[(i-4) * w + (j-1)];
        picture2[i * w + j] += (0.1192) * picture1[(i-4) * w + j];
        picture2[i * w + j] += (0.0924) * picture1[(i-4) * w + (j+1)];
        picture2[i * w + j] += (0.1192) * picture1[i * w + (j-1)];
        picture2[i * w + j] += (0.1538) * picture1[i * w + j];
        picture2[i * w + j] += (0.1192) * picture1[i * w + (j+1)];
        picture2[i * w + j] += (0.0924) * picture1[(i+4) * w + (j-1)];
        picture2[i * w + j] += (0.1192) * picture1[(i+4) * w + j];
        picture2[i * w + j] += (0.0924) * picture1[(i+4) * w + (j+1)];
    }

    /*picture1 = picture2;
    int l = 0;
    for (i=0; i < 4*w*h; i++)
        picture1[l++] = 0.2 * picture2[i] + 0.6 * picture2[i+1] + 0.114 * picture2[i+2];
*/

    int q;
    for (i = 1; i < h - 1; i++)
    for (j = 1; j < w - 1; j++)
    for (q = 0; q < 3; q++) {
        picture2[4 * i * w + 4 * j + q] = 0.0924 * picture1[4 * (i-1) * w + 4 *(j-1) + q];
        picture2[4 * i * w + 4 * j + q] += 0.1192 * picture1[4 * (i-1) * w + 4 * j + q];
        picture2[4 * i * w + 4 * j + q] += 0.0924 * picture1[4 * (i-1) * w + 4 * (j+1) + q];
        picture2[4 * i * w + 4 * j + q] += 0.1192 * picture1[4 * i * w + 4 * (j-1) + q];
        picture2[4 * i * w + 4 * j + q] += 0.1538 * picture1[4 * i * w + 4 * j + q];
        picture2[4 * i * w + 4 * j + q] += 0.1192 * picture1[4 * i * w + 4 * (j+1) + q];
        picture2[4 * i * w + 4 * j + q] += 0.0924 * picture1[4 * (i+1) * w + 4 * (j-1) + q];
        picture2[4 * i * w + 4 * j + q] += 0.1192 * picture1[4 * (i+1) * w + 4 * j + q];
        picture2[4 * i * w + 4 * j + q] += 0.0924 * picture1[4 * (i+1) * w + 4 * (j+1) + q];

    }

    /*int x,y;
    double G[3][3];
    G[0][0] = 0.0924;
    G[0][1] = 0.1192;
    G[0][2] = 0.0924;
    G[1][0] = 0.1192;
    G[1][1] = 0.1538;
    G[1][2] = 0.1192;
    G[2][0] = 0.0924;
    G[2][1] = 0.1192;
    G[2][2] = 0.0924;

    for (i = 0; i < w; i++)
        for (j = 0; j < h; j++)
            for (x = -1; x <= 1; x++)
                for (y = -1; y <= 1; y++)
                    picture2[(i + x) * h + j + y] += G[2 - x][2 - y];*/




    /*double x,y;
    for(i = 1; i < h - 1; i++)
    for (j = 1; j < w - 1; j++) {
        x = (-1) * picture1[(i-1)*w+(j-1)] - 2*picture1[i*w+(j-1)] - 1 * picture1[(i+1)*w+(j-1)] + picture1[(i-1)*w+j+1] + 2*picture1[i*w+j+1] + picture1[(i+1)*w+j+1];
        y = (-1)*picture1[(i-1)*w+j-1] - 2*picture1[(i-1)*w+j] - picture1[(i-1)*w+j+1] + picture1[(i+1)*w+j-1] + 2*picture1[(i+1)*w+j] + picture1[(i+1)*w+j+1];
        picture2[i*w+j] = sqrt(x*x+y*y);
    }*/
/*
    for (i=w+1; i < 4 * w * h - w - 1; i++) {
        picture2[i] = 0.09 * picture1[i-w-1] + 0.1192 * picture1[i-w] + 0.09 * picture1[i-w+1] + 0.1192 * picture1[i-1] + 0.1538 * picture1[i] + 0.1192 * picture1[i+1] + 0.09 * picture1[i+w-1] + 0.1192 * picture1[i+w] + 0.09 * picture1[i+w+1];

    }
    */
    picture3 = picture2;

    for ( i = 1; i < h; i++)
    for (j = 0; j < w; j++) {
        picture3[4 * i * w + 4 * j + 0] = picture2[4 * i * w + 4 * j + 0] + 10;
        picture3[4 * i * w + 4 * j + 1] = picture2[4 * i * w + 4 * j + 1] + 80;
        picture3[4 * i * w + 4 * j + 2] = picture2[4 * i * w + 4 * j + 2] + 160;
        picture3[4 * i * w + 4 * j + 3] = 255;
    }

    /*int c[w*h];
    for(i = 0; i < w*h; i++)
        c[i] = picture2[i];*/

    /*for (i = 1; i < 4 * w * h - 4; i+=4) {
        picture3[i] = 30 + picture2[i] + 0.5 * picture2[i-1];
        picture3[i+1] = 25 + picture2[i] + 0.2*picture2[i-1];
        picture3[i+2] = 170 + picture2[i];
        picture3[i+4] = 255;
    }

    /*for(i = 0; i < h - 1; i++)
    for (j = 0; j < w - 1; j++) {
        picture3[i * w + j + 0] = 30 + picture2[i * w + j ];
        picture3[i * w + j + 1] = 25 + picture2[i * w + j ];
        picture3[i * w + j + 2] = 70 + picture2[i * w + j ];
        picture3[i * w + j + 3] = 255;
    }*/

    char * new_image = "scull-modified.png";
    writePng(new_image, picture3, w, h);

    //free(new_image);
    //free(picture1);
    //free(picture2);
    //free(picture3);

    return 0;
}


