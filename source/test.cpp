#include <vector>

template <typename T, unsigned int Dim, typename size_type, template <typename _Tp, typename _Ap> class list_type>
class HyperArray;

template <typename T, unsigned int Dim, typename size_type, template <typename _Tp, typename _Ap> class list_type>
struct HyperArrayTrait
{
    using InternalType = HyperArray<T, Dim - 1, size_type, list_type>;
};

template <typename T, typename size_type, template <typename _Tp, typename _Ap> class list_type>
struct HyperArrayTrait<T, 1, size_type, list_type>
{
    using InternalType = list_type<T, std::allocator<T>>;
};

template <typename T, unsigned int Dim, typename size_type, template <typename _Tp, typename _Ap> class list_type>
struct HyperArrayPlacer
{
public:
    virtual void placeElement(InternalType* hyper_array, const T& el, std::array<size_type, Dim> coords) = 0;
};

template <typename T, typename size_type, template <typename _Tp, typename _Ap> class list_type>
struct HyperArrayPlacer<T, 1, size_type, list_type>
{
public:
    virtual void placeElement(HyperArray<T, 1, size_type, list_type>* hyper_array, const T& el, std::array<size_type, 1> coords) = 0;
};

template <typename T, unsigned int Dim, typename size_type>
struct HyperArrayPlacer<T, Dim, size_type, std::vector>
{
public:
    void placeElement(HyperArray<T, Dim, size_type, std::vector>* hyper_array, const T& el, std::array<size_type, Dim> coords)
    {
        std::array<size_type, Dim - 1> sub_coords;
        std::copy(coords.begin(), coords.end(), sub_coords);
        hyper_array->internal_arr[coords].placeElement(el, sub_coords);
    }
};

template <typename T, typename size_type>
struct HyperArrayPlacer<T, 1, size_type, std::vector>
{
public:
    void placeElement(HyperArray<T, 1, size_type, std::vector>* hyper_array, const T& el, std::array<size_type, 1> coords)
    {
        // Works
        // hyper_array->push_back(el);
        
        // Won't compile
        //hyper_array[coords[0]] = el;

        // EXC_BAD_ACCESS (code=1, address=0x0)
        (*hyper_array).resize(coords[0] + 1);
        (*hyper_array)[coords[0]] = el;
    }
};

template <typename T, unsigned int Dim, typename size_type, template <typename _Tp, typename _Ap> class list_type>
class HyperArray
{
    friend class HyperArrayPlacer<T, Dim, size_type, list_type>;
  private:
    using InternalType = typename HyperArrayTrait<T, Dim, size_type, list_type>::InternalType;
    InternalType internal_arr;

    HyperArrayPlacer<T, Dim, size_type, list_type> internal_placer;

  public:
    HyperArray() : internal_arr(), internal_placer() { 
        std::cout << "empty constructor" << std::endl; }

    HyperArray(const HyperArray &v) = delete;
    HyperArray(HyperArray &&v) : internal_arr(std::move(v.internal_arr)), internal_placer(std::move(v.internal_placer)) { std::cout << "copy cons" << std::endl; }
    HyperArray& operator=(const HyperArray &v) = delete;
    HyperArray& operator=(HyperArray &&v) = delete;

    void placeElement(const T& el, std::array<size_type, Dim> coords) { internal_placer.placeElement(&internal_arr, el, coords); }
};




// // template <typename T, unsigned int Dim, typename size_type>
// // {

// // }
// // template <typename T,

// // template <typename T, unsigned int Dim, typename size_type, template <typename _Tp, typename _Ap> class list_type>
// // class HyperArray;

// // template <typename T, unsigned int Dim, typename size_type, template <typename _Tp, typename _Ap> class list_type>
// // struct HyperArrayTrait
// // {
// //     using InternalType = list_type<HyperArray<T, Dim - 1, size_type, list_type>,
// //                                    std::allocator<HyperArray<T, Dim - 1, size_type, list_type>>>;
// // };

// // template <typename T, typename size_type, template <typename _Tp, typename _Ap> class list_type>
// // struct HyperArrayTrait<T, 1, size_type, list_type>
// // {
// //     using InternalType = list_type<T, std::allocator<T>>;
// // };

// // template <typename T, unsigned int Dim, typename size_type, template <typename _Tp, typename _Ap> class list_type>
// // class HyperArray
// // {
// //   private:
// //     using InternalType = typename HyperArrayTrait<T, Dim, size_type, list_type>::InternalType;
// //     InternalType internal_arr;

// //     template <typename... Coords> 
// //     void placeElementHelper(const T &el, size_type index, Coords... coords);
// //     void placeElementHelper(const T &el, size_type index);

// //     // template <typename... Coords> void HyperArrayConstructor(size_type index, Coords... coords);
// //     // void HyperArrayConstructor(size_type index);

