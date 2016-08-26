#
# This file is part of the VSS-Viewer project.
#
# This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
# v. 3.0. If a copy of the GPL was not distributed with this
# file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
#


CCX = g++ -std=c++11 -w



INCLUDES = -Isrc -Isrc/proto -Isrc/interface
LIBRARIES = `pkg-config --cflags --libs protobuf` -lzmq -lpthread -lGLU -lglut -lGL -w



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
	cd src/VSS-Interface/protos && make -f protos.make

docm:
	cd doc && doxygen
