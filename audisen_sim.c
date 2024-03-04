/**
 * @authors Nom Prenom Nom Prenom Groupe Ville
 */

#include <stdio.h>
#include "amp.h"


int main(){
    printf("Demarrage du projet AUDISEN\n");
    FILE * playlist = NULL;
    playlist = initAMP("ma_playlist.amp");
    closeAMP(playlist);

    return 0;
}