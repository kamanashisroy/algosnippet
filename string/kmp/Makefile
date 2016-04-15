

TARGET_BIN:=app.bin
SOURCES:=$(wildcard src/*.cpp)
OBJECTS:=$(subst .cpp,.o,$(SOURCES))
CPPFLAGS:=-Wall
LDFLAGS:=-std=c++11

all:$(TARGET_BIN)

$(TARGET_BIN):$(OBJECTS)
	g++ $^ -o $@

test:$(TARGET_BIN)
	./$(TARGET_BIN) < input1.txt
	./$(TARGET_BIN) < input2.txt
	./$(TARGET_BIN) < input3.txt
	
clean:
	rm -f $(OBJECTS) $(TARGET_BIN)

.PHONY:clean
	
