#include <vector>

template <typename X, unsigned int D, typename I = unsigned int>
class Array
{
private:
    std::array<X, D> internal_arr;

public:
    Array() : internal_arr() {}
    Array(std::array<X, D> arr) : internal_arr(arr) {}

    void add(const Array<X, D, I>& arr2);
    void scale(const X& scalar);

    I size() { return internal_arr.size(); }

    X front() { return getElement(0); }
    X back() { return getElement(size() - 1); }
    typename std::array<X, D>::iterator begin() { return internal_arr.begin(); }
    typename std::array<X, D>::iterator end() { return internal_arr.end(); }

    X& operator[](const I& i);
    X getElement(const I& i) const;
    bool operator==(const Array<X, D, I>& arr);
};

template <typename X, unsigned int D, typename I>
X& Array<X, D, I>::operator[](const I& i) 
{
    return internal_arr[i];
}

template <typename X, unsigned int D, typename I>
X Array<X, D, I>::getElement(const I& i) const 
{
    return internal_arr[i];
}

template <typename X, unsigned int D, typename I>
bool Array<X, D, I>::operator==(const Array<X, D, I>& arr) {
    bool matches = true;
    for (I i = 0; i < internal_arr.size(); i++)
    {
        matches = (internal_arr[i] == arr.getElement(i));
    }
    return matches;
}

template <typename X, unsigned int D, typename I>
void Array<X, D, I>::add(const Array<X, D, I>& arr2) {
    for (I i = 0; i < internal_arr.size(); i++)
    {
        internal_arr[i] += arr2.getElement(i);
    }
}

template <typename X, unsigned int D, typename I>
void Array<X, D, I>::scale(const X& scalar)  
{
    for (I i = 0; i < internal_arr.size(); i++)
    {
        internal_arr[i] *= scalar;
    }
}

////

template <typename T, unsigned int Dim, typename Index> 
class NArray
{
  protected:
    std::vector<NArray<T, Dim - 1, Index>> internal_vec;
    void resize(Array<Index, Dim> widths);

  public:
    NArray();
    NArray(Array<Index, Dim> widths);
    NArray(const NArray &v) = delete;
    NArray(NArray &&v) : internal_vec(std::move(v.internal_vec))
    {
    }
    NArray &operator=(const NArray &v) = delete;
    NArray &operator=(NArray &&v) = delete;
    NArray<T, Dim - 1, Index> &operator[](const Index &i);
    T &getElement(Array<Index, Dim> coords);
    bool putElement(Array<Index, Dim> coords, const T &el);

    // Want to only expose this to other NArrays
    template<typename U, unsigned int D, typename I>
    friend class NArray;
};

template <typename T, unsigned int Dim, typename Index> 
NArray<T, Dim, Index>::NArray()
{
    internal_vec = std::vector<NArray<T, Dim - 1, Index>>();
}

template <typename T, unsigned int Dim, typename Index> 
NArray<T, Dim, Index>::NArray(Array<Index, Dim> widths)
{
    resize(widths);
}

template <typename T, unsigned int Dim, typename Index> 
void NArray<T, Dim, Index>::resize(Array<Index, Dim> widths)
{
    if(widths.front() >= internal_vec.size()) {
        internal_vec.resize(widths.front() + 1);
    }
    Array<Index, Dim - 1> sub_widths;
    std::copy(widths.begin() + 1, widths.end(), sub_widths.begin());
    for (NArray<T, Dim - 1, Index>& narr : internal_vec) 
    { 
        narr.resize(sub_widths);
    }
}

template <typename T, unsigned int Dim, typename Index>
NArray<T, Dim - 1, Index> &NArray<T, Dim, Index>::operator[](const Index &i)
{
    if (i < 0)
    {
        std::throw_with_nested(std::out_of_range("Index was too low"));
    }
    if (i >= internal_vec.size())
    {
        std::throw_with_nested(std::out_of_range("Index was too high"));
    }
    return internal_vec[i];
}

template <typename T, unsigned int Dim, typename Index>
T& NArray<T, Dim, Index>::getElement(Array<Index, Dim> coords)
{
    if (coords.front() >= internal_vec.size())
    {
        std::throw_with_nested(std::out_of_range("Index was too high"));
    }
    NArray<T, Dim - 1, Index> &sub_nvec = internal_vec[coords.front()];
    Array<Index, Dim - 1> sub_coords;
    std::copy(coords.begin() + 1, coords.end(), sub_coords.begin());
    return sub_nvec.getElement(sub_coords);
}

