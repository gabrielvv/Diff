#include <stdio.h>
#include <stdlib.h>

int main()
{
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


   /* for(i=0;i<10;i++){
        if(sequence1[i] != sequenceto[j]){
            printf("C'est un delete %d %d\n",sequence1[i],sequenceto[j]);
        }
        if(sequence2[i] != sequenceto[j]){
            printf("C'est un add %d %d\n",sequence2[i],sequenceto[j]);
        }
        if(sequence1[i] == sequenceto[j] ) {
            if(j<8)
                j++;
            else
                j=8;
        }

    }*/
   /* for(i=0;i<10;i++){
        // printf("%d %d\n",i,j);
         //printf("value1 %d value2 %d\n",sequence1[i],sequenceto[j]);
         printf("tab2value1 %d tab2value2 %d\n",sequence2[i],sequenceto[j]);
         if(sequence1[i] == sequenceto[j] && sequence1[i] == sequenceto[j] ){
         if(j<8)
                j++;
            else
                j=8;
         }

        else if(sequence1[i] != sequenceto[j]){
                printf("C'est un delete %d %d\n",sequence1[i],sequenceto[j]);

        }
        else if (sequence2[i] !=sequenceto[j]){
           printf("c'est un add %d %d\n",sequence2[i],sequenceto[j]);
        }

        }*/

       /* if(sequence2[i]!= sequenceto[i]){
            printf("c'est un add %d %d\n",sequence1[i],sequenceto[i]);
        }*/



    //second soluce
    /*for (i=0; i<9; i++){
        if(sequence1[i]!=sequence2[j] && sequence1[i]<sequence2[j]){
            printf("delete\n");
        }
        else if(sequence1[i]!=sequence2[j] && sequence1[i]>sequence2[j]){
            printf("add %d %d\n",i,j);
            printf("valeur 1 : %d valeurs 2  : %d\n",sequence1[i],sequence2[j]);
            ++j;
            --i;
        }
        else if (sequence1[i]==sequence2[j]) {
        printf("boucle égal value1 : %d value2: %d\n",sequence1[i],sequence2[j]);
           sequenceto[h] = sequence2[j];
           ++h;
           --j;
        }
    }
    for(h=0;h<8;h++){
        printf("%d ",sequenceto[h]);
    }*/

    /*first soluce
    for(i=0; i<9 ;i++){

        if (sequence1[i]!= sequence2[j] && sequence1[i]<sequence2[j]){
                printf("delete\n");
                printf("valeur 1 : %d valeurs 2  : %d\n",sequence1[i],sequence2[j]);

            }
            else if (sequence1[i]!=sequence2[j] && sequence1[i]>sequence2[j]){
                printf("add\n");
                printf("valeur 1 : %d valeurs 2  : %d\n",sequence1[i],sequence2[j]);
                //i--;
                j++;
            }
            else
                j++;

    }*/
    return 0;
}
