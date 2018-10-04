# vim: tabstop=4 noexpandtab shiftwidth=4 softtabstop=4

TARGET_PREFIX=./connected_components

#CXX=g++
SOURCES:=$(wildcard src/*.cc)
OBJECTS:=
TARGET_BIN:=$(subst .cc,.bin,$(notdir $(SOURCES)))
CXXFLAGS:=-Wall -ggdb3
#CXXFLAGS:=-Wall -O2
LDFLAGS:=-std=c++14


all:$(TARGET_BIN) Makefile
	@echo targets = ${TARGET_BIN}

%.bin:src/%.cc
	${CXX} ${CXXFLAGS} $^ -o $@ ${LDFLAGS}

clean:
	rm $(OBJECTS) $(TARGET_BIN)

include test.mk

.PHONY:clean all
	
