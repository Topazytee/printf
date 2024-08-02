#include "main.h"
#include <unistd.h>

/**
 * print_buffer - prints the contents of the buffer.
 * @buffer: The character array to be printed.
 * @buff_ind: A pointer to the index indicating the length of the buffer.
 */

void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}
