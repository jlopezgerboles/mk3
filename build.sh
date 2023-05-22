set echo on

mkdir bin

CFiles=$(find . -type f -name "*.c")
echo "Files found to be compiled:" $CFiles

echo "Building game initialized"
assembly="game"
compilerflags="-g -fPIC"
includeflags="-Idev/mk3/src -I/Include"
linkerflags="-g -shared -lSDL2 -lSDL2_image -lSDL2_ttf -L/Lib -lX11 -L/usr/X11R6/lib -lm -ldl -lGL -no-pie"
echo "Compilation is using the Compiler flags: " $compilerflags
echo "Compilation is using the Include  flags: " $includeflags
echo "Compilation is using the Linker   flags: " $linkerflags

echo "Building $assembly..."

echo gcc $CFiles -o $assembly $compilerflags $includeflags $linkerflags
gcc $CFiles $compilerflags $includeflags $linkerflags -o $assembly
