#include <iostream>
#include <vector>
#include <exception>
#include <stdexcept>

#include "Mine_field.h"

void drawMineField(const Mine_field& M);

const int MIN_SIDE_SIZE = 2;

int main()
try
{
    int field_rows_size = 0, field_cols_size = 0;

    do
    {
        std::cout << "\nInput field size, N of rows and N of columns, \nboth >= " << MIN_SIDE_SIZE << ": ";
        std::cin >> field_rows_size >> field_cols_size;
        if (!std::cin)
        {
            std::cin.clear();
            std::cin.ignore();
            continue;
        }
    }
    while (field_rows_size < MIN_SIDE_SIZE && field_cols_size < MIN_SIDE_SIZE);

    std::cout << "Your field has " << field_rows_size << " rows and " << field_cols_size << " columns." <<  std::endl;

    Mine_field m(field_rows_size, field_cols_size);

    int number_of_mines = 0;

    do
    {
        std::cout << "\nInput number of mines, N < " << m.cells_number() << ": ";
        std::cin >> number_of_mines;
        if (!std::cin)
        {
            std::cin.clear();
            std::cin.ignore();
            continue;
        }
    } while (number_of_mines >= m.cells_number() || number_of_mines < 1);

    std::cout << "Your number of mines is " << number_of_mines << std::endl;

    int select_row = -1, select_col = -1;

    do
    {
        std::cout << "\nInput row and column number of the cell you want to start with: ";
        std::cin >> select_row >> select_col;
        if (!std::cin)
        {
            std::cin.clear();
            std::cin.ignore();
            continue;
        }
    } while (!m.is_within_field(select_row, select_col));

    m.generate_mines(number_of_mines, select_row, select_col);
    m.generate_neighbor_numbers();

    drawMineField(m);
    return 0;
}
catch (std::exception& e)
{
    std::cerr << e.what() << std::endl;
    return 1;
}

void drawMineField(const Mine_field& M)
{
    for (int i = 0; i < M.rows(); ++i)
    {
        for (int j = 0; j < M.cols(); ++j)
        {
            std::cout << M.get_cell(i, j).value << '\t';
        }
        std::cout << std::endl;
    }

}
