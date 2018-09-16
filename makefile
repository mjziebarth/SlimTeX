# Configuration:
#GTKSOURCEVIEWMM_PATH=include




ODIR=build
IDIR=include

CC=g++
CFLAGS=-Iinclude $(shell pkg-config gtkmm-3.0 --cflags) \
       $(shell pkg-config gtksourceviewmm-3.0 --cflags) \
       $(shell pkg-config evince-view-3.0 --cflags) \
       $(shell pkg-config libxml-2.0 --cflags)
LIBS=-lm $(shell pkg-config gtkmm-3.0 --libs) \
     $(shell pkg-config gtksourceviewmm-3.0 --libs) \
     $(shell pkg-config evince-view-3.0 --libs) \
     $(shell pkg-config libxml-2.0 --libs)

#_DEPS=
#DEPS=$(patsubstr %,$(ODIR)/%,$(_DEPS))
DEPS= 

# Everything in .cpp:
src = $(wildcard src/*.cpp)
obj = $(subst .cpp,.o,$(subst src,build,$(src)))

default: slimtex

# Pattern to compile source files from src to object files
# in build:
build/%.o: src/%.cpp include/%.hpp $(DEPS)
	$(CC) $(CFLAGS) -std=c++17 -c -g -o $@ $<

build/slimtex.o: src/slimtex.cpp $(DEPS)
	$(CC) $(CFLAGS) -std=c++17 -c -g -o $@ $<



slimtex: $(obj)
	$(CC) $(LIBS) -std=c++17 -g -o slimtex $(obj)
#	echo "TEST"
#	echo $(CFLAGS)
#	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean
clean:
