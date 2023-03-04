CC = clang
CFLAGS = -g

clox: main.c debug.c value.c chunk.c memory.c
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

clean:
	rm -f clox
	if [ -d clox.dSYM ]; then \
		rm -rf clox.dSYM; \
	fi

format:
	find . -name "*.c" -o -name "*.h" -exec clang-format -style=file -i {} \;

