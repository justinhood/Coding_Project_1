CC = g++
all: stage1.exe stage2.exe stage3.exe Vigenere_decryptor.exe 

V_Cipher.o: V_Cipher.cpp V_Cipher.h
	$(CC) V_Cipher.cpp -c -g
stage1.exe: main1.o V_Cipher.o
	$(CC) main1.o V_Cipher.o -o stage1.exe -g
main1.o: main1.cpp V_Cipher.h
	$(CC) main1.cpp -c -g
stage2.exe: main2.o V_Cipher.o
	$(CC) main2.o V_Cipher.o -o stage2.exe -g
main2.o: main2.cpp V_Cipher.h
	$(CC) main2.cpp -c -g

stage3.exe: main3.o V_Cipher.o
	$(CC) main3.o V_Cipher.o -o stage3.exe -g
main3.o: main3.cpp V_Cipher.h
	$(CC) main3.cpp -c -g

Vigenere_decryptor.exe: Vigenere_decryptor.o V_Cipher.o
	$(CC) Vigenere_decryptor.o V_Cipher.o -o Vigenere_decryptor.exe -g
Vigenere_decryptor.o: Vigenere_decryptor.cpp V_Cipher.h
	$(CC) Vigenere_decryptor.cpp -c -g

