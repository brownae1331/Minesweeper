#include "../include/Board.hpp"
#include "../include/Cell.hpp"
#include <iostream>
#include <random>

Board::Board(int rows, int cols, int mines) : 
    m_rows(rows), m_cols(cols), m_mines(mines), is_initialized(false)
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
        if (!is_initialized){
            initializeBoard(cell);
            is_initialized = true;
        }
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

void Board::initializeBoard(Cell& startingCell) {
    std::vector<std::tuple<int, int>> mineCoordinates;
    mineCoordinates.reserve(m_mines);

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> xDist(0, m_cols-1);
    std::uniform_int_distribution<int> yDist(0, m_rows-1);

    while (mineCoordinates.size() < m_mines){
        std::tuple<int, int> mineCoord(xDist(gen), yDist(gen));

        if (std::find(mineCoordinates.begin(), mineCoordinates.end(), mineCoord) == mineCoordinates.end()){

            mineCoordinates.push_back(mineCoord);
        }
    }
    for (const auto& t : mineCoordinates){
        Cell& cell = m_cells[std::get<0>(t)][std::get<1>(t)];
        cell.setMine();
    }
}