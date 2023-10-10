// spreadsheet.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <stdexcept>

template <class T>
class Table {
public:
    // Запретить оператор присваивания
    //Table& operator=(const Table&) = delete;
    // Запретить конструктор копирования
    //Table(const Table&) = delete;

    Table(int rows, int columns) : rows_(rows), columns_(columns), data_(new T[rows * columns]) {}
    Table() : rows_(0), columns_(0), data_(nullptr) {}
  
    Table(const Table& other) : rows_(other.rows_), columns_(other.columns_), data_(new T[other.rows_ * other.columns_]) {
        std::copy(other.data_, other.data_ + (other.rows_ * other.columns_), data_);
    }

    
    Table& operator=(const Table& other) {
        if (this == &other) {
            return *this; 
        }

        delete[] data_;

       
        rows_ = other.rows_;
        columns_ = other.columns_;
        data_ = new T[other.rows_ * other.columns_];

        
        std::copy(other.data_, other.data_ + (other.rows_ * other.columns_), data_);

        return *this;
    }

    ~Table() {
        delete[] data_;
    }

    struct Accessor {
        Accessor(T* data, int columns) : data_(data), columns_(columns) {}

        T& operator()(int index) {
            if (index < 0 || index >= columns_) {
                throw std::out_of_range("выход за пределы массива!");
            }
            return data_[index];
        }

        const T& operator()(int index) const {
            if (index < 0 || index >= columns_) {
                throw std::out_of_range("выход за пределы массива!");
            }
            return data_[index];
        }

    private:
        T* data_;
        int columns_;
    };

    Accessor operator[](int index) {
        if (index < 0 || index >= rows_) {
            throw std::out_of_range("выход за пределы массива!");
        }
        return Accessor(data_ + (index * columns_), columns_);
    }

    const Accessor operator[](int index) const {
        if (index < 0 || index >= rows_) {
            throw std::out_of_range("выход за пределы массива!");
        }
        return Accessor(data_ + (index * columns_), columns_);
    }

    int Size() const {
        return rows_ * columns_;
    }

private:
    int rows_;
    int columns_;
    T* data_;
};

int main() {
    std::setlocale(LC_ALL, "RU");
    Table<int> test(2, 3);

    test[0](0) = 4;
    std::cout << test[0](0);

   
    Table<int> copy(test);

    
    Table<int> another;
    another = test;

    return 0;
}


//Когда указатель складывается с целым числом, компилятор интерпретирует это как перемещение указателя на заданное количество элементов. 
//Размер каждого элемента зависит от типа указателя. Например, для указателя на целое число (int*) операция сложения добавляет к указателю количество байт, 
//равное размеру int.



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
