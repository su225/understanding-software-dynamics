build:
	clang -Iinclude/ -O3 -o benchmark main.c src/*.c -lm -framework CoreServices

run-all:
	# @./benchmark --simple-ijk
	@./benchmark --simple-ikj
	@./benchmark --vec-ikj
	# @./benchmark --simple-jik
	# @./benchmark --simple-jki
	@./benchmark --simple-kij
	@./benchmark --vec-kij
	# @./benchmark --simple-kji

clean:
	rm -rf benchmark