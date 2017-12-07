all: main.c
	gcc main.c

run: all
	@echo Running tests
	@echo -------------
	./a.out -c 60
	./a.out -v
	./a.out -c 100
	./a.out -v
	./a.out -r

clean:
	rm a.out
