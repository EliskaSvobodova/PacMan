CPP=g++
FLAGS= -Wall -pedantic -fsanitize=address -g
NC= -lncurses
SRC= main.cpp CMenu.cpp CGame.cpp CSettings.cpp CMap.cpp CTile.cpp CWall.cpp CTeleport.cpp CSpace.cpp CBonus.cpp CCoin.cpp CCherry.cpp CShield.cpp CEntity.cpp CPacMan.cpp CGhost.cpp CBehavior.cpp CAggresive.cpp CAmbush.cpp CPatrol.cpp CRandomOutOfWay.cpp CScatter.cpp
NAME=svoboel5

compile: $(NAME)

$(NAME): main.o CMenu.o CGame.o CSettings.o CMap.o CTile.o CWall.o CTeleport.o CSpace.o CBonus.o CCoin.o CCherry.o CShield.o CEntity.o CPacMan.o CGhost.o CBehavior.o CAggresive.o CAmbush.o CPatrol.o CRandomOutOfWay.o CScatter.o
	$(CPP) $(FLAGS) -o $(NAME) $^ $(NC)

main.o: src/main.cpp
	$(CPP) $(FLAGS) -c $^ $(NC)

CAggresive.o: src/CAggresive.cpp
	$(CPP) $(FLAGS) -c $^ $(NC)

CAmbush.o: src/CAmbush.cpp
	$(CPP) $(FLAGS) -c $^ $(NC)

CBehavior.o: src/CBehavior.cpp
	$(CPP) $(FLAGS) -c $^ $(NC)

CBonus.o: src/CBonus.cpp
	$(CPP) $(FLAGS) -c $^ $(NC)

CCoin.o: src/CCoin.cpp
	$(CPP) $(FLAGS) -c $^ $(NC)

CEntity.o: src/CEntity.cpp
	$(CPP) $(FLAGS) -c $^ $(NC)

CGame.o: src/CGame.cpp
	$(CPP) $(FLAGS) -c $^ $(NC)

CGhost.o: src/CGhost.cpp
	$(CPP) $(FLAGS) -c $^ $(NC)

CCherry.o: src/CCherry.cpp
	$(CPP) $(FLAGS) -c $^ $(NC)

CMap.o: src/CMap.cpp
	$(CPP) $(FLAGS) -c $^ $(NC)

CMenu.o: src/CMenu.cpp
	$(CPP) $(FLAGS) -c $^ $(NC)

CPacMan.o: src/CPacMan.cpp
	$(CPP) $(FLAGS) -c $^ $(NC)

CPatrol.o: src/CPatrol.cpp
	$(CPP) $(FLAGS) -c $^ $(NC)

CRandomOutOfWay.o: src/CRandomOutOfWay.cpp
	$(CPP) $(FLAGS) -c $^ $(NC)

CScatter.o: src/CScatter.cpp
	$(CPP) $(FLAGS) -c $^ $(NC)

CSettings.o: src/CSettings.cpp
	$(CPP) $(FLAGS) -c $^ $(NC)

CShield.o: src/CShield.cpp
	$(CPP) $(FLAGS) -c $^ $(NC)

CSpace.o: src/CSpace.cpp
	$(CPP) $(FLAGS) -c $^ $(NC)

CTeleport.o: src/CTeleport.cpp
	$(CPP) $(FLAGS) -c $^ $(NC)

CTile.o: src/CTile.cpp
	$(CPP) $(FLAGS) -c $^ $(NC)

CWall.o: src/CWall.cpp
	$(CPP) $(FLAGS) -c $^ $(NC)

clean: 
	rm -v *.o ./$(NAME)
	rm -v -r ./doc

run:
	./$(NAME)

doc:
	doxygen src/config_file
	cp -r doc/html/* doc/
	rm -r ./doc/html
