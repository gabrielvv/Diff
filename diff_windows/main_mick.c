#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[])
{
   //char sequence1[10]={'a','b','c','d','e','f','g','j','h','i'};
   //char sequence2[10]={'b','c','d','e','f','g','j','k','h','l'};
   int sequence1[10]={0,3,4,5,6,7,8,9,19,15}; 
   int sequence2[10]={3,4,5,6,7,8,9,10,19,13};
   //int sequence1[4]={0,1,2,3};
   //int sequence2[4]={1,3,4,5};
   int sequenceto[8]= {};
   int i;
   int j=0;
   int h=0;
   int tabdelete[9] = {};
   int tabadd[9] = {};

   //third soluce
   for(i=0;i<10;i++){
       for(j=0;j<10;j++){
           if(sequence1[i] == sequence2[j]){
               sequenceto[h]=sequence1[i];
               h++;
           }
       }
   }
       for(h=0;h<8;h++){
       printf("%d ",sequenceto[h]);

   }
   printf("\n");
   j=0;
   int cpt=0;

   for(i=0;i<10;i++){
       if(sequence1[i] !=sequenceto[j]){
           tabdelete[cpt] = sequence1[i];
           cpt++;
       }
       else{
           if(j<8)
               j++;
           else
               j=8;
       }
   }

   for(i=0;i<2;i++){
       printf("%d ", tabdelete[i]);
   }
   printf("\n");

   j=0;
   cpt=0;
   for(i=0;i<10;i++){
       if(sequence2[i] !=sequenceto[j]){
           tabadd[cpt] = sequence2[i];
           cpt++;
       }
       else{
           if(j<8)
               j++;
           else
               j=8;
       }
   }

   for(i=0;i<2;i++){
       printf("%d ", tabadd[i]);
   }

  return 0;
}
