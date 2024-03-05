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
		char line[MAX_SIZE_LINE];
		fgets(line , TMP_MAX, songFile);
		mySong.tpm = atoi(line);
		for (int i = 0; i < MAX_NUMBER_TICKS; ++i) {
			for (int j = 0; j < MAX_SIZE_LINE; ++j) {

			}
		}
	}
	printf("%s", mySong.title);
	printf("%d", mySong.tpm);
	return mySong;
}


void createAMS(char* txtFileName, char* amsFileName){


}