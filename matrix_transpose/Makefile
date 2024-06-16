compile-all: compile-O0 compile-O1 compile-O2 compile-O3

compile-O0:
	clang -o benchmark-O0.S main.c -S -O0 -Wall -Wextra -Werror -Wpedantic
	clang -o benchmark-O0 main.c -O0 -Wall -Wextra -Werror -Wpedantic

compile-O1:
	clang -o benchmark-O1.S main.c -S -O1 -Wall -Wextra -Werror -Wpedantic
	clang -o benchmark-O1 main.c -O1 -Wall -Wextra -Werror -Wpedantic

compile-O2:
	clang -o benchmark-O2.S main.c -S -O2 -Wall -Wextra -Werror -Wpedantic
	clang -o benchmark-O2 main.c -O2 -Wall -Wextra -Werror -Wpedantic

compile-O3:
	clang -o benchmark-O3.S main.c -S -O3 -Wall -Wextra -Werror -Wpedantic
	clang -o benchmark-O3 main.c -O3 -S -Wall -Wextra -Werror -Wpedantic
