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

.PHONY: debug
debug: compile
	./ruzicsi1 --debug

.PHONY: compile
compile: ruzicsi1

ruzicsi1: build/main
	cp $< $@

build/main: $(OBJECTS)
	mkdir -p $(@D)
	g++ $^ -o $@ $(LDLIBS)

build/%.o: src/%.cpp
	mkdir -p $(@D)
	g++ $(CXXFLAGS) $< -c -o $@ -g

doc: Doxyfile $(HEADERS)
	doxygen Doxyfile

.PHONY: clean
clean:
	rm -rf ruzicsi1 build/ debug/ doc/ 2>/dev/null

# Requirements / Dependencies
# Proudly generated from g++ src/*.cpp -MM
CCard.o: src/CCard.cpp src/CCard.h src/EAbility.h src/CCardWarcry.h \
 src/CCardTroop.h src/CPlayer.h src/CDeck.h src/CShop.h \
 src/CCardGeneral.h
CCardGeneral.o: src/CCardGeneral.cpp src/CCardGeneral.h src/CCard.h \
 src/EAbility.h
CCardTroop.o: src/CCardTroop.cpp src/CCardTroop.h src/CCard.h \
 src/EAbility.h
CCardWarcry.o: src/CCardWarcry.cpp src/CCardWarcry.h src/CCard.h \
 src/EAbility.h
CDeck.o: src/CDeck.cpp src/CDeck.h src/CCard.h src/EAbility.h \
 src/CCardWarcry.h
CDisplay.o: src/CDisplay.cpp src/CDisplay.h src/CPlayer.h src/CDeck.h \
 src/CCard.h src/EAbility.h src/CCardWarcry.h src/CShop.h \
 src/CCardGeneral.h
CGame.o: src/CGame.cpp src/CGame.h src/CPlayer.h src/CDeck.h src/CCard.h \
 src/EAbility.h src/CCardWarcry.h src/CShop.h src/CCardGeneral.h \
 src/CDisplay.h
CPlayerAI.o: src/CPlayerAI.cpp src/CPlayerAI.h src/CPlayer.h src/CDeck.h \
 src/CCard.h src/EAbility.h src/CCardWarcry.h src/CShop.h \
 src/CCardGeneral.h
CPlayer.o: src/CPlayer.cpp src/CPlayer.h src/CDeck.h src/CCard.h \
 src/EAbility.h src/CCardWarcry.h src/CShop.h src/CCardGeneral.h
CPlayerHuman.o: src/CPlayerHuman.cpp src/CDisplay.h src/CPlayer.h \
 src/CDeck.h src/CCard.h src/EAbility.h src/CCardWarcry.h src/CShop.h \
 src/CCardGeneral.h src/CPlayerHuman.h
CShop.o: src/CShop.cpp src/CShop.h src/CDeck.h src/CCard.h src/EAbility.h \
 src/CCardWarcry.h
main.o: src/main.cpp src/Test.h src/EAbility.h src/CCardTroop.h \
 src/CCard.h src/CCardWarcry.h src/CCardGeneral.h src/CDisplay.h \
 src/CPlayer.h src/CDeck.h src/CShop.h src/CPlayerHuman.h
Test.o: src/Test.cpp src/EAbility.h src/CCardTroop.h src/CCard.h \
 src/CCardWarcry.h src/CCardGeneral.h src/CDisplay.h src/CPlayer.h \
 src/CDeck.h src/CShop.h src/CPlayerHuman.h
