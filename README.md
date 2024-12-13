# Overview

This project was started recently and is still in development.

This is a custom cpp library to improve my workflow on personal and professional projects.

Every hpp file can be seen as a library of its own and is designed to work as a standalone, so that you just need to import the hpp file in order to use it.
Using keyword has been omitted in the construction of these libraries to facilitate the integration into your projects.
Methods intended for use are declared as static and within a namespace to simplify their usage, while auxiliary methods and attributes are kept private or placed in unnamed namespace to restrict their scope.

### Printer/Printer.hpp

  Three print functions to output to stdout, stderr or to a file, inspired from the python print function. Scalar types and standard containers can be passed as argument directly and will be printed like in python, for custom objects, the print functions can output their values if the appropriate std::ostream& operator<< overload is provided.

 - Usage: import Printer.hpp into your project and call stdOut(), stdCerr() or fout(). Call setFoutFile(), pass desired output file and set option to truncate as argument .

### Logger

The latest addition !

Uses the print function from Printer.hpp to output elements into a file!
Call debug(), info(), warning(), error(), fatal() depending on the log level you need.
Call setLoggerFile() set define your log output file.

### Parser

- Convenient POSIX cmd line parser.
- Includes: options, positional arguments, setting default values and conversion of arguments to their desired data types.

### Strings/Strings.hpp

- some string manipulation functions
  
#
PS: Feel free to provide suggestions
