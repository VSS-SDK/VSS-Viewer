CCX = g++ -std=c++11 -w



INCLUDES = -Isrc -Isrc/proto
LIBRARIES = `pkg-config --cflags --libs protobuf` -lpthread -lGLU -lglut -lGL -w



SRC := $(shell find -name '*.cpp')
FILE_NAMES_SRC = $(SRC:.cpp=.o)

PROTOS := $(shell find -name '*.cc')
FILE_NAMES_PROTOS = $(PROTOS:.cc=.o)



FILE_NAMES = $(FILE_NAMES_SRC) $(FILE_NAMES_PROTOS)



EXEC = VSS-Viewer



.cpp.o:
	@$(CCX) $(INCLUDES) $(LIBRARIES) -Wall -Wformat -c -o $@ $< -w

.cc.o:
	@$(CCX) $(INCLUDES) $(LIBRARIES) -Wall -Wformat -c -o $@ $< -w

all: message $(EXEC)
	@echo Done .
	
message:
	@echo Compiling VSS-Viewer ...

run:
	./VSS-Viewer

$(EXEC): $(FILE_NAMES)
	@$(CCX) -o $(EXEC) $(FILE_NAMES) $(LIBRARIES) $(INCLUDES)

clean:
	rm $(EXEC) $(FILE_NAMES)

proto:
	cd proto/ && make -f protos.make

