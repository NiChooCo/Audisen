/**
 * @authors Nom Prenom Nom Prenom Groupe Ville
 */

#include "define.h"
#include "ams.h"


s_song readAMS(char* fileName){
	s_song mySong;
	FILE * songFile;
	songFile = fopen(fileName, "r");
	if(songFile==NULL){
		printf("Erreur, fichier ams non trouvé\n");
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
        mySong.title[strlen(mySong.title)-1]='\0';
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
            /*printf("Accent : %d\n", mySong.tickTab[i].accent);
            for (int j = 0; j < 4; ++j) {
                printf("%d ", mySong.tickTab[i].note[j]);
            }
            printf("\n");*/
            i+=1;
        }
        mySong.nTicks = nb_lignes;
    }



	//printf("Titre : %s\n", mySong.title);
	//printf("Tick par minute : %d\n", mySong.tpm);
    //printf("%d\n", mySong.tickTab[14].note[2]);
    //printf("%d\n", mySong.nTicks);
	return mySong;
}


/*void createAMS(char* txtFileName, char* amsFileName){

    FILE * myBook;
    myBook = fopen(txtFileName, "r");
    char line[MAX_SIZE_LINE];
    fgets(title, MAX_SIZE_LINE, myBook);

    fclose(myBook);

}*/