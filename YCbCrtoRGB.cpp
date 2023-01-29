#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char cNomImgLueY[250], cNomImgLueCB[250], cNomImgLueCR[250], cNomImgEcrite[250];
  int nH, nW, nTaille;
  
  if (argc != 5) 
     {
       printf("Usage: ImageInY.ppm ImageInCB.ppm ImageInCR.ppm ImageOut.pgm \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLueY);
   sscanf (argv[2],"%s",cNomImgLueCR);
   sscanf (argv[3],"%s",cNomImgLueCB);
   sscanf (argv[4],"%s",cNomImgEcrite);

   OCTET *ImgInY, *ImgInCB, *ImgInCR, *ImgOut;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLueY, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(ImgInY, OCTET, nTaille);
   allocation_tableau(ImgInCB, OCTET, nTaille);
   allocation_tableau(ImgInCR, OCTET, nTaille);

   lire_image_pgm(cNomImgLueY, ImgInY, nH * nW);
   lire_image_pgm(cNomImgLueCB, ImgInCB, nH * nW);
   lire_image_pgm(cNomImgLueCR, ImgInCR, nH * nW);

   allocation_tableau(ImgOut, OCTET, nTaille*3);

    for (int elt=0; elt < nTaille*3; elt+=3)
    {
      if (ImgInY[elt/3] + 1.402*(ImgInCR[elt/3]-128) > 255){
        ImgOut[elt] = 255;
      } 
      else if (ImgInY[elt/3] + 1.402*(ImgInCR[elt/3]-128) < 0){
        ImgOut[elt] = 0;
      } 
      else{
        ImgOut[elt] = ImgInY[elt/3] + 1.402*(ImgInCR[elt/3]-128);
      } 

      if (ImgInY[elt/3] - 0.34414*(ImgInCB[elt/3]-128) - 0.714414*(ImgInCR[elt/3]-128) > 255){
        ImgOut[elt+1] = 255;
      } 
      else if (ImgInY[elt/3] - 0.34414*(ImgInCB[elt/3]-128) - 0.714414*(ImgInCR[elt/3]-128) < 0){
        ImgOut[elt+1] = 0;
      } 
      else{
        ImgOut[elt+1] = ImgInY[elt/3] - 0.34414*(ImgInCB[elt/3]-128) - 0.714414*(ImgInCR[elt/3]-128);
      }
      
      if (ImgInY[elt/3] + 1.772*(ImgInCB[elt/3]-128) > 255){
        ImgOut[elt+2] = 255;
      } 
      else if (ImgInY[elt/3] + 1.772*(ImgInCB[elt/3]-128) < 0){
        ImgOut[elt+2] = 0;
      } 
      else{
        ImgOut[elt+2] = ImgInY[elt/3] + 1.772*(ImgInCB[elt/3]-128);
      }
    }


    ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
    free(ImgInY); free(ImgInCB); free(ImgInCR); free(ImgOut);

    return 1;
}
