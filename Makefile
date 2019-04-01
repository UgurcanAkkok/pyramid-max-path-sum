SOURCE=maxpath.cpp
EXECUTABLE=maxpath
CC=g++
FLAGS=-g --std=c++17

main: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCE)
	$(CC) $(FLAGS) $(SOURCE) -o $(EXECUTABLE)

clean:
	rm $(EXECUTABLE)
