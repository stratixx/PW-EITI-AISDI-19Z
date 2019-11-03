# Author: Konrad Winnicki
# Github account: stratixx
# My makefile - type 'make all' to compile project

# Latest working version
###################################################################

# nazwa projektu
project_name = sorting

# komenda kompilacji
CC = g++

# katalog zawierajacy pliki *.c
s = src

# katalog zawierajacy wynikowy plik wykonywalny 'project_name'
b = bin

# katalog zawierajacy skompilowane obiekty *.o
o = obj

###################################################################

# kompilacja wszystkich zaleznosci do pliku wykonywalnego
all: main

# wyczyszczenie projektu
clean: 
	rm -r -f $o $b
	mkdir $o $b

# kompilacja poszczegolnych zaleznosci. wywolywane przez regule all

object1 = main
$(object1): $s/$(object1).cpp 
	$(CC) $s/$(object1).cpp     -o $b/$(project_name)
