#ifndef CELL_HPP
#define CELL_HPP

#include <SFML/Graphics.hpp>

class Cell : public sf::Drawable {
    public:
        static constexpr int SIZE = 32;
        static constexpr sf::Color LIGHT_BLUE = sf::Color(65, 105, 225);
        static constexpr sf::Color DARK_BLUE = sf::Color(15, 82, 186);
        static constexpr sf::Color LIGHT_GREY = sf::Color(211, 211, 211);
        Cell(int row, int col, bool isMine);
        void reveal();
        void flag();
        bool isFlagged() const;

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