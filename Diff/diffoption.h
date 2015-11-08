#ifndef DIFFOPTION_H_INCLUDED
#define DIFFOPTION_H_INCLUDED

/*************************************************
* Program        : command diff                  *
* Description    :                               *
* Author         : Fournier David                *
*                  Gabriel Vautrin               *
*                  Bordage Mickael               *
* Date           : 07/11/2015                    *
* Version        : V1.0                          *
*************************************************/

void defaultmode(c_String**,c_String**);

void defaultmode(c_String** array1,c_String** array2){
int i=0,j=0;
//int morelong;
int lesslong;
if (sizeof(array1)< sizeof(array2)){
   // morelong = sizeof(array2);
    lesslong = sizeof(array1);
}
else{
   // morelong = sizeof(array1);
    lesslong = sizeof(array2);
}

printf("lenghtMax : %d\n", sizeof(array1));
    for(i=1; i < lesslong ; i++){
        if(array1[i]->lenght != array2[i]->lenght){
            printf("%d,%dc%d,%d",i,sizeof(array1),i,sizeof(array2));
            break;
        }
        for (j=0; j<array1[i]->lenght-1; j++){

        }
        printf("\n");
    }
}



#endif // DIFFOPTION_H_INCLUDED
