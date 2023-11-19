#include "main.h"

/**
 * print_error - Prints an error message
 * @err: Error message to be printed on the Standard error stream
 *
 * Return: Nothing
 */
void print_error(const char *err)
{
	perror(err);
	exit(EXIT_FAILURE);
}
