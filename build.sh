#! /usr/bin/bash
echo "Building Files"
cmake -S. -B build/ -DCMAKE_EXPORT_COMPILE_COMMANDS=1

echo "Doing second build:"
cmake --build ./build --clean-first  --parallel #--verbose
echo "Copying Compile Commands"
cp build/compile_commands.json .