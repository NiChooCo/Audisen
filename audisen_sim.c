/**
 * @authors Nom Prenom Nom Prenom Groupe Ville
 */

#include <stdio.h>
#include "amp.h"
#include "ams.h"
#include "frame.h"
#include "autotests.h"

/** Permet de créer un fichier frm avec les frames des morceaux
 *
 * @param playlist_amp nom du fichier amp à lire, va etre utilisé pour récupérer les titres pour pouvoir faire un readAMS après
 * @param playlist_frm fichier frm qui va être crée dans lequel les frames vont être écrites
 */
void create_frm(char * playlist_amp, char * playlist_frm){
    FILE * amp = NULL;
    FILE * frm = NULL;
    frm = fopen(playlist_frm, "w");
    if(frm == NULL){
        printf("Fichier non trouvé");
        exit(0);
    }
    s_song mySong;
    char frm_titre[MAX_SIZE_TITLE];
    char frm_tick[TICK_FRAME_SIZE];
    char titre[MAX_SONGNAME_SIZE];
    amp = initAMP(playlist_amp);
    while (!feof(amp)){
        readAMP(amp, titre);
        mySong = readAMS(titre);
        if(strlen(mySong.title) != 0){
            mySong.title[strlen(mySong.title)-1] = '\0';
            createInitFrame(mySong, frm_titre);
            fprintf(frm, "%s",frm_titre);
            for (int i = 0; i < mySong.nTicks; ++i) {
                createTickFrame(mySong.tickTab[i], frm_tick);
                fprintf(frm, "%s", frm_tick);
            }
        }
    }
}

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
    //create_frm("ma_playlist.amp", "Playlist.frm");
    //createAMS("bohemian_rhapsody.txt", "bohemian_pour_create.ams");

    return 0;
}