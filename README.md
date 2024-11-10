# MyCppLib

This project was started recentyl and is still far from complete.

This is a custom cpp library to improve my workflow on personal and professional projects.
Namespace and using keyword have been ommited to facilitate integration to projects.

## Features

### printer.hpp

  The main method in this class is the all method which can be called as such Printer::all() by including the printer.hpp header file, the method takes an arbitrary amount of arguments that can be all scalar types and most containers, some of the less common containers have not been included. The all method prints a new line after every parameter;
  
### utils.hpp

  TypeChecker::isContainer(), will check if the parameter given is a container or not, returning true or false.
