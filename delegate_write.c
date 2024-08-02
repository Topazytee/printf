#include "main.h"
#include <unistd.h>


/**
 * handle_write_char - Prints a string
 * @c: Char types.
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags.
 * @width: Width specifier.
 * @precision: precision specifier.
 * @size: Size specifier.
 *
 * Return: Number of characters printed.
 */
int write_char(char c, char buffer[],
	int flags, int width, int precision, int size)
{ /* char is stored at left and paddind at buffer's right */
	int g = 0;
	char padd = ' ';

	SUPPRESS(precision);
	SUPPRESS(size);

	if (flags & 4)
		padd = '0';

	buffer[g++] = c;
	buffer[g] = '\0';

	if (width > 1)
	{
		buffer[1023] = '\0';
		for (g = 0; g < width - 1; g++)
			buffer[1022 - g] = padd;

		if (flags & 1)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[1023 - g], width - 1));
		else
			return (write(1, &buffer[1023 - g], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}


/**
 * write_number - Prints a string
 * @is_negative: Lista of arguments
 * @ind: Character types.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags.
 * @width: Width specifier.
 * @precision: precision specifier.
 * @size: Size specifier.
 *
 * Return: Number of characters printed.
 */
int write_number(int is_negative, int ind, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 1023 - ind;
	char padd = ' ', extra_ch = 0;

	SUPPRESS(size);

	if ((flags & 4) && !(flags & 1))
		padd = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flags & 2)
		extra_ch = '+';
	else if (flags & 16)
		extra_ch = ' ';

	return (write_num(ind, buffer, flags, width, precision,
		length, padd, extra_ch));
}

/**
 * write_num - Write a number using a bufffer
 * @ind: Index at which the number starts on the buffer
 * @buffer: Buffer.
 * @flags: Flags.
 * @width: width specifier.
 * @prec: Precision specifier.
 * @length: Number length.
 * @padd: Pading character.
 * @extra_c: Extra character.
 *
 * Return: Number of printed characters.
 */
int write_num(int ind, char buffer[],
	int flags, int width, int prec,
	int length, char padd, char extra_c)
{
	int g, padd_start = 1;

	if (!prec && ind == 1022 && buffer[ind] == '0' && !width)
		return (0); /* printf(".0d", 0)  no character is printed */
	if (!prec && ind == 1022 && buffer[ind] == '0')
		buffer[ind] = padd = ' '; /* width is displayed with padding ' ' */
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		buffer[--ind] = '0', length++;
	if (extra_c)
		length++;
	if (width > length)
	{
		for (g = 1; g < width - length + 1; g++)
			buffer[g] = padd;
		buffer[g] = '\0';
		if (flags & 1 && padd == ' ')
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[1], g - 1));
		}
		else if (!(flags & 1) && padd == ' ')
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[1], g - 1) + write(1, &buffer[ind], length));
		}
		else if (!(flags & 1) && padd == '0')
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			return (write(1, &buffer[padd_start], g - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start)));
		}
	}
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], length));
}

/**
 * write_unsgnd - Writes an unsigned number
 * @is_negative: Number indicating if the num is negative
 * @ind: Index at which the number starts in the buffer
 * @buffer: Array of characters.
 * @flags: Flags specifiers.
 * @width: Width specifier.
 * @precision: Precision specifier.
 * @size: Size specifier.
 *
 * Return: Number of written characters.
 */
int write_unsgnd(int is_negative, int ind,
	char buffer[],
	int flags, int width, int precision, int size)
{
	/* The number is stored at the bufer's right and starts at position i */
	int length = 1023 - ind, g = 0;
	char padd = ' ';

	SUPPRESS(is_negative);
	SUPPRESS(size);

	if (precision == 0 && ind == 1022 && buffer[ind] == '0')
		return (0); /* printf(".0d", 0)  no char is printed */

	if (precision > 0 && precision < length)
		padd = ' ';

	while (precision > length)
	{
		buffer[--ind] = '0';
		length++;
	}

	if ((flags & 4) && !(flags & 1))
		padd = '0';

	if (width > length)
	{
		for (g = 0; g < width - length; g++)
			buffer[g] = padd;

		buffer[g] = '\0';

		if (flags & 1)
		{
			return (write(1, &buffer[ind], length) + write(1, &buffer[0], g));
		}
		else
		{
			return (write(1, &buffer[0], i) + write(1, &buffer[ind], length));
		}
	}

	return (write(1, &buffer[ind], length));
}

/**
 * write_pointer - Write a memory address
 * @buffer: Arrays of chars
 * @ind: Index at which the number starts in the buffer
 * @length: Length of number
 * @width: Width specifier
 * @flags: Flags specifier
 * @padd: Character representing the padding
 * @extra_c: Character representing extra char
 * @padd_start: Index at which padding should start
 *
 * Return: Number of written characters.
 */
int write_pointer(char buffer[], int ind, int length,
	int width, int flags, char padd, char extra_c, int padd_start)
{
	int g;

	if (width > length)
	{
		for (g = 3; g < width - length + 3; g++)
			buffer[g] = padd;
		buffer[g] = '\0';
		if (flags & 1 && padd == ' ')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[3], g - 3));
		}
		else if (!(flags & 1) && padd == ' ')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[3], g - 3) + write(1, &buffer[ind], length));
		}
		else if (!(flags & 1) && padd == '0')
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], g - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start) - 2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], 1023 - ind));
}
