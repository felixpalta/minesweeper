#include <iostream>
#include <vector>
#include <exception>
#include <stdexcept>
#include <limits>
#include "Mine_field.h"
#include "input_loop.h"

void drawMineField(const Mine_field& M, bool naked);

const int MIN_SIDE_SIZE = 2;
const int MIN_MINES = 2;

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
                        [&m](int x) {return (x < m.cells_number()) && (x >= MIN_MINES);}
                        );

    cout << "Your number of mines is " << number_of_mines << endl;

    int select_row = -1, select_col = -1;
    input_loop<int, int>(
                cin,
                "\nInput row and column number of the cell you want to start with: ",
                cout,
                [&m](int r, int c) {return is_within_field(m, r, c);},
                select_row,
                select_col
                );


    m.start(number_of_mines, select_row, select_col);

    while (true)
    {
        drawMineField(m, false);
        input_loop<int, int>(
                    cin,
                    "\nInput row and column number of the cell you want to open: ",
                    cout,
                    [&m](int r, int c) {return is_within_field(m, r, c);},
                    select_row,
                    select_col
                    );
        // if uncovered a mine
        if (m.try_cell(select_row, select_col) == false)
            break;
    }
    drawMineField(m, true);
    cout << "Game over!" << endl;
    return 0;
}
catch (std::exception& e)
{
    std::cerr << e.what() << std::endl;
    return 1;
}

void drawMineField(const Mine_field& M, bool naked)
{
    const char cover = '#';
    const char mine = '@';

    for (int i = 0; i < M.rows(); ++i)
    {
        for (int j = 0; j < M.cols(); ++j)
        {

            const auto& mc = M.get_cell(i, j);

            std::string cell_symbol;


                if (mc.is_a_mine())
                    cell_symbol = mine;
                else
                    cell_symbol = std::to_string(M.get_cell(i,j).value);

                if (!naked && mc.is_covered())
                    cell_symbol = cover;

            std::cout << cell_symbol << ' ';
        }
        std::cout << std::endl;
    }

}
