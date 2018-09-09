

#TARGET_BIN:=app.bin
SOURCES:=$(wildcard src/*.cc)
OBJECTS:=$(subst .cc,.o,$(SOURCES))
TARGET_BIN:=$(subst .cc,.bin,$(notdir $(SOURCES)))
CXXFLAGS:=-Wall -ggdb3 -DALGO_TEST
LDFLAGS:=-std=c++11

all:$(TARGET_BIN)

%.bin:src/%.cc
	${CXX} ${CXXFLAGS} $^ -o $@ ${LDFLAGS}

test:$(TARGET_BIN)
	./$(TARGET_BIN)
	
clean:
	rm -f $(OBJECTS) $(TARGET_BIN)

.PHONY:clean
	
