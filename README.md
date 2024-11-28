# Overview

This project was started recently and is still far from complete.

This is a custom cpp library to improve my workflow on personal and professional projects.
Every hpp file can be seen as a library of its own and is designed to work as a standalone, so that you just need to import the hpp file in order to use it.
Namespace and the using keywords have been omitted to facilitate integration to projects.

Here are the different sections of the library
- Parser.hpp: A class making parsing CLI arguments more convenient.
- Printer.hpp: A more convenient way of printing than using cout as containers can be passed directly as argumentm inspired from python's print()
- Strings.hpp: String manipulation library

### Parser/Parser.hpp

- Please refer to the README.md file inside of the Parser directory to understand the parser's usage.

### Printer/Printer.hpp

  Usage: import Printer.hpp into your project and call out() or fout(), pass variables and objects as parameters to the out function.
  
  - out:
  out() takes an arbitrary amount of arguments that can be scalar types or containers, some of the less common containers have not been included, out() prints a new line after every parameter, except for c strings.
  C++ strings from std::string are displayed within double quotes which is not the case for C char* strings.
  
  - fout:
  fout() works like out(), except that calling Out::setFoutFd() will redirect its output making it easier to store text in debug log files, the method setFoutFd will not redirect the output of out(). This way fout() can be used to effortlesly output into a file while out() is being used to redirect to std out in the same program.

  These function are calling write from unistd to output data, be mindful when redirecting std out;

### Strings/Strings.hpp

- a long list of string manipulation functions
  
#
PS: Feel free to provide suggestions
