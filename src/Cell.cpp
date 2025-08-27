#include "../include/Cell.hpp"

Cell::Cell(int row, int col, bool isMine) : 
    m_row(row), m_col(col), m_isMine(isMine), m_isRevealed(false), m_isFlagged(false), neighborMines(0) 
    {
        
    }

void Cell::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::RectangleShape cell;
    cell.setSize(sf::Vector2f(SIZE, SIZE));
    cell.setFillColor(sf::Color::Blue);
    target.draw(cell, states);
}