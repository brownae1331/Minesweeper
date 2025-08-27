#include <SFML/Graphics.hpp>
#include "../include/Cell.hpp"

using namespace sf;
using namespace std;

int main()
{
    RenderWindow window(VideoMode({800, 600}), "Minesweeper");

    Cell cell(0, 0, false);

    while (window.isOpen())
    {
        while (const optional<Event> event = window.pollEvent())
        {
            if (event->is<Event::Closed>())
                window.close();
        }

        window.clear();
        window.draw(cell);
        window.display();
    }
}