// //   public:
// //     HyperArray() : internal_arr() { std::cout << "empty constructor" << std::endl; }
// //     // template <typename... Coords> HyperArray(Coords... coords) : internal_arr() 
// //     // { 
// //     //     static_assert(sizeof...(coords) == Dim, "Number of coordinates must match the dimension of the array");
// //     //     HyperArrayConstructor(coords...);
// //     // } 
// //     HyperArray(const HyperArray &v) = delete;
// //     HyperArray(HyperArray &&v) : internal_arr(std::move(v.internal_arr)) { std::cout << "copy cons" << std::endl; }
// //     HyperArray& operator=(const HyperArray &v) = delete;
// //     HyperArray& operator=(HyperArray &&v) = delete;
// //     //InternalType& operator[](const size_type &i);

// //     template <typename... Coords> void placeElement(const T& el, Coords... coords)
// //     {
// //         static_assert(sizeof...(coords) == Dim, "Number of coordinates must match the dimension of the array");
// //         placeElementHelper(el, coords...);
// //     }
// // };

// // // template <typename T, unsigned int Dim, typename size_type>
// // // class HyperArrayVector : public HyperArray<typename T, unsigned int Dim, typename size_type, std::vector>
// // // {
// // // template <typename... Coords> 
// // //     void placeElementHelper(const T &el, size_type index, Coords... coords);
// // //     void placeElementHelper(const T &el, size_type index);
// // // };

// // // template <typename T, unsigned int Dim, typename size_type>
// // // template <typename... Coords>
// // // void HyperArrayVector<T, Dim, size_type>::placeElementHelper(const T& el, size_type index, Coords... coords)
// // // {
// // //     // // The use of resize here forces us to define a move constructor
// // //     internal_arr.resize(index + 1);
// // //     internal_arr[index].placeElement(el, coords...);
// // // }

// // // template <typename T, unsigned int Dim, typename size_type>
// // // void HyperArrayVector<T, Dim, size_type>::placeElementHelper(const T& el, size_type index)
// // // {
// // //     internal_arr.resize(index + 1);
// // //     internal_arr[index] = el;
// // // }



// // // template <typename T, unsigned int Dim, typename size_type, template <typename _Tp, typename _Ap> class list_type>
// // // struct ElementPlacer
// // // {
// // //     template <typename... Coords> 
// // //     virtual void placeElement(const T&, Coords... coords) = 0;
// // // };

// // // template <typename T, unsigned int Dim, typename size_type, template <typename _Tp, typename _Ap> class list_type>
// // // struct ElementPlacer
// // // {
// // //     template <typename... Coords> 
// // //     virtual void placeElement(const T&, Coords... coords) = 0;
// // // };


// // template <typename T, unsigned int Dim, typename size_type, template <typename _Tp, typename _Ap> class list_type>
// // template <typename... Coords>
// // void HyperArray<T, Dim, size_type, list_type>::placeElementHelper(const T& el, size_type index, Coords... coords)
// // {
// //     // // The use of resize here forces us to define a move constructor
// //     internal_arr.resize(index + 1);
// //     internal_arr[index].placeElement(el, coords...);
// // }

// // template <typename T, unsigned int Dim, typename size_type, template <typename _Tp, typename _Ap> class list_type>
// // void HyperArray<T, Dim, size_type, list_type>::placeElementHelper(const T& el, size_type index)
// // {
// //     internal_arr.resize(index + 1);
// //     internal_arr[index] = el;
// // }

// // template <typename T, unsigned int Dim, typename size_type, template <typename _Tp, typename _Ap> class list_type>
// // template <typename... Coords>
// // void HyperArray<T, Dim, size_type, list_type>::HyperArrayConstructor(size_type index, Coords... coords)
// // {
// //     internal_arr.resize(index + 1);

// //     for (std::vector<)
// //     internal_arr[index].placeElement(el, coords...);
// // }

// // template <typename T, unsigned int Dim, typename size_type, template <typename _Tp, typename _Ap> class list_type>
// // void HyperArray<T, Dim, size_type, list_type>::HyperArrayConstructor(size_type index)
// // {
// //     internal_arr.resize(index + 1);

// //     internal_arr[index] = el;
// // }

// // template <typename T, unsigned int Dim, typename size_type, template <typename _Tp, typename _Ap> class list_type>
// // HyperArray<T, Dim, size_type, list_type> &HyperArray<T, Dim, size_type, list_type>::operator=(HyperArray &&v)
// // {
// //     std::cout << "move assignment" << std::endl;
// //     if (this != &v)
// //     {
// //         internal_arr = std::move(v.internal_arr);
// //     }
// //     return *this;
// // }

