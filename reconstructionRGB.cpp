#include <stdio.h>
#include "image_ppm.h"
#include <list>
#include <algorithm>
#include <iostream>
#include <vector>

int main(int argc, char* argv[])
{
  char cNomImgEcrite[250], cNomImgLueInterR[250], cNomImgLueInterG[250], cNomImgLueInterB[250];
  int nH, nW, nTaille;
  
  if (argc != 5) 
     {
       printf("Usage: ImageIn.pgm ImageOut1.pgm\n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLueInterR);
   sscanf (argv[2],"%s",cNomImgLueInterG);
   sscanf (argv[3],"%s",cNomImgLueInterB);
   sscanf (argv[4],"%s",cNomImgEcrite) ;

   OCTET *ImgInterR, *ImgInterG, *ImgInterB, *ImgOut;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLueInterR, &nH, &nW);
   nTaille = nH * nW;
   int nTaille3 = nTaille * 3;

   allocation_tableau(ImgInterR, OCTET, nTaille);
   allocation_tableau(ImgInterG, OCTET, nTaille);
   allocation_tableau(ImgInterB, OCTET, nTaille);
   allocation_tableau(ImgOut, OCTET, nTaille3);

   lire_image_pgm(cNomImgLueInterR, ImgInterR, nH * nW);
   lire_image_pgm(cNomImgLueInterG, ImgInterG, nH * nW);
   lire_image_pgm(cNomImgLueInterB, ImgInterB, nH * nW);


    OCTET *tabIdR, *tabIdG, *tabIdB;

    allocation_tableau(tabIdR, OCTET, nTaille);
    allocation_tableau(tabIdG, OCTET, nTaille);
    allocation_tableau(tabIdB, OCTET, nTaille);

    for (int i = 0; i < nH; i++) {
      for (int j = 0; j < nW; j++) {
      
        tabIdR[i*nW+j] = ImgInterR[i*nW+j];
        tabIdG[i*nW+j] = ImgInterG[i*nW+j];
        tabIdB[i*nW+j] = ImgInterB[i*nW+j];
        } 
    } 

   for (int elt=0; elt < nTaille*3; elt+=3)
    {
      ImgOut[elt] = tabIdR[elt/3];
      ImgOut[elt+1] = tabIdG[elt/3];
      ImgOut[elt+2] = tabIdB[elt/3];
    }

    
    ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgOut); free(ImgInterR);free(ImgInterG);free(ImgInterB);
   return 1;
}