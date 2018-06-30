

TARGET_BIN:=app.bin
SOURCES:=$(wildcard src/*.cpp)
OBJECTS:=$(subst .cpp,.o,$(SOURCES))
CPPFLAGS:=-Wall
LDFLAGS:=-std=c++11
INCLUDES:=-Isrc
CPPFLAGS+=$(INCLUDES)

all:$(TARGET_BIN)

$(TARGET_BIN):$(OBJECTS)
	g++ $^ -o $@

test:$(TARGET_BIN)
	./$(TARGET_BIN) < input1.txt
	./$(TARGET_BIN) < input2.txt
	
clean:
	rm -f $(OBJECTS) $(TARGET_BIN)

.PHONY:clean
	