// // template <typename T, unsigned int Dim, typename size_type, template
// // <typename _Tp, typename _Ap> class list_type> typename HyperArrayTrait<T,
// // Dim, size_type, list_type>::InternalType& HyperArray<T, Dim, size_type,
// // list_type>::operator[](const size_type &i)
// // {
// //     return internal_arr[i];
// // }

// // implement using variadics?
// // implement using Traits?
// //

// // // our element is const& so that it doesn't copy over
// // template <typename T, unsigned int Dim, typename size_type>
// // void HyperArray<T, Dim, size_type>::placeElement(const T &el,
// // std::array<size_type, Dim> coords)
// // {
// //     std::array<size_type, Dim - 1> sub_coords;
// //     std::copy(coords.begin(), coords.end(), sub_coords);
// //     internal_arr.at(coords.back()).placeElement(el, sub_coords);
// // }

// // template <typename T, typename size_type>
// // void HyperVector<T, 1, size_type>::addElement(const T &el,
// // std::array<size_type, 1> coords)
// // {
// //     return internal_vec[]
// // }

// /////
// /////

// template <typename T, unsigned int Dim, typename size_type> struct Matrix
// {
//   private:
//     std::vector<Matrix<T, Dim - 1, size_type>> internal_vec;

//   public:
//     Matrix() : internal_vec()
//     {
//     }
//     // Matrix(size_type size, T fill_element);
//     const std::vector<Matrix<T, Dim - 1, size_type>> &getVector()
//     {
//         return internal_vec;
//     }
//     void add(const Matrix<T, Dim - 1, size_type> &element)
//     {
//         internal_vec.push_back(element);
//     }
//     T getElement(std::array<size_type, Dim> coords);
//     size_type size()
//     {
//         return internal_vec.size();
//     }
// };

// template <typename T, typename size_type> struct Matrix<T, 1, size_type>
// {
//   private:
//     std::vector<T> internal_vec;

//   public:
//     Matrix() : internal_vec()
//     {
//     }
//     // Matrix(size_type size, T fill_element) : internal_vec(size, fill_element)
//     // {}
//     const std::vector<T> &getVector()
//     {
//         return internal_vec;
//     }
//     void add(const T &element)
//     {
//         internal_vec.push_back(element);
//     }
//     T getElement(std::array<size_type, 1> coords);
//     size_type size()
//     {
//         return internal_vec.size();
//     }
// };

// template <typename T, unsigned int Dim, typename size_type>
// T Matrix<T, Dim, size_type>::getElement(std::array<size_type, Dim> coords)
// {
//     if (coords[Dim - 1] < 0)
//     {
//         std::throw_with_nested(std::out_of_range("Coordinate was too low"));
//     }
//     if (coords[Dim - 1] >= size())
//     {
//         std::throw_with_nested(std::out_of_range("Coordinate out of range"));
//     }
//     std::array<size_type, Dim - 1> popped_coords;
//     std::copy(coords.begin(), coords.end() - 1, popped_coords.begin());
//     return internal_vec[coords[Dim - 1]].getElement(popped_coords);
// }

// template <typename T, typename size_type> T Matrix<T, 1, size_type>::getElement(std::array<size_type, 1> coords)
// {
//     if (coords[0] < 0)
//     {
//         std::throw_with_nested(std::out_of_range("Coordinates was too low"));
//     }
//     if (coords[0] >= size())
//     {
//         std::throw_with_nested(std::out_of_range("Coordinate was too high"));
//     }
//     return internal_vec[coords[0]];
// }
// } // namespace spaces





// void testMultiDimVectors()
// {
//     // 1D vector tests
//     spaces::Matrix<int, 1, size_t> vec1d;
//     vec1d.add(1);
//     vec1d.add(2);
//     vec1d.add(3);

//     assert(vec1d.getElement({0}) == 1);
//     assert(vec1d.getElement({1}) == 2);
//     assert(vec1d.size() == 3);

//     // 2D vector tests
//     spaces::Matrix<int, 2, size_t> vec2d;
//     spaces::Matrix<int, 1, size_t> row1;
//     row1.add(1);
//     row1.add(2);

//     spaces::Matrix<int, 1, size_t> row2;
//     row2.add(3);
//     row2.add(4);

//     vec2d.add(row1);
//     vec2d.add(row2);

//     assert(vec2d.getElement({0, 0}) == 1);
//     assert(vec2d.getElement({1, 1}) == 4);
//     assert(vec2d.size() == 2);

//     // 3D vector tests
//     spaces::Matrix<int, 3, size_t> vec3d;
//     spaces::Matrix<int, 2, size_t> plane1;
//     plane1.add(row1);
//     plane1.add(row2);
//     vec3d.add(plane1);

//     assert(vec3d.getElement({0, 0, 0}) == 1);
//     assert(vec3d.getElement({1, 1, 0}) == 4);

