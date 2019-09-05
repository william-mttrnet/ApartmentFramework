#This sample makefile has been setup for a project which contains the following files: main.h, ap-main.c, ap-main.h, ap-gen.c, ap-gen.h   Edit as necessary for your project

#Change output_file_name.a below to your desired executible filename

#Set all your object files (the object files of all the .c files in your project, e.g. main.o my_sub_functions.o )
OBJ = main.o apa102.o udp_frame.o udp_low.o sk6812rgbw.o sk6812.o

#Set any dependant header files so that if they are edited they cause a complete re-compile (e.g. main.h some_subfunctions.h some_definitions_file.h ), or leave blank
<<<<<<< HEAD
DEPS = apa102.h udp_frame.h udp_low.h sk6812rgbw.h sk6812.h
=======
DEPS = apa102.h udp_frame.h udp_low.h sk6812rgbw.hpp sk6812.hpp rgb_strip_common.hpp
<<<<<<< HEAD
=======
>>>>>>> 730a18e7559b4fcb19dab86876701c9ba7c4dab2
>>>>>>> c0c95f9b30d33f54f5404420a4cc24c71b12a5b3

#Any special libraries you are using in your project (e.g. -lbcm2835 -lrt `pkg-config --libs gtk+-3.0` ), or leave blank
LIBS = -lwiringPi

#Set any compiler flags you want to use (e.g. -I/usr/include/somefolder `pkg-config --cflags gtk+-3.0` ), or leave blank
CFLAGS = -lrt

#Set the compiler you are using ( gcc for C or g++ for C++ )
CC = g++

#Set the filename extensiton of your C files (e.g. .c or .cpp )
EXTENSION = .cpp

#define a rule that applies to all files ending in the .o suffix, which says that the .o file depends upon the .c version of the file and all the .h files included in the DEPS macro.  Compile each object file
%.o: %$(EXTENSION) $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

#Combine them into the output file
#Set your desired exe output file name here
led_testing: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

#Cleanup
.PHONY: clean

clean:
	rm -f *.o *~ core *~ 
