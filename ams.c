/**
 * @authors Nom Prenom Nom Prenom Groupe Ville
 */

#include "define.h"
#include "ams.h"
#include <ctype.h>

/** Permet de lire le fichier ams d'un titre
 *
 * @param fileName titre du son dont on va lire l'ams
 * @return
 */
s_song readAMS(char* fileName){

    s_song mySong;
    FILE * songFile;
    songFile = fopen(fileName, "r");
    if(songFile==NULL){
        printf("Erreur, fichier non trouvé\n");
        mySong.title[0] = '\0';
        for (int i = 0; i < MAX_NUMBER_TICKS; ++i) {
            mySong.tickTab[i].accent = 0;
            for (int j = 0; j < 4; ++j) {
                mySong.tickTab[i].note[j] = 0;
            }
        }
        mySong.nTicks = 0;
        mySong.tpm = 0;
    }
    else{
        fgets(mySong.title, MAX_SONGNAME_SIZE, songFile);
        mySong.title[strlen(mySong.title) -1]='\0';
        char line[MAX_SIZE_LINE];
        fgets(line , TMP_MAX, songFile);
        mySong.tpm = atoi(line)*2;
        fgets(line, MAX_SIZE_LINE, songFile); //enlève les 2 premières lignes
        fgets(line, MAX_SIZE_LINE, songFile);
        int nb_lignes = 0;
        int i = 0;
        while(fgets(line, MAX_SIZE_LINE, songFile) != NULL){
            int pipe = 0;
            nb_lignes+=1;
            mySong.tickTab[i].accent = 0;
            int note_index = 0;
            for (int j = 0; j < MAX_SIZE_LINE; ++j) {
                if (line[j] == '|') {
                    pipe += 1;
                    if (line[j + 1] == '^' || line[j + 1] == 'x') {
                        mySong.tickTab[i].note[note_index] = pipe;
                        note_index += 1;
                    }
                }
                if (line[j] == '^') {
                    mySong.tickTab[i].accent = 1;
                }
            }
            printf("Accent : %d\n", mySong.tickTab[i].accent);
            for (int j = 0; j < 4; ++j) {
                //printf("%d ", mySong.tickTab[i].note[j]);
            }
            i+=1;
        }
        mySong.nTicks = nb_lignes;
        //printf("%s\n", mySong.title);
        //printf("\n");
        //printf("tpm : %d\n", mySong.tpm);
    }



	//printf("Titre : %s\n", mySong.title);
	//printf("Tick par minute : %d\n", mySong.tpm);
    //printf("%d\n", mySong.tickTab[14].note[2]);
    //printf("%d\n", mySong.nTicks);
	return mySong;
}


