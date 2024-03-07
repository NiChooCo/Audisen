/**
 * @authors Nom Prenom Nom Prenom Groupe Ville
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "frame.h"
#include "define.h"


/** Permet de crée une frame d'initiation
 *
 * @param mySong struct du son contenant toutes les infos nécessaires pour créer les frames
 * @param frame pointeur vers une frame qui sera modifiée grâce à cette fonction
 */
void createInitFrame(s_song mySong, char* frame){
    char content[INIT_FRAME_MAX_SIZE];
    sprintf(content, "%s,%d,%d", mySong.title, mySong.tpm, mySong.nTicks);
    int checksum = 0;
    int i = 0;
    while (content[i] != '\0') {
        checksum ^= content[i];
        i++;
    }
    sprintf(frame, "#%s*%02x\r\n", content, checksum);
    printf("%s", frame);
}

/** Permet de créer une frame de tick
 *
 * @param myTick struck d'un tick, contenant toutes les infos pour créer la frame
 * @param frame pareil que la fonction au dessus
 */
void createTickFrame(s_tick myTick, char* frame){
    char content[INIT_FRAME_MAX_SIZE];
    sprintf(content, "0,%d,%02d,%02d,%02d,%02d", myTick.accent, myTick.note[0], myTick.note[1], myTick.note[2], myTick.note[3]);
    int checksum = 0;
    int i = 0;
    while (content[i] != '\0') {
        checksum ^= content[i];
        i++;
    }
    sprintf(frame, "#%s*%02x\r\n", content, checksum);
    printf("%s", frame);
}
