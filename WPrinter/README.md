# Explanation

Works the same as Printer except that WPrinter can also handle printing wide characters like wchar_t and wstring. Using std::cout and std::wcout in the same project may cause issues, so if you to print wide characteres in your project, you may want to only use WPrinter and not Printer. WPrinter can handle non wide characters.

# Usage

  - include locale library #include <clocale>
  - add the following line of code setlocale(LC_ALL, "");
  - requires c++17 or later
  - import WPrinter.hpp and call WPrinter::stdOut, WPrinter::stdErr, WPrinter::Fout, and WPrinter::setFoutFile. You may use "using namespace WPrinter".
