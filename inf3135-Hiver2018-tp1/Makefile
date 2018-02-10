.PHONY: all tests clean

all: bin/generator bin/pandemic

bin/generator: src/generator.c
	mkdir -p bin
	gcc -std=c11 -o bin/generator src/generator.c

bin/pandemic: src/pandemi.c
	mkdir -p bin
	gcc -std=c11 -o bin/pandemic src/pandemi.c
        
check:
	./tests.sh

clean:
	rm -rf bin/
	rm -rf tests_out/
