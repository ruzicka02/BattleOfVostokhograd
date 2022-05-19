CXXFLAGS = -Wall -pedantic -std=c++17
LDLIBS = -lncursesw -lstdc++fs

HEADERS = $(wildcard src/*.h) $(wildcard src/card/*.h) $(wildcard src/player/*.h)
SOURCES = $(wildcard src/*.cpp) $(wildcard src/card/*.cpp) $(wildcard src/player/*.cpp)
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
	cp zadani.txt README.md
	doxygen Doxyfile

.PHONY: clean
clean:
	rm -rf ruzicsi1 build/ doc/ README.md 2>/dev/null

# Requirements / Dependencies
# Proudly generated from g++ src/*.cpp -MM
CDeck.o: src/CDeck.cpp src/CDeck.h src/card/CCard.h \
 src/card/../EAbility.h src/EAbility.h
CDisplay.o: src/CDisplay.cpp src/CDisplay.h src/player/CPlayer.h \
 src/player/../CDeck.h src/player/../card/CCard.h \
 src/player/../card/../EAbility.h src/player/../EAbility.h \
 src/player/../CShop.h src/player/../CDeck.h \
 src/player/../card/CCardGeneral.h src/player/../card/CCard.h src/CShop.h
CGame.o: src/CGame.cpp src/CGame.h src/player/CPlayer.h \
 src/player/../CDeck.h src/player/../card/CCard.h \
 src/player/../card/../EAbility.h src/player/../EAbility.h \
 src/player/../CShop.h src/player/../CDeck.h \
 src/player/../card/CCardGeneral.h src/player/../card/CCard.h src/CShop.h \
 src/CDisplay.h src/player/CPlayerHuman.h src/player/CPlayer.h \
 src/player/CPlayerAI.h src/player/CPlayerBogo.h
CShop.o: src/CShop.cpp src/CShop.h src/CDeck.h src/card/CCard.h \
 src/card/../EAbility.h src/EAbility.h
main.o: src/main.cpp src/Test.h src/EAbility.h src/card/CCardTroop.h \
 src/card/CCard.h src/card/../EAbility.h src/card/CCardWarcry.h \
 src/card/CCardGeneral.h src/CDisplay.h src/player/CPlayer.h \
 src/player/../CDeck.h src/player/../card/CCard.h \
 src/player/../EAbility.h src/player/../CShop.h src/player/../CDeck.h \
 src/player/../card/CCardGeneral.h src/CShop.h src/player/CPlayerHuman.h \
 src/player/CPlayer.h src/CGame.h
Test.o: src/Test.cpp src/Test.h src/EAbility.h src/card/CCardTroop.h \
 src/card/CCard.h src/card/../EAbility.h src/card/CCardWarcry.h \
 src/card/CCardGeneral.h src/CDisplay.h src/player/CPlayer.h \
 src/player/../CDeck.h src/player/../card/CCard.h \
 src/player/../EAbility.h src/player/../CShop.h src/player/../CDeck.h \
 src/player/../card/CCardGeneral.h src/CShop.h src/player/CPlayerHuman.h \
 src/player/CPlayer.h

# card
CCard.o: src/card/CCard.cpp src/card/CCard.h src/card/../EAbility.h \
 src/card/CCardWarcry.h src/card/CCardTroop.h \
 src/card/../player/CPlayer.h src/card/../player/../CDeck.h \
 src/card/../player/../card/CCard.h src/card/../player/../EAbility.h \
 src/card/../player/../CShop.h src/card/../player/../CDeck.h \
 src/card/../player/../card/CCardGeneral.h \
 src/card/../player/../card/CCard.h
CCardGeneral.o: src/card/CCardGeneral.cpp src/card/CCardGeneral.h \
 src/card/CCard.h src/card/../EAbility.h
CCardTroop.o: src/card/CCardTroop.cpp src/card/CCardTroop.h \
 src/card/CCard.h src/card/../EAbility.h
CCardWarcry.o: src/card/CCardWarcry.cpp src/card/CCardWarcry.h \
 src/card/CCard.h src/card/../EAbility.h

# player
CPlayerAI.o: src/player/CPlayerAI.cpp src/player/CPlayerAI.h \
 src/player/CPlayer.h src/player/../CDeck.h src/player/../card/CCard.h \
 src/player/../card/../EAbility.h src/player/../EAbility.h \
 src/player/../CShop.h src/player/../CDeck.h \
 src/player/../card/CCardGeneral.h src/player/../card/CCard.h
CPlayerBogo.o: src/player/CPlayerBogo.cpp src/player/CPlayerBogo.h \
 src/player/CPlayer.h src/player/../CDeck.h src/player/../card/CCard.h \
 src/player/../card/../EAbility.h src/player/../EAbility.h \
 src/player/../CShop.h src/player/../CDeck.h \
 src/player/../card/CCardGeneral.h src/player/../card/CCard.h \
 src/player/../CDisplay.h src/player/../player/CPlayer.h \
 src/player/../CShop.h
CPlayer.o: src/player/CPlayer.cpp src/player/CPlayer.h \
 src/player/../CDeck.h src/player/../card/CCard.h \
 src/player/../card/../EAbility.h src/player/../EAbility.h \
 src/player/../CShop.h src/player/../CDeck.h \
 src/player/../card/CCardGeneral.h src/player/../card/CCard.h \
 src/player/../CDisplay.h src/player/../player/CPlayer.h \
 src/player/../CShop.h
CPlayerHuman.o: src/player/CPlayerHuman.cpp src/player/../CDisplay.h \
 src/player/../player/CPlayer.h src/player/../player/../CDeck.h \
 src/player/../player/../card/CCard.h \
 src/player/../player/../card/../EAbility.h \
 src/player/../player/../EAbility.h src/player/../player/../CShop.h \
 src/player/../player/../CDeck.h \
 src/player/../player/../card/CCardGeneral.h \
 src/player/../player/../card/CCard.h src/player/../CShop.h \
 src/player/CPlayerHuman.h src/player/CPlayer.h
