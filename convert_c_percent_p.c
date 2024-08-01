#include "main.h"

unsigned int convert_c(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_percent(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_p(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);

/**
 * convert_c - Converts an argument to an unsigned char and
 *             stores it to a buffer contained in a struct.
 * @args: Va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @wid: Width modifier.
 * @prec: Precision modifier.
 * @len: Length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes written to the buffer.
 */
unsigned int convert_c(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	char a;
	unsigned int ret = 0;

	(void)prec;
	(void)len;

	a = va_arg(args, int);

	ret += print_width(output, ret, flags, wid);
	ret += _memcpy(output, &a, 1);
	ret += print_neg_width(output, ret, flags, wid);

	return (ret);
}

/**
 * convert_percent - Stores a percent sign to a
 *                   buffer contained in a struct.
 * @args: Va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @wid: Width modifier.
 * @prec: Precision modifier.
 * @len: Length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes written to the buffer (always 1).
 */
unsigned int convert_percent(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	char per = '%';
	unsigned int ret = 0;

	(void)args;
	(void)prec;
	(void)len;

	ret += print_width(output, ret, flags, wid);
	ret += _memcpy(output, &per, 1);
	ret += print_neg_width(output, ret, flags, wid);

	return (ret);
}

/**
 * convert_p - Converts the address of an argument to hex and
 *             stores it to a buffer contained in a struct.
 * @args: Va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @wid: Width modifier.
 * @prec: Precision modifier.
 * @len: Length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes written to the buffer.
 */
unsigned int convert_p(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	char *null = "(nil)";
	unsigned long int add;
	unsigned int ret = 0;

	(void)len;

	add = va_arg(args, unsigned long int);
	if (add == '\0')
		return (_memcpy(output, null, 5));

	flags |= 32;
	ret += convert_ubase(output, add, "0123456789abcdef",
			flags, wid, prec);
	ret += print_neg_width(output, ret, flags, wid);

	return (ret);
}
