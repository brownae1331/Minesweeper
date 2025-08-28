#include "../include/Cell.hpp"
#include <string>
#include <SFML/Graphics.hpp>

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
        target.draw(cell, states);
        if (m_isMine){
            static sf::Texture mineTexture;
            static bool mineLoaded = false;
            if (!mineLoaded) {
                mineLoaded = mineTexture.loadFromFile("/Users/andy/Desktop/Minesweeper/assets/sprites/Mine.png");
            }
                if (mineLoaded) {
                    sf::Sprite mineSprite(mineTexture);
                    const float baseX = static_cast<float>(m_col * SIZE);
                    const float baseY = static_cast<float>(m_row * SIZE);
                    const sf::FloatRect spriteBounds = mineSprite.getLocalBounds();
                    const float scaleX = static_cast<float>(SIZE) / spriteBounds.size.x;
                    const float scaleY = static_cast<float>(SIZE) / spriteBounds.size.y;
                    const float uniformScale = (scaleX < scaleY ? scaleX : scaleY);
                    mineSprite.setScale(sf::Vector2f(uniformScale, uniformScale));
                    mineSprite.setPosition(sf::Vector2f(baseX, baseY));

                    target.draw(mineSprite, states);
                }
        }
        else {  
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
    else {
        const bool isLight = ((m_row + m_col) % 2) == 0;
        cell.setFillColor(isLight ? LIGHT_BLUE : DARK_BLUE);
        target.draw(cell, states);
    }

    if (m_isFlagged) {
        static sf::Texture flagTexture;
        static bool flagLoaded = false;
        if (!flagLoaded) {
            flagLoaded = flagTexture.loadFromFile("/Users/andy/Desktop/Minesweeper/assets/sprites/Single-Flag.png");
            if (flagLoaded) {
                flagTexture.setSmooth(true);
            }
        }

        if (flagLoaded) {
            sf::Sprite flagSprite(flagTexture);
            const float baseX = static_cast<float>(m_col * SIZE);
            const float baseY = static_cast<float>(m_row * SIZE);
            const sf::FloatRect spriteBounds = flagSprite.getLocalBounds();
            const float scaleX = static_cast<float>(SIZE) / spriteBounds.size.x;
            const float scaleY = static_cast<float>(SIZE) / spriteBounds.size.y;
            const float uniformScale = (scaleX < scaleY ? scaleX : scaleY);
            flagSprite.setScale(sf::Vector2f(uniformScale, uniformScale));
            flagSprite.setPosition(sf::Vector2f(baseX, baseY));
            target.draw(flagSprite, states);
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

void Cell::setMine()
{
    m_isMine = true;
}

int Cell::getRow() const
{
    return m_row;
}

int Cell::getCol() const
{
    return m_col;
}