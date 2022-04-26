CXXFLAGS = -Wall -pedantic -std=c++17
LDLIBS = -lncursesw

HEADERS = $(wildcard src/*.h)
SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(SOURCES:src/%.cpp=build/%.o)

.PHONY: all
all: compile doc

.PHONY: run
run: compile
	./ruzicsi1

.PHONY: compile
compile: ruzicsi1

ruzicsi1: build/main
	cp $< $@

build/main: $(OBJECTS)
	mkdir -p $(@D)
	g++ $^ -o $@ $(LDLIBS)

build/%.o: src/%.cpp
	mkdir -p $(@D)
	g++ $(CXXFLAGS) $< -c -o $@

debug/test_%.o: tests/%.test.cpp
	mkdir -p $(@D)
	g++ $(CXXFLAGS) $< -I src/ -c -o $@

doc: Doxyfile $(HEADERS)
	doxygen Doxyfile

.PHONY: clean
clean:
	rm -rf ruzicsi1 build/ debug/ doc/ 2>/dev/null

.PHONY: test_all
test_all: debug/test_CCoord
	debug/test_CCoord

# Requirements / Dependencies