void createAMS(char* txtFileName, char *amsFileName){

    FILE * myRead;
    FILE * myWrite;
    myRead = fopen(txtFileName, "r");
    myWrite = fopen(amsFileName, "w");
    s_song mySong;

    //titre
    char title[MAX_SIZE_LINE];
    fgets(title, MAX_SIZE_LINE, myRead);
    fputs(title, myWrite);

    //tpm
    char tpm[MAX_SIZE_LINE];
    fgets(tpm, MAX_SIZE_LINE, myRead);
    fputs(tpm, myWrite);

    //ligne vide
    char vide[MAX_SIZE_LINE];
    fgets(vide, MAX_SIZE_LINE, myRead);
    fputs(vide, myWrite);

    //ligne des notes de 01 à 60
    fputs("    ", myWrite);
    for(int nNote = 1; nNote < 61; nNote++){
        if(nNote < 10){
            fprintf(myWrite, "0");
        }
        fprintf(myWrite, "%d ", nNote);
    }
    fprintf(myWrite, "\n");





    //gros tableau qui commence
    char tick[MAX_SIZE_LINE];
    int nTick = 0;
    int repet[MAX_NUMBER_TICKS][60];

    while(fgets(tick, sizeof(tick), myRead) != NULL){
        nTick += 1;
        printf("|%d|\n", nTick);
        int compteur = 1;
        int indiceNote = 0;

        //afficher les 3 chiffres correspondant au numéro de la ligne
        if(nTick < 100){
            fprintf(myWrite, "0");
            if(nTick < 10){
                fprintf(myWrite, "0");
            }
        }
        fprintf(myWrite, "%d", nTick);

        /*for(indiceNote = 0; indiceNote <= 3; indiceNote++){
            if(mySong.tickTab[nTick].note[indiceNote] != 0){
                for(int nNote = compteur; nNote < mySong.tickTab[nTick].note[indiceNote]; nNote++) {
                    fprintf(myWrite, "|  ");
                }
                fprintf(myWrite, "|x ");

            }
        }
        indiceNote = 0;
        compteur = mySong.tickTab[nTick].note[indiceNote] + 1;*/



        char *separators = ",";
        char *strToken = strtok(tick, separators);
        while(strToken != NULL){

            for(int c = 0; c < strlen(strToken); c++){
                if(strToken[c] == ' '){
                    memmove(&strToken[c], &strToken[c + 1], (strlen(strToken) - (c + 1) + 1));
                }
            }
            int octave = ((12 * ((int)strToken[1] - 48)) - 12);
            printf("-> %s\n", strToken);

            //choix de la note
            switch(strToken[0]){
                case 'C':
                    if(strchr(strToken, '#') == NULL){
                        while(mySong.tickTab[nTick].note[indiceNote] != 0){
                            indiceNote += 1;
                        }
                        mySong.tickTab[nTick].note[indiceNote] = 1;
                    }
                    else{
                        while(mySong.tickTab[nTick].note[indiceNote] != 0){
                            indiceNote += 1;
                        }
                        mySong.tickTab[nTick].note[indiceNote] = 2;
                    }
                    mySong.tickTab[nTick].note[indiceNote] = mySong.tickTab[nTick].note[indiceNote] + octave;
                    break;

                case 'D':
                    if(strchr(strToken, '#') == NULL){
                        while(mySong.tickTab[nTick].note[indiceNote] != 0){
                            indiceNote += 1;
                        }
                        mySong.tickTab[nTick].note[indiceNote] = 3;
                    }
                    else{
                        while(mySong.tickTab[nTick].note[indiceNote] != 0){
                            indiceNote += 1;
                        }
                        mySong.tickTab[nTick].note[indiceNote] = 4;
                    }
                    mySong.tickTab[nTick].note[indiceNote] = mySong.tickTab[nTick].note[indiceNote] + octave;
                    break;

                case 'E':
                    while(mySong.tickTab[nTick].note[indiceNote] != 0){
                        indiceNote += 1;
                    }
                    mySong.tickTab[nTick].note[indiceNote] = 5;
                    mySong.tickTab[nTick].note[indiceNote] = mySong.tickTab[nTick].note[indiceNote] + octave;
                    break;

                case 'F':
                    if(strchr(strToken, '#') == NULL){
                        while(mySong.tickTab[nTick].note[indiceNote] != 0){
                            indiceNote += 1;
                        }
                        mySong.tickTab[nTick].note[indiceNote] = 6;
                    }
                    else{
                        while(mySong.tickTab[nTick].note[indiceNote] != 0){
                            indiceNote += 1;
                        }
                        mySong.tickTab[nTick].note[indiceNote] = 7;
                    }
                    mySong.tickTab[nTick].note[indiceNote] = mySong.tickTab[nTick].note[indiceNote] + octave;
                    break;

                case 'G':
                    if(strchr(strToken, '#') == NULL){
                        while(mySong.tickTab[nTick].note[indiceNote] != 0){
                            indiceNote += 1;
                        }
                        mySong.tickTab[nTick].note[indiceNote] = 8;
                    }
                    else{
                        while(mySong.tickTab[nTick].note[indiceNote] != 0){
                            indiceNote += 1;
                        }
                        mySong.tickTab[nTick].note[indiceNote] = 9;
                    }
                    mySong.tickTab[nTick].note[indiceNote] = mySong.tickTab[nTick].note[indiceNote] + octave;
                    break;

                case 'A':
                    if(strchr(strToken, '#') == NULL){
                        while(mySong.tickTab[nTick].note[indiceNote] != 0){
                            indiceNote += 1;
                        }
                        mySong.tickTab[nTick].note[indiceNote] = 10;
                    }
                    else{
                        while(mySong.tickTab[nTick].note[indiceNote] != 0){
                            indiceNote += 1;
                        }
                        mySong.tickTab[nTick].note[indiceNote] = 11;
                    }
                    mySong.tickTab[nTick].note[indiceNote] = mySong.tickTab[nTick].note[indiceNote] + octave;
                    printf("note en A : %d\n", mySong.tickTab[nTick].note[indiceNote]);
                    printf("indiceNote en A : %d\n", indiceNote);
                    break;

                case 'B':
                    while(mySong.tickTab[nTick].note[indiceNote] != 0){
                        indiceNote += 1;
                    }
                    mySong.tickTab[nTick].note[indiceNote] = 12;
                    mySong.tickTab[nTick].note[indiceNote] = mySong.tickTab[nTick].note[indiceNote] + octave;
                    break;
            }

            //choix de la répétition
            if(strchr(strToken, '#') == NULL){
                switch(strToken[2]){
                    case 'R':
                        for(int n = 1; n <= 7; n++){
                            mySong.tickTab[nTick + n].note[indiceNote] = mySong.tickTab[nTick].note[indiceNote];
                            repet[nTick + n][mySong.tickTab[nTick + n].note[indiceNote]] = 1;
                        }
                        break;

                    case 'B':
                        for(int n = 1; n <= 3; n++){
                            mySong.tickTab[nTick + n].note[indiceNote] = mySong.tickTab[nTick].note[indiceNote];
                            repet[nTick + n][mySong.tickTab[nTick + n].note[indiceNote]] = 1;
                        }
                        break;

                    case 'N':
                        mySong.tickTab[nTick + 1].note[indiceNote] = mySong.tickTab[nTick].note[indiceNote];
                        repet[nTick + 1][mySong.tickTab[nTick + 1].note[indiceNote]] = 1;
                        break;

                    case 'C':
                        break;

                }
            } else {

                switch(strToken[3]){
                    case 'R':
                        for(int n = 1; n <= 7; n++){
                            mySong.tickTab[nTick + n].note[indiceNote] = mySong.tickTab[nTick].note[indiceNote];
                            repet[nTick + n][mySong.tickTab[nTick + n].note[indiceNote]] = 1;
                        }
                        break;

                    case 'B':
                        for(int n = 1; n <= 3; n++){
                            mySong.tickTab[nTick + n].note[indiceNote] = mySong.tickTab[nTick].note[indiceNote];
                            repet[nTick + n][mySong.tickTab[nTick + n].note[indiceNote]] = 1;
                        }
                        break;

                    case 'N':
                        mySong.tickTab[nTick + 1].note[indiceNote] = mySong.tickTab[nTick].note[indiceNote];
                        repet[nTick + 1][mySong.tickTab[nTick + 1].note[indiceNote]] = 1;
                        break;

                    case 'C':
                        break;
                }
            }

            printf("indiceNoteee : %d\n", indiceNote);

            strToken = strtok(NULL, separators);
        }

        for(int i = 1; i <= 60; i++) {
            if (i == mySong.tickTab[nTick].note[0] || i == mySong.tickTab[nTick].note[1] || i == mySong.tickTab[nTick].note[2] || i == mySong.tickTab[nTick].note[3]){
                if(repet[nTick][i] == 1){
                    fprintf(myWrite, "|x ");
                } else {
                    fprintf(myWrite, "|^ ");
                }
            } else {
                fprintf(myWrite, "|  ");
            }
        }

        printf("indiceNote : %d\n", indiceNote);
        printf("dernière note du tick : %d\n", mySong.tickTab[nTick].note[indiceNote]);



        //printf("\n");
        if(nTick == 16)
            fprintf(myWrite, "|");
        else
        fprintf(myWrite, "|\n");
    }

    for(int i = 1; i <= 16; i++){
        printf("notes du tick %d : %d %d %d %d\n", i, mySong.tickTab[i].note[0], mySong.tickTab[i].note[1], mySong.tickTab[i].note[2], mySong.tickTab[i].note[3]);
    }
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 60; j++){
            printf("%d ", repet[i][j]);
        }
        printf("\n");
    }








    fclose(myRead);
    fclose(myWrite);
}