/**
 * @authors Nom Prenom Nom Prenom Groupe Ville
 */

#include "define.h"
#include "amp.h"
#include <ctype.h>

/**
 *
 * @param filename nom du fichier amp
 * @return les valeurs contenues dans le fichier amp de base, dans une variable (ici pf)
 */
FILE* initAMP(char* filename){
    FILE * pf = NULL;
    pf = fopen(filename, "r");
    if(pf == NULL){
        printf("Erreur ! Fichier non trouvé !\n");
    }
    else{
        printf("Fichier amp trouvé !\n");
        return pf;
    }
   
    return pf;
}


/**
 *
 * @param pf variable contenant les valeurs dans le fichier amp après avoir utilisé initAMP
 * @param song_filename variable contenant le titre récupéré dans l'amp, ce titre va permettre le readAMS par la suite
 */
void readAMP(FILE* pf, char * song_filename){
    fgets(song_filename, MAX_SONGNAME_SIZE, pf);
    int count = (int)strlen(song_filename);
    for (int i = 0; i < count; ++i) {
        song_filename[i] = (char)tolower((int)song_filename[i]);
        if(song_filename[i] != '\n' && song_filename[i] != '\r'){
            if(!(isalpha((int) song_filename[i]))){
                song_filename[i] = '_';
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
        else{
            song_filename[i] = '\0';
        }
    }
    //song_filename[strlen(song_filename)]='\0';
    strcat(song_filename, ".ams");
    printf("%s\n", song_filename);
}

/**
 *
 * @param pf fichier à fermer
 */
void closeAMP(FILE* pf){
    if(pf){
        fclose(pf);
        printf("Fichier trouvé, et fermé !\n\n");
    }
}