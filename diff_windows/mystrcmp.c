#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mystrcmp.h"


/********************************************************************
* Compare two string  ------------> Use to verify options's name
* Input :   2 Strings
* Output : 0 ->identical     -1->different
**********************************************************************/
int compare(char*NameFonction,char*options)
{
    int sizeStringFonction=strlen(NameFonction),sizeStringoptions=strlen(options),i;

    if (sizeStringFonction!=sizeStringoptions)
        return -1;
    for(i=0;i<sizeStringFonction;i++){
        if(NameFonction[i]!=options[i])
            return -1;

    }
    return 0;
}

/******************************************************
* Compare two strings with options
* Input : 3 Strings (2 lines + options)
* Output : 0 ->identical     -1->different
****************************************************/
int compareString(char *lineA,char *lineB,char *options){

    int max=0,i,index1=0,index2=0,changeIndex1=0,changeIndex2=0,size1=strlen(lineA),size2=strlen(lineB);

    ///Option ignore all space (- w)
    if(compare(options,"-w") == 0 || compare(options,"--ignore-all-space") == 0){
        if(size1>size2)
            max=size1;
        else
            max=size2;
        for(i=0;i<max;i++){

            if(lineA[index1]!=lineB[index2])
            {
                if(lineA[index1]==32||lineA[index1]==9||(lineA[index1]>=11&&lineA[index1]<=13))//if character is a space/tab hori/tab vert/form feed/carriage return
                    changeIndex2=1;
                else if(!(lineB[index2]==32||lineB[index2]==9||(lineB[index2]>=11&&lineB[index2]<=13)))
                    return -1;

                if(lineB[index2]==32||lineB[index2]==9||(lineB[index2]>=11&&lineB[index2]<=13))
                    changeIndex1=1;
                else if(!(lineA[index1]==32||lineA[index1]==9||(lineA[index1]>=11&&lineA[index1]<=13)))
                    return -1;
            }

            if(changeIndex1==1)
                index1--;
            if(changeIndex2==1){
                index2--;
                i--;
            }
            changeIndex1=changeIndex2=0;
            if(index1<size1)
                index1++;
            if(index2<size2)
                index2++;
        }
    }
   ///Compare normaly
    else{
        if (size1!=size2)
            return -1;
        for(i=0;i<size1;i++){
            if(lineA[i]!=lineB[i])
                return -1;
        }
    }
    return 0;
}
