#include "lodepng.h"
#include <stdio.h>


char* loadPng(const char* filename, int* width, int* height) {
  
  unsigned char* image = NULL;
  unsigned int width, height;

  int error = lodepng_decode32_file(&image, width, height, filename);
  if(error) 
  {
    printf("error %u: %s\n", error, lodepng_error_text(error));
  }
  
  return (image);
}



void writePng(const char* filename, const unsigned char* image, unsigned width, unsigned height) {
  unsigned char* png;
  int pngsize;

  int error = lodepng_encode32(&png, &pngsize, image, width, height);
  if(!error) {
    lodepng_save_file(png, pngsize, filename);
  }

  /*if there's an error, display it*/
  if(error) printf("error %u: %s\n", error, lodepng_error_text(error));

  free(png);
}

void get_pixel(int x, int y, int *r, int *g, int *b, int *a, char* image, int width ) 
{

   *r =  image[4 * width * y + 4 * x + 0]; 
   *g =  image[4 * width * y + 4 * x + 1]; 
   *b =  image[4 * width * y + 4 * x + 2]; 
   *a =  image[4 * width * y + 4 * x + 3];
   
   return;
}

bool is_close(int r1, r2, g1, g2, b1, b2) {
    int e_r = 10;
    return fabs(r1 - r2) < e_r 
        &&  fabs(g1 - g2) < e_g 
        &&  fabs(b1 - b2) < e_b
    }

bool 
is_black(int r, g, b) {
  // Here is the place for experiments and improvments
      int gray=(r+g+b)/3; 
      if ( gray < 128 ) {
        return true;
      } else 
        return false;
}


struct Graph {
  int ** V;
  int N; // number of vertices of G;
};

Graph* init_graph(int N) {
  Graph * pG = (Graph*)malloc(sizeof(Graph));
  pG->V = (int**) malloc(N*sizeof(int*));
// add links for incedent vertices
for (int i =0 ; i < N; i++) {
   ???????? 
  pG->V[i] = malloc()
}
  return pG;
}


int add_edge(Graph *G, int i, int j , int x, int y, int width) {
  int n = i*width + j;
  int m = x*width + y;
  int *incedent = p->V[n];
  for (????)  {
    // if m not in incedent[] - add it there!
  }

}

int main() {

    char * filename = "skull.png";
    int w, h;
    char * picture = loadPng(filename, &w, &h);
    if (picture == NULL){
        printf("I can not read the picture from the file %s. Error.\n", filename);
        return -1;
    }
    
    Graph* G = init_graph(w*h);
    if (G == NULL) {
      printf("Can not allocate memory for Graph\n");
      return -1;
    }


    // read file and convert it to 2D array
        // function get_pixel is simple
    for (int i = 1; i < w-1; i++){
        for (int j = 1; j < h-1; j++){
            int r, g, b, a;
            int r1, g1, b1, a1;
            get_pixel(i, j, &r, &g, &b, &a, picture, w);
            
            get_pixel(i-1, j, &r1, &g1, &b1, &a1, picture, w );
            if (is_close(r,  g,  b,  a,
                         r1, g1, b1, a1  )) {
                             add_edge(G, i,j , i-1, j, w);
                         }

            get_pixel(i+1, j, &r1, &g1, &b1, &a1, picture, w );
            if (is_close(r,  g,  b,  a,
                         r1, g1, b1, a1  )) {
                             add_edge(G, i,j , i+1, j, w);
                         }
            get_pixel(i, j-1, &r1, &g1, &b1, &a1, picture, w );
            if (is_close(r,  g,  b,  a,
                         r1, g1, b1, a1,  )) {
                        add_edge(G, i,j , i, j-1, w);
            }
            get_pixel(i, j+1, &r1, &g1, &b1, &a1, picture, w );
            if (is_close(r,  g,  b,  a,
                         r1, g1, b1, a1  )) {
                        add_edge(G, i,j , i, j+1, w);
            }


        }
    }


    // analyze 2D array
        // use graph connectivity algorithm for connectivity areas

    // convert 2D array to file and write it
    char * new_image = "scull-modified.png";
    writePng(new_image, picture, w, h);

    return 0;
}


