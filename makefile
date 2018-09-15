# Configuration:
#GTKSOURCEVIEWMM_PATH=include




ODIR=build
IDIR=include

CC=g++
CFLAGS=-Iinclude $(shell pkg-config gtkmm-3.0 --cflags) \
       $(shell pkg-config gtksourceviewmm-3.0 --cflags)
LIBS=-lm $(shell pkg-config gtkmm-3.0 --libs) $(shell pkg-config gtksourceviewmm-3.0 --libs)

#_DEPS=
#DEPS=$(patsubstr %,$(ODIR)/%,$(_DEPS))
DEPS= 

# Everything in .cpp:
src = $(wildcard src/*.cpp)
obj = $(subst .cpp,.o,$(subst src,build,$(src)))

# Pattern to compile source files from src to object files
# in build:
build/%.o: src/%.cpp include/%.hpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

build/slimtex.o: src/slimtex.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

default: slimtex


slimtex: $(obj)
	$(CC) $(LIBS) -o slimtex $(obj)
#	echo "TEST"
#	echo $(CFLAGS)
#	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean
clean:
