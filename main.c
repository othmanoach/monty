#include "monty.h"
bus_t bus = {NULL, NULL, NULL, 0};

/**
 * main - the monty code interpreter
 * @argc: the number of arguments
 * @argv: the monty file location
 * Return: return 0 on success
 */
int main(int argc, char *argv[])
{
    char *content;
    FILE *file;
    size_t size = 0;
    ssize_t read_line = 1;
    stack_t *stack = NULL;
    unsigned int counter = 0;

    if (argc != 2)
    {
        fprintf(stderr, "USAGE: monty file\n");
        exit(EXIT_FAILURE);
    }
    file = fopen(argv[1], "r");
    bus.file = file;
    if (!file)
    {
        fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    while (read_line > 0)
    {
        content = NULL;
        read_line = getline(&content, &size, file);
        bus.content = content;
        counter++;
        if (read_line > 0)
        {
            execute(content, &stack, counter, file);
        }
        free(content);
    }
    free_stack(stack);
    fclose(file);
    return (0);
}

/**
 * execute - execute Monty opcodes
 * @content: the opcode and its arguments
 * @stack: pointer to the stack
 * @line_number: current line number
 * @file: file pointer
 */
void execute(char *content, stack_t **stack, unsigned int line_number, FILE *file)
{
    char *opcode, *arg;
    int num;

    (void)file; 

    opcode = strtok(content, " \t\n");
    if (!opcode || opcode[0] == '#')
        return; 

    if (strcmp(opcode, "push") == 0)
    {
        arg = strtok(NULL, " \t\n");
        if (!arg)
        {
            fprintf(stderr, "L%d: usage: push integer\n", line_number);
            exit(EXIT_FAILURE);
        }
        num = atoi(arg);
        push(stack, num);
    }
    else if (strcmp(opcode, "pall") == 0)
    {
        pall(*stack);
    }
}

/**
 * push - push an element onto the stack
 * @stack: pointer to the stack
 * @num: integer to push onto the stack
 */
void push(stack_t **stack, int num)
{
    stack_t *new_node = malloc(sizeof(stack_t));
    if (!new_node)
    {
        fprintf(stderr, "Error: malloc failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->n = num;
    new_node->next = *stack;
    new_node->prev = NULL;
    if (*stack)
    {
        (*stack)->prev = new_node;
    }
    *stack = new_node;
}

/**
 * pall - print all elements in the stack
 * @stack: pointer to the stack
 */
void pall(stack_t *stack)
{
    while (stack)
    {
        printf("%d\n", stack->n);
        stack = stack->next;
    }
}
