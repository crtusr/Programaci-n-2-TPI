game: main.cpp
	g++ main.cpp grilla.cpp celda.cpp defaultcelda.cpp -std=c++17 -I"C:/SFML_Built/include" -L"C:/SFML_Built/lib" -lsfml-graphics -lsfml-window -lsfml-system -o game.exe -I.
