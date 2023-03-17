#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "chunk.h"
#include "common.h"
#include "debug.h"
#include "vm.h"

static void repl()
{
    char line[1024];
    for (;;)
    {
        printf("> ");
        if (!fgets(line, sizeof(line), stdin))
        {
            printf("\n");
            break;
        }

        interpret(line);
    }
}

static void runFile(const char* path)
{
    char* source = readFile(path);
    InterpretResult result = interpret(source);
    free(source);

    if (result == INTERPRET_COMPILE_ERROR)
        exit(65);
    if (result == INTERPRET_RUNTIME_ERROR)
        exit(70);
}

static char* readFile(const char* path)
{
    FILE* file = fopen(path, "rb");

    if (file == NULL)
    {
        fprintf(stderr, "Could not open file \"%s\". \n", path);
        exit(74);
    }

    // we don't know how big the file is a priori, so we need to seek to the end
    fseek(file, 0L, SEEK_END); // seek to end of file; seek means move the
                               // pointer, 0L means the beginning of the file,
                               // SEEK_END means the end of the file
    size_t fileSize = ftell(file); // get the current position of the pointer
    rewind(file); // move the pointer back to the beginning of the file

    char* buffer = (char*)malloc(
        fileSize +
        1); // allocate memory for the file; +1 for the null terminator

    if (buffer == NULL)
    {
        fprintf(stderr, "Not enough memory to read \"%s\". \n", path);
        exit(74);
    }

    size_t bytesRead = fread(
        buffer, sizeof(char), fileSize, file); // read the file into the buffer

    if (bytesRead < fileSize)
    {
        fprintf(stderr, "Could not read file \"%s\". \n", path);
        exit(74);
    }

    buffer[bytesRead] = '\0'; // add the null terminator

    fclose(file);
    return buffer;
}

int main(int argc, char* argv[])
{
    initVM();

    if (argc == 1)
    {
        repl();
    }
    else if (argc == 2)
    {
        runFile(argv[1]);
    }
    else
    {
        fprintf(stderr, "Usage: clox [path]\n");
    }

    freeVM();
    return 0;
}
