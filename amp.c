/**
 * @authors Nom Prenom Nom Prenom Groupe Ville
 */

#include "define.h"
#include "amp.h"


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

}

void closeAMP(FILE* pf){
    if(pf){
        fclose(pf);
        printf("Fichier trouvé, et fermé !\n");
    }
}