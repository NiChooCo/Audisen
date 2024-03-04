/**
 * @authors Nom Prenom Nom Prenom Groupe Ville
 */

#include "define.h"
#include "amp.h"
#include <ctype.h>


FILE* initAMP(char* filename){
    FILE * pf = NULL;
    pf = fopen(filename, "r");
    if(pf == NULL){
        printf("Erreur ! Fichier non trouvé !\n");
    }
    else{
        printf("Fichier trouvé !\n");
        return pf;
    }
   
    return pf;
}



/*void readAMP(FILE* pf, char * song_filename){
    while(fgets(song_filename, MAX_SONGNAME_SIZE, pf)!=NULL){
        fgets(song_filename, MAX_SONGNAME_SIZE, pf);
        printf("%s", song_filename);
    }
}*/
void readAMP(FILE* pf, char * song_filename){
    fgets(song_filename, MAX_SONGNAME_SIZE, pf);
    for (int i = 0; i < strlen(song_filename); ++i) {
        song_filename[i] = (char)tolower((int)song_filename[i]);
    }
    printf("%s\n", song_filename);
}

void closeAMP(FILE* pf){
    if(pf){
        fclose(pf);
        printf("Fichier trouvé, et fermé !\n");
    }
}