default:
	g++ ../src/*.cpp -I ../include/ -o brainduck_cpp

test:
	@g++ ../src/*.cpp -I ../include/
	@.\a.exe ../../brainfuck/neo.bf
	@rm .\a.exe .\output.c .\output.exe

release:
	g++ ../src/*.cpp -I ../include/ -o brainduck_cpp -O3 -static -static-libgcc -static-libstdc++
	mv brainduck_cpp.exe ..
