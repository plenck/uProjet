#include <stdlib.h>
#include <stdio.h>
#include "projet.h"

int main(int agrc, char* agrv[]){

  IMAGEUCHAR image;
  printf("nb d'arguments : %d\n", agrc);
  if(agrc<2){
    printf("nb d'arguments trop faible \n");
  }
  if (lectureImagePgmBinaire(agrv[1], &image)==0){
    printf("lecture de l'image OK\n");
    resetImageUChar(&image);
    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
}
