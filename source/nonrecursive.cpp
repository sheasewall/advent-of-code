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

template <typename EntityType, unsigned int Dim, typename Index = unsigned long>
struct PointEntity
{
    EntityType entity;
    MyArray<Index, Dim> coords;
};

template <typename PointEntity, typename Id = unsigned long>
struct HashedEntity
{
    Id id;
    PointEntity point_entity;

    HashedEntity(Id _id, PointEntity e) : id(_id), point_entity(e) {}
};

///

template <typename T, unsigned int Dim, typename Index = unsigned long>
class CellGrid2 {
    using DiscreteEntity = HashedEntity<PointEntity<T, Dim, Index>, Index>;
    using WeakEntityPtr = std::weak_ptr<DiscreteEntity>;
    using Coords = MyArray<Index, Dim>;
    using Cell = std::unordered_map<Index, WeakEntityPtr>;

private:
    DimensionalArray<Cell, Dim, Index> world;

public:
    CellGrid2() : world() {}
    CellGrid2(Coords widths) : world(widths) {}

    void spawn(const WeakEntityPtr& weak_e_ptr);
    void despawn(const WeakEntityPtr& to_despawn);
    Cell getCell(Coords coords);

    bool isInBounds(Coords coords);
};

template<unsigned int Dim, typename Index>
std::vector<Index> toVec(MyArray<Index, Dim> arr)
{
    std::vector<Index> vec;
    for (Index i : arr)
    {
        vec.push_back(i);
    }
    return vec;
}

template <typename T, unsigned int Dim, typename Index>
void CellGrid2<T, Dim, Index>::spawn(const WeakEntityPtr& weak_e_ptr) {
    if (std::shared_ptr<DiscreteEntity> e_ptr = weak_e_ptr.lock())
    {
        world.getElement(e_ptr->point_entity.coords)[e_ptr->id] = weak_e_ptr;
    }
}

template <typename T, unsigned int Dim, typename Index>
void CellGrid2<T, Dim, Index>::despawn(const WeakEntityPtr& to_despawn) {
    if (std::shared_ptr<DiscreteEntity> e_ptr = to_despawn.lock())
    {
        world.getElement(e_ptr->point_entity.coords).erase(e_ptr->id);
    }
}

template <typename T, unsigned int Dim, typename Index>
std::unordered_map<Index, std::weak_ptr<HashedEntity<PointEntity<T, Dim, Index>, Index>>>
CellGrid2<T, Dim, Index>::getCell(Coords coords)
{
    return world.getElement(coords);
}

template <typename E, unsigned int Dim, typename Index>
bool CellGrid2<E, Dim, Index>::isInBounds(Coords coords)
{
    return world.isInBounds(coords);
}


///
///
///

template <typename T, unsigned int Dim, typename Index = unsigned long>
class DiscreteUnorderedEngine2
{
    using DiscreteEntity = PointEntity<T, Dim, Index>;
    using HashEntity = HashedEntity<DiscreteEntity, Index>;
    using EntityPtr = std::shared_ptr<HashEntity>;
    using WeakEntityPtr = std::weak_ptr<HashEntity>;
    using Coords = MyArray<Index, Dim>;
    using World = CellGrid2<T, Dim, Index>;
    using Cell = std::unordered_map<Index, EntityPtr>;
    using WeakCell = std::unordered_map<Index, WeakEntityPtr>;

private:
    World world;
    Index max_id;
    std::unordered_map<Index, EntityPtr> entities;
    std::unordered_map<T, std::unordered_map<Index, WeakEntityPtr>> entities_by_type;

public:
    DiscreteUnorderedEngine2() : world(), max_id(), entities(), entities_by_type() {}
    DiscreteUnorderedEngine2(World _world) : world(_world), max_id(), entities(), entities_by_type() {}
    DiscreteUnorderedEngine2(Coords widths) : world(widths), max_id(), entities(), entities_by_type() {}

    Index spawn(const DiscreteEntity& entity);
    void despawn(const HashEntity& entity);
    void despawn(const Index& id);

    void moveEntityBy(const Index id, Coords displacement);
    void moveEntityTo(const Index id, Coords new_coords);

    // for testing
    std::unordered_map<Index, EntityPtr> getEntities() { return entities; }

    WeakEntityPtr getEntity(const Index id);
    WeakCell getEntitiesAt(Coords coords) { return world.getCell(coords); }
    WeakCell getEntitiesOf(const T& entity_type);
};

template <typename E, unsigned int Dim, typename Index>
Index DiscreteUnorderedEngine2<E, Dim, Index>::spawn(const DiscreteEntity& entity) {
    HashEntity hashed = HashEntity(max_id, entity);
    max_id++;
    EntityPtr e_ptr = std::make_shared<HashEntity>(hashed);
    entities[hashed.id] = e_ptr;
    WeakEntityPtr weak_e_ptr = WeakEntityPtr(e_ptr);
    entities_by_type[hashed.point_entity.entity][hashed.id] = weak_e_ptr;
    world.spawn(weak_e_ptr);
    return hashed.id;
}

template <typename T, unsigned int Dim, typename Index>
std::weak_ptr<HashedEntity<PointEntity<T, Dim, Index>, Index>> DiscreteUnorderedEngine2<T, Dim, Index>::getEntity(const Index id) {
    return WeakEntityPtr(entities[id]);
}

template <typename T, unsigned int Dim, typename Index>
void DiscreteUnorderedEngine2<T, Dim, Index>::despawn(const HashEntity& to_despawn)
{
    world.despawn(entities[to_despawn.id]);
    entities.erase(to_despawn.id);
    entities_by_type[to_despawn.point_entity.entity].erase(to_despawn.id);
}

template <typename T, unsigned int Dim, typename Index>
void DiscreteUnorderedEngine2<T, Dim, Index>::despawn(const Index& id)
{
    EntityPtr to_despawn = entities[id];
    despawn(*to_despawn);
}

template <typename T, unsigned int Dim, typename Index>
std::unordered_map<Index, std::weak_ptr<HashedEntity<PointEntity<T, Dim, Index>, Index>>> DiscreteUnorderedEngine2<T, Dim, Index>::getEntitiesOf(const T& entity_type) {
    return entities_by_type[entity_type];
}

template <typename T, unsigned int Dim, typename Index>
void DiscreteUnorderedEngine2<T, Dim, Index>::moveEntityBy(const Index id, Coords displacement)
{
    displacement.add(entities[id]->point_entity.coords);
    moveEntityTo(id, displacement);
}

template <typename T, unsigned int Dim, typename Index>
void DiscreteUnorderedEngine2<T, Dim, Index>::moveEntityTo(const Index id, Coords new_coords)
{
    if (!world.isInBounds(new_coords))
    {
        throw std::invalid_argument("Coordinates out of bounds");
    }
    EntityPtr to_move = entities[id];
    world.despawn(to_move);
    to_move->point_entity.coords = new_coords;
    world.spawn(to_move);
}

///