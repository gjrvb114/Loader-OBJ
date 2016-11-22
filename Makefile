CC = g++
FREEGLUT_LIB = C:\MinGW\freeglut\lib
FREEGLUT_INCLUDE = C:\MinGW\freeglut\include

all: LoaderOBJ clean

LoaderOBJ : main.o Objet3D.o Point3D.o Camera.o Loader.o
	$(CC) -o $@ $^ -L"$(FREEGLUT_LIB)" -lfreeglut -lopengl32 -lglu32
	
main.o : main.cpp Loader.h includes.h
	$(CC) -o $@ -c $< -I"$(FREEGLUT_INCLUDE)" -std=c++11
	
Loader.o : Loader.cpp Loader.h Camera.h Objet3D.h includes.h
	$(CC) -o $@ -c $< -I"$(FREEGLUT_INCLUDE)" -std=c++11
	
Objet3D.o : Objet3D.cpp Objet3D.h Point3D.h Point2D.h Indices.h includes.h
	$(CC) -o $@ -c $< -I"$(FREEGLUT_INCLUDE)" -std=c++11

Camera.o : Camera.cpp Camera.h Point3D.h includes.h
	$(CC) -o $@ -c $< -I"$(FREEGLUT_INCLUDE)" -std=c++11
	
Point3D.o : Point3D.cpp Point3D.h includes.h
	$(CC) -o $@ -c $< -I"$(FREEGLUT_INCLUDE)" -std=c++11
	
clean:
	rm -f *.o