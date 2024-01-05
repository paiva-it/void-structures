CC=gcc
CFLAGS=-I.
DEPS = common.h list/list.h test/test.h
OBJ = main.o list/list.o test/test.o

%.o: %.c $(DEPS)
	@$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	@$(CC) -o $@ $^ $(CFLAGS)
	@make clean

clean:
	@echo "Cleaning up..."
	@rm -f *.o **/*.o
	@echo "Done."

run-tests:
	@make
	@echo "Running Tests..."
	@./main test

run:
	@make
	@echo "Running..."
	@./main