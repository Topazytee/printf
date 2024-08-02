#include "main.h"

/**
 * _printf - Printf function.
 * @format: Format.
 * Return: Printed characters.
 */
int _printf(const char *format, ...)
{
	int g, printed = 0, printed_chars = 0;
	int flags, width, precision, size, buff_ind = 0;
	va_list args;
	char buffer[1024];

	if (!format)
		return (-1);

	va_start(args, format);

	for (g = 0; format && format[g]; g++)
	{
		if (format[g] != '%')
		{
			buffer[buff_ind++] = format[g];
			if (buff_ind == 1024)
				print_buffer(buffer, &buff_ind);
			printed_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			flags = get_flags(format, &g);
			width = get_width(format, &g, args);
			precision = get_precision(format, &g, args);
			size = get_size(format, &g);
			++g;
			printed = delegate_print(format, &g, args, buffer,
				flags, width, precision, size);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
	}

	print_buffer(buffer, &buff_ind);

	va_end(args);

	return (printed_chars);
}
