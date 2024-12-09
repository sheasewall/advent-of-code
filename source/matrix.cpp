#include <vector>

namespace spaces
{
    // template <typename T, unsigned int Dim, typename size_type>
    // {

    // }
    // template <typename T, 


    template <typename T, unsigned int Dim, typename size_type>
    struct Matrix
    {
    private:
        std::vector<Matrix<T, Dim - 1, size_type>> internal_vec;

    public:
        Matrix() : internal_vec() {}
        Matrix(size_type size, T fill_element);
        const std::vector<Matrix<T, Dim - 1, size_type>> &getVector() { return internal_vec; }
        void add(const Matrix<T, Dim - 1, size_type> &element) { internal_vec.push_back(element); }
        T getElement(std::array<size_type, Dim> coords);
        size_type size() { return internal_vec.size(); }
    };

    template <typename T, typename size_type>
    struct Matrix<T, 1, size_type>
    {
    private:
        std::vector<T> internal_vec;

    public:
        Matrix() : internal_vec() {}
        Matrix(size_type size, T fill_element) : internal_vec(size, fill_element) {}
        const std::vector<T> &getVector() { return internal_vec; }
        void add(const T &element) { internal_vec.push_back(element); }
        T getElement(std::array<size_type, 1> coords);
        size_type size() { return internal_vec.size(); }
    };

    template <typename T, unsigned int Dim, typename size_type>
    T Matrix<T, Dim, size_type>::getElement(std::array<size_type, Dim> coords)
    {
        if (coords[Dim - 1] < 0)
        {
            std::throw_with_nested(std::out_of_range("Coordinate was too low"));
        }
        if (coords[Dim - 1] >= size())
        {
            std::throw_with_nested(std::out_of_range("Coordinate out of range"));
        }
        std::array<size_type, Dim - 1> popped_coords;
        std::copy(coords.begin(), coords.end() - 1, popped_coords.begin());
        return internal_vec[coords[Dim - 1]].getElement(popped_coords);
    }

    template <typename T, typename size_type>
    T Matrix<T, 1, size_type>::getElement(std::array<size_type, 1> coords)
    {
        if (coords[0] < 0)
        {
            std::throw_with_nested(std::out_of_range("Coordinates was too low"));
        }
        if (coords[0] >= size())
        {
            std::throw_with_nested(std::out_of_range("Coordinate was too high"));
        }
        return internal_vec[coords[0]];
    }
}