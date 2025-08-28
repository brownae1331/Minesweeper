#include <SFML/Graphics.hpp>
#include "../include/Board.hpp"

using namespace sf;
using namespace std;

int main()
{
    Board board(16, 30, 99);
    int rows = board.getRows();
    int cols = board.getCols();
    unsigned int windowWidth = cols * Cell::SIZE;
    unsigned int windowHeight = rows * Cell::SIZE;
    
    RenderWindow window(VideoMode({windowWidth, windowHeight}), "Minesweeper");

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