/**
 * @authors Nom Prenom Nom Prenom Groupe Ville
 */
#define _WIN32
#include <stdio.h>
#include "ftd2xx.h"
#include "usb.h"
#include "amp.h"
#include "ams.h"
#include "frame.h"

void frame_to_usb(char * playlist_name, FT_HANDLE ftHandle){

    FILE * playlist = NULL;
    s_song mySong;
    char frm_titre[MAX_SIZE_TITLE];
    char frm_tick[TICK_FRAME_SIZE];
    char titre[MAX_SONGNAME_SIZE];
    playlist = initAMP(playlist_name);
    while (!feof(playlist)){
        readAMP(playlist, titre);
        mySong = readAMS(titre);
        if(strlen(mySong.title) != 0){
            mySong.title[strlen(mySong.title)] = '\0';
            createInitFrame(mySong, frm_titre);
            writeUSB(frm_titre, ftHandle);
            for (int i = 0; i < mySong.nTicks; ++i) {
                createTickFrame(mySong.tickTab[i], frm_tick);
                writeUSB(frm_tick, ftHandle);
            }
            Sleep(1000);
        }

    }

}

int main(){
    printf("Demarrage du projet AUDISEN USB\n");
    FT_HANDLE ft_handle;
    ft_handle = initUSB();
    frame_to_usb("Playlist.amp", ft_handle);
    closeUSB(ft_handle);

    return 0;
}