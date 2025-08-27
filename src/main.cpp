#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

int main()
{
    RenderWindow window(VideoMode({800, 600}), "Minesweeper");

    while (window.isOpen())
    {
        while (const optional<Event> event = window.pollEvent())
        {
            if (event->is<Event::Closed>())
                window.close();
        }

        window.clear();
        window.display();
    }
}