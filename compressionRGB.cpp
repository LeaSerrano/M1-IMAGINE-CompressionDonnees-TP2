#include <stdio.h>
#include "image_ppm.h"
#include <list>
#include <algorithm>
#include <iostream>
#include <vector>

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcriteInterR256[250], cNomImgEcriteInterR512[250], cNomImgEcriteInterB256[250], cNomImgEcriteInterB512[250],cNomImgEcriteInterG256[250], cNomImgEcriteInterG512[250];
  int nH, nW, nTaille;
  
  if (argc != 8) 
     {
        std::cout << argc << std::endl;
       printf("Usage: ImageIn.pgm ImageOut1.pgm\n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcriteInterR256);
   sscanf (argv[3],"%s",cNomImgEcriteInterG256);
   sscanf (argv[4],"%s",cNomImgEcriteInterB256);
   sscanf (argv[5],"%s",cNomImgEcriteInterR512);
   sscanf (argv[6],"%s",cNomImgEcriteInterG512);
   sscanf (argv[7],"%s",cNomImgEcriteInterB512);

   OCTET *ImgIn, *ImgInterR256, *ImgInterG256, *ImgInterB256;
   
   lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
   int nTaille3 = nTaille * 3;

   allocation_tableau(ImgIn, OCTET, nTaille3);

   allocation_tableau(ImgInterR256, OCTET, nTaille/4);
   allocation_tableau(ImgInterG256, OCTET, nTaille/4);
   allocation_tableau(ImgInterB256, OCTET, nTaille/4);

   lire_image_ppm(cNomImgLue, ImgIn, nH * nW);


    OCTET *tabIdR, *tabIdG, *tabIdB;
    
    allocation_tableau(tabIdR, OCTET, nTaille);
    allocation_tableau(tabIdG, OCTET, nTaille);
    allocation_tableau(tabIdB, OCTET, nTaille);

    planR(tabIdR, ImgIn, nTaille);
    planV(tabIdG, ImgIn, nTaille);
    planB(tabIdB, ImgIn, nTaille);


    for (int i = 0; i < nH/2; i++) {
        for (int j = 0; j < nW/2; j++) {
            ImgInterR256[i*(nW/2)+j] = (tabIdR[(2*i)*nW+(2*j)] + tabIdR[(2*i)*nW+(2*j+1)] + tabIdR[((2*i)+1)*nW+(2*j)] + tabIdR[(2*i+1)*nW+(2*j+1)])/4;
            ImgInterG256[i*(nW/2)+j] = (tabIdG[(2*i)*nW+(2*j)] + tabIdG[(2*i)*nW+(2*j+1)] + tabIdG[((2*i)+1)*nW+(2*j)] + tabIdG[(2*i+1)*nW+(2*j+1)])/4;
            ImgInterB256[i*(nW/2)+j] = (tabIdB[(2*i)*nW+(2*j)] + tabIdB[(2*i)*nW+(2*j+1)] + tabIdB[((2*i)+1)*nW+(2*j)] + tabIdB[(2*i+1)*nW+(2*j+1)])/4;
        }
    }


    ecrire_image_pgm(cNomImgEcriteInterR256, ImgInterR256,  nH/2, nW/2);
    ecrire_image_pgm(cNomImgEcriteInterG256, ImgInterG256,  nH/2, nW/2);
    ecrire_image_pgm(cNomImgEcriteInterB256, ImgInterB256,  nH/2, nW/2);

    ecrire_image_pgm(cNomImgEcriteInterR512, tabIdR,  nH, nW);
    ecrire_image_pgm(cNomImgEcriteInterG512, tabIdG,  nH, nW);
    ecrire_image_pgm(cNomImgEcriteInterB512, tabIdB,  nH, nW);

   free(ImgIn); free(ImgInterR256);free(ImgInterG256);free(ImgInterB256);
   return 1;
}