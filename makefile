C=g++
CFLAGS=-c -Wall
LDFLAGS=-lstdc++
SOURCES=main.cpp parser.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=parser

all: $(SOURCES) $(EXECUTABLE)

clean:
	rm $(OBJECTS) $(EXECUTABLE) 
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