//     // fill constructor tests
//     // spaces::MultiDimVector<char, 1, size_t> fill_vec1d = vec::MultiDimVector<char, 1, size_t>('k', 5);

//     // Error handling tests
//     try
//     {
//         // vec1d.getElement({999}); // Should throw
//         // assert(false);  // Should not reach here
//     }
//     catch (const std::nested_exception &e)
//     {
//         std::cout << "Successfully caught out of range error\n";
//     }

//     try
//     {
//         // vec1d.getElement({-1}); // Should throw
//         // assert(false);  // Should not reach here
//     }
//     catch (const std::nested_exception &e)
//     {
//         std::cout << "Successfully caught negative index error\n";
//     }

//     std::cout << "All Matrix tests passed!\n";
// }

// void testMDV()
// {
//     spaces::Matrix<char, 1, int> x1a = spaces::Matrix<char, 1, int>();
//     spaces::Matrix<char, 1, int> x1b = spaces::Matrix<char, 1, int>();
//     x1a.add('a');
//     x1a.add('b');
//     x1a.add('c');
//     x1a.add('e');
//     x1b.add('f');
//     x1b.add('g');
//     x1b.add('h');
//     x1b.add('i');
//     spaces::Matrix<char, 2, int> x2a = spaces::Matrix<char, 2, int>();
//     x2a.add(x1a);
//     x2a.add(x1b);

//     spaces::Matrix<char, 1, int> x1c = spaces::Matrix<char, 1, int>();
//     spaces::Matrix<char, 1, int> x1d = spaces::Matrix<char, 1, int>();
//     x1c.add('j');
//     x1c.add('k');
//     x1c.add('l');
//     x1c.add('m');
//     x1d.add('n');
//     x1d.add('o');
//     x1d.add('p');
//     x1d.add('q');
//     spaces::Matrix<char, 2, int> x2b = spaces::Matrix<char, 2, int>();
//     x2b.add(x1c);
//     x2b.add(x1d);

//     spaces::Matrix<char, 1, int> x1e = spaces::Matrix<char, 1, int>();
//     spaces::Matrix<char, 1, int> x1f = spaces::Matrix<char, 1, int>();
//     x1e.add('r');
//     x1e.add('s');
//     x1e.add('t');
//     x1e.add('u');
//     x1f.add('v');
//     x1f.add('w');
//     x1f.add('x');
//     x1f.add('y');
//     spaces::Matrix<char, 2, int> x2c = spaces::Matrix<char, 2, int>();
//     x2c.add(x1e);
//     x2c.add(x1f);

//     spaces::Matrix<char, 3, int> x3a = spaces::Matrix<char, 3, int>();
//     x3a.add(x2a);
//     x3a.add(x2b);
//     x3a.add(x2c);

//     auto &x3av = x3a.getVector();

//     auto ex1 = x1a.getElement({0});

//     auto ex2 = x2a.getElement({0, 1});

//     auto ex3 = x3a.getElement({0, 1, 1});
//     return;
// }

// int main(int argc, char *argv[])
// {
//     // testMultiDimVectors();
//     //  testMDV();
//     //  timeDay7();

//     // spaces::HyperVector<char, 1, long> hv1 = spaces::HyperVector<char, 1, long>();
//     //  spaces::HyperArray<char, 1, long, std::list> hv2{};
//     //  hv2.placeElement('c', 0);

//     int x = 5;

//     spaces::HyperArray<char, 1, long, std::vector> hv1d{};
//     hv1d.placeElement('d', {0l});
//     hv1d.placeElement('e', {1l});
//     hv1d.placeElement('9', {9l});


//     spaces::HyperArray<char, 2, long, std::vector> hv2d{};
//     hv2d.placeElement('d', {0l, 0l});

//     // spaces::HyperArray<char, 2, long, std::vector> hv2dp{};
//     // // hv2d = std::move(hv2dp);
//     // hv2d.placeElement('a', 0l, 1l);
//     // hv2dp.placeElement('b', 0, 1l);

//     // hv2.placeElement('c', std::array<1, long>{0});
//     // hv2.addElement('c');

//     return 0;
// }




