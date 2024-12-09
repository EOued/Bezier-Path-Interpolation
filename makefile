pathing: pathing.o display.o bezier.o path.o
	g++ -O0 pathing.o display.o bezier.o path.o -g -Wall -Wextra -Wvla -Werror -fsanitize=address,undefined -o pathing -lsfml-graphics -lsfml-window -lsfml-system -lm

pathing.o: pathing.cpp
	g++ -c -g pathing.cpp

display.o: Display/display.cpp
	g++ -c -g Display/display.cpp

bezier.o: Maths/bezier.cpp
	g++ -c -g Maths/bezier.cpp

path.o: Maths/path.cpp
	g++ -c -g Maths/path.cpp

clean:
	rm -f pathing && rm -f *.o && echo "Cleaned executable"
