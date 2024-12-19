#include <vector>
#include <unordered_map>


template <typename X, unsigned int D, typename I = unsigned int>
class MyArray
{
private:
    std::array<X, D> internal_arr;

public:
    MyArray() : internal_arr() {}
    MyArray(std::array<X, D> arr) : internal_arr(arr) {}

    void add(const MyArray<X, D, I>& arr2);
    void scale(const X& scalar);

    I size() { return internal_arr.size(); }

    X front() { return getElement(0); }
    X back() { return getElement(size() - 1); }
    typename std::array<X, D>::iterator begin() { return internal_arr.begin(); }
    typename std::array<X, D>::iterator end() { return internal_arr.end(); }

    X& operator[](const I& i);
    X getElement(const I& i) const;
    bool operator==(const MyArray<X, D, I>& arr);
};

template <typename X, unsigned int D, typename I>
X& MyArray<X, D, I>::operator[](const I& i)
{
    return internal_arr[i];
}

template <typename X, unsigned int D, typename I>
X MyArray<X, D, I>::getElement(const I& i) const
{
    return internal_arr[i];
}

template <typename X, unsigned int D, typename I>
bool MyArray<X, D, I>::operator==(const MyArray<X, D, I>& arr) {
    for (I i = 0; i < internal_arr.size(); i++)
    {
        if (internal_arr[i] != arr.getElement(i))
        {
            return false;
        }
    }
    return true;
}

template <typename X, unsigned int D, typename I>
void MyArray<X, D, I>::add(const MyArray<X, D, I>& arr2) {
    for (I i = 0; i < internal_arr.size(); i++)
    {
        internal_arr[i] += arr2.getElement(i);
    }
}

template <typename X, unsigned int D, typename I>
void MyArray<X, D, I>::scale(const X& scalar)
{
    for (I i = 0; i < internal_arr.size(); i++)
    {
        internal_arr[i] *= scalar;
    }
}

template <typename T, unsigned int Dim, typename Index>
class DimensionalArray
{
protected:
    std::vector<DimensionalArray<T, Dim - 1, Index>> internal_vec;
    MyArray<Index, Dim> dimensions;

    void setDimensions(MyArray<Index, Dim> dims);

    template<unsigned int D>
    T& getElement(MyArray<Index, D> coords, const Index& idx);
    template<unsigned int D>
    void putElement(MyArray<Index, D> coords, const T& el, const Index& idx);

public:
    DimensionalArray() : internal_vec(), dimensions() {}
    DimensionalArray(MyArray<Index, Dim> dims);
    DimensionalArray(const DimensionalArray& v) = delete;
    DimensionalArray(DimensionalArray&& v) : internal_vec(std::move(v.internal_vec)), dimensions(v.dimensions) {}

    DimensionalArray& operator=(const DimensionalArray& v) = delete;
    DimensionalArray& operator=(DimensionalArray&& v) = delete;

    T& getElement(MyArray<Index, Dim> coords);
    void putElement(MyArray<Index, Dim> coords, const T& el);
    bool isInBounds(MyArray<Index, Dim> coords);

    // Want to only expose this to other DimensionalArrays
    template<typename U, unsigned int D, typename I>
    friend class DimensionalArray;
};

template <typename T, unsigned int Dim, typename Index>
void DimensionalArray<T, Dim, Index>::setDimensions(MyArray<Index, Dim> dims)
{
    internal_vec.resize(dims.front());
    dimensions = dims;
    MyArray<Index, Dim - 1> sub_dims;
    std::copy(dims.begin() + 1, dims.end(), sub_dims.begin());
    for (DimensionalArray<T, Dim - 1, Index>& narr : internal_vec)
    {
        narr.setDimensions(sub_dims);
    }
}

template <typename T, unsigned int Dim, typename Index>
DimensionalArray<T, Dim, Index>::DimensionalArray(MyArray<Index, Dim> dims)
{
    setDimensions(dims);
}

template <typename T, unsigned int Dim, typename Index>
template <unsigned int D>
T& DimensionalArray<T, Dim, Index>::getElement(MyArray<Index, D> coords, const Index& idx)
{
    return internal_vec[coords[idx]].getElement(coords, idx + 1);
}

template <typename T, unsigned int Dim, typename Index>
T& DimensionalArray<T, Dim, Index>::getElement(MyArray<Index, Dim> coords)
{
    if (!isInBounds(coords))
    {
        throw std::invalid_argument("Coordinates out of bounds");
    }
    return getElement(coords, 0);
}

template <typename T, unsigned int Dim, typename Index>
template <unsigned int D>
void DimensionalArray<T, Dim, Index>::putElement(MyArray<Index, D> coords, const T& el, const Index& idx)
{
    return internal_vec[coords[idx]].putElement(coords, el, idx + 1);
}

