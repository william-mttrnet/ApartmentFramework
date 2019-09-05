#This sample makefile has been setup for a project which contains the following files: main.h, ap-main.c, ap-main.h, ap-gen.c, ap-gen.h   Edit as necessary for your project

# to run: sudo ./led_testing -D0  --led-slowdown-gpio=2  --led-cols=64 --led-gpio-mapping=adafruit-hat-pwm

#Change output_file_name.a below to your desired executible filenames

RGB_LIB_DISTRIBUTION=rpi-rgb-led-matrix
RGB_INCDIR=$(RGB_LIB_DISTRIBUTION)/include
RGB_LIBDIR=$(RGB_LIB_DISTRIBUTION)/lib
RGB_LIBRARY_NAME=rgbmatrix
RGB_LIBRARY=$(RGB_LIBDIR)/lib$(RGB_LIBRARY_NAME).a
LDFLAGS+=-L$(RGB_LIBDIR) -l$(RGB_LIBRARY_NAME) -lrt -lm -lpthread

#Set all your object files (the object files of all the .c files in your project, e.g. main.o my_sub_functions.o )
OBJ = main.o udp_frame.o udp_low.o

#Set any dependant header files so that if they are edited they cause a complete re-compile (e.g. main.h some_subfunctions.h some_definitions_file.h ), or leave blank
DEPS = udp_frame.h udp_low.h

#Any special libraries you are using in your project (e.g. -lbcm2835 -lrt `pkg-config --libs gtk+-3.0` ), or leave blank
LIBS = -lwiringPi 

#Set any compiler flags you want to use (e.g. -I/usr/include/somefolder `pkg-config --cflags gtk+-3.0` ), or leave blank
CFLAGS = -lrt -Wall -O3 -g -Wextra -Wno-unused-parameter

#Set the compiler you are using ( gcc for C or g++ for C++ )
CCX = g++

#Set the filename extensiton of your C files (e.g. .c or .cpp )
EXTENSION = .cc

#define a rule that applies to all files ending in the .o suffix, which says that the .o file depends upon the .c version of the file and all the .h files included in the DEPS macro.  Compile each object file
%.o: %$(EXTENSION)  -I$(RGB_LIBRARY) $(DEPS)
	$(CCX) -c -o $@ $< $(CFLAGS)

#Combine them into the output file
#Set your desired exe output file name here
led_testing: $(RGB_LIBRARY) $(OBJ) 
	$(CCX) $(CFLAGS) -o $@ $^  $(LIBS) $(LDFLAGS)

#Cleanup
.PHONY: clean

clean:
	rm -f *.o *~ core *~
