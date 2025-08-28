#include "../include/Cell.hpp"
#include <string>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

Cell::Cell(int row, int col, bool isMine) : 
    m_row(row), m_col(col), m_isMine(isMine), m_isRevealed(false), m_isFlagged(false), neighborMines(0) 
    {
        
    }

void Cell::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::RectangleShape cell;
    cell.setSize(sf::Vector2f(SIZE, SIZE)); 
    cell.setPosition(sf::Vector2f(static_cast<float>(m_col * SIZE), static_cast<float>(m_row * SIZE)));

    if (m_isRevealed) {
        cell.setFillColor(LIGHT_GREY);
    } else {
        const bool isLight = ((m_row + m_col) % 2) == 0;
        cell.setFillColor(isLight ? LIGHT_BLUE : DARK_BLUE);
    }

    target.draw(cell, states);

    if (m_isRevealed) {
        static sf::Font font;
        static bool fontLoaded = false;
        if (!fontLoaded) {
            fontLoaded = font.openFromFile("/Library/Fonts/Arial.ttf");
            if (!fontLoaded) {
                fontLoaded = font.openFromFile("/System/Library/Fonts/Supplemental/Arial.ttf");
            }
        }
        
        if (fontLoaded) {
            sf::Text text(font);
            text.setString(std::to_string(neighborMines));
            text.setCharacterSize(18);
            text.setFillColor(sf::Color::White);
            
            const float baseX = static_cast<float>(m_col * SIZE);
            const float baseY = static_cast<float>(m_row * SIZE);
            const sf::FloatRect bounds = text.getLocalBounds();
            const float posX = baseX + (SIZE - bounds.size.x) * 0.5f - bounds.position.x;
            const float posY = baseY + (SIZE - bounds.size.y) * 0.5f - bounds.position.y;
            text.setPosition(sf::Vector2f(posX, posY));
            
            target.draw(text);
        }
    }
}

void Cell::reveal()
{
    m_isRevealed = true;
}

void Cell::flag()
{
    if (m_isFlagged) {
        m_isFlagged = false;
    } else {
        m_isFlagged = true;
    }
}

bool Cell::isFlagged() const
{
    return m_isFlagged;
}