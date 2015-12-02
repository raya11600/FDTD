CC=g++
CFLAGS=-I -03 -ffast-math.
DEPS = Fourier.h Parameter.h ArrayGenerator.h Coefficient.h CPML.h Source.h TFSF.h Update.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

fdtdmake: Fourier.o Parameter.o ArrayGenerator.o Coefficient.o CPML.o main.o Source.o TFSF.o Update.o
	g++ -o fdtd Fourier.o Parameter.o ArrayGenerator.o Coefficient.o CPML.o main.o Source.o TFSF.o Update.o

clean_obj:
	rm -rv *.o

clean_all:
	rm -rv *.o *.log fdtd *.data
