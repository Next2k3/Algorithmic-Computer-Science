# Kompilator
CXX = g++

# Flagi kompilatora
CXXFLAGS = -std=c++17 -Wall -O2

# Pliki źródłowe i ścieżki
SRC = source/main.cpp
OUT_DIR = bin
OUT = $(OUT_DIR)/program

# Domyślna reguła
all: $(OUT)

# Tworzenie katalogu bin i kompilacja
$(OUT): $(SRC)
	mkdir -p $(OUT_DIR)
	$(CXX) $(CXXFLAGS) -o $(OUT) $(SRC)

# Czyszczenie
clean:
	rm -f $(OUT)

