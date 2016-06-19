

TARGET_BIN:=app.s
SOURCES:=$(wildcard src/*.c)
#OBJECTS:=$(subst .c,.s,$(SOURCES))
CPPFLAGS:=-Wall -fverbose-asm -S
LDFLAGS:=-std=c++11
INCLUDES:=-Isrc
CPPFLAGS+=$(INCLUDES)

all:$(TARGET_BIN)

$(TARGET_BIN):$(SOURCES)
	$(CC) -O0 -S $^ -o $@

clean:
	rm -f $(OBJECTS) $(TARGET_BIN)

.PHONY:clean
	
