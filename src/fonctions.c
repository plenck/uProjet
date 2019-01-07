#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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

PIXEL *alloueMemoireImageChar(int nl, int nc){
  PIXEL *tab;
  tab = calloc(nl*nc, sizeof(PIXEL));
  if (tab == NULL){
    exit(0);
  }
  return tab;
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
  PIXEL *tab;
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
    PIXEL *valeurs;
    size_t nbelement;
    valeurs = alloueMemoireImageChar((*image).nl, (*image).nc);
    nbelement = fread(valeurs, sizeof(PIXEL), (*image).nl * (*image).nc, f);
    printf("nbelemnt %ld \n", nbelement);
    (*image).val = valeurs;
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
