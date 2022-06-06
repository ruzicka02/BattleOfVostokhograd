CXXFLAGS = -Wall -pedantic -std=c++17
LDLIBS = -lncursesw -lstdc++fs

HEADERS = $(wildcard src/*.h) $(wildcard src/*/*.h)
SOURCES = $(wildcard src/*.cpp) $(wildcard src/*/*.cpp)
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

# linking process, creating the executable binary file in the main directory
ruzicsi1: $(OBJECTS)
	g++ $^ -o $@ $(LDLIBS)

# compiles the given cpp file into an object file in the 'build' directory
# $(@D) stands for the needed (sub)directory that has to be created first
build/%.o: src/%.cpp
	mkdir -p $(@D)
	g++ $(CXXFLAGS) $< -c -o $@ -g

doc: Doxyfile $(HEADERS)
	doxygen Doxyfile

.PHONY: clean
clean:
	rm -rf ruzicsi1 build/ doc/ 2>/dev/null

# Requirements / Dependencies
# Proudly generated from g++ src/*.cpp src/*/*.cpp -MM
# Manually tweaked afterwards to avoid jumps between directories (src/player/../card/CCard.h)
CDeck.o: src/CDeck.cpp src/CDeck.h src/card/CCardDeckable.h \
 src/card/CCard.h src/card/EAbility.h
CDisplay.o: src/CDisplay.cpp src/CDisplay.h src/player/CPlayer.h \
 src/CShop.h src/CDeck.h \
 src/card/CCardDeckable.h src/card/CCard.h \
 src/card/EAbility.h src/card/CCardGeneral.h \
 src/CShop.h
CGame.o: src/CGame.cpp src/CGame.h src/CDisplay.h src/player/CPlayer.h \
 src/CShop.h src/CDeck.h \
 src/card/CCardDeckable.h src/card/CCard.h \
 src/card/EAbility.h src/card/CCardGeneral.h \
 src/player/CPlayerHuman.h src/player/CPlayer.h src/player/CPlayerAI.h \
 src/player/CPlayerBogo.h
CShop.o: src/CShop.cpp src/CShop.h src/CDeck.h src/card/CCardDeckable.h \
 src/card/CCard.h src/card/EAbility.h
main.o: src/main.cpp src/Test.h src/CGame.h src/CDisplay.h \
 src/player/CPlayer.h src/CShop.h src/CDeck.h \
 src/card/CCardDeckable.h src/card/CCard.h \
 src/card/EAbility.h src/card/CCardGeneral.h
Test.o: src/Test.cpp src/Test.h src/card/CCardTroop.h \
 src/card/CCardDeckable.h src/card/CCard.h src/card/EAbility.h \
 src/card/CCardWarcry.h src/card/CCardGeneral.h src/CDisplay.h \
 src/player/CPlayer.h src/CShop.h src/CDeck.h \
 src/card/CCardDeckable.h src/card/CCardGeneral.h \
 src/player/CPlayerHuman.h src/CGame.h

# card
CCard.o: src/card/CCard.cpp src/card/CCard.h src/card/EAbility.h \
 src/player/CPlayer.h src/CShop.h \
 src/CDeck.h src/card/CCardDeckable.h \
 src/card/CCardGeneral.h
CCardDeckable.o: src/card/CCardDeckable.cpp src/card/CCardDeckable.h \
 src/card/CCard.h src/card/EAbility.h src/card/CCardWarcry.h \
 src/card/CCardTroop.h
CCardGeneral.o: src/card/CCardGeneral.cpp src/card/CCardGeneral.h \
 src/card/CCard.h src/card/EAbility.h
CCardTroop.o: src/card/CCardTroop.cpp src/card/CCardTroop.h \
 src/card/CCardDeckable.h src/card/CCard.h src/card/EAbility.h
CCardWarcry.o: src/card/CCardWarcry.cpp src/card/CCardWarcry.h \
 src/card/CCardDeckable.h src/card/CCard.h src/card/EAbility.h

# player
CPlayerAI.o: src/player/CPlayerAI.cpp src/player/CPlayerAI.h \
 src/player/CPlayer.h src/CShop.h src/CDeck.h \
 src/card/CCardDeckable.h src/card/CCard.h \
 src/card/EAbility.h src/card/CCardGeneral.h \
 src/CDisplay.h
CPlayerBogo.o: src/player/CPlayerBogo.cpp src/player/CPlayerBogo.h \
 src/player/CPlayer.h src/CShop.h src/CDeck.h \
 src/card/CCardDeckable.h src/card/CCard.h \
 src/card/EAbility.h src/card/CCardGeneral.h \
 src/CDisplay.h
CPlayer.o: src/player/CPlayer.cpp src/player/CPlayer.h \
 src/CShop.h src/CDeck.h \
 src/card/CCardDeckable.h src/card/CCard.h \
 src/card/EAbility.h src/card/CCardGeneral.h \
 src/CDisplay.h
CPlayerHuman.o: src/player/CPlayerHuman.cpp src/player/CPlayerHuman.h \
 src/player/CPlayer.h src/CShop.h src/CDeck.h \
 src/card/CCardDeckable.h src/card/CCard.h \
 src/card/EAbility.h src/card/CCardGeneral.h \
 src/CDisplay.h

