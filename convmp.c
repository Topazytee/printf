#include "main.h"

/**
 * is_printable - Checks if a character is printable.
 * @c: Character to be checked.
 *
 * Return: 1 if the character is printable, 0 otherwise.
 */
int is_printable(char c)
{
	if (c >= 32 && c < 127)
		return (1);

	return (0);
}

/**
 * append_hexa_code - Append ascci in hexadecimal code to buffer
 * @buffer: The buffer to store the hexadecimal representation.
 * @i: Index at which to start appending.
 * @ascii_code: ASSCI CODE.
 * Return:The number of characters appended to the buffer, always 3.
 */
int append_hexa_code(char ascii_code, char buffer[], int i)
{
	char map_to[] = "0123456789ABCDEF";

	if (ascii_code < 0)
		ascii_code *= -1;

	buffer[i++] = '\\';
	buffer[i++] = 'x';

	buffer[i++] = map_to[ascii_code / 16];
	buffer[i] = map_to[ascii_code % 16];

	return (3);
}

/**
 * is_digit - Checks if a char is a digit.
 * @c: Character to be checked.
 *
 * Return: 1 if character is a digit, 0 otherwise
 */
int is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);

	return (0);
}

/**
 * convert_size_number - Casts a number to the specified size
 * @num: Number to be casted.
 * @size: Number indicating the type to be casted.
 *
 * Return: Casted value of number.
 */
long int convert_size_number(long int num, int size)
{
	if (size == 2)
		return (num);
	else if (size == 1)
		return ((short)num);
	else
		return ((int)num);
}

/**
 * convert_size_unsgnd - Casts a number to the specified size
 * @num: Number to be casted.
 * @size: Number indicating the type to be casted.
 *
 * Return: Casted value of number.
 */
long int convert_size_unsgnd(unsigned long int num, int size)
{
	if (size == 2)
		return (num);
	else if (size == 1)
		return ((unsigned short)num);
	else
		return ((unsigned int)num);
}
