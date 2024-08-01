#include "main.h"

unsigned int convert_x(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_X(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);

/**
 * convert_x - Converts an unsigned int argument to hex using abcdef
 *             and stores it to a buffer contained in a struct.
 * @args: Va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @wid: Width modifier.
 * @prec: Precision modifier.
 * @len: Length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes written to the buffer.
 */
unsigned int convert_x(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	unsigned long int n;
	unsigned int ret = 0;
	char *lead = "0x";

	if (len == LONG)
		n = va_arg(args, unsigned long int);
	else
		n = va_arg(args, unsigned int);
	if (len == SHORT)
		n = (unsigned short)n;

	if (HASH_FLAG == 1 && n != 0)
		ret += _memcpy(output, lead, 2);

	if (!(n == 0 && prec == 0))
		ret += convert_ubase(output, n, "0123456789abcdef",
				flags, wid, prec);

	ret += print_neg_width(output, ret, flags, wid);

	return (ret);
}

/**
 * convert_X - Converts an unsigned int argument to hex using ABCDEF
 *             and stores it to a buffer contained in a struct.
 * @args: Va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @wid: Width modifier.
 * @prec: Precision modifier.
 * @len: Length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes written to the buffer.
 */
unsigned int convert_X(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	unsigned long int n;
	unsigned int ret = 0;
	char *lead = "0X";

	if (len == LONG)
		n = va_arg(args, unsigned long);
	else
		n = va_arg(args, unsigned int);
	if (len == SHORT)
		n = (unsigned short)n;

	if (HASH_FLAG == 1 && n != 0)
		ret += _memcpy(output, lead, 2);

	if (!(n == 0 && prec == 0))
		ret += convert_ubase(output, n, "0123456789ABCDEF",
				flags, wid, prec);

	ret += print_neg_width(output, ret, flags, wid);

	return (ret);
}
