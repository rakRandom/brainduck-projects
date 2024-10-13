default:
	g++ ../src/*.cpp -I ../include/ -o brainduck_cpp

test:
	@g++ ../src/*.cpp -I ../include/
	@.\a.exe -i -f ../brainfuck/codes/test.bf
	@rm .\a.exe

release:
	g++ ../src/*.cpp -I ../include/ -o brainduck_cpp -O3 -static -static-libgcc -static-libstdc++
	mv brainduck_cpp.exe ..
