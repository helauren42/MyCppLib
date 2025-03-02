# Explanation

Works the same as Printer except that WPrinter can also handle printing wide characters like wchar_t and wstring. WPrinter unlike Printer does not store data inside of a buffer before printing, every argument passed to WPrinter's print methods will be printed one after the other.

# Usage

  - include locale library #include <clocale>
  - add the following line of code setlocale(LC_ALL, "");
  - requires c++17 or later
  - import WPrinter.hpp and call WPrinter::stdOut, WPrinter::stdErr, WPrinter::Fout, and WPrinter::setFoutFile. You may use "using namespace WPrinter".
