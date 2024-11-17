# Overview

This project was started recently and is still far from complete.

This is a custom cpp library to improve my workflow on personal and professional projects.
Namespace and using keyword have been omitted to facilitate integration to projects.

Here are the different sections of the library
- Printer.hpp: A more convenient way of printing than using cout as containers can be passed directly as argument
- Strings.hpp: String manipulation library

### Printer/Printer.hpp

  Usage: import Printer.hpp into your project and call out() or fout(), pass variables and objects as parameters to the out function.
  
  - out:
  out() takes an arbitrary amount of arguments that can be scalar types or containers, some of the less common containers have not been included, out() prints a new line after every parameter, except for c strings.
  

  - fout:
  fout() works like out(), except that calling Out::setFoutFd() will redirect its output making it easier to store text in debug log files, the method setFoutFd will not redirect the output of out, so that fout() can be used to effortlesly output into a file while out() is being used to redirect to std out in the same program.

  These function are calling write from unistd to output data, be mindful when redirecting std out;

### Strings/Strings.hpp

  
#
PS: Feel free to provide suggestions
