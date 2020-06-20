
CMP = g++
CLASS = snake
MAIN = project
EXEC = snake

$(EXEC): $(CLASS).o $(MAIN).o
	$(CMP) $(CLASS).o $(MAIN).o -o $(EXEC) gfx.o -lX11

$(CLASS).o: $(CLASS).cpp $(CLASS).h
	$(CMP) -c $(CLASS).cpp -o $(CLASS).o -std=c++11 

$(MAIN).o: $(MAIN).cpp $(CLASS).h
	$(CMP) -c $(MAIN).cpp -o $(MAIN).o -std=c++11

clean:
	rm $(EXEC)
	rm $(CLASS).o $(MAIN).o

