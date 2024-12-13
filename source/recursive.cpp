#include <vector>
#include <array>
#include <iostream>

///

template <typename X, unsigned int Dim>
class VecArrayR
{
private:
    const std::array<X, Dim> arr;
    
public:
    VecArrayR() = delete;
    VecArrayR(std::array<X, Dim> v) : arr(v) {}

    typename std::array<X, Dim>::const_iterator begin() { return arr.begin(); }
    typename std::array<X, Dim>::const_iterator end() { return arr.end(); }

    X back() const;
    static VecArrayR<X, Dim - 1> subVec(VecArrayR<X, Dim> u);
    static VecArrayR<X, Dim> cat(VecArrayR<X, Dim - 1> u, X e);

    static VecArrayR<X, Dim> scale(X s, VecArrayR<X, Dim> u);
    static VecArrayR<X, Dim> add(VecArrayR<X, Dim> u, VecArrayR<X, Dim> v);

    static std::array<X, Dim> toArray(VecArrayR<X, Dim> u);
    static std::string toString(VecArrayR<X, Dim> u);
};

template <typename X, unsigned int Dim>
X VecArrayR<X, Dim>::back() const
{
    return arr.back();
}

template <typename X, unsigned int Dim>
VecArrayR<X, Dim - 1> VecArrayR<X, Dim>::subVec(VecArrayR<X, Dim> vec)
{
    std::array<X, Dim - 1> sub_arr;
    std::copy(vec.begin(), vec.end() - 1, sub_arr.begin());
    return VecArrayR<X, Dim - 1>(sub_arr);
}

template <typename X, unsigned int Dim>
VecArrayR<X, Dim> VecArrayR<X, Dim>::cat(VecArrayR<X, Dim - 1> vec, X element)
{
    std::array<X, Dim> output;
    std::copy(vec.begin(), vec.end(), output.begin());
    output.back() = element;
    return VecArrayR<X, Dim>(output);
}

template <typename X, unsigned int Dim>
VecArrayR<X, Dim> VecArrayR<X, Dim>::scale(X scalar, VecArrayR<X, Dim> vec)
{
    VecArrayR<X, Dim - 1> sub_vec = subVec(vec);
    VecArrayR<X, Dim - 1> sub_vec_scaled = VecArrayR<X, Dim - 1>::scale(scalar, sub_vec);
    return cat(sub_vec, scalar * vec.back());
}

template <typename X, unsigned int Dim>
VecArrayR<X, Dim> VecArrayR<X, Dim>::add(VecArrayR<X, Dim> vec1, VecArrayR<X, Dim> vec2)
{
    VecArrayR<X, Dim - 1> sub_vec1 = subVec(vec1);
    VecArrayR<X, Dim - 1> sub_vec2 = subVec(vec2);
    VecArrayR<X, Dim - 1> sub_added = VecArrayR<X, Dim - 1>::add(sub_vec1, sub_vec2);

    return cat(sub_added, vec1.back() + vec2.back());
}

template <typename X, unsigned int Dim> 
std::array<X, Dim> VecArrayR<X, Dim>::toArray(VecArrayR<X, Dim> u)
{
    return u.arr;
}

template <typename X, unsigned int Dim>
std::string VecArrayR<X, Dim>::toString(VecArrayR<X, Dim> u) {
    std::string result = "[";
    auto it = u.arr.begin();
    if (it != u.arr.end()) {
        result += std::to_string(*it);
        ++it;
    }
    for (; it != u.arr.end(); ++it) {
        result += ", " + std::to_string(*it);
    }
    result += "]";
    return result;
}


//

template <typename X>
class VecArrayR<X, 1>
{
private:
    const std::array<X, 1> arr;

public:
    VecArrayR() = delete;
    VecArrayR(std::array<X, 1> v) : arr(v) {}

    typename std::array<X, 1>::const_iterator begin() { return arr.begin(); }
    typename std::array<X, 1>::const_iterator end() { return arr.end(); }

    X back() const;
    static VecArrayR<X, 0> subVec(VecArrayR<X, 1> u);
    static VecArrayR<X, 1> cat(VecArrayR<X, 0> u, X e);

    static VecArrayR<X, 1> scale(X s, VecArrayR<X, 1> u);
    static VecArrayR<X, 1> add(VecArrayR<X, 1> u, VecArrayR<X, 1> v);

    static std::array<X, 1> toArray(VecArrayR<X, 1> u);
    static std::string toString(VecArrayR<X, 1> u);
};

template <typename X>
X VecArrayR<X, 1>::back() const
{
    return arr.back();
}

template <typename X>
VecArrayR<X, 0> VecArrayR<X, 1>::subVec(VecArrayR<X, 1> u)
{
    return {};
}


template <typename X>
VecArrayR<X, 1> cat(VecArrayR<X, 0> u, X e)
{
    return VecArrayR<X, 1>(std::array<X, 1>{e});
}


