

TARGET_BIN:=repeat_sum.bin
SOURCES:=$(wildcard src/*.cpp)
OBJECTS:=$(subst .cpp,.o,$(SOURCES))
CPPFLAGS:=-Wall
LDFLAGS:=-std=c++11
INCLUDES:=-Isrc
CPPFLAGS+=$(INCLUDES)

all:$(TARGET_BIN)

%.bin:src/%.cpp
	${CXX} $^ -o $@

test:$(TARGET_BIN)
	./$(TARGET_BIN) < input1.txt
	./$(TARGET_BIN) < input2.txt
	
clean:
	rm -f $(OBJECTS) $(TARGET_BIN)

.PHONY:clean
	
