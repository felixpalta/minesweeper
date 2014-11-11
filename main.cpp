#include <iostream>
#include <vector>
#include <exception>
#include <stdexcept>
#include <limits>
#include "Mine_field.h"

void drawMineField(const Mine_field& M);

const int MIN_SIDE_SIZE = 2;

using namespace std;

int main()
try
{
    int field_rows_size = 0, field_cols_size = 0;


    while (!(cout << "\nInput field size, N of rows and N of columns, \nboth >= " << MIN_SIDE_SIZE << ": ") ||
           !(cin >> field_rows_size >> field_cols_size) ||
           (field_rows_size < MIN_SIDE_SIZE && field_cols_size < MIN_SIDE_SIZE))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int c;
    if ((c = cin.peek()) != '\n')
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Your field has " << field_rows_size << " rows and " << field_cols_size << " columns." <<  endl;

    Mine_field m(field_rows_size, field_cols_size);

    int number_of_mines = 0;

    while (!(cout << "\nInput number of mines, N < " << m.cells_number() << ": ") ||
           !(cin >> number_of_mines) ||
           (number_of_mines >= m.cells_number() || number_of_mines < 1))

    {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if ((c = cin.peek()) != '\n')
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Your number of mines is " << number_of_mines << endl;

    int select_row = -1, select_col = -1;

    while (!(cout << "\nInput row and column number of the cell you want to start with: ") ||
           !(cin >> select_row >> select_col) ||
           !m.is_within_field(select_row, select_col))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if ((c = cin.peek()) != '\n')
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    m.generate_mines(number_of_mines, select_row, select_col);
    m.generate_neighbor_numbers();

    drawMineField(m);
    return 0;
}
catch (exception& e)
{
    cerr << e.what() << endl;
    return 1;
}

void drawMineField(const Mine_field& M)
{
    for (int i = 0; i < M.rows(); ++i)
    {
        for (int j = 0; j < M.cols(); ++j)
        {
            cout << M.get_cell(i, j).value << '\t';
        }
        cout << endl;
    }

}
