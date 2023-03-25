CC = clang
CFLAGS = -Iinclude -Wall -Wextra -Wconversion -Wshadow -std=c11 -g

SRCDIR = src
BINDIR = bin
OBJDIR = obj

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

TARGET = $(BINDIR)/clox

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: format
format:
	clang-format -i -style=file $(SOURCES) $(HEADERS)


.PHONY: clean
clean:
	rm -rf $(OBJDIR) $(TARGET)