template <typename T, unsigned int Dim, typename Index>
bool NArray<T, Dim, Index>::putElement(Array<Index, Dim> coords, const T &el)
{
    if (coords.front() >= internal_vec.size())
    {
        return false;
    }
    NArray<T, Dim - 1, Index> &sub_nvec = internal_vec[coords.front()];
    Array<Index, Dim - 1> sub_coords;
    std::copy(coords.begin() + 1, coords.end(), sub_coords.begin());
    return sub_nvec.putElement(sub_coords, el);
}

///

template <typename T, typename Index> 
class NArray<T, 1, Index>
{
  protected:
    std::vector<T> internal_vec;
    void resize(Array<Index, 1> width);

  public:
    NArray();
    NArray(Array<Index, 1> width);
    NArray(const NArray &v) = delete;
    NArray(NArray &&v) : internal_vec(std::move(v.internal_vec))
    {
    }
    NArray &operator=(const NArray &v) = delete;
    NArray &operator=(NArray &&v) = delete;
    T &operator[](const Index &i);
    T &getElement(Array<Index, 1> coords);
    bool putElement(Array<Index, 1> coords, const T &el);

    // Want to only expose this to other NArrays
    template<typename U, unsigned int D, typename I>
    friend class NArray;
};

template <typename T, typename Index> NArray<T, 1, Index>::NArray()
{
    internal_vec = std::vector<T>();
}

template <typename T, typename Index> NArray<T, 1, Index>::NArray(Array<Index, 1> width)
{
    internal_vec = std::vector<T>(); // necessary?
    internal_vec.resize(width[0]);
}

template <typename T, typename Index> 
void NArray<T, 1, Index>::resize(Array<Index, 1> width)
{
    if (width[0] < internal_vec.size())
    {
        return;
    }
    internal_vec.resize(width[0] + 1);
}

template <typename T, typename Index>
T& NArray<T, 1, Index>::operator[](const Index &i)
{
    if (i < 0)
    {
        std::throw_with_nested(std::out_of_range("Index was too low"));
    }
    if (i >= internal_vec.size())
    {
        std::throw_with_nested(std::out_of_range("Index was too high"));
    }
    return internal_vec[i];
}

template <typename T, typename Index> 
T& NArray<T, 1, Index>::getElement(Array<Index, 1> coords)
{
    if (coords[0] + 1 > internal_vec.size())
    {
        std::throw_with_nested(std::out_of_range("Index was too high"));
    }
    return internal_vec[coords[0]];
}

template <typename T, typename Index> 
bool NArray<T, 1, Index>::putElement(Array<Index, 1> coords, const T &el)
{
    if (coords[0] + 1 > internal_vec.size())
    {
        return false;
    }
    internal_vec[coords[0]] = el;
    return true;
}

///

template <typename EntityType, unsigned int Dim, typename Index = unsigned long>
struct Entity
{
    EntityType entity;
    Array<Index, Dim> coords;
};

template <typename E, unsigned int Dim, typename Index = unsigned long>
class DiscreteWorld
{
    using DiscreteEntity = Entity<E, Dim, Index>;
    using Coords = Array<Index, Dim>;
private:
    NArray<std::vector<DiscreteEntity>, Dim, Index> world;
    std::vector<Coords> entity_coords;

public:
    DiscreteWorld() : world(), entity_coords() {}
    DiscreteWorld(Coords widths) : world(widths), entity_coords() {}

    void spawn(DiscreteEntity& entity);
    std::vector<DiscreteEntity>& getEntitiesAt(Coords coords);
    std::vector<DiscreteEntity> getEntitiesOf(const E& entity_type);
};

template <typename E, unsigned int Dim, typename Index>
void DiscreteWorld<E, Dim, Index>::spawn(DiscreteEntity& entity) 
{
    entity_coords.push_back(entity.coords);
    std::vector<DiscreteEntity>& entities_at_coords = world.getElement(entity.coords);
    entities_at_coords.push_back(entity);
}

template <typename E, unsigned int Dim, typename Index>
std::vector<Entity<E, Dim, Index>>& DiscreteWorld<E, Dim, Index>::getEntitiesAt(Coords coords) 
{
    return world.getElement(coords);
}

