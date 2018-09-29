

TARGET_BIN:=$(subst .cc,.bin, $(notdir $(sort $(wildcard src/*.cc))))
CXXFLAGS:=-Wall -ggdb3
INCLUDES:=-Isrc
CXXFLAGS+=$(INCLUDES)
LDFLAGS:=-std=c++14
#CXX=g++

all:$(TARGET_BIN)


%.bin:src/%.cc
	${CXX} ${CXXFLAGS} $^ -o $@ ${LDFLAGS}


test:$(TARGET_BIN)
	./$(TARGET_BIN)
	
clean:
	rm -f $(OBJECTS) $(TARGET_BIN)

.PHONY:clean
	
