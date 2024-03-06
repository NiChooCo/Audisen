/**
 * @authors Nom Prenom Nom Prenom Groupe Ville
 */

#include <stdio.h>
#include "amp.h"
#include "ams.h"
#include "frame.h"
#include "autotests.h"


int main(){
    printf("Démarrage du projet AUDISEN\n");
    FILE * playlist = NULL;
    char *titre;
    playlist = initAMP("ma_playlist.amp");
    //readAMP(playlist, titre);
    //closeAMP(playlist);
    //readAMS("bohemian_rhapsody.ams");
    //printf("\n");
    //testCreateAMS();
    testFrame();
    //testReadAMP();
    //testReadAMS();
    return 0;
}