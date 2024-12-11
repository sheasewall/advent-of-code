#include <vector>
#include <array>
#include <iostream>

template <typename X, unsigned int Dim>
class Vec
{
private:
    const std::array<X, Dim> arr;
    
public:
    Vec() = delete;
    Vec(std::array<X, Dim> v) : arr(v) {}

    typename std::array<X, Dim>::const_iterator begin() { return arr.begin(); }
    typename std::array<X, Dim>::const_iterator end() { return arr.end(); }

    X back() const;
    static Vec<X, Dim - 1> subVec(Vec<X, Dim> u);
    static Vec<X, Dim> cat(Vec<X, Dim - 1> u, X e);

    static Vec<X, Dim> scale(X s, Vec<X, Dim> u);
    static Vec<X, Dim> add(Vec<X, Dim> u, Vec<X, Dim> v);
};

template <typename X, unsigned int Dim>
X Vec<X, Dim>::back() const
{
    return arr.back();
}

template <typename X, unsigned int Dim>
Vec<X, Dim - 1> Vec<X, Dim>::subVec(Vec<X, Dim> vec)
{
    std::array<X, Dim - 1> sub_arr;
    std::copy(vec.begin(), vec.end() - 1, sub_arr.begin());
    return Vec<X, Dim - 1>(sub_arr);
}

template <typename X, unsigned int Dim>
Vec<X, Dim> Vec<X, Dim>::cat(Vec<X, Dim - 1> vec, X element)
{
    std::array<X, Dim> output;
    std::copy(vec.begin(), vec.end(), output.begin());
    output.back() = element;
    return Vec<X, Dim>(output);
}

template <typename X, unsigned int Dim>
Vec<X, Dim> Vec<X, Dim>::scale(X scalar, Vec<X, Dim> vec)
{
    Vec<X, Dim - 1> sub_vec = subVec(vec);
    Vec<X, Dim - 1> sub_vec_scaled = Vec<X, Dim - 1>::scale(scalar, sub_vec);
    return cat(sub_vec, scalar * vec.back());
}

template <typename X, unsigned int Dim>
Vec<X, Dim> Vec<X, Dim>::add(Vec<X, Dim> vec1, Vec<X, Dim> vec2)
{
    Vec<X, Dim - 1> sub_vec1 = subVec(vec1);
    Vec<X, Dim - 1> sub_vec2 = subVec(vec2);
    Vec<X, Dim - 1> sub_added = Vec<X, Dim - 1>::add(sub_vec1, sub_vec2);

    return cat(sub_added, vec1.back() + vec2.back());
}

//

template <typename X>
class Vec<X, 1>
{
private:
    const std::array<X, 1> arr;

public:
    Vec() = delete;
    Vec(std::array<X, 1> v) : arr(v) {}

    typename std::array<X, 1>::const_iterator begin() { return arr.begin(); }
    typename std::array<X, 1>::const_iterator end() { return arr.end(); }

    X back() const;
    static Vec<X, 0> subVec(Vec<X, 1> u);
    static Vec<X, 1> cat(Vec<X, 0> u, X e);

    static Vec<X, 1> scale(X s, Vec<X, 1> u);
    static Vec<X, 1> add(Vec<X, 1> u, Vec<X, 1> v);
};

template <typename X>
X Vec<X, 1>::back() const
{
    return arr.back();
}

template <typename X>
Vec<X, 0> Vec<X, 1>::subVec(Vec<X, 1> u)
{
    return {};
}


template <typename X>
Vec<X, 1> cat(Vec<X, 0> u, X e)
{
    return Vec<X, 1>(std::array<X, 1>{e});
}


template <typename X>
Vec<X, 1> Vec<X, 1>::scale(X scalar, Vec<X, 1> vec)
{
    return Vec<X, 1>(std::array<X, 1>{scalar * vec.back()});
}

template <typename X>
Vec<X, 1> Vec<X, 1>::add(Vec<X, 1> vec1, Vec<X, 1> vec2)
{
    return Vec<X, 1>(std::array<X, 1>{vec1.back() + vec2.back()});
}

///
///
///

template <typename T, unsigned int Dim>
class NVector
{
  protected:
    std::vector<NVector<T, Dim - 1>> internal_vec;

  public:
    NVector();
    NVector(const NVector &v) = delete;
    NVector(NVector &&v) : internal_vec(std::move(v.internal_vec)) { std::cout << "copy cons" << std::endl; }
    NVector& operator=(const NVector &v) = delete;
    NVector& operator=(NVector &&v) = delete;
    NVector<T, Dim - 1>& operator[](const typename std::vector<T>::size_type &i);
    T& getElement(std::array<typename std::vector<T>::size_type, Dim> coords);

    void resize(std::array<typename std::vector<T>::size_type, Dim> widths);
};

template <typename T, unsigned int Dim>
NVector<T, Dim>::NVector() 
{
    internal_vec = std::vector<NVector<T, Dim - 1>>();
}

template <typename T, unsigned int Dim>
void NVector<T, Dim>::resize(std::array<typename std::vector<T>::size_type, Dim> widths) 
{
    internal_vec.resize(widths.back());
    std::array<typename std::vector<T>::size_type, Dim - 1> sub_widths;
    std::copy(widths.begin(), widths.end() - 1, sub_widths.begin());
    for (NVector<T, Dim - 1>& nvec : internal_vec) 
    {
        nvec.resize(sub_widths);
    }
}

template <typename T, unsigned int Dim>
NVector<T, Dim - 1>& NVector<T, Dim>::operator[](const typename std::vector<T>::size_type &i)
{
    return internal_vec[i];
}

template <typename T, unsigned int Dim>
T& NVector<T, Dim>::getElement(std::array<typename std::vector<T>::size_type, Dim> coords)
{
    NVector<T, Dim - 1>& sub_nvec = internal_vec[coords.front()];
    std::array<typename std::vector<T>::size_type, Dim - 1> sub_coords;
    std::copy(coords.begin() + 1, coords.end(), sub_coords.begin());
    return sub_nvec.getElement(sub_coords);
}

/// 

template <typename T>
class NVector<T, 1>
{
    std::vector<T> internal_vec;

public:
    NVector();
    NVector(std::array<typename std::vector<T>::size_type, 1> width) { resize(width); }

    NVector(const NVector &v) = delete;
    NVector(NVector &&v) : internal_vec(std::move(v.internal_vec)) { std::cout << "copy cons 1d" << std::endl; }
    NVector& operator=(const NVector &v) = delete;
    NVector& operator=(NVector &&v) = delete;
    T& operator[](const typename std::vector<T>::size_type &i);
    T& getElement(std::array<typename std::vector<T>::size_type, 1> coords);

    void resize(std::array<typename std::vector<T>::size_type, 1> width);
    // std::vector<T&> wave(std::array<const typename std::vector<T>::size_type&, 1> v);
};

template <typename T>
NVector<T, 1>::NVector() 
{
    internal_vec = std::vector<T>();
}

template <typename T>
void NVector<T, 1>::resize(std::array<typename std::vector<T>::size_type, 1> width) 
{
    internal_vec.resize(width[0]);
}

template <typename T>
T& NVector<T, 1>::operator[](const typename std::vector<T>::size_type &i)
{
    return internal_vec[i];
}

template <typename T>
T& NVector<T, 1>::getElement(std::array<typename std::vector<T>::size_type, 1> coords)
{
    return internal_vec[coords[0]];
}