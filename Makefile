CC = g++
FREEGLUT_LIB = C:\MinGW\freeglut\lib
FREEGLUT_INCLUDE = C:\MinGW\freeglut\include

all: Loader clean

Loader : main.o Objet.o Point3D.o
	$(CC) -o $@ $^ -L"$(FREEGLUT_LIB)" -lfreeglut -lopengl32 -lglu32
	
main.o : main.cpp Objet.h Point3D.h
	$(CC) -o $@ -c $< -I"$(FREEGLUT_INCLUDE)" -std=c++11
	
Objet.o : Objet.cpp Objet.h Point3D.h
	$(CC) -o $@ -c $< -I"$(FREEGLUT_INCLUDE)" -std=c++11
	
Point3D.o : Point3D.cpp Point3D.h 
	$(CC) -o $@ -c $< -I"$(FREEGLUT_INCLUDE)" -std=c++11
	
clean:
	rm -f *.o