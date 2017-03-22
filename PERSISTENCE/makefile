all:merge

cc = g++
INCLUDE = ../include 
cflags = -g -Wall -ansi -D_LINUX
LIBDIR = ../lib
lib = -lpthread  -L$(LIBDIR) 
workdir = ../work
objects =	mfc.o my.o

merge: DYNCREATE.exe
DYNCREATE.exe  : $(objects) main.o
	$(cc)   -I $(INCLUDE) $(cflags) -o $@ $(objects) main.o $(lib)
main.o: %.o: %.cpp 
	$(cc)   -I $(INCLUDE) $(cflags) -c $<
mfc.o: %.o: %.cpp %.h 
	$(cc)   -I $(INCLUDE) $(cflags) -c $<
my.o: %.o: %.cpp %.h
	$(cc) 	-I $(INCLUDE) $(cflags) -c $<
clean:
	rm -rf *.o

