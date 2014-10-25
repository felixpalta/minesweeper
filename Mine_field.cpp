#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include <cassert>

#include <Mine_field.h>

bool operator==(const Mine_cell& left, const Mine_cell& right)
{
    return right.row == left.row && left.column == right.column;
}

bool operator!=(const Mine_cell& left, const Mine_cell& right)
{
    return !(left == right);
}

Mine_field::Mine_field(int n)
: side_sz(n)
{
    int k = 0;
    for (int i = 0; i < side_sz; ++i)
        for (int j = 0; j < side_sz; ++j)
        {
            mines.push_back(Mine_cell(i, j, Mine_cell::EMPTY));
            ++k;
        }
}

const Mine_cell& Mine_field::get_cell(int r, int c) const
{
    assert (cell_is_present_in_field(r, c));

    for (unsigned int i = 0; i < mines.size(); ++i)
    {
        if (mines[i].row == r && mines[i].column == c)
            return mines[i];
    }
    throw std::runtime_error("Tried to get impossible cell");
}

void Mine_field::generate_mines(int N, int row, int col)
{
    // these checks should be caller responsibility
    // that is why only asserts() are used
    assert(N < cell_number());
    assert (cell_is_present_in_field(row, col));

    srand(time(NULL));
    for (int i = 0; i < N; ++i)
    {
        int cell_number = rand() % mines.size();
        if (mines[cell_number].value != Mine_cell::MINE && mines[cell_number] != get_cell(row, col))
            mines[cell_number].value = Mine_cell::MINE;
        else
            --i;
    }

}

void Mine_field::generate_neighbor_numbers()
{
    for (int i = 0; i < cell_number(); ++i)
    {
        Mine_cell& this_cell = mines[i];
        if (this_cell.is_a_mine()) continue;

        int neighbor_mines_N = 0;
        for (int dr = -1; dr <= 1; ++dr)
            for (int dc = -1; dc <=1; ++dc)
            {
                int neighbor_row = this_cell.row + dr;
                int neighbor_col = this_cell.column + dc;
                if (cell_is_present_in_field(neighbor_row, neighbor_col))
                {
                    if (get_cell(neighbor_row, neighbor_col).is_a_mine())
                        ++neighbor_mines_N;
                }
            }
        assert(neighbor_mines_N <= Mine_cell::MAX_VALUE);
        this_cell.value = neighbor_mines_N;
    }
}

bool Mine_field::cell_is_present_in_field(int row, int col) const
{
    return (row >= 0 && row < side_sz && col >= 0 && col < side_size());
}
