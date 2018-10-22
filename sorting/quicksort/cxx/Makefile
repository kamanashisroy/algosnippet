# vim: tabstop=4 noexpandtab shiftwidth=4 softtabstop=4

#CXX=g++
SOURCES:=$(wildcard src/*.cc)
OBJECTS:=
TARGET_BIN:=$(subst .cc,.bin,$(notdir $(SOURCES)))
CXXFLAGS:=-Wall -ggdb3
INCLUDES=-Iinc
#CXXFLAGS:=-Wall -O2
CXXFLAGS+= -DDEBUG_QUICK_SORT
CXXFLAGS+= -DTEST_QUICK_SORT
LDFLAGS:=-std=c++14


all:$(TARGET_BIN) Makefile
	@echo targets = ${TARGET_BIN}

%.bin:src/%.cc inc/%.h
	${CXX} ${CXXFLAGS} ${INCLUDES} $< -o $@ ${LDFLAGS}

clean:
	rm $(OBJECTS) $(TARGET_BIN)

.PHONY:clean all
	
