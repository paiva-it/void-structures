CC=gcc
CFLAGS=-I.
DEPS = common.h
OBJ = main.o

%.o: %.c $(DEPS)
	@$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	@$(CC) -o $@ $^ $(CFLAGS)
	@make clean

clean:
	@echo "Cleaning up..."
	@rm -f *.o **/*.o
	@echo "Done."

run:
	@make
	@echo "Running..."
	@./main