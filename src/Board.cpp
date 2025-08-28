#include "../include/Board.hpp"
#include "../include/Cell.hpp"
#include <algorithm>
#include <random>
#include <queue>

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
        return;
    }

    if (cell.isFlagged()) {
        return;
    }

    if (!m_isInitialized) {
        initializeBoard(cell);
    }

    if (cell.isMine()) {
        cell.reveal();
        return;
    }

    if (cell.getNeighborMines() == 0) {
        floodRevealFrom(row, col);
    } else {
        cell.reveal();
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
    }

    for (int r = 0; r < m_rows; ++r) {
        for (int c = 0; c < m_cols; ++c) {
            if (m_cells[r][c].isMine()) {
                continue;
            }

            int count = 0;
            for (int dr = -1; dr <= 1; ++dr) {
                for (int dc = -1; dc <= 1; ++dc) {
                    if (dr == 0 && dc == 0) {
                        continue;
                    }
                    const int nr = r + dr;
                    const int nc = c + dc;
                    if (nr < 0 || nr >= m_rows || nc < 0 || nc >= m_cols) {
                        continue;
                    }
                    if (m_cells[nr][nc].isMine()) {
                        ++count;
                    }
                }
            }
            m_cells[r][c].setNeighborMines(count);
        }
    }
}

void Board::floodRevealFrom(int startRow, int startCol) {
    if (startRow < 0 || startRow >= m_rows || startCol < 0 || startCol >= m_cols) {
        return;
    }

    std::queue<std::pair<int, int>> toVisit;
    toVisit.emplace(startRow, startCol);

    while (!toVisit.empty()) {
        const auto [row, col] = toVisit.front();
        toVisit.pop();

        Cell& current = m_cells[row][col];

        if (current.isRevealed() || current.isFlagged()) {
            continue;
        }

        current.reveal();

        if (current.isMine()) {
            continue;
        }

        if (current.getNeighborMines() == 0) {
            for (int dr = -1; dr <= 1; ++dr) {
                for (int dc = -1; dc <= 1; ++dc) {
                    if (dr == 0 && dc == 0) {
                        continue;
                    }
                    const int nr = row + dr;
                    const int nc = col + dc;
                    if (nr < 0 || nr >= m_rows || nc < 0 || nc >= m_cols) {
                        continue;
                    }
                    if (!m_cells[nr][nc].isRevealed() && !m_cells[nr][nc].isFlagged()) {
                        toVisit.emplace(nr, nc);
                    }
                }
            }
        }
    }
}