/*

// void testTileEntity()
// {
//     vec::Entity<char, int, 1> tile = vec::Entity<char, int, 1>({0}, 'c');
//     vec::operator<<(std::cout, tile);

//     vec::Entity<std::string, long, 1> tile2 = vec::Entity<std::string, long, 1>({1000}, "jo");
//     vec::operator<<(std::cout, tile2);

//     vec::Entity<std::string, long, 2> tile3 = vec::Entity<std::string, long, 2>({-10, 10}, "jo");
//     vec::operator<<(std::cout, tile3);
// }

// void testMDV()
// {
//     spaces::Matrix<char, 1, int> x1a = spaces::Matrix<char, 1, int>();
//     spaces::Matrix<char, 1, int> x1b = spaces::Matrix<char, 1, int>();
//     x1a.add('a');
//     x1a.add('b');
//     x1a.add('c');
//     x1a.add('e');
//     x1b.add('f');
//     x1b.add('g');
//     x1b.add('h');
//     x1b.add('i');
//     spaces::Matrix<char, 2, int> x2a = spaces::Matrix<char, 2, int>();
//     x2a.add(x1a);
//     x2a.add(x1b);

//     spaces::Matrix<char, 1, int> x1c = spaces::Matrix<char, 1, int>();
//     spaces::Matrix<char, 1, int> x1d = spaces::Matrix<char, 1, int>();
//     x1c.add('j');
//     x1c.add('k');
//     x1c.add('l');
//     x1c.add('m');
//     x1d.add('n');
//     x1d.add('o');
//     x1d.add('p');
//     x1d.add('q');
//     spaces::Matrix<char, 2, int> x2b = spaces::Matrix<char, 2, int>();
//     x2b.add(x1c);
//     x2b.add(x1d);

//     spaces::Matrix<char, 1, int> x1e = spaces::Matrix<char, 1, int>();
//     spaces::Matrix<char, 1, int> x1f = spaces::Matrix<char, 1, int>();
//     x1e.add('r');
//     x1e.add('s');
//     x1e.add('t');
//     x1e.add('u');
//     x1f.add('v');
//     x1f.add('w');
//     x1f.add('x');
//     x1f.add('y');
//     spaces::Matrix<char, 2, int> x2c = spaces::Matrix<char, 2, int>();
//     x2c.add(x1e);
//     x2c.add(x1f);

//     spaces::Matrix<char, 3, int> x3a = spaces::Matrix<char, 3, int>();
//     x3a.add(x2a);
//     x3a.add(x2b);
//     x3a.add(x2c);

//     auto &x3av = x3a.getVector();

//     auto ex1 = x1a.getElement({0});

//     auto ex2 = x2a.getElement({0, 1});

//     auto ex3 = x3a.getElement({0, 1, 1});
//     return;
// }

void testVec()
{
    std::array<float, 3> f1 = {0.1, 0.2, 0.3};
    VecArrayR<float, 3> f1v(f1);

    std::array<float, 3> f2 = {0.7, 0.8, 0.9};
    VecArrayR<float, 3> f2v(f2);
    
    VecArrayR<float, 3> af = VecArrayR<float, 3>::add(f1, f2);
    std::cout << af.back() << std::endl;

    // Test VecArrayR<X, 1> char
    std::array<std::string, 1> ch1 = {"hi"};
    VecArrayR<std::string, 1> chv1(ch1);
    std::cout << "VecArrayR<int, 1> back: " << chv1.back() << std::endl;

    std::array<std::string, 1> ch2 = {"there"};
    VecArrayR<std::string, 1> chv2(ch2);
    std::cout << "VecArrayR<int, 1> back: " << chv2.back() << std::endl;

    // Test add
    VecArrayR<std::string, 1> achv = VecArrayR<std::string, 1>::add(chv1, chv2);
    std::cout << "VecArrayR<int, 2> added back: " << achv.back() << std::endl;

    // Test VecArrayR<X, 1>
    std::array<int, 1> arr1 = {1};
    VecArrayR<int, 1> vec1(arr1);
    std::cout << "VecArrayR<int, 1> back: " << vec1.back() << std::endl;

    // Test VecArrayR<X, 2>
    std::array<int, 2> arr2 = {1, 2};
    VecArrayR<int, 2> vec2(arr2);
    std::cout << "VecArrayR<int, 2> back: " << vec2.back() << std::endl;

    // Test subVec
    VecArrayR<int, 1> subVec = VecArrayR<int, 2>::subVec(vec2);
    std::cout << "VecArrayR<int, 2> subVec back: " << subVec.back() << std::endl;

    // Test cat
    VecArrayR<int, 2> catVec = VecArrayR<int, 2>::cat(subVec, 2);
    std::cout << "VecArrayR<int, 2> cat back: " << catVec.back() << std::endl;

    // Test scale
    VecArrayR<int, 2> scaledVec = VecArrayR<int, 2>::scale(2, vec2);
    std::cout << "VecArrayR<int, 2> scaled: " << scaledVec.back() << std::endl;

    // Test add
    VecArrayR<int, 2> addedVec = VecArrayR<int, 2>::add(vec2, vec2);
    std::cout << "VecArrayR<int, 2> added back: " << addedVec.back() << std::endl;
}

int testNVec() {
    // Test for 1D NVector
    NVector<int, 1, int> nm1{};
    nm1.resize({5});
    nm1[0] = 10;
    nm1[1] = 20;
    nm1[2] = 30;
    nm1[3] = 40;
    nm1[4] = 50;

    std::cout << "1D NVector Test:" << std::endl;
    std::cout << "Expected: 10, Actual: " << nm1.getElement({0}) << std::endl;
    std::cout << "Expected: 20, Actual: " << nm1.getElement({1}) << std::endl;
    std::cout << "Expected: 30, Actual: " << nm1.getElement({2}) << std::endl;
    std::cout << "Expected: 40, Actual: " << nm1.getElement({3}) << std::endl;
    std::cout << "Expected: 50, Actual: " << nm1.getElement({4}) << std::endl;

    // Test for 2D NVector
    NVector<int, 2, int> nm2{};
    nm2.resize({3, 3});
    nm2[0][0] = 1;
    nm2[0][1] = 2;
    nm2[0][2] = 3;
    nm2[1][0] = 4;
    nm2[1][1] = 5;
    nm2[1][2] = 6;
    nm2[2][0] = 7;
    nm2[2][1] = 8;
    nm2[2][2] = 9;

    std::cout << "2D NVector Test:" << std::endl;
    std::cout << "Expected: 1, Actual: " << nm2.getElement({0, 0}) << std::endl;
    std::cout << "Expected: 2, Actual: " << nm2.getElement({0, 1}) << std::endl;
    std::cout << "Expected: 3, Actual: " << nm2.getElement({0, 2}) << std::endl;
    std::cout << "Expected: 4, Actual: " << nm2.getElement({1, 0}) << std::endl;
    std::cout << "Expected: 5, Actual: " << nm2.getElement({1, 1}) << std::endl;
    std::cout << "Expected: 6, Actual: " << nm2.getElement({1, 2}) << std::endl;
    std::cout << "Expected: 7, Actual: " << nm2.getElement({2, 0}) << std::endl;
    std::cout << "Expected: 8, Actual: " << nm2.getElement({2, 1}) << std::endl;
    std::cout << "Expected: 9, Actual: " << nm2.getElement({2, 2}) << std::endl;

    // Test for 3D NVector
    NVector<int, 3, int> nm3{};
    nm3.resize({2, 2, 2});
    nm3[0][0][0] = 1;
    nm3[0][0][1] = 2;
    nm3[0][1][0] = 3;
    nm3[0][1][1] = 4;
    nm3[1][0][0] = 5;
    nm3[1][0][1] = 6;
    nm3[1][1][0] = 7;
    nm3[1][1][1] = 8;

    std::cout << "3D NVector Test:" << std::endl;
    std::cout << "Expected: 1, Actual: " << nm3.getElement({0, 0, 0}) << std::endl;
    std::cout << "Expected: 2, Actual: " << nm3.getElement({0, 0, 1}) << std::endl;
    std::cout << "Expected: 3, Actual: " << nm3.getElement({0, 1, 0}) << std::endl;
    std::cout << "Expected: 4, Actual: " << nm3.getElement({0, 1, 1}) << std::endl;
    std::cout << "Expected: 5, Actual: " << nm3.getElement({1, 0, 0}) << std::endl;
    std::cout << "Expected: 6, Actual: " << nm3.getElement({1, 0, 1}) << std::endl;
    std::cout << "Expected: 7, Actual: " << nm3.getElement({1, 1, 0}) << std::endl;
    std::cout << "Expected: 8, Actual: " << nm3.getElement({1, 1, 1}) << std::endl;

    // putElement tests.
    // Test for 1D NVector
    NVector<int, 1, int> nmp1{};
    nmp1.resize({5});
    nmp1.putElement({0}, 10);
    nmp1.putElement({1}, 20);
    nmp1.putElement({2}, 30);
    nmp1.putElement({3}, 40);
    nmp1.putElement({4}, 50);

    std::cout << "1D NVector Test:" << std::endl;
    std::cout << "Expected: 10, Actual: " << nmp1.getElement({0}) << std::endl;
    std::cout << "Expected: 20, Actual: " << nmp1.getElement({1}) << std::endl;
    std::cout << "Expected: 30, Actual: " << nmp1.getElement({2}) << std::endl;
    std::cout << "Expected: 40, Actual: " << nmp1.getElement({3}) << std::endl;
    std::cout << "Expected: 50, Actual: " << nmp1.getElement({4}) << std::endl;

    // Test for 2D NVector
    NVector<int, 2, int> nmp2{};
    nmp2.resize({3, 3});
    nmp2.putElement({0, 0}, 1);
    nmp2.putElement({0, 1}, 2);
    nmp2.putElement({0, 2}, 3);
    nmp2.putElement({1, 0}, 4);
    nmp2.putElement({1, 1}, 5);
    nmp2.putElement({1, 2}, 6);
    nmp2.putElement({2, 0}, 7);
    nmp2.putElement({2, 1}, 8);
    nmp2.putElement({2, 2}, 9);

    std::cout << "2D NVector Test:" << std::endl;
    std::cout << "Expected: 1, Actual: " << nmp2.getElement({0, 0}) << std::endl;
    std::cout << "Expected: 2, Actual: " << nmp2.getElement({0, 1}) << std::endl;
    std::cout << "Expected: 3, Actual: " << nmp2.getElement({0, 2}) << std::endl;
    std::cout << "Expected: 4, Actual: " << nmp2.getElement({1, 0}) << std::endl;
    std::cout << "Expected: 5, Actual: " << nmp2.getElement({1, 1}) << std::endl;
    std::cout << "Expected: 6, Actual: " << nmp2.getElement({1, 2}) << std::endl;
    std::cout << "Expected: 7, Actual: " << nmp2.getElement({2, 0}) << std::endl;
    std::cout << "Expected: 8, Actual: " << nmp2.getElement({2, 1}) << std::endl;
    std::cout << "Expected: 9, Actual: " << nmp2.getElement({2, 2}) << std::endl;

    // Test for 3D NVector
    NVector<int, 3, int> nmp3{};
    nmp3.resize({2, 2, 2});
    nmp3.putElement({0, 0, 0}, 1);
    nmp3.putElement({0, 0, 1}, 2);
    nmp3.putElement({0, 1, 0}, 3);
    nmp3.putElement({0, 1, 1}, 4);
    nmp3.putElement({1, 0, 0}, 5);
    nmp3.putElement({1, 0, 1}, 6);
    nmp3.putElement({1, 1, 0}, 7);
    nmp3.putElement({1, 1, 1}, 8);

    std::cout << "3D NVector Test:" << std::endl;
    std::cout << "Expected: 1, Actual: " << nmp3.getElement({0, 0, 0}) << std::endl;
    std::cout << "Expected: 2, Actual: " << nmp3.getElement({0, 0, 1}) << std::endl;
    std::cout << "Expected: 3, Actual: " << nmp3.getElement({0, 1, 0}) << std::endl;
    std::cout << "Expected: 4, Actual: " << nmp3.getElement({0, 1, 1}) << std::endl;
    std::cout << "Expected: 5, Actual: " << nmp3.getElement({1, 0, 0}) << std::endl;
    std::cout << "Expected: 6, Actual: " << nmp3.getElement({1, 0, 1}) << std::endl;
    std::cout << "Expected: 7, Actual: " << nmp3.getElement({1, 1, 0}) << std::endl;
    std::cout << "Expected: 8, Actual: " << nmp3.getElement({1, 1, 1}) << std::endl;

    return 0;
}

void testGridWorld() {
    using namespace day8;
    std::cout << "\n=== GridWorld Comprehensive Tests ===\n" << std::endl;

    // 1. Test 1D GridWorld with char entities
    {
        std::cout << "1. Testing 1D GridWorld with char entities:" << std::endl;
        GridWorld<Entity<char, int, 1>, 1, int> world1D;
        
        // Create multiple entities
        VecArrayR<int, 1> coords1({0});
        VecArrayR<int, 1> coords2({5});
        VecArrayR<int, 1> coords3({3});
        
        Entity<char, int, 1> entity1(coords1, 'A');
        Entity<char, int, 1> entity2(coords2, 'B');
        Entity<char, int, 1> entity3(coords3, 'C');
        
        // Spawn entities
        world1D.spawn(entity1);
        world1D.spawn(entity2);
        world1D.spawn(entity3);
        
        std::cout << entity1 << "\n" << entity2 << "\n" << entity3 << std::endl;
    }

    // 2. Test 2D GridWorld with string entities
    {
        std::cout << "\n2. Testing 2D GridWorld with string entities:" << std::endl;
        GridWorld<Entity<std::string, long, 2>, 2, long> world2D;
        
        // Create multiple entities
        VecArrayR<long, 2> coords1({0l, 0l});
        VecArrayR<long, 2> coords2({5l, 3l});
        VecArrayR<long, 2> coords3({2l, 7l});
        
        Entity<std::string, long, 2> entity1(coords1, "Player");
        Entity<std::string, long, 2> entity2(coords2, "Enemy");
        Entity<std::string, long, 2> entity3(coords3, "Item");
        
        // Spawn entities
        world2D.spawn(entity1);
        world2D.spawn(entity2);
        world2D.spawn(entity3);
        
        std::cout << entity1 << "\n" << entity2 << "\n" << entity3 << std::endl;
    }

    // 3. Test 3D GridWorld with float entities
    {
        std::cout << "\n3. Testing 3D GridWorld with float entities:" << std::endl;
        GridWorld<Entity<float, int, 3>, 3, int> world3D;
        
        // Create multiple entities
        VecArrayR<int, 3> coords1({0, 0, 0});
        VecArrayR<int, 3> coords2({1, 2, 3});
        VecArrayR<int, 3> coords3({4, 1, 7});
        
        Entity<float, int, 3> entity1(coords1, 1.5f);
        Entity<float, int, 3> entity2(coords2, 2.7f);
        Entity<float, int, 3> entity3(coords3, 3.14f);
        
        // Spawn entities
        world3D.spawn(entity1);
        world3D.spawn(entity2);
        world3D.spawn(entity3);
        
        std::cout << entity1 << "\n" << entity2 << "\n" << entity3 << std::endl;
    }

    // 4. Test 2D GridWorld with complex entity type (struct)
    {
        // std::cout << "\n4. Testing 2D GridWorld with custom struct entities:" << std::endl;
        
        // struct GameEntity {
        //     std::string name;
        //     int health;
        //     friend std::ostream& operator<<(std::ostream& os, const GameEntity& e) {
        //         return os << e.name << "(HP:" << e.health << ")";
        //     }
        // };

        // GridWorld<Entity<GameEntity, int, 2>, int, 2> gameWorld;
        
        // // Create multiple entities
        // VecArrayR<int, 2> coords1({0, 0});
        // VecArrayR<int, 2> coords2({10, 10});
        
        // Entity<GameEntity, int, 2> hero(coords1, {"Hero", 100});
        // Entity<GameEntity, int, 2> boss(coords2, {"Boss", 500});
        
        // // Spawn entities
        // gameWorld.spawn(hero);
        // gameWorld.spawn(boss);
        
        // std::cout << hero << "\n" << boss << std::endl;
    }

    std::cout << "\n=== GridWorld Tests Complete ===\n" << std::endl;
}

void testNArray() {
    std::cout << "\n=== Testing NArray Implementation ===\n" << std::endl;

    // Test 1D NArray
    {
        std::cout << "1. Testing 1D NArray:" << std::endl;
        std::array<int, 1> size1d = {5};
        NArray<int, 1, int> arr1d(size1d);
        
        // Test putting elements
        std::array<int, 1> coord1d = {0};
        arr1d.putElement(coord1d, 42);
        coord1d = {4};
        arr1d.putElement(coord1d, 99);
        
        // Test getting elements
        std::cout << "Value at [0]: " << arr1d.getElement({0}) << std::endl;
        std::cout << "Value at [4]: " << arr1d.getElement({4}) << std::endl;
        
        // Test operator[]
        arr1d[2] = 77;
        std::cout << "Value at [2]: " << arr1d[2] << std::endl;
    }

    // Test 2D NArray
    {
        std::cout << "\n2. Testing 2D NArray:" << std::endl;
        std::array<int, 2> size2d = {3, 4};
        NArray<int, 2, int> arr2d(size2d);
        
        // Test putting elements
        arr2d.putElement({0, 0}, 1);
        arr2d.putElement({1, 1}, 5);
        arr2d.putElement({2, 2}, 9);
        
        // Test getting elements
        std::cout << "Value at [0,0]: " << arr2d.getElement({0, 0}) << std::endl;
        std::cout << "Value at [1,1]: " << arr2d.getElement({1, 1}) << std::endl;
        std::cout << "Value at [2,2]: " << arr2d.getElement({2, 2}) << std::endl;
    }

    // Test 3D NArray
    {
        std::cout << "\n3. Testing 3D NArray:" << std::endl;
        std::array<int, 3> size3d = {2, 2, 2};
        NArray<int, 3, int> arr3d(size3d);
        
        // Test putting elements
        arr3d.putElement({0, 0, 0}, 111);
        arr3d.putElement({1, 1, 1}, 999);
        
        // Test getting elements
        std::cout << "Value at [0,0,0]: " << arr3d.getElement({0, 0, 0}) << std::endl;
        std::cout << "Value at [1,1,1]: " << arr3d.getElement({1, 1, 1}) << std::endl;
    }

    // Test different data types
    {
        std::cout << "\n4. Testing with different data types:" << std::endl;
        
        // String NArray
        std::array<int, 1> sizeStr = {3};
        NArray<std::string, 1, int> arrStr(sizeStr);
        arrStr.putElement({0}, "Hello");
        arrStr.putElement({1}, "World");
        std::cout << "String values: " << arrStr.getElement({0}) << " " 
                  << arrStr.getElement({1}) << std::endl;
        
        // Double NArray
        std::array<int, 2> sizeDouble = {2, 2};
        NArray<double, 2, int> arrDouble(sizeDouble);
        arrDouble.putElement({0, 0}, 3.14);
        arrDouble.putElement({1, 1}, 2.718);
        std::cout << "Double values: " << arrDouble.getElement({0, 0}) << " " 
                  << arrDouble.getElement({1, 1}) << std::endl;
    }

    std::cout << "\n=== NArray Tests Complete ===\n" << std::endl;
}

*/