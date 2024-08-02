# 0x11. C - printf

#Project Instructions
Allowed editors: vi, vim, emacs
All your files will be compiled on Ubuntu 20.04 LTS using gcc, using the options -Wall -Werror -Wextra -pedantic -std=gnu89
All your files should end with a new line
A README.md file, at the root of the folder of the project is mandatory
Your code should use the Betty style. It will be checked using betty-style.pl and betty-doc.pl
You are not allowed to use global variables
No more than 5 functions per file
In the following examples, the main.c files are shown as examples. You can use them to test your functions, but you don’t have to push them to your repo (if you do we won’t take them into account). We will use our own main.c files at compilation. Our main.c files might be different from the one shown in the examples
The prototypes of all your functions should be included in your header file called main.h
Don’t forget to push your header file
All your header files should be include guarded
Note that we will not provide the _putchar function for this project

#Compilation
Your code will be compiled this way:
$ gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c
As a consequence, be careful not to push any c file containing a main function in the root directory of your project (you could have a test folder containing all your tests files including main functions)
Our main files will include your main header file (main.h): #include main.h
You might want to look at the gcc flag -Wno-format when testing with your _printf and the standard printf.

#Outline
_printf
A custom implementation of the C standard library printf function.

#Table of Contents
Build and Execute
Usage
Contributors
Acknowledgments
License

#Build and Execute
To install this project, follow these steps:

1.Clone the repository to your local machine.
2.Run the make command to compile the program.
3.Run the printf executable to use the program.

#Usage
To use this program, follow these steps:

1.Include the main.h header file in your program.
2.Call the _printf function with the desired format string and arguments.

Here's an example of how to use the _printf function:

#include “main.h”

int main(void)
{
    _printf(“Hello, %s!\n”, “world”);
    return (0);
}

This will output:

"Hello world"


#include "main.h"

int main(void)
    int a = 1, b = 2, c = a + b;
    int d = 10, e = 20, f = d - e;

    printf("%.2d + %.2d = %+.2d\n", a, b, c);
    printf("%d - %d = %+d\n", d, e, f);

    return 0;
}

To print the result of basic mathematical operations prepended by signs and 
all numbers printed with a minimum precision of two digits.


#Contributor
Anthony Igbodiegwu (@Topazytee)

#Acknowledgments
This project is built on the foundation of the C programming language and the C standard library. I would like to thank the developers of C for creating such a powerful and versatile language.

I would also like to acknowledge ALX SE for providing me this special  opportunity to work on this project and develop my skills as software engineering. Thank you for your support and guidance throughout this journey.

#License
This project is licensed under the MIT License - see the LICENSE.md file for details

