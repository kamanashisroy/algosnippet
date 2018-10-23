# vim: tabstop=4 noexpandtab shiftwidth=4 softtabstop=4

#CXX=g++
SOURCES:=$(wildcard src/*.cc)
OBJECTS:=
TARGET_BIN:=$(subst .cc,.bin,$(notdir $(SOURCES)))
CXXFLAGS:=-Wall -ggdb3
INCLUDES=-Iinc
#CXXFLAGS:=-Wall -O2
CXXFLAGS+= -DDEBUG_KMP
CXXFLAGS+= -DTEST_KMP
LDFLAGS:=-std=c++14

TEST_TARGET:=$(word 1,${TARGET_BIN})

all:$(TARGET_BIN) Makefile
	@echo targets = ${TARGET_BIN}

%.bin:src/%.cc inc/%.h
	${CXX} ${CXXFLAGS} ${INCLUDES} $< -o $@ ${LDFLAGS}

test:$(TEST_TARGET)
	./$(TEST_TARGET) < input1.txt
	./$(TEST_TARGET) < input2.txt
	./$(TEST_TARGET) < input3.txt
	./$(TEST_TARGET) < input4.txt
	./$(TEST_TARGET) < input5.txt

clean:
	rm $(OBJECTS) $(TARGET_BIN)

.PHONY:clean all
	
