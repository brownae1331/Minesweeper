#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include "Cell.hpp"
#include <SFML/Graphics.hpp>

class Board : public sf::Drawable {
    public:
        Board(int rows, int cols, int mines);
        void handleClick(const sf::Vector2i& pixelPosition, bool isRightClick);
        
    private:
    void draw(sf::RenderTarget& target, sf::RenderStates states = {}) const override;
    std::vector<std::vector<Cell>> m_cells;
    int m_rows;
    int m_cols;
    int m_mines;
};

#endif