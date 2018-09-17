# Configuration:
#GTKSOURCEVIEWMM_PATH=include



# Directories:
ODIR=build
IDIR=include
SRCDIR=src

# Use c++17 as standard. If c++17 is not available (e.g. in linked
# libraries), pkg-config should default to the required standard.
# Since pkg-config is called afterwards this overrides.
STD=c++17
CC=g++
CFLAGS= -std=$(STD) -Iinclude $(shell pkg-config gtkmm-3.0 --cflags) \
       $(shell pkg-config gtksourceviewmm-3.0 --cflags) \
       $(shell pkg-config evince-view-3.0 --cflags) \
       $(shell pkg-config libxml-2.0 --cflags)
LIBS=-lm $(shell pkg-config gtkmm-3.0 --libs) \
     $(shell pkg-config gtksourceviewmm-3.0 --libs) \
     $(shell pkg-config evince-view-3.0 --libs) \
     $(shell pkg-config libxml-2.0 --libs)

DEPS= 

# Everything in .cpp:
src = $(wildcard $(SRCDIR)/*.cpp)
obj = $(subst .cpp,.o,$(subst src,build,$(src)))

default: slimtex

# Pattern to compile source files from src to object files
# in build:
build/%.o: src/%.cpp include/%.hpp $(DEPS)
	mkdir -p $(ODIR)
	$(CC) $(CFLAGS) -c -g -o $@ $<

build/slimtex.o: src/slimtex.cpp $(DEPS)
	mkdir -p $(ODIR)
	$(CC) $(CFLAGS) -c -g -o $@ $<



slimtex: $(obj)
	mkdir -p $(ODIR)
	$(CC) $(obj) $(LIBS) -g -o slimtex 

.PHONY: clean
clean:
