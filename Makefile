CC=gcc
CFLAGS=-Wall
INCLUDES=./includes
BUILD_D=./build/debug
BUILD_R=./build/release
OBJECTS=./objects
SOURCES=./src
AR=ar
# SECONDARY=APPROACH_SECONDARY



all: main.o stream.o filter.o streamlib.o map.o
	$(CC) $(CFLAGS) -I$(INCLUDES) $(OBJECTS)/main.o $(OBJECTS)/stream.o $(OBJECTS)/filter.o $(OBJECTS)/streamlib.o $(OBJECTS)/map.o -o streamlib_test 

filter.o: $(SOURCES)/filter.c
	$(CC) $(CFLAGS) -I$(INCLUDES) -c $(SOURCES)/filter.c -o $(OBJECTS)/filter.o

stream.o: $(SOURCES)/stream.c
	$(CC) $(CFLAGS) -I$(INCLUDES) -c $(SOURCES)/stream.c -o $(OBJECTS)/stream.o

streamlib.o: $(SOURCES)/streamlib.c
	$(CC) $(CFLAGS) -I$(INCLUDES) -c $(SOURCES)/streamlib.c -o $(OBJECTS)/streamlib.o

map.o: $(SOURCES)/map.c
	$(CC) $(CFLAGS) -I$(INCLUDES) -c $(SOURCES)/map.c -o $(OBJECTS)/map.o

main.o: ./main.c
	$(CC) $(CFLAGS) -I$(INCLUDES) -c ./main.c -o $(OBJECTS)/main.o

clean:
	rm -rf $(OBJECTS)/*.o
	rm -rf $(BUILD_R)/*.a
	rm -rf $(BUILD_D)/*.a
	rm -rf $(BUILD_D)/*.dll
	rm -rf $(BUILD_R)/*.dll
	rm -f streamlib_test.exe
	rm -f streamlib_test