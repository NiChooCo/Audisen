/**
 * @authors Nom Prenom Nom Prenom Groupe Ville
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "frame.h"
#include "define.h"



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