template <typename T, unsigned int Dim, typename Index>
void DimensionalArray<T, Dim, Index>::putElement(MyArray<Index, Dim> coords, const T& el)
{
    if (!isInBounds(coords))
    {
        throw std::invalid_argument("Coordinates out of bounds");
    }
    return putElement(coords, el, 0);
}

template <typename T, unsigned int Dim, typename Index>
bool DimensionalArray<T, Dim, Index>::isInBounds(MyArray<Index, Dim> coords)
{
    if (coords.size() != dimensions.size())
    {
        return false;
    }
    for (Index i = 0; i < coords.size(); i++)
    {
        if (coords[i] >= dimensions[i])
        {
            return false;
        }
    }
    return true;
}

/// 

template <typename T, typename Index>
class DimensionalArray<T, 1, Index>
{
protected:
    std::vector<T> internal_vec;
    MyArray<Index, 1> dimensions;

    void setDimensions(MyArray<Index, 1> dims);

    template <unsigned int D>
    T& getElement(MyArray<Index, D> coords, const Index& idx);
    template <unsigned int D>
    void putElement(MyArray<Index, D> coords, const T& el, const Index& idx);

public:
    DimensionalArray() : internal_vec(), dimensions() {}
    DimensionalArray(MyArray<Index, 1> dims);
    DimensionalArray(const DimensionalArray& v) = delete;
    DimensionalArray(DimensionalArray&& v) : internal_vec(std::move(v.internal_vec)), dimensions(v.dimensions) {}

    DimensionalArray& operator=(const DimensionalArray& v) = delete;
    DimensionalArray& operator=(DimensionalArray&& v) = delete;

    T& getElement(MyArray<Index, 1> coords);
    void putElement(MyArray<Index, 1> coords, const T& el);
    bool isInBounds(MyArray<Index, 1> coords);

    // Want to only expose this to other DimensionalArrays
    template<typename U, unsigned int D, typename I>
    friend class DimensionalArray;
};

template <typename T, typename Index>
void DimensionalArray<T, 1, Index>::setDimensions(MyArray<Index, 1> dims)
{
    internal_vec.resize(dims.front());
    dimensions = dims;
}

template <typename T, typename Index>
DimensionalArray<T, 1, Index>::DimensionalArray(MyArray<Index, 1> dims)
{
    setDimensions(dims);
}

template <typename T, typename Index>
template <unsigned int D>
T& DimensionalArray<T, 1, Index>::getElement(MyArray<Index, D>  coords, const Index& idx)
{
    return internal_vec[coords[idx]];
}

template <typename T, typename Index>
T& DimensionalArray<T, 1, Index>::getElement(MyArray<Index, 1>  coords)
{
    if (!isInBounds(coords))
    {
        throw std::invalid_argument("Coordinates out of bounds");
    }
    return getElement(coords, 0);
}

template <typename T, typename Index>
template <unsigned int D>
void DimensionalArray<T, 1, Index>::putElement(MyArray<Index, D>  coords, const T& el, const Index& idx)
{
    internal_vec[coords[idx]] = el;
}

template <typename T, typename Index>
void DimensionalArray<T, 1, Index>::putElement(MyArray<Index, 1> coords, const T& el)
{
    if (!isInBounds(coords))
    {
        throw std::invalid_argument("Coordinates out of bounds");
    }
    return putElement(coords, el, 0);
}

template <typename T, typename Index>
bool DimensionalArray<T, 1, Index>::isInBounds(MyArray<Index, 1> coords)
{
    if (coords.size() != dimensions.size())
    {
        return false;
    }
    for (Index i = 0; i < coords.size(); i++)
    {
        if (coords[i] >= dimensions[i])
        {
            return false;
        }
    }
    return true;
}

///

template <typename BaseEntity, unsigned int Dim>
class TileEntity
{
    using Id = unsigned long;
    using BaseEntityPtr = std::unique_ptr<BaseEntity>;
    using Coords = MyArray<Id, Dim>;

    const Id id;
    BaseEntityPtr internal_entity;
    Coords coords;

public:
    TileEntity(Id i, BaseEntityPtr e, Coords c) : id(i), internal_entity(std::move(e)), coords(c) {}
    Id getId() { return id; }
    BaseEntityPtr getInternalEntity() { return internal_entity; }
    Coords getCoords() { return coords; }
    void setCoords(Coords new_coords) { coords = new_coords; }
};

///

template <typename BaseEntity, unsigned int Dim>
class TileGrid {
    using EngineEntity = TileEntity<BaseEntity, Dim>;
    using SharedEntityPtr = std::shared_ptr<EngineEntity>;
    using WeakEntityPtr = std::weak_ptr<EngineEntity>;

    using Id = unsigned long;
    using Coords = MyArray<Id, Dim>;
    using Tile = std::unordered_map<Id, WeakEntityPtr>;

private:
    DimensionalArray<Tile, Dim, Id> world;

public:
    TileGrid() : world() {}
    TileGrid(Coords widths) : world(widths) {}

