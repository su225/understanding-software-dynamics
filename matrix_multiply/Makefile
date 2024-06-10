build:
	clang -Iinclude/ -O3 -o benchmark main.c src/*.c -lm

run-all:
	@./benchmark --simple-ijk
	@./benchmark --simple-ikj
	@./benchmark --simple-jik
	@./benchmark --simple-jki
	@./benchmark --simple-kij
	@./benchmark --simple-kji

clean:
	rm -rf benchmark