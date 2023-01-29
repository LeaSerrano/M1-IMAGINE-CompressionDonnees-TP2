#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcriteY[250], cNomImgEcriteCB[250], cNomImgEcriteCR[250];
  int nH, nW, nTaille;
  
  if (argc != 5) 
     {
       printf("Usage: ImageIn.ppm ImageOutY.pgm ImageOutCB.pgm ImageOutCR.pgm \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue);
   sscanf (argv[2],"%s",cNomImgEcriteY);
   sscanf (argv[3],"%s",cNomImgEcriteCB);
   sscanf (argv[4],"%s",cNomImgEcriteCR);

   OCTET *ImgIn, *ImgOutY, *ImgOutCB, *ImgOutCR;
   
   lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, nTaille*3);
   lire_image_ppm(cNomImgLue, ImgIn, nH * nW);

   allocation_tableau(ImgOutY, OCTET, nTaille);
   allocation_tableau(ImgOutCB, OCTET, nTaille);
   allocation_tableau(ImgOutCR, OCTET, nTaille);

    OCTET *tabIdR, *tabIdG, *tabIdB;

    allocation_tableau(tabIdR, OCTET, nTaille);
    allocation_tableau(tabIdG, OCTET, nTaille);
    allocation_tableau(tabIdB, OCTET, nTaille);

    planR(tabIdR, ImgIn, nTaille);
    planV(tabIdG, ImgIn, nTaille);
    planB(tabIdB, ImgIn, nTaille);

    int elt=0;
    for (int i = 0; i < nTaille; i++) {
      ImgOutY[i] = 0.299*tabIdR[elt] + 0.587*tabIdG[elt] + 0.114*tabIdB[elt];
      ImgOutCB[i] = -0.1687*tabIdR[elt] - 0.3313*tabIdG[elt] + 0.5*tabIdB[elt] + 128;
      ImgOutCR[i] = 0.5*tabIdR[elt] - 0.4187*tabIdG[elt] - 0.0813*tabIdB[elt] + 128;
      elt++;
    }

    ecrire_image_pgm(cNomImgEcriteY, ImgOutY,  nH, nW);
    ecrire_image_pgm(cNomImgEcriteCB, ImgOutCB,  nH, nW);
    ecrire_image_pgm(cNomImgEcriteCR, ImgOutCR,  nH, nW);
    free(ImgIn); free(ImgOutY); free(ImgOutCB); free(ImgOutCR);

    return 1;
}
