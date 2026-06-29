CXX = g++

STD = -std=c++20

SFML_INCLUDE = -I"C:/SFML_Built/include" -I.
SFML_LIB = -L"C:/SFML_Built/lib"
SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

CPP_FILES = main.cpp grilla.cpp celda.cpp defaultcelda.cpp celdaterrestre.cpp sismov.cpp personaje.cpp render_interfaz_mapa.cpp managerpersonaje.cpp menu.cpp juego.cpp cursor.cpp partida.cpp proc_input.cpp ataque.cpp adminarchivo.cpp texmanager.cpp animacion.cpp combate.cpp ia.cpp utilidades.cpp adminclase.cpp claseTrabajo.cpp managerjuego.cpp adminmusica.cpp

DEBUG_FILE = game_debug.exe
RELEASE_FILE = game_release.exe

DEBUG_FLAGS = -g -O0 -DDEBUG
RELEASE_FLAGS = -O3 -DNDEBUG -static

all: $(DEBUG_FILE) $(RELEASE_FILE)

$(DEBUG_FILE): $(CPP_FILES)
	$(CXX) $(STD) $(DEBUG_FLAGS) $(CPP_FILES) $(SFML_INCLUDE) $(SFML_LIB) $(SFML_FLAGS) -o $(DEBUG_FILE)

$(RELEASE_FILE): $(CPP_FILES)
	$(CXX) $(STD) $(RELEASE_FLAGS) $(CPP_FILES) $(SFML_INCLUDE) $(SFML_LIB) $(SFML_FLAGS) -o $(RELEASE_FILE)

clean:
	del $(DEBUG_EXE) $(RELEASE_EXE)

.PHONY: all clean
