

TARGET_BIN:=app.bin
SOURCES:=$(wildcard src/*.c)
OBJECTS:=$(subst .c,.o,$(SOURCES))
CPPFLAGS:=-Wall
LDFLAGS:=-std=c++11
INCLUDES:=-Isrc
CPPFLAGS+=$(INCLUDES)

all:$(TARGET_BIN)

$(TARGET_BIN):$(OBJECTS)
	$(CC) $^ -o $@

test:$(TARGET_BIN)
	./$(TARGET_BIN)
	
clean:
	rm -f $(OBJECTS) $(TARGET_BIN)

.PHONY:clean
	
