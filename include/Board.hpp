#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include "Cell.hpp"
#include <SFML/Graphics.hpp>

class Board {
    public:
        Board(int rows, int cols, int mines);
        void draw(sf::RenderTarget& target) const;
};

#endif