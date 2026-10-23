# 1. Radikal alles Alte löschen
rm -rf build
mkdir build
cd build

# 2. CMake mit dem korrekten ARM-Cross-Compiler initialisieren
cmake ..

# 3. Den Build starten und die Ausgabe erzwingen
cmake --build .
