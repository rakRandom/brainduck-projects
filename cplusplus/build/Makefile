default:
	g++ ../src/*.cpp -I ../include/ -o brainduck_cpp

test:
	@g++ ../src/*.cpp -I ../include/
	@.\a.exe -f ../../brainfuck/neo.bf -o neo
	@rm .\a.exe .\neo.c .\neo.exe

release:
	g++ ../src/*.cpp -I ../include/ -o brainduck_cpp -O3 -static -static-libgcc -static-libstdc++
	mv brainduck_cpp.exe ..
