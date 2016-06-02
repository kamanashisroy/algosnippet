
TARGET_BIN = app.bin
ALG_SOURCES = $(wildcard src/*.cpp)


all:test


$(TARGET_BIN):$(ALG_SOURCES)
	g++ $^ -o $@

test:$(TARGET_BIN)
	./$(TARGET_BIN)

