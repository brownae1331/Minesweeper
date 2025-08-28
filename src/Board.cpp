#include "../include/Board.hpp"
#include "../include/Cell.hpp"

Board::Board(int rows, int cols, int mines) : 
    m_rows(rows), m_cols(cols), m_mines(mines)
    {
        m_cells.reserve(m_rows);
        for (int r = 0; r < m_rows; ++r) {
            std::vector<Cell> rowCells;
            rowCells.reserve(m_cols);
            for (int c = 0; c < m_cols; ++c) {
                rowCells.emplace_back(r, c, false);
            }
            m_cells.emplace_back(std::move(rowCells));
        }
    }

void Board::handleClick(const sf::Vector2i& pixelPosition, bool isRightClick)
{
    const int col = pixelPosition.x / Cell::SIZE;
    const int row = pixelPosition.y / Cell::SIZE;

    if (row < 0 || row >= m_rows || col < 0 || col >= m_cols) {
        return;
    }

    Cell& cell = m_cells[row][col];
    if (isRightClick) {
        cell.flag();
    } else {
        if (!cell.isFlagged()) {
            cell.reveal();
        }
    }
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (const auto& row : m_cells) {
        for (const auto& cell : row) {
            target.draw(cell, states);
        }
    }
}