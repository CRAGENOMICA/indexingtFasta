#indexingtFasta v0.1 (20170913) Jordi Leno-Colorado
#
#Usage: Usage: ./indexingtFasta -i file.tfa(.gz)
#
#Flags:
#      -i [tFasta file to index]
#   OPTIONAL PARAMETERS:
#      -h [help and exit]

# To compile:
make -f nbproject/Makefile-Release.mk build/Release/GNU-Linux/main.o
mkdir -p build/Release/GNU-Linux
rm -f "build/Release/GNU-Linux/main.o.d"
g++ -std=c++0x -lz   -c -O2 -MMD -MP -MF "build/Release/GNU-Linux/main.o.d" -o build/Release/GNU-Linux/main.o sources/main.cpp
/usr/bin/make -f Makefile CONF=Release

cd ./Examples

# Run examples

echo -------------------------------
echo Example 1. Index a tFasta file
echo -------------------------------
echo
echo ../bin/indexingtFasta -i example_1.tfa.gz
../bin/indexingtFasta -i example_1.tfa.gz
echo
