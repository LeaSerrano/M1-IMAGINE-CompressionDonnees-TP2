#include <stdio.h>
#include "image_ppm.h"
#include <list>
#include <algorithm>
#include <iostream>
#include <vector>

int main(int argc, char* argv[])
{
  char cNomImgEcriteInterCr256[250], cNomImgEcriteInterCr512[250], cNomImgEcriteInterCb256[250], cNomImgEcriteInterCb512[250];
  int nH, nW, nTaille;
  
  if (argc != 5) 
     {
        std::cout << argc << std::endl;
       printf("Usage: ImageIn.pgm ImageOut1.pgm\n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgEcriteInterCr512);
   sscanf (argv[2],"%s",cNomImgEcriteInterCb512);
   sscanf (argv[3],"%s",cNomImgEcriteInterCr256);
   sscanf (argv[4],"%s",cNomImgEcriteInterCb256);

   OCTET *ImgInterY256, *ImgInterCr256, *ImgInterCb256;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgEcriteInterCr512, &nH, &nW);
   nTaille = nH * nW;
   int nTaille3 = nTaille * 3;

   allocation_tableau(ImgInterCr256, OCTET, nTaille);
   allocation_tableau(ImgInterCb256, OCTET, nTaille);


    OCTET *tabIdCr, *tabIdCb;
    
    allocation_tableau(tabIdCr, OCTET, nTaille);
    allocation_tableau(tabIdCb, OCTET, nTaille);

    lire_image_pgm(cNomImgEcriteInterCr512, tabIdCr, nH * nW);
    lire_image_pgm(cNomImgEcriteInterCb512, tabIdCb, nH * nW);

    for (int i = 0; i < nH/2; i++) {
        for (int j = 0; j < nW/2; j++) {
            ImgInterCr256[i*(nW/2)+j] = (tabIdCr[(2*i)*nW+(2*j)] + tabIdCr[(2*i)*nW+(2*j+1)] + tabIdCr[((2*i)+1)*nW+(2*j)] + tabIdCr[(2*i+1)*nW+(2*j+1)])/4;
            ImgInterCb256[i*(nW/2)+j] = (tabIdCb[(2*i)*nW+(2*j)] + tabIdCb[(2*i)*nW+(2*j+1)] + tabIdCb[((2*i)+1)*nW+(2*j)] + tabIdCb[(2*i+1)*nW+(2*j+1)])/4;
        }
    }

    ecrire_image_pgm(cNomImgEcriteInterCr256, ImgInterCr256,  nH/2, nW/2);
    ecrire_image_pgm(cNomImgEcriteInterCb256, ImgInterCb256,  nH/2, nW/2);

   free(ImgInterY256);free(ImgInterCr256);free(ImgInterCb256);
   return 1;
}