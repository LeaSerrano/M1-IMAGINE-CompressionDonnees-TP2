#include <stdio.h>
#include "image_ppm.h"
#include <list>
#include <algorithm>
#include <iostream>
#include <vector>


int main(int argc, char* argv[])
{
  char cNomImgEcriteCr[250], cNomImgEcriteCb[250], cNomImgLueInterCr[250], cNomImgLueInterCb[250];
  int nH, nW, nTaille;
  
  if (argc != 5) 
     {
       printf("Usage: ImageIn.pgm ImageOut1.pgm\n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLueInterCr);
   sscanf (argv[2],"%s",cNomImgLueInterCb);
   sscanf (argv[3],"%s",cNomImgEcriteCr);
   sscanf (argv[4],"%s",cNomImgEcriteCb);

   OCTET *ImgInterY, *ImgInterCr, *ImgInterCb;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLueInterCr, &nH, &nW);
   nTaille = nH * nW;

   int width = nW*2;
  int height = nH*2;

  int nTailleEchantillonnee = width * height;

   allocation_tableau(ImgInterCr, OCTET, nTaille);
   allocation_tableau(ImgInterCb, OCTET, nTaille);

   lire_image_pgm(cNomImgLueInterCr, ImgInterCr, nH * nW);
   lire_image_pgm(cNomImgLueInterCb, ImgInterCb, nH * nW);


  OCTET *tabIdCr, *tabIdCb;

    allocation_tableau(tabIdCr, OCTET, nTailleEchantillonnee);
    allocation_tableau(tabIdCb, OCTET, nTailleEchantillonnee);


  for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {

          int row = i/2;
          int col = j/2;

          int row_index = floor(row);
          int col_index = floor(col);

          float alpha = row - row_index;
          float beta = col - col_index;

          tabIdCr[i*width+j] = (1 - alpha) * (1 - beta) * ImgInterCr[row * nW + col] + alpha * (1 - beta) * ImgInterCr[row * nW + col + 1] 
          + (1 - alpha) * beta * ImgInterCr[(row + 1) * nW + col] + alpha * beta * ImgInterCr[(row + 1) * nW + col + 1];

          tabIdCb[i*width+j] = (1 - alpha) * (1 - beta) * ImgInterCb[row * nW + col] + alpha * (1 - beta) * ImgInterCb[row * nW + col + 1] 
          + (1 - alpha) * beta * ImgInterCb[(row + 1) * nW + col] + alpha * beta * ImgInterCb[(row + 1) * nW + col + 1];
            
        }
    }

  

    ecrire_image_pgm(cNomImgEcriteCr, tabIdCr,  height, width);
    ecrire_image_pgm(cNomImgEcriteCb, tabIdCb,  height, width);

   free(ImgInterCr);free(ImgInterCb);
   return 1;
}