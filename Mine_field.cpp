#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include <cassert>

#include "Mine_field.h"

void Mine_field::start(int N, int start_row, int start_col)
{
    // these checks should be caller's responsibility
    if (N >= cells_number() || !is_within_field(*this, start_row, start_col))
        throw std::runtime_error("Bad arguments for Mine_field::start()");

    generate_mines(N, start_row, start_col);
    generate_neighbor_numbers();
    try_cell(start_row, start_col);
}

bool Mine_field::try_cell(int row, int col)
{
    if (!is_within_field(*this, row, col))
        throw std::runtime_error("Bad arguments for Mine_field::start()");

    Mine_cell& mc = get_cell(row, col);

    if (mc.is_covered())
    {
        mc.uncover();
        if (mc.is_a_mine())
            return false;
        if (mc.is_empty())
            uncover_neighbours(row, col);
    }
    return true;
}

void Mine_field::uncover_neighbours(int row, int col)
{
    for (int neighbor_row = row-1; neighbor_row <= row + 1; ++neighbor_row)
        for (int neighbor_col = col-1; neighbor_col <=col + 1; ++neighbor_col)
        {
            if (is_within_field(*this, neighbor_row, neighbor_col))
            {
                Mine_cell& mc = get_cell(neighbor_row, neighbor_col);
                if (mc.is_covered())
                {
                    if (mc.is_empty())
                    {
                        mc.uncover();
                        uncover_neighbours(neighbor_row, neighbor_col);
                    }
                    else if (!mc.is_a_mine())
                        mc.uncover();
                }
            }
        }
}

void Mine_field::generate_mines(int N, int start_row, int start_col)
{
    srand(1);
    while (N > 0)
    {
        int this_row = rand() % mines.rows();
        int thic_col = rand() % mines.cols();

        Mine_cell& this_cell = mines(this_row, thic_col);

        if ((start_row == this_row && start_col == thic_col) || this_cell.is_a_mine())
            continue;
        this_cell.value = Mine_cell::MINE;
        --N;
    }
}

void Mine_field::generate_neighbor_numbers()
{
    for (int row = 0; row < mines.rows(); ++row)
        for (int col = 0; col < mines.cols(); ++col)
        {
            Mine_cell& this_cell = mines(row, col);
            if (this_cell.is_a_mine())
                continue;

            int neighbor_mines_N = 0;
            for (int dr = -1; dr <= 1; ++dr)
                for (int dc = -1; dc <=1; ++dc)
                {
                    int neighbor_row = row + dr;
                    int neighbor_col = col + dc;
                    if (is_within_field(*this, neighbor_row, neighbor_col))
                    {
                        const Mine_cell& neighbour_cell = mines(neighbor_row, neighbor_col);
                        if (neighbour_cell.is_a_mine())
                            ++neighbor_mines_N;
                    }
                }
            // This should not be possible, only assert is needed here.
            assert(neighbor_mines_N <= Mine_cell::MAX_VALUE);
            this_cell.value = neighbor_mines_N;
        }
}

bool is_within_field(const Mine_field& m, int row, int col)
{
    return (row < m.rows()) && (col < m.cols()) && (row >= 0) && (col >= 0);
}
