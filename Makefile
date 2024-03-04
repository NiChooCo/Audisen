#MakeFile squelette à modifier par les étudiants
# Taillebois Nicolas Beunon Nicolas Groupe2 Caen

#TARGET = audisen_usb.exe # pour la partie USB
TARGET = audisen_sim.out


all: $(TARGET)

run: all
	@./$(TARGET)

#Etudiants : creez les cibles de votre makefile ICI, et completez
audisen_sim.out: audisen_sim.c
	gcc audisen_sim.c -o audisen_sim.out
ams.o: ams.c ams.h
	gcc -Wall -c ams.c -o ams.o
amp.o: amp.c amp.h
	gcc -Wall -c amp.c -o amp.o
frame.o: frame.c frame.h
	gcc -Wall -c frame.c -o frame.o
usb.o: usb.c usb.h
	gcc -Wall -c frame.c -o frame.o


#CIBLE a garder pour la partie USB
# Commande de compilation pour Windows mingw a copier en console PowerShell
#  mingw32-make -f Makefile clear test_usb.exe
#audisen_usb.exe : audisen_usb.c ftd2xx.h ftd2xx.lib
#	gcc audisen_usb.c ftd2xx.lib -o audisen_usb.exe

clean:
	rm *.o *.out *.exe

clear:
	del *.o *.exe


