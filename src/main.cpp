#include <SFML/Graphics.hpp>
#include "../include/Board.hpp"

using namespace sf;
using namespace std;

int main()
{
    RenderWindow window(VideoMode({320, 320}), "Minesweeper");

    Board board(10, 10, 0);

    while (window.isOpen())
    {
        while (const optional<Event> event = window.pollEvent())
        {
            if (event->is<Event::Closed>())
                window.close();
            else if (event->is<Event::MouseButtonPressed>())
            {
                if (const auto* mouseEvent = event->getIf<Event::MouseButtonPressed>())
                {
                    const bool isRightClick = mouseEvent->button == Mouse::Button::Right;
                    const Vector2i mousePos = mouseEvent->position;
                    board.handleClick(mousePos, isRightClick);
                }
            }
        }

        window.clear();
        window.draw(board);
        window.display();
    }
}