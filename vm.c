#include "common.h"
#include "debug.h"
#include "vm.h"

VM vm;

void initVM()
{
}

void freeVM()
{
}

static InterpretResult run()
{
// Macros only exist within the scope of the function they are defined in.
#define READ_BYTE() \
    (*vm.ip++) // Note that the ip always points to the next instruction.
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])

    for (;;)
    {
#ifdef DEBUG_TRACE_EXECUTION
        disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
#endif

        // Dispatching on the instruction.
        // The instruction is read from the chunk and then the switch statement.
        // The switch statement then dispatches to the appropriate code.
        uint8_t instruction;
        switch (instruction = READ_BYTE())
        {
            case OP_CONSTANT:
            {
                Value constant = READ_CONSTANT();
                printValue(constant);
                printf("\n");
                break;
            }
            case OP_RETURN:
            {
                return INTERPRET_OK;
            }
        }
    }

// Undefine macros to avoid polluting the global namespace.
#undef READ_BYTE
#undef READ_CONSTANT
}

InterpretResult interpret(Chunk* chunk)
{
    vm.chunk = chunk;
    vm.ip = vm.chunk->code;
    return run();
}
