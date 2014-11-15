#include <iostream>
#include <vector>
#include <exception>
#include <stdexcept>
#include <limits>
#include "Mine_field.h"
#include "input_loop.h"

void drawMineField(const Mine_field& M);

constexpr int MIN_SIDE_SIZE = 2;

int main()
try
{
    using namespace std;

    int field_rows_size = 0, field_cols_size = 0;
    input_loop<int, int>(
                cin,
                "\nInput field size, N of rows and N of columns, \nboth >= " + to_string(MIN_SIDE_SIZE) +  ": ",
                cout,
                [](int x) {return x >= MIN_SIDE_SIZE;},
                [](int x) {return x >= MIN_SIDE_SIZE;},
                field_rows_size,
                field_cols_size
               );

    cout << "Your field has " << field_rows_size << " rows and " << field_cols_size << " columns." <<  endl;

    Mine_field m(field_rows_size, field_cols_size);

    int number_of_mines = 0;
    number_of_mines = input_loop<int>(
                        cin,
                        "\nInput number of mines, N < " + to_string(m.cells_number()) + ": ",
                        cout,
                        [&m](int x) {return (x < m.cells_number()) && (x > 1);}
                        );

    cout << "Your number of mines is " << number_of_mines << endl;

    int select_row = -1, select_col = -1;
    new_input_loop<int, int>(
                cin,
                "\nInput row and column number of the cell you want to start with: ",
                cout,
                [&m](int r, int c) {return is_within_field(m, r, c);},
                select_row,
                select_col
                );


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
