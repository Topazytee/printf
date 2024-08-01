#include "main.h"

unsigned char handle_flags(const char *flag, char *index);
unsigned char handle_length(const char *modifier, char *index);
int handle_width(va_list args, const char *modifier, char *index);
int handle_precision(va_list args, const char *modifier, char *index);
unsigned int (*handle_specifiers(const char *specifier))(va_list, buffer_t *,
		unsigned char, int, int, unsigned char);

/**
 * handle_flags - Matches flags with corresponding values.
 * @flag: Pointer to the potential string of flags.
 * @index: Index into the original format string.
 *
 * Return: If flag characters are matched - a corresponding value.
 *         Or 0 if no flags found.
 */

unsigned char handle_flags(const char *flag, char *index)
{
	int x, g;
	unsigned char ret = 0;
	flag_t flags[] = {
		{'+', PLUS},
		{' ', SPACE},
		{'#', HASH},
		{'0', ZERO},
		{'-', NEG},
		{0, 0}
	};

	for (x = 0; flag[x]; x++)
	{
		for (g = 0; flags[g].flag != 0; g++)
		{
			if (flag[x] == flags[g].flag)
			{
				(*index)++;
				if (ret == 0)
					ret = flags[g].value;
				else
					ret |= flags[g].value;
				break;
			}
		}
		if (flags[g].value == 0)
			break;
	}

	return (ret);
}

/**
 * handle_length - Matches length modifiers with their corresponding string.
 * @modifier: Pointer to the potential length modifier.
 * @index: Index into the original format string.
 *
 * Return: If a lenth modifier is matched - its corresponding value.
 *         Or 0 if no modifier found.
 */
unsigned char handle_length(const char *modifier, char *index)
{
	if (*modifier == 'h')
	{
		(*index)++;
		return (SHORT);
	}

	else if (*modifier == 'l')
	{
		(*index)++;
		return (LONG);
	}

	return (0);
}

/**
 * handle_width - Matches a width modifier with its corresponding value.
 * @args: Va_list of arguments.
 * @modifier: Pointer to the potential width modifier.
 * @index: Index into the original format string.
 *
 * Return: Width value.
 *         Or 0 if no width specified.
 */
int handle_width(va_list args, const char *modifier, char *index)
{
	int value = 0;

	while ((*modifier >= '0' && *modifier <= '9') || (*modifier == '*'))
	{
		(*index)++;

		if (*modifier == '*')
		{
			value = va_arg(args, int);
			if (value <= 0)
				return (0);
			return (value);
		}

		value *= 10;
		value += (*modifier - '0');
		modifier++;
	}

	return (value);
}

/**
 * handle_precision - Matches a precision modifier with
 *                    its corresponding value.
 * @args: A va_list of arguments.
 * @modifier: A pointer to a potential precision modifier.
 * @index: An index counter for the original format string.
 *
 * Return: If a precision modifier is matched - its value.
 *         If the precision modifier is empty, zero, or negative - 0.
 *         Otherwise - -1.
 */
int handle_precision(va_list args, const char *modifier, char *index)
{
	int value = 0;

	if (*modifier != '.')
		return (-1);

	modifier++;
	(*index)++;

	if ((*modifier <= '0' || *modifier > '9') &&
	     *modifier != '*')
	{
		if (*modifier == '0')
			(*index)++;
		return (0);
	}

	while ((*modifier >= '0' && *modifier <= '9') ||
	       (*modifier == '*'))
	{
		(*index)++;

		if (*modifier == '*')
		{
			value = va_arg(args, int);
			if (value <= 0)
				return (0);
			return (value);
		}

		value *= 10;
		value += (*modifier - '0');
		modifier++;
	}

	return (value);
}

/**
 * handle_specifiers - Matches a conversion specifier with
 *                     a corresponding conversion function.
 * @specifier: Pointer to the potential conversion specifier.
 *
 * Return: If a conversion function is matched - a pointer to the function.
 *         Otherwise - NULL.
 */
unsigned int (*handle_specifiers(const char *specifier))(va_list, buffer_t *,
		unsigned char, int, int, unsigned char)
{
	int a;
	converter_t converters[] = {
		{'c', convert_c},
		{'s', convert_s},
		{'d', convert_di},
		{'i', convert_di},
		{'%', convert_percent},
		{'b', convert_b},
		{'u', convert_u},
		{'o', convert_o},
		{'x', convert_x},
		{'X', convert_X},
		{'S', convert_S},
		{'p', convert_p},
		{'r', convert_r},
		{'R', convert_R},
		{0, NULL}
	};

	for (a = 0; converters[a].func; a++)
	{
		if (converters[a].specifier == *specifier)
			return (converters[a].func);
	}

	return (NULL);
}