template <typename X>
VecArrayR<X, 1> VecArrayR<X, 1>::scale(X scalar, VecArrayR<X, 1> vec)
{
    return VecArrayR<X, 1>(std::array<X, 1>{scalar * vec.back()});
}

template <typename X>
VecArrayR<X, 1> VecArrayR<X, 1>::add(VecArrayR<X, 1> vec1, VecArrayR<X, 1> vec2)
{
    return VecArrayR<X, 1>(std::array<X, 1>{vec1.back() + vec2.back()});
}

template <typename X> 
std::array<X, 1> VecArrayR<X, 1>::toArray(VecArrayR<X, 1> u)
{
    return u.arr;
}

template <typename X>
std::string VecArrayR<X, 1>::toString(VecArrayR<X, 1> u) {
    return "[" + std::to_string(u.back()) + "]";
}

///
///
///

template <typename T, unsigned int Dim, typename Index>
class NVector
{
  protected:
    std::vector<NVector<T, Dim - 1, Index>> internal_vec;

  public:
    NVector();
    NVector(const NVector &v) = delete;
    NVector(NVector &&v) : internal_vec(std::move(v.internal_vec)) { std::cout << "copy cons" << std::endl; }
    NVector& operator=(const NVector &v) = delete;
    NVector& operator=(NVector &&v) = delete;
    NVector<T, Dim - 1, Index>& operator[](const Index &i);
    T& getElement(std::array<Index, Dim> coords);
    void putElement(std::array<Index, Dim> coords, const T& el);

    void resize(std::array<Index, Dim> widths);
};

template <typename T, unsigned int Dim, typename Index>
NVector<T, Dim, Index>::NVector() 
{
    internal_vec = std::vector<NVector<T, Dim - 1, Index>>();
}

template <typename T, unsigned int Dim, typename Index>
void NVector<T, Dim, Index>::resize(std::array<Index, Dim> widths) 
{
    if(widths.back() >= internal_vec.size()) {
        internal_vec.resize(widths.back() + 1);
    }
    std::array<Index, Dim - 1> sub_widths;
    std::copy(widths.begin(), widths.end() - 1, sub_widths.begin());
    for (NVector<T, Dim - 1, Index>& nvec : internal_vec) 
    {
        nvec.resize(sub_widths);
    }
}

template <typename T, unsigned int Dim, typename Index>
NVector<T, Dim - 1, Index>& NVector<T, Dim, Index>::operator[](const Index &i)
{
    return internal_vec[i];
}

template <typename T, unsigned int Dim, typename Index>
T& NVector<T, Dim, Index>::getElement(std::array<Index, Dim> coords)
{
    NVector<T, Dim - 1, Index>& sub_nvec = internal_vec[coords.front()];
    std::array<Index, Dim - 1> sub_coords;
    std::copy(coords.begin() + 1, coords.end(), sub_coords.begin());
    return sub_nvec.getElement(sub_coords);
}

template <typename T, unsigned int Dim, typename Index>
void NVector<T, Dim, Index>::putElement(std::array<Index, Dim> coords, const T& el)
{
    resize(coords);
    NVector<T, Dim - 1, Index>& sub_nvec = internal_vec[coords.front()];
    std::array<Index, Dim - 1> sub_coords;
    std::copy(coords.begin() + 1, coords.end(), sub_coords.begin());
    return sub_nvec.putElement(sub_coords, el);
}

/// 

template <typename T, typename Index>
class NVector<T, 1, Index>
{
    std::vector<T> internal_vec;

public:
    NVector();
    NVector(std::array<Index, 1> width) { resize(width); }

    NVector(const NVector &v) = delete;
    NVector(NVector &&v) : internal_vec(std::move(v.internal_vec)) { std::cout << "copy cons 1d" << std::endl; }
    NVector& operator=(const NVector &v) = delete;
    NVector& operator=(NVector &&v) = delete;
    T& operator[](const Index &i);
    T& getElement(std::array<Index, 1> coords);
    void putElement(std::array<Index, 1> coords, const T& el);

    void resize(std::array<Index, 1> width);
    // std::vector<T&> wave(std::array<const Index&, 1> v);
};

template <typename T, typename Index>
NVector<T, 1, Index>::NVector() 
{
    internal_vec = std::vector<T>();
}

template <typename T, typename Index>
void NVector<T, 1, Index>::resize(std::array<Index, 1> width) 
{
    if(width[0] >= internal_vec.size()) {
        internal_vec.resize(width[0] + 1);
    }
}

template <typename T, typename Index>
T& NVector<T, 1, Index>::operator[](const Index &i)
{
    return internal_vec[i];
}

template <typename T, typename Index>
T& NVector<T, 1, Index>::getElement(std::array<Index, 1> coords)
{
    return internal_vec[coords[0]];
}

template <typename T, typename Index>
void NVector<T, 1, Index>::putElement(std::array<Index, 1> coords, const T &el)
{
    resize(coords);
    internal_vec[coords[0]] = el;
}
