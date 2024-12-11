#include <vector>

template <typename T, unsigned int Dim, typename size_type, template <typename _Tp, typename _Ap> class list_type>
class HyperArray;

template <typename T, unsigned int Dim, typename size_type, template <typename _Tp, typename _Ap> class list_type>
struct HyperArrayTrait
{
    using InternalType = list_type<HyperArray<T, Dim - 1, size_type, list_type>,
                                   std::allocator<HyperArray<T, Dim - 1, size_type, list_type>>>;
};

template <typename T, typename size_type, template <typename _Tp, typename _Ap> class list_type>
struct HyperArrayTrait<T, 1, size_type, list_type>
{
    using InternalType = list_type<T, std::allocator<T>>;
};

template <typename T, unsigned int Dim, typename size_type, template <typename _Tp, typename _Ap> class list_type>
class HyperArray
{
  protected:
    using InternalType = typename HyperArrayTrait<T, Dim, size_type, list_type>::InternalType;
    InternalType internal_arr;

    template <typename... Coords> 
    void placeElementHelper(const T &el, size_type index, Coords... coords);
    void placeElementHelper(const T &el, size_type index);

  public:
    HyperArray() : internal_arr() { std::cout << "empty constructor" << std::endl; }
    template <typename... Coords> HyperArray(Coords... coords) : internal_arr() 
    { 
        static_assert(sizeof...(coords) == Dim, "Number of coordinates must match the dimension of the array");
        HyperArrayConstructor(coords...);
    } 
    HyperArray(std::array<size_type, Dim> coords) : internal_arr();

    template <typename... Coords> 
    void HyperArrayConstructor(size_type index, Coords... coords);
    void HyperArrayConstructor(size_type index);

    HyperArray(const HyperArray &v) = delete;
    HyperArray(HyperArray &&v) : internal_arr(std::move(v.internal_arr)) { std::cout << "copy cons" << std::endl; }
    HyperArray& operator=(const HyperArray &v) = delete;
    HyperArray& operator=(HyperArray &&v) = delete;
    //InternalType& operator[](const size_type &i);

    template <typename... Coords> void placeElement(const T& el, Coords... coords)
    {
        static_assert(sizeof...(coords) == Dim, "Number of coordinates must match the dimension of the array");
        placeElementHelper(el, coords...);
    }
};

// template <typename T, unsigned int Dim, typename size_type, template <typename _Tp, typename _Ap> class list_type>
// HyperArray<T, Dim, size_type, list_type>::HyperArray(std::array<size_type, Dim> coords) : internal_arr()
// {
//     static_assert(coords.size() == Dim, "Number of coordinates must match the dimension of the array");

// }



template <typename T, unsigned int Dim, typename size_type, template <typename _Tp, typename _Ap> class list_type>
template <typename... Coords>
void HyperArray<T, Dim, size_type, list_type>::placeElementHelper(const T& el, size_type index, Coords... coords)
{
    // // The use of resize here forces us to define a move constructor
    internal_arr.resize(index + 1);
    internal_arr[index].placeElement(el, coords...);
}

template <typename T, unsigned int Dim, typename size_type, template <typename _Tp, typename _Ap> class list_type>
void HyperArray<T, Dim, size_type, list_type>::placeElementHelper(const T& el, size_type index)
{
    internal_arr.resize(index + 1);
    internal_arr[index] = el;
}


template <typename T, unsigned int Dim, typename size_type, template <typename _Tp, typename _Ap> class list_type>
template <typename... Coords>
void HyperArray<T, Dim, size_type, list_type>::HyperArrayConstructor(size_type index, Coords... coords)
{
    internal_arr.resize(index);
    for (HyperArray<T, Dim - 1, size_type, list_type>& h : internal_arr)
    {
        h.HyperArrayConstructor(coords...);
    }
}

template <typename T, unsigned int Dim, typename size_type, template <typename _Tp, typename _Ap> class list_type>
void HyperArray<T, Dim, size_type, list_type>::HyperArrayConstructor(size_type index)
{
    internal_arr.resize(index);
}