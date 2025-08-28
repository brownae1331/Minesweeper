#include "../include/Board.hpp"
#include "../include/Cell.hpp"
#include <iostream>
#include <algorithm>
#include <random>

Board::Board(int rows, int cols, int mines) : 
    m_rows(rows), m_cols(cols), m_mines(mines), m_isInitialized(false)
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
            if (!m_isInitialized) {
                initializeBoard(cell);
            }
            cell.reveal();
        }
    }
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
    for (const auto& row : m_cells) {
        for (const auto& cell : row) {
            target.draw(cell, states);
        }
    }
}

void Board::initializeBoard(Cell& initialCell) {
    m_isInitialized = true;

    const int totalCells = m_rows * m_cols;
    const int targetMines = std::min(m_mines, totalCells - 1);
    const int initRow = initialCell.getRow();
    const int initCol = initialCell.getCol();

    std::vector<int> indices;
    indices.reserve(totalCells);
    for (int r = 0; r < m_rows; ++r) {
        for (int c = 0; c < m_cols; ++c) {
            indices.push_back(r * m_cols + c);
        }
    }

    const int initialIndex = initRow * m_cols + initCol;
    indices.erase(std::remove(indices.begin(), indices.end(), initialIndex), indices.end());

    std::mt19937 rng(std::random_device{}());
    std::shuffle(indices.begin(), indices.end(), rng);

    for (int i = 0; i < targetMines; ++i) {
        int idx = indices[i];
        int row = idx / m_cols;
        int col = idx % m_cols;
        m_cells[row][col].setMine();
        std::cout << "Mine set at: " << row << ", " << col << std::endl;
    }
}