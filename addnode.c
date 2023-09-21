#include "monty.h"
/**
 * addnode - adding node to head stack
 * @head: the head of stack
 * @n: the new value
 * Return: nothing
*/
void addnode(stack_t **head, int n)
{
	stack_t *new_node, *aux;

	aux = *head;
	new_node = malloc(sizeof(stack_t));

