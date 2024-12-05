#include "Pieces.hpp"
#include "../Printer.hpp"
#include <iostream>
#include <memory>

int main(void) {
	std::unique_ptr<Pieces> piece = std::make_unique<Pawn>(6, 7);
	setFoutFd("example.txt");
	fout(piece);
}