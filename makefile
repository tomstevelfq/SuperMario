CC=g++ -g
IDIR=-IC:\Users\tomst\Desktop\sfml\SFML-2.5.1\include
LDIR=-LC:\Users\tomst\Desktop\sfml\SFML-2.5.1\lib
LIB=-lsfml-graphics -lsfml-window -lsfml-system
RM=del
target=main.exe
Outputs=Outputs\\
lfile=$(IDIR) $(LDIR) $(LIB)
ofile=$(Outputs)main.o $(Outputs)Mario.o $(Outputs)MapDesigner.o $(Outputs)Map.o
$(target):$(ofile)
	$(CC) $(ofile) $(lfile) -o $(target)
$(Outputs)Mario.o:Mario.cpp
	$(CC) Mario.cpp $(lfile) -c -o $(Outputs)Mario.o
$(Outputs)main.o:main.cpp
	$(CC) main.cpp $(lfile) -c -o $(Outputs)main.o
$(Outputs)MapDesigner.o:MapDesigner.cpp
	$(CC) MapDesigner.cpp $(lfile) -c -o $(Outputs)MapDesigner.o
$(Outputs)Map.o:Map.cpp
	$(CC) Map.cpp $(lfile) -c -o $(Outputs)Map.o
clean:
	$(RM) $(ofile) main.exe
