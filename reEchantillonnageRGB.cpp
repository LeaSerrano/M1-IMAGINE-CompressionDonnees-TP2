#include <stdio.h>
#include "image_ppm.h"
#include <list>
#include <algorithm>
#include <iostream>
#include <vector>


int main(int argc, char* argv[])
{
  char cNomImgEcriteR[250], cNomImgEcriteG[250], cNomImgEcriteB[250], cNomImgLueInterR[250], cNomImgLueInterG[250], cNomImgLueInterB[250];
  int nH, nW, nTaille;
  
  if (argc != 7) 
     {
       printf("Usage: ImageIn.pgm ImageOut1.pgm\n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLueInterR);
   sscanf (argv[2],"%s",cNomImgLueInterG);
   sscanf (argv[3],"%s",cNomImgLueInterB);
   sscanf (argv[4],"%s",cNomImgEcriteR);
   sscanf (argv[5],"%s",cNomImgEcriteG);
   sscanf (argv[6],"%s",cNomImgEcriteB);

   OCTET *ImgInterR, *ImgInterG, *ImgInterB;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLueInterR, &nH, &nW);
   nTaille = nH * nW;

   int width = nW*2;
  int height = nH*2;

  int nTailleEchantillonnee = width * height;

   allocation_tableau(ImgInterR, OCTET, nTaille);
   allocation_tableau(ImgInterG, OCTET, nTaille);
   allocation_tableau(ImgInterB, OCTET, nTaille);

   lire_image_pgm(cNomImgLueInterR, ImgInterR, nH * nW);
   lire_image_pgm(cNomImgLueInterG, ImgInterG, nH * nW);
   lire_image_pgm(cNomImgLueInterB, ImgInterB, nH * nW);


  OCTET *tabIdR, *tabIdG, *tabIdB;

    allocation_tableau(tabIdR, OCTET, nTailleEchantillonnee);
    allocation_tableau(tabIdG, OCTET, nTailleEchantillonnee);
    allocation_tableau(tabIdB, OCTET, nTailleEchantillonnee);


  for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {

          int row = i/2;
          int col = j/2;

          int row_index = floor(row);
          int col_index = floor(col);

          float alpha = row - row_index;
          float beta = col - col_index;


          tabIdR[i*width+j] = (1 - alpha) * (1 - beta) * ImgInterR[row * nW + col] + alpha * (1 - beta) * ImgInterR[row * nW + col + 1] 
          + (1 - alpha) * beta * ImgInterR[(row + 1) * nW + col] + alpha * beta * ImgInterR[(row + 1) * nW + col + 1];

          tabIdG[i*width+j] = (1 - alpha) * (1 - beta) * ImgInterG[row * nW + col] + alpha * (1 - beta) * ImgInterG[row * nW + col + 1] 
          + (1 - alpha) * beta * ImgInterG[(row + 1) * nW + col] + alpha * beta * ImgInterG[(row + 1) * nW + col + 1];

          tabIdB[i*width+j] = (1 - alpha) * (1 - beta) * ImgInterB[row * nW + col] + alpha * (1 - beta) * ImgInterB[row * nW + col + 1] 
          + (1 - alpha) * beta * ImgInterB[(row + 1) * nW + col] + alpha * beta * ImgInterB[(row + 1) * nW + col + 1];
            
        }
    }

  

    ecrire_image_pgm(cNomImgEcriteR, tabIdR,  height, width);
    ecrire_image_pgm(cNomImgEcriteG, tabIdG,  height, width);
    ecrire_image_pgm(cNomImgEcriteB, tabIdB,  height, width);

   free(ImgInterR);free(ImgInterG);free(ImgInterB);
   return 1;
}