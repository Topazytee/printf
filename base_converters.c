#include "main.h"

unsigned int convert_sbase(buffer_t *output, long int num, char *base,
		unsigned char flags, int wid, int prec);
unsigned int convert_ubase(buffer_t *output,
		unsigned long int num, char *base,
		unsigned char flags, int wid, int prec);

/**
 * convert_sbase - Converts a signed long to an inputted base and stores
 *                 the result to a buffer contained in a struct.
 * @output: A buffer_t struct containing a string.
 * @num: The signed integer to be converted.
 * @base: The base to use for conversion (e.g., "0123456789").
 * @flags: Flag modifiers.
 * @wid: Width modifier.
 * @prec: Precision modifier.
 *
 * Return: The number of bytes written to the buffer.
 */
unsigned int convert_sbase(buffer_t *output, long int num, char *base,
		unsigned char flags, int wid, int prec)
{
	int b;
	char digit, pad = '0';
	unsigned int ret = 1;

	for (b = 0; *(base + b);)
		b++;

	if (num >= b || num <= -b)
		ret += convert_sbase(output, num / b, base,
				flags, wid - 1, prec - 1);

	else
	{
		for (; prec > 1; prec--, wid--)
			ret += _memcpy(output, &pad, 1);

		if (NEG_FLAG == 0)
		{
			pad = (ZERO_FLAG == 1) ? '0' : ' ';
			for (; wid > 1; wid--)
				ret += _memcpy(output, &pad, 1);
		}
	}

	digit = base[(num < 0 ? -1 : 1) * (num % b)];
	_memcpy(output, &digit, 1);

	return (ret);
}

/**
 * convert_ubase - Converts an unsigned long to an inputted base and
 *                 stores the result to a buffer contained in a struct.
 * @output: A buffer_t struct containing a character array.
 * @num: The unsigned integer to be converted.
 * @base: The base to use for conversion (e.g., "0123456789").
 * @flags: Flag modifiers.
 * @wid: Width modifier.
 * @prec: Precision modifier.
 *
 * Return: The number of bytes written to the buffer.
 */
unsigned int convert_ubase(buffer_t *output, unsigned long int num, char *base,
		unsigned char flags, int wid, int prec)
{
	unsigned int b, ret = 1;
	char digit, pad = '0', *lead = "0x";

	for (b = 0; *(base + b);)
		b++;

	if (num >= b)
		ret += convert_ubase(output, num / b, base,
				flags, wid - 1, prec - 1);

	else
	{
		if (((flags >> 5) & 1) == 1)
		{
			wid -= 2;
			prec -= 2;
		}
		for (; prec > 1; prec--, wid--)
			ret += _memcpy(output, &pad, 1);

		if (NEG_FLAG == 0)
		{
			pad = (ZERO_FLAG == 1) ? '0' : ' ';
			for (; wid > 1; wid--)
				ret += _memcpy(output, &pad, 1);
		}
		if (((flags >> 5) & 1) == 1)
			ret += _memcpy(output, lead, 2);
	}

	digit = base[(num % b)];
	_memcpy(output, &digit, 1);

	return (ret);
}
