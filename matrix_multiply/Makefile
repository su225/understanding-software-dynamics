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

	@./benchmark --block --ijk --block_size 16
	@./benchmark --block --ijk --block_size 32
	@./benchmark --block --ijk --block_size 64
	@./benchmark --block --ijk --block_size 128

	@./benchmark --block --ikj --block_size 16
	@./benchmark --block --ikj --block_size 32
	@./benchmark --block --ikj --block_size 64
	@./benchmark --block --ikj --block_size 128

	@./benchmark --block --ikj --block_size 16 --vec
	@./benchmark --block --ikj --block_size 32 --vec
	@./benchmark --block --ikj --block_size 64 --vec
	@./benchmark --block --ikj --block_size 128 --vec

clean:
	rm -rf benchmark