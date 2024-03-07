/**
 * @authors Nom Prenom Nom Prenom Groupe Ville
 */

#include "define.h"
#include "frame.h"
#include "ftd2xx.h"
#include "usb.h"


/** Permet d'initialiser la carte et créer une instance
 *
 * @return
 */
FT_HANDLE initUSB() {
    FT_HANDLE ftHandle;
    FT_STATUS ftStatus;

    ftStatus = FT_Open(0, &ftHandle);
    if (ftStatus != FT_OK) {
        printf("Failed to open USB device\n");
        FT_Close(ftHandle);
        exit(1);
    } else {
        printf("USB Device open in initUSB\n");
    }
    ftStatus = FT_SetBaudRate(ftHandle, 9600);
    if (ftStatus == FT_OK) {
        printf("BaudRate set\n");
    } else {
        printf("raté\n");
        FT_Close(ftHandle);
    }

// Set 8 data bits, 1 stop bit and no parity
    ftStatus = FT_SetDataCharacteristics(ftHandle, FT_BITS_8, FT_STOP_BITS_1,
    FT_PARITY_NONE);
    if (ftStatus == FT_OK) {
        printf("Data Characteristics set\n");
    }
    else {
        printf("Failed\n");
        FT_Close(ftHandle);
    }

    ftStatus = FT_SetFlowControl(ftHandle, FT_FLOW_NONE, 0, 0);
    if (ftStatus == FT_OK) {
        printf("SetFlowControl Complete\n");
    }
    else {
        printf("SetFlowControl Failed\n");
        FT_Close(ftHandle);
    }

    ftStatus = FT_SetTimeouts(ftHandle, 1000, 1000); //read 1s write 1s
    if (ftStatus == FT_OK) {
        printf("Timeouts set\n");
    }
    else {
        printf("Error\n");
        FT_Close(ftHandle);
    }
    return ftHandle;
}

/** Permet de fermer l'instance
 *
 * @param ftHandle instance
 */
void closeUSB(FT_HANDLE ftHandle){
    FT_Close(ftHandle);
}

/** Permet de transférer les frames à la carte pour jouer le morceau
 *
 * @param frame la frame qui va être envoyée à la carte
 * @param ftHandle l'instance
 */
void writeUSB(char* frame, FT_HANDLE ftHandle){
    FT_STATUS ftStatus;
    DWORD bytesWritten;

    ftStatus = FT_Write(ftHandle, frame, strlen(frame), &bytesWritten);
    if (ftStatus == FT_OK) {
        printf("Successfully written\n");
        printf("%s",frame);
    }
    else {
        printf("Error while writing\n");
    }
}