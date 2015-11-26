#include <stdio.h>
#include <stdlib.h>

//GESTION DES ERREURS
int compare(char*,char*);
int compareString(char *chaine1,char *chaine2,char *param);

int main(int argc, char* argv[])
{
     char *Param="";

    if(argc < 2&&compare(argv[1],"-- help")){
        printf("Usage: diff [OPTION] FILE1 FILE2\n\n  -w  --ignore-all-space Ignore all white space.\n  -s  --report-identical-files Report when two files are the same.\n  --help Output this help.\n\nIf FILE1 or FILE2 is '-', read standard input.");
        return 1;
    }
    if(argc < 2){
        printf("diff: missing operand\ndiff: try 'diff --help' for more information.");
        return 1;
    }
    if(argc == 3){
       char *Source1=argv[argc-1],*Source2=argv[argc];     //Les fichiers � comparer ou dossier
    }
    if(argc ==4 ){
        char *Source1=argv[argc-1],*Source2=argv[argc];     //Les fichiers � comparer ou dossier
        char *Param=argv[1];

    }
    if(argc > 4 ){
        printf("Usage: diff [OPTION] FILE1 FILE2\n  You can use one option.\n  --help Output this help.\n\nIf FILE1 or FILE2 is '-', read standard input.");
        return 1;

    }

    printf("%d",compareString("abcd","abcd","-w"));

    return 0;
}

///Compare two string  ------------> Use for verify param's name
///Input :   2 Strings
///Output : 0 ->identical     -1->different
int compare(char*NameFonction,char*param)
{
    int sizeStringFonction=strlen(NameFonction),sizeStringParam=strlen(param),i;

    if (sizeStringFonction!=sizeStringParam)
        return -1;
    for(i=0;i<sizeStringFonction;i++){
        if(NameFonction[i]!=param[i])
            return -1;

    }
    return 0;
}

/******************************************************
* Compare two strings with param
* Input : 3 Strings (2 lines + param)
* Output : 0 ->identical     -1->different
****************************************************/
int compareString(char *lineA,char *lineB,char *param){

    int max=0,i,index1=0,index2=0,changeIndex1=0,changeIndex2=0,size1=strlen(lineA),size2=strlen(lineB);

    ///Option ignore all space (- w)
    if(compare(param,"-w") == 0 || compare(param,"-w")){
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