template <typename E, unsigned int Dim, typename Index>
std::vector<Entity<E, Dim, Index>> DiscreteWorld<E, Dim, Index>::getEntitiesOf(const E& entity_type) {
    std::vector<DiscreteEntity> entities_of;
    for (Coords coords : entity_coords)
    {
        std::vector<DiscreteEntity>& entities = getEntitiesAt(coords);
        for (DiscreteEntity e : entities)
        {
            if (e.entity == entity_type)
            {
                entities_of.push_back(e);
            }
        }
    }
    return entities_of;
}

/////
////

template <typename E, unsigned int Dim, typename Index = unsigned long>
class DiscretePtrWorld {
    using DiscreteEntity = Entity<E, Dim, Index>;
    using EntityPtr = std::shared_ptr<DiscreteEntity>;
    using Coords = Array<Index, Dim>;
private:
    NArray<std::vector<EntityPtr>, Dim, Index> world; 
    std::vector<Coords> entity_coords;

public:
    DiscretePtrWorld() : world(), entity_coords() {}
    DiscretePtrWorld(Coords widths) : world(widths), entity_coords() {}

    void spawn(const EntityPtr& entity);
    std::vector<EntityPtr> getEntitiesAt(Coords coords);
    std::vector<EntityPtr> getEntitiesOf(const E& entity_type);
};

template <typename E, unsigned int Dim, typename Index>
void DiscretePtrWorld<E, Dim, Index>::spawn(const EntityPtr& entity) {
    entity_coords.push_back(entity->coords);
    std::vector<EntityPtr>& entities_at_coords = world.getElement(entity->coords);
    entities_at_coords.push_back(entity);
}

template <typename E, unsigned int Dim, typename Index>
std::vector<std::shared_ptr<Entity<E, Dim, Index>>> DiscretePtrWorld<E, Dim, Index>::getEntitiesAt(Coords coords) {
    return world.getElement(coords);
}

template <typename E, unsigned int Dim, typename Index>
std::vector<std::shared_ptr<Entity<E, Dim, Index>>> DiscretePtrWorld<E, Dim, Index>::getEntitiesOf(const E& entity_type) {
    std::vector<EntityPtr> entities_of;
    for (const Coords& coords : entity_coords) {
        std::vector<EntityPtr> entities = getEntitiesAt(coords);
        for (const EntityPtr& e : entities) {
            if (e->entity == entity_type) {
                entities_of.push_back(e); 
            }
        }
    }
    return entities_of;
}

///

template <typename E, unsigned int Dim, typename Index = unsigned long>
class DiscretePtrWorld2 {
    using DiscreteEntity = Entity<E, Dim, Index>;
    using EntityPtr = std::shared_ptr<DiscreteEntity>;
    using WeakEntityPtr = std::weak_ptr<DiscreteEntity>;
    using Coords = Array<Index, Dim>;

private:
    NArray<std::vector<WeakEntityPtr>, Dim, Index> world; 
    std::vector<EntityPtr> entities;

public:
    DiscretePtrWorld2() : world(), entities() {}
    DiscretePtrWorld2(Coords widths) : world(widths), entities() {}
    // ~DiscretePtrWorld2();

    void spawn(const EntityPtr& entity);
    void despawn(const EntityPtr& entity);
    std::vector<WeakEntityPtr> getEntities();
    std::vector<WeakEntityPtr> getEntitiesAt(Coords coords);
    std::vector<WeakEntityPtr> getEntitiesOf(const E& entity_type);
    std::vector<WeakEntityPtr> getEntitiesMatching(const DiscreteEntity& entity);
};

template <typename E, unsigned int Dim, typename Index>
void DiscretePtrWorld2<E, Dim, Index>::spawn(const EntityPtr& entity) {
    entities.push_back(entity);
    std::vector<WeakEntityPtr>& entities_at_coords = world.getElement(entity->coords);
    entities_at_coords.push_back(WeakEntityPtr(entity));
}

template <typename E, unsigned int Dim, typename Index>
void DiscretePtrWorld2<E, Dim, Index>::despawn(const EntityPtr& entity) 
{
    // Delete entity from the entities vector
    auto it = std::find(entities.begin(), entities.end(), entity);
    if (it != entities.end()) {
        entities.erase(it);
    }

    // Remove weak pointer from the world
    std::vector<WeakEntityPtr>& entities_at_coords = world.getElement(entity->coords);
    entities_at_coords.erase(
        std::remove_if(entities_at_coords.begin(), entities_at_coords.end(),
                       [&entity](const WeakEntityPtr& weak_ptr) {
                           return weak_ptr.lock() == entity;
                       }),
        entities_at_coords.end());
}

