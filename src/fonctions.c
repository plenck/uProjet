#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "projet.h"
/*
----------------------------------------------------------------------------
FONCTION : alloueMemoireImageChar
----------------------------------------------------------------------------
DESCRIPTION : allocation de l'espace memoire pour les pixels
----------------------------------------------------------------------------
PARAMETERS :
  -int nl , nc ;
    nl : nb de ligne
    nc : nb de colonnes
----------------------------------------------------------------------------
RETURN : adresse de l'addresse du premier element du tableau
----------------------------------------------------------------------------
*/

PIXEL **alloueMemoireImageChar(int nl, int nc){
  PIXEL **image; //tableau contenant les adresses des lignes
  image = NULL ;

  image = calloc(nl, sizeof(PIXEL*));
  if (image == NULL){
    exit(0);
    }
  int i;
  for(i = 0 ; i < nl ; i++){
    image[i] = NULL;
    image[i] = calloc(nc , sizeof(PIXEL));
    if (image[i] == NULL){
      exit(0);
    }
  }
  return image;
}

/*
----------------------------------------------------------------------------
FONCTION : creationImageUChar
----------------------------------------------------------------------------
DESCRIPTION : Creation d’une image de d’unsigned char avec allocation dynamique
              de l’espace des pixels
----------------------------------------------------------------------------
PARAMETERS :
  - int nc
  - int nl
----------------------------------------------------------------------------
RETURN : IMAGEUCHAR structure contenant le tableau de pixels
----------------------------------------------------------------------------
*/
/*
IMAGEUCHAR creationImageUChar(int nl, int nc){
  IMAGEUCHAR image;
  image.nl = nl;
  image.nc = nc;
  PIXEL **tab;
  tab = NULL;
  tab = alloueMemoireImageChar(nl,nc);
  return image;
}
*/
/*
----------------------------------------------------------------------------
FONCTION : lectureImagePgmBinaire
----------------------------------------------------------------------------
DESCRIPTION : lecture d'une image dans un fichier
----------------------------------------------------------------------------
PARAMETERS :
  - char *fichier
  - IMAGEUCHAR *image
----------------------------------------------------------------------------
RETURN : retourne 0 si succès, toute autre valeur sinon
----------------------------------------------------------------------------
*/

int lectureImagePgmBinaire(char *fichier, IMAGEUCHAR *image){
  /*=====VERIFICATION DU FORMAT DU FICHIER===== */
  FILE *f;
  printf("ouverture de %s \n",fichier);
  f = fopen(fichier, "rb" );

  if(f==NULL ){
    printf("Erreur fichier introuvable\n");
    return 1;
  }

  char s[60];

  if (fgets(s,60,f)!= NULL){
    if(strcmp(s, "P5\n")==0){
      printf("ouverture du fichier\n");
    }
    else {
      printf("%s",s);
      printf("erreur format de l'image 'P5' non trouvé\n");
      return 1;
    }
  }
  else {
    printf("fgets à foiré\n");
  }

  fgets(s,60,f); // on lit la ligne de commentaire pour l'ignorer
  printf("commenttaire igoré : %s\n", s);


  /*======LECTURE DU CONTENU =======*/
  int iMax; // iMax : intensité maximale

  fscanf(f,"%d %d %d", &(*image).nl, &(*image).nc, &iMax);
  printf("nl = %d\n", (*image).nl);
  printf("nc = %d\n", (*image).nc);
  printf("valeur de iMax : %d\n", iMax);

  if (iMax == 255){
    PIXEL **tabpix;
    tabpix = NULL;
    size_t nbelement;
    tabpix = alloueMemoireImageChar((*image).nl, (*image).nc); //allocation de l'espace des pixels
    int i;
    for (i = 0; i< (*image).nl ; i++){
      nbelement = fread(tabpix[i], sizeof(PIXEL), (*image).nc, f);
      if (nbelement != (size_t)(*image).nc){
        printf("nombre de valeurs lues != du nb de colonnes \n");
      }
    }
    image->val = tabpix ;
    return 0;
  }
  else {
    printf("erreur lecture de l'image impossible\n");
    printf("intensité > 255\n");
    return 1;
  }
}

/*
----------------------------------------------------------------------------
FONCTION : resetImageUChar
----------------------------------------------------------------------------
DESCRIPTION :  Reset l’image avec liberation de l’espace memoire des pixels, mise a 0 des nombres de lignes et de
colonnes
----------------------------------------------------------------------------
PARAMETERS :
  - IMAGEUCHAR *im
----------------------------------------------------------------------------
RETURN : void
----------------------------------------------------------------------------
*/

void resetImageUChar(IMAGEUCHAR *im){
  (*im).nc = 0;
  (*im).nl = 0;
  free((*im).val);
}

/*
----------------------------------------------------------------------------
FONCTION : distance
----------------------------------------------------------------------------
DESCRIPTION : Distance d^2 entre le modele et l’image au pixel de coordonees
              is, js
----------------------------------------------------------------------------
PARAMETERS :
  - IMAGEUCHAR im
  - IMAGEUCHAR patch
      passage par adresse : c'est dans patch que l'on stocke la matrice
  - int is
  - int js
----------------------------------------------------------------------------
RETURN : int distance : valeur de distance
----------------------------------------------------------------------------
*/
int distance(IMAGEUCHAR im, IMAGEUCHAR patch, int is, int js){
  int distquadra; //distance (ecart quadratique)
  int nlm, ncm;
  nlm = patch.nl;
  ncm = patch.nc;
  int sum;
  int i, j ;
  for(i=0 ; i<(nlm-1); i++){
    for(j=0 ; i <(ncm-1) ; i++){
        sum += pow((im.val[((is+im.nl)%im.nl)-nlm/2+i][((js+im.nc)%im.nc)-ncm/2+j]-patch.val[i][j]), 2);
    }
  }

  distquadra = (1/nlm*ncm)*sum;
  return distquadra;
}
