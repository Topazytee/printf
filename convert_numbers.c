#include "main.h"

unsigned int convert_di(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_b(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_u(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_o(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);

/**
 * convert_di - Converts an argument to a signed int and
 *              stores it to a buffer contained in a struct.
 * @args: Va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @wid: Width modifier.
 * @prec: Precision modifier.
 * @len: Length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int convert_di(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	long int s, copy;
	unsigned int ret = 0, count = 0;
	char pad, space = ' ', neg = '-', plus = '+';

	if (len == LONG)
		s = va_arg(args, long int);
	else
		s = va_arg(args, int);
	if (len == SHORT)
		s = (short)s;

	if (SPACE_FLAG == 1 && s >= 0)
		ret += _memcpy(output, &space, 1);

	if (prec <= 0 && NEG_FLAG == 0)
	{
		if (s == LONG_MIN)
			count += 19;
		else
		{
			for (copy = (s < 0) ? -s : s; copy > 0; copy /= 10)
				count++;
		}
		count += (s == 0) ? 1 : 0;
		count += (s < 0) ? 1 : 0;
		count += (PLUS_FLAG == 1 && s >= 0) ? 1 : 0;
		count += (SPACE_FLAG == 1 && s >= 0) ? 1 : 0;

		if (ZERO_FLAG == 1 && PLUS_FLAG == 1 && s >= 0)
			ret += _memcpy(output, &plus, 1);
		if (ZERO_FLAG == 1 && s < 0)
			ret += _memcpy(output, &neg, 1);

		pad = (ZERO_FLAG == 1) ? '0' : ' ';
		for (wid -= count; wid > 0; wid--)
			ret += _memcpy(output, &pad, 1);
	}

	if (ZERO_FLAG == 0 && s < 0)
		ret += _memcpy(output, &neg, 1);

	if (ZERO_FLAG == 0 && (PLUS_FLAG == 1 && s >= 0))
		ret += _memcpy(output, &plus, 1);

	if (!(s == 0 && prec == 0))
		ret += convert_sbase(output, d, "0123456789",
				flags, 0, prec);

	ret += print_neg_width(output, ret, flags, wid);

	return (ret);
}

/**
 * convert_b - Converts an unsigned int argument to binary
 *             and stores it to a buffer contained in a struct.
 * @args: Va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @wid: Width modifier.
 * @prec: Precision modifier.
 * @len: Length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int convert_b(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	unsigned int n;

	n = va_arg(args, unsigned int);

	(void)len;

	return (convert_ubase(output, n, "01", flags, wid, prec));
}

/**
 * convert_o - Converts an unsigned int to octal and
 *             stores it to a buffer contained in a struct.
 * @args: Va_list poinitng to the argument to be converted.
 * @flags: Flag modifiers.
 * @wid: Width modifier.
 * @prec: Precision modifier.
 * @len: Length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int convert_o(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	unsigned long int n;
	unsigned int ret = 0;
	char zero = '0';

	if (len == LONG)
		n = va_arg(args, unsigned long int);
	else
		n = va_arg(args, unsigned int);
	if (len == SHORT)
		n = (unsigned short)n;

	if (HASH_FLAG == 1 && n != 0)
		ret += _memcpy(output, &zero, 1);

	if (!(n == 0 && prec == 0))
		ret += convert_ubase(output, n, "01234567",
				flags, wid, prec);

	ret += print_neg_width(output, ret, flags, wid);

	return (ret);
}

/**
 * convert_u - Converts an unsigned int argument to decimal and
 *               stores it to a buffer contained in a struct.
 * @args: Va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @wid: Width modifier.
 * @prec: Precision modifier.
 * @len: Length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int convert_u(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	unsigned long int n;
	unsigned int ret = 0;

	if (len == LONG)
		n = va_arg(args, unsigned long int);
	else
		n = va_arg(args, unsigned int);
	if (len == SHORT)
		n = (unsigned short)n;

	if (!(n == 0 && prec == 0))
		ret += convert_ubase(output, n, "0123456789",
				flags, wid, prec);

	ret += print_neg_width(output, ret, flags, wid);

	return (ret);
}