template <typename E, unsigned int Dim, typename Index>
std::vector<std::weak_ptr<Entity<E, Dim, Index>>> DiscretePtrWorld2<E, Dim, Index>::getEntities() {
    std::vector<WeakEntityPtr> weak_e_ptrs;
    for (EntityPtr e_ptr : entities)
    {
        weak_e_ptrs.push_back(e_ptr);
    }
    return weak_e_ptrs;
}

template <typename E, unsigned int Dim, typename Index>
std::vector<std::weak_ptr<Entity<E, Dim, Index>>> DiscretePtrWorld2<E, Dim, Index>::getEntitiesAt(Coords coords) {
    return world.getElement(coords);  // Already contains weak pointers
}

template <typename E, unsigned int Dim, typename Index>
std::vector<std::weak_ptr<Entity<E, Dim, Index>>> DiscretePtrWorld2<E, Dim, Index>::getEntitiesOf(const E& entity_type) {
    std::vector<WeakEntityPtr> weak_entities_of;
    std::copy_if(entities.begin(), entities.end(), std::back_inserter(weak_entities_of),
                 [&entity_type](const EntityPtr& e_ptr) {
                     return e_ptr->entity == entity_type;
                 });
    
    return weak_entities_of;
}

// template <typename E, unsigned int Dim, typename Index>
// std::vector<std::weak_ptr<Entity<E, Dim, Index>>> DiscretePtrWorld2<E, Dim, Index>::getEntitiesMatching(const Entity<E, Dim, Index>& entity) {
//     std::vector<WeakEntityPtr> matching_type = getEntitiesOf(entity.entity);
//     std::vector<WeakEntityPtr> matching_both;
//     std::copy_if(matching_type.begin(), matching_type.end(), std::back_inserter(matching_both), 
//                  [&entity](const WeakEntityPtr& weak_e_ptr) {
//                     if (auto e_ptr = weak_e_ptr.lock()) {
//                         return e_ptr->coords == entity.coords;
//                     }
//                     return false;
//                  });
//     return matching_both;
// }

template <typename E, unsigned int Dim, typename Index>
std::vector<std::weak_ptr<Entity<E, Dim, Index>>> DiscretePtrWorld2<E, Dim, Index>::getEntitiesMatching(const Entity<E, Dim, Index>& entity) {
    std::vector<WeakEntityPtr> matching_coords = getEntitiesAt(entity.coords);
    std::vector<WeakEntityPtr> matching_both;
    std::copy_if(matching_coords.begin(), matching_coords.end(), std::back_inserter(matching_both), 
                 [&entity](const WeakEntityPtr& weak_e_ptr) {
                    if (auto e_ptr = weak_e_ptr.lock()) {
                        return e_ptr->entity == entity.entity;
                    }
                    return false;
                 });
    return matching_both;
}

///
///
///

template <typename E, unsigned int Dim, typename Index = unsigned long>
class Engine
{
    using DiscreteEntity = Entity<E, Dim, Index>;
    using EntityPtr = std::shared_ptr<DiscreteEntity>;
    using WeakEntityPtr = std::weak_ptr<DiscreteEntity>;
    using Coords = Array<Index, Dim>;
    using World = DiscretePtrWorld2<E, Dim, Index>;

public:
    World world;

public: 
    Engine() : world() {}
    Engine(World _world) : world(_world) {}
    Engine(Coords widths) : world(widths) {}

    void spawn(const DiscreteEntity entity);
    void despawn(const DiscreteEntity entity);
};

template <typename E, unsigned int Dim, typename Index>
void Engine<E, Dim, Index>::spawn(const DiscreteEntity entity) 
{
    EntityPtr e_ptr = std::make_shared<DiscreteEntity>(entity);
    world.spawn(e_ptr);
}

template <typename E, unsigned int Dim, typename Index>
void Engine<E, Dim, Index>::despawn(const DiscreteEntity entity) 
{
    std::vector<WeakEntityPtr> matching = world.getEntitiesMatching(entity);
    for (auto& weak_ptr : matching) {
        if (auto e_ptr = weak_ptr.lock()) {
            world.despawn(e_ptr);
        }
    }
}