    void put(const WeakEntityPtr& weak_e_ptr);
    void remove(const WeakEntityPtr& to_despawn);
    Tile getTile(Coords coords);

    bool isInBounds(Coords coords);
};

template <typename BaseEntity, unsigned int Dim>
void TileGrid<BaseEntity, Dim>::put(const WeakEntityPtr& weak_e_ptr) {
    if (SharedEntityPtr e_ptr = weak_e_ptr.lock())
    {
        world.getElement(e_ptr->getCoords())[e_ptr->getId()] = weak_e_ptr;
    }
}

template <typename BaseEntity, unsigned int Dim>
void TileGrid<BaseEntity, Dim>::remove(const WeakEntityPtr& to_despawn) {
    if (SharedEntityPtr e_ptr = to_despawn.lock())
    {
        world.getElement(e_ptr->getCoords()).erase(e_ptr->getId());
    }
}

template <typename BaseEntity, unsigned int Dim>
std::unordered_map<unsigned long, std::weak_ptr<TileEntity<BaseEntity, Dim>>> TileGrid<BaseEntity, Dim>::getTile(Coords coords)
{
    return world.getElement(coords);
}

template <typename BaseEntity, unsigned int Dim>
bool TileGrid<BaseEntity, Dim>::isInBounds(Coords coords)
{
    return world.isInBounds(coords);
}


///
///
///

template <typename BaseEntity, unsigned int Dim>
class TileEngine
{
    using EngineEntity = TileEntity<BaseEntity, Dim>;
    using SharedEntityPtr = std::shared_ptr<EngineEntity>;
    using WeakEntityPtr = std::weak_ptr<EngineEntity>;

    using Id = unsigned long;
    using BaseEntityPtr = std::unique_ptr<BaseEntity>;
    using Coords = MyArray<Id, Dim>;
    using Tile = std::unordered_map<Id, WeakEntityPtr>;
    using WeakTile = std::unordered_map<Id, WeakEntityPtr>;
    using World = TileGrid<BaseEntity, Dim>;

private:
    SharedEntityPtr createEntity(const BaseEntity& e, Coords loc);

protected:
    World world;
    Id max_id;
    std::unordered_map<Id, SharedEntityPtr> entities;

public:
    TileEngine() : world(), max_id(), entities() {}
    TileEngine(Coords widths) : world(widths), max_id(), entities() {}

    Id spawn(const BaseEntity& new_entity, const Coords loc = std::vector<unsigned long>(Dim));
    void despawn(const Id& id);

    void moveEntityBy(const Id id, Coords displacement);
    void moveEntityTo(const Id id, Coords new_coords);

    WeakEntityPtr getEntity(const Id id);
    WeakTile getEntitiesAt(Coords coords) { return world.getTile(coords); }
};

template <typename BaseEntity, unsigned int Dim>
std::shared_ptr<TileEntity<BaseEntity, Dim>> TileEngine<BaseEntity, Dim>::createEntity(const BaseEntity& entity, Coords loc)
{
    BaseEntityPtr base_ptr(new BaseEntity(entity));
    return std::make_shared<EngineEntity>(max_id++, std::move(base_ptr), loc);
}

template <typename BaseEntity, unsigned int Dim>
typename TileEngine<BaseEntity, Dim>::Id TileEngine<BaseEntity, Dim>::spawn(const BaseEntity& new_entity, const Coords loc)
{
    SharedEntityPtr e_ptr = createEntity(new_entity, loc);
    Id id = e_ptr->getId();
    entities[id] = e_ptr;
    world.put(e_ptr);
    return id;
}

template <typename BaseEntity, unsigned int Dim>
void TileEngine<BaseEntity, Dim>::despawn(const Id& id)
{
    world.remove(entities[id]);
    entities.erase(id);
}

template <typename BaseEntity, unsigned int Dim>
void TileEngine<BaseEntity, Dim>::moveEntityBy(const Id id, Coords displacement)
{
    displacement.add(entities[id]->getCoords());
    moveEntityTo(id, displacement);
}

template <typename BaseEntity, unsigned int Dim>
void TileEngine<BaseEntity, Dim>::moveEntityTo(const Id id, Coords new_coords)
{
    if (!world.isInBounds(new_coords))
    {
        throw std::invalid_argument("Coordinates out of bounds");
    }
    SharedEntityPtr to_move = entities[id];
    world.remove(to_move);
    to_move->setCoords(new_coords);
    world.put(to_move);
}

template <typename BaseEntity, unsigned int Dim>
std::weak_ptr<TileEntity<BaseEntity, Dim>> TileEngine<BaseEntity, Dim>::getEntity(const Id id)
{
    return entities[id];
}

///
///
///

