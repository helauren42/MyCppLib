#include <iostream>

struct Multiplier {
    int factor;
    int factor2;

    int operator()(int value) const {
        return factor2 * value;
    }
};

int main() {
    Multiplier multiply_by_2 = {2, 3};
    std::cout << "5 * 2 = " << multiply_by_2(5) << "\n";
    return 0;
}
