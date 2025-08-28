#include "../include/Cell.hpp"

Cell::Cell(int row, int col, bool isMine) : 
    m_row(row), m_col(col), m_isMine(isMine), m_isRevealed(false), m_isFlagged(false), neighborMines(0) 
    {
        
    }

void Cell::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::RectangleShape cell;
    cell.setSize(sf::Vector2f(SIZE, SIZE)); 

    const bool isLight = ((m_row + m_col) % 2) == 0;
    cell.setFillColor(isLight ? LIGHT_BLUE : DARK_BLUE);
    
    cell.setPosition(sf::Vector2f(static_cast<float>(m_col * SIZE), static_cast<float>(m_row * SIZE)));
    target.draw(cell, states);
}