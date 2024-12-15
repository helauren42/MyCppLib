# Printer.hpp

This library holds print functions that aim to satisfy all my needs in projects, as I find more requirements in personal and group projects I will continuously add and update this library.

## Usage

  - requires c++17 or later
  - import Printer.hpp and call Out::stdOut, Out::stdErr, Out::Fout, and Out::setFoutFile. You may add "using namespace Out" for simpler usage of the library.

## Functions

### setFoutFile

Description: This function sets the output file where the Fout function will write. It allows specifying whether to truncate or append to the file.
Parameters:
file: The name of the file to open. If the file does not exist, it will be created.
trunc: A boolean flag that defines the file open mode. If true, the file will be truncated (default behavior). If false, it will append to the file.
Throws: A std::runtime_error if the file cannot be opened.

int main() {
    Out::setFoutFile("output.txt");  // Opens and truncates "output.txt"
    Out::setFoutFile("output.txt", false);  // Appends to "output.txt"
    return 0;
}

### stdOut

Description: This function prints the given arguments to the standard output (stdout). It works with scalar types, containers and custom objects if the std::ostream& operator<< overload is implemented.
Template Parameters: Variadic template to accept multiple arguments of any type.

int main() {
    std::vector<int> numbers = {1, 2, 3, 4};
    Out::stdOut("Numbers: ", numbers);  // Output to stdout: Numbers: 1 2 3 4
    return 0;
}

### stdErr

Description: This function prints the given arguments to the standard error (stderr). It works similarly to stdOut but outputs to stderr.

### Fout

Description: This function works similarly to stdOut and stdErr but outputs the given arguments to a file. The output file is defined by calling setFoutFile before using this function. It throws an error if the output file is not set.
Throws: A std::logic_error if the output file is not defined before calling this function.

int main() {
    Out::setFoutFile("log.txt");
    Out::Fout("Writing to file: ", 42);  // Output to log.txt: Writing to file: 42
    return 0;
}

## Explanation

The printing functions stdOut, stdErr, and Fout call Printer::printAll, which iterates through every argument and passes it to print(). Depending on the argument type, the appropriate print() function is invoked:

- For scalar types, like int or std::string, the corresponding print(int a) or print(std::string s) is called.
- For containers, like std::vector or std::list, printAll recursively calls print for each element, allowing nested data structures to be handled. For example, when printing a std::vector<int>, the print(int a) function is called for each element in the vector.
- For custom objects, the template version of print() is invoked, which requires the implementation of std::ostream& operator<< for that object type.
This recursive design ensures that containers, no matter how deeply nested, are printed correctly.

To see the inner workings of printAll() and print(), look into the code.
