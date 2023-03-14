CC = clang
CFLAGS = -Wall -Wextra -g

SRCDIR = .
SOURCES = $(wildcard $(SRCDIR)/*.c) $(wildcard $(SRCDIR)/**/*.c)
OBJECTS = $(SOURCES:.c=.o)

clox: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f clox $(OBJECTS)
	if [ -d clox.dSYM ]; then \
		rm -rf clox.dSYM; \
	fi

format:
	find . -name "*.c" -exec clang-format -style=file -i {} \;
	find . -name "*.h" -exec clang-format -style=file -i {} \;
