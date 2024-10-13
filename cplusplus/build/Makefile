default:
	g++ ../src/*.cpp -I ../include/ -o brainduck_cpp

test:
	g++ ../src/*.cpp -I ../include/
	.\a.exe ../brainfuck/codes/test.bf
	echo
	.\output.exe
	echo
	rm .\a.exe
	mv output.c output.exe ../brainfuck/out

release:
	g++ ../src/*.cpp -I ../include/ -o brainduck_cpp -O3 -static -static-libgcc -static-libstdc++
	mv brainduck_cpp.exe ..
