

TARGET_BIN:=app.bin
SOURCES:=$(wildcard src/*.cc)
OBJECTS:=$(subst .cc,.o,$(SOURCES))
CXXFLAGS:=-Wall -DALGO_TEST
LDFLAGS:=-std=c++11

all:$(TARGET_BIN)

$(TARGET_BIN):$(OBJECTS)
	${CXX} ${CXXFLAGS} $^ -o $@

test:$(TARGET_BIN)
	./$(TARGET_BIN)
	./$(TARGET_BIN)
	
clean:
	rm -f $(OBJECTS) $(TARGET_BIN)

.PHONY:clean
	
