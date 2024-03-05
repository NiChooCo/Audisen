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



void readAMP(FILE* pf, char * song_filename){
    fgets(song_filename, MAX_SONGNAME_SIZE, pf);
    int count = strlen(song_filename);
    for (int i = 0; i < count; ++i) {
        song_filename[i] = (char)tolower((int)song_filename[i]);
        if(!(isalpha((int) song_filename[i]))){
            song_filename[i] = '_';
            //printf("|%c|", song_filename[i-1]);
            if(song_filename[i-1] == '_'){
                for(int j = i; j < count; j++){
                    song_filename[j] = song_filename[j+1];
                    song_filename[j] = (char)tolower((int)song_filename[j]);
                }
                count -= 1;
                i-=1;
            }
        }
    }
    printf("%s\n", song_filename);
}

void closeAMP(FILE* pf){
    if(pf){
        fclose(pf);
        printf("Fichier trouvé, et fermé !\n");
    }
}