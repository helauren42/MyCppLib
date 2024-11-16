#include <iostream>
using namespace std;

class Rectangle {
    protected:
        int width;
        int height;
    public:
        void    display () {
            cout << this->width << " ";
            cout << this->height << endl;
        }
 };

class RectangleArea : public Rectangle {
    public:
        void    read_input() {
            std::string line;
            getline(std::cin, line);
            width = std::stoi(line);
            int next = line.find_first_of(' ');
            height = std::stoi(&line[next]);
        };
        void    display () {
            cout << this->width * this->height << endl;
        }
};

int main()
{
    /*
     * Declare a RectangleArea object
     */
    RectangleArea r_area;
    
    /*
     * Read the width and height
     */
    r_area.read_input();
    
    /*
     * Print the width and height
     */
    r_area.Rectangle::display();
    
    /*
     * Print the area
     */
    r_area.display();
    
    return 0;
}
