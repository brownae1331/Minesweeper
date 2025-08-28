#ifndef CELL_HPP
#define CELL_HPP

#include <SFML/Graphics.hpp>

class Cell : public sf::Drawable {
    public:
        static constexpr int SIZE = 32;
        static constexpr sf::Color LIGHT_BLUE = sf::Color(173, 216, 230);
        static constexpr sf::Color DARK_BLUE = sf::Color::Blue;
        Cell(int row, int col, bool isMine);

    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        int m_row;
        int m_col;
        bool m_isMine;
        bool m_isRevealed;
        bool m_isFlagged;
        int neighborMines;
};

#endif