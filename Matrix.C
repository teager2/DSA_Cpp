#include <iostream>

#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
template <typename Object>
class matrix
{
    public:
        matrix(int rows, int cols) : array(rows)
        {
            for(auto & thisRow : array)
                thisRow.resize(cols);
        }

        matrix(std::vector<std::vector<Object>> v) : array{v}
        {std::cout << "copy constructor" << std::endl;}
        matrix(std::vector<std::vector<Object>> && v) : array{std::move(v)}
        {
        std::cout << "move constructor" << std::endl;
        }

        const std::vector<Object> & operator[] (int row) const //return by const-ref. it is an accessor
        {
            return array[ row ];
        }

        //return by ref. not very in use for most cases. here the caller wants to modify the vector
        std::vector<Object> & operator[] (int row)//return by const-ref. it is an accessor
        {
            return array[ row ];
        }

        int numrows() const //check the number of rows
        {
            return array.size();
        }

        int numcols() const //check the number of cols
        {
            return numrows() ? array[0].size() : 0; //if numrows is not 0, tht is if the row(s) exist(s), 
        }

    private:
        std::vector<std::vector<Object>> array;
};
#endif

int main()
{
    matrix<int> m(7,5);
    matrix<int> v = m;

    for (int i=0; i < m.numrows(); ++i)
        for (int j=0; j < m.numcols(); ++j)
            m[i][j] = (i+1) * (j+1);

    for (int i=0; i < m.numrows(); ++i)
    {
        for (int j=0; j < m.numcols(); ++j)
        {
            std::cout << m[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

