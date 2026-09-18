/*
#include <iostream>
#include <vector>

template <typename T>
class matrix {
    int rows = 0, cols = 0;
    T* data = nullptr;
public:

    matrix()=default ;
    //rows and cols constructor
    matrix(int r, int c): rows(r), cols(c){
        data = new T[rows*cols]();
    }
    // destructor
    ~matrix() {
        delete[] data;
    }

    // copy constructor
    matrix(const matrix& other) : rows(other.rows), cols(other.cols) {
        data = new T[rows * cols]();
        for (int i = 0; i < rows * cols; i++) {
            data[i] = other.data[i];
        }
    }

    //move constructor
    matrix(matrix&& other) noexcept: rows(other.rows), cols(other.cols), data(other.data) {
        other.data = nullptr;
        other.rows = 0;
        other.cols = 0;
    }

    matrix& operator=(matrix&& other) noexcept {
        if (this != &other) {
            delete[] data;
            rows = other.rows, cols = other.cols;
            data = other.data;
            other.data = nullptr;
            other.rows = 0;
            other.cols = 0;
        }
        return *this;
    }

    matrix& operator=(const matrix& other) {
        if (this != &other) {
            delete[] data;
            rows = other.rows, cols = other.cols;
            data = new T[rows*cols];
            for (int i = 0; i < rows*cols; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    matrix& operator+=(const matrix& other) {
        if (rows != other.rows || cols != other.cols) {
            throw std::invalid_argument("Matrix dimension mismatch for sum");
        }
        for (size_t i = 0; i < rows * cols; i++) {
            data[i] += other.data[i];
        }
        return *this;
    }

    matrix& operator-=(const matrix& other) {
        if (rows != other.rows || cols != other.cols) {
            throw std::invalid_argument("Matrix dimension mismatch for subtraction");
        }
        for (size_t i = 0; i < rows * cols; i++) {
            data[i] -= other.data[i];
        }
        return *this;
    }

    friend matrix operator+(matrix lhs, const matrix& rhs) {
        lhs += rhs;
        return lhs;
    }

    friend matrix operator-(matrix lhs, const matrix& rhs) {
        lhs -= rhs;
        return lhs;
    }

    matrix operator*(const matrix& other) const {
        if (cols != other.rows) {
            throw std::invalid_argument("Matrix dimension mismatch for multiplication");
        }

        matrix newMatrix(rows, other.cols);

        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < other.cols; ++j) {
                auto val = 0;
                for (size_t k = 0; k < cols; ++k) {
                    val += this->data[i * cols + k] * other.data[k * other.cols + j];
                }
                newMatrix.data[i * other.cols + j] = val;
            }
        }

        return newMatrix;
    }
//times a constant
    friend matrix operator*(matrix lhs, const T& other) {
        lhs *= other;
        return lhs;
    }

    matrix& operator*=(const T& other) {
        for (size_t i = 0; i < rows * cols; i++) {
            data[i] *= other;
        }
        return *this;
    }


    void resize(int rows_, int cols_) {

        T* newData = new T[rows_ * cols_]();
        int min_rows = std::min(rows, rows_);
        int min_cols = std::min(cols, cols_);

        for (int r = 0; r < min_rows; ++r) {
            for (int c = 0; c < min_cols; ++c) {
                newData[r * cols_ + c] = data[r * cols + c];
            }
        }
        delete[] data;
        data = newData;
        rows = rows_;
        cols = cols_;
    }

    matrix& operator*=(const matrix& other) {
        if (cols != other.rows) {
            throw std::invalid_argument("Matrix dimension mismatch for multiplication");
        }
        matrix result(rows, other.cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < other.cols; ++j) {
                T val = T();
                for (size_t k = 0; k < cols; ++k) {
                    val += data[i * cols + k] * other.data[k * other.cols + j];
                }
                result.data[i * other.cols + j] = val;
            }
        }
        *this = std::move(result);
        return *this;
    }

    T& operator[](int n, int m) {
        return data[n*cols + m];
    }

    T& operator()(int n, int m) {
        return data[n*cols + m];
    }

    explicit matrix(int full, int rows_, int cols_): rows(rows_), cols(cols_) {
        data = new T[rows*cols];
        for (size_t i = 0; i < rows_*cols_; i++) {
            data[i] = T(full);
        }
    }

    matrix& identity() {
        if (rows != cols) {
            resize(rows, rows);
        }
        for (size_t i = 0; i < rows; i++) {
            data[i*cols+i] = T(1);
        }
        return *this;
    }



    matrix& fill(std::vector<T> a) {
        if (rows*cols == a.size()) {
            for (size_t i = 0; i < rows*cols; i++) {
                data[i] = a[i];
            }
            return *this;
        }
        std::cerr << "Matrix size mismatch" << std::endl;
        return *this;
    }

    matrix& transpose() {
        T* newData = new T[rows * cols];

        for (size_t r = 0; r < rows; ++r) {
            for (size_t c = 0; c < cols; ++c) {
                newData[c * rows + r] = data[r * cols + c];
            }
        }
        delete[] data;
        data = newData;
        std::swap(rows, cols);

        return *this;
    }

    void swap_rows(size_t r1, size_t r2) {
        if (r1 == r2) return;
        for (size_t c = 0; c < cols; ++c) {
            std::swap(data[r1 * cols + c], data[r2 * cols + c]);
        }
    }

    void row_mult(int row, T number) {
        for (size_t c = 0; c < cols; ++c) {
            data[row * cols + c] = data[row * cols + c] * number;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const matrix<T>& s) {
        os<<"[";
        for (size_t i = 0; i < s.rows * s.cols; i++) {
            if (i%s.cols == 0 && i > 0) {
                os<<"\n";
            }
            os << s.data[i];
            if (i != s.rows * s.cols - 1) {
                os<<", ";
            }
        }
        os<<"]";
        return os;
    }

    std::pair<int, int > size() {
        return std::make_pair(rows, cols);
    }


};



int main() {

    std::cout<<"Create a matrix and fill it with a vector\n";
    matrix<int> m(3,4);
    m.fill(std::vector<int>{1,2,3,4,
                            5,1,2,3,
                            4,5,4,5});

    std::cout << m << "\n\n";

    matrix<int> n (4,3);
    n.fill(std::vector<int>{1,2,3,
                            4,5,1,
                            2,3,4,
                            5,4,5});

    std::cout << n << "\n\n";

    std::cout<<"Making an identity matrix\n";

    matrix<int> r(2,5);
    r.identity();

    std::cout<<r<<"\n\n";

    std::cout<<"Make a matrix filled with one number\n";
    matrix<int> a(4,3,2);
    std::cout<<a<<"\n\n";
    //copy
    matrix<int> m2 = m;

    //basic operations

    std::cout<<"Sum matrices\n";
    m+=m;
    std::cout << m <<"+"<< m2 << m+m2<< "\n\n";

    std::cout<<"Substraction matrices\n";
    std::cout << m<<"-"<< m2 << m2-m << "\n\n";

    std::cout<<"Multiplication matrices\n";
    std::cout << m<<"\n\n"<<"*"<<"\n\n"<<n << m*n << "\n\n";
    std::cout << m2<<"\n\n"<<"*"<<"\n\n"<<n << m2*n << "\n\n";
    n*=2;
    std::cout  << n<<"\n\n"<<"*"<<"\n\n"<<2 << n << "\n\n";

    //some transformations (and some elemental operations)
    std::cout<<"Transpose of a matrix\n";
    std::cout<<m<<"\n\n"<<"->"<<"\n\n"<<m.transpose() << "\n\n";

    std::cout<<"Resize of a matrix\n";
    std::cout << "Rows: "<<m2.size().first<<"\n"<<"Cols: "<<m2.size().second<<"\n"
    << m2 << "\n\n" << "Resize to Rows: 2, Cols: 5"<<"\n";
    m2.resize(2,5);
    std::cout<<m2<<"\n\n";

    std::cout<<"Swap rows (row 1 with row 2)\n";
    std::cout << m<<"\n\n";
    m.swap_rows(1,2);
    std::cout << m << "\n\n";

    std::cout<<"Row multiplication by a constant (Row 1, constant 2.5)\n";
    m.row_mult(1,2);
    std::cout << m << "\n\n";


    return 0;
}
*/
