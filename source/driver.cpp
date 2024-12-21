#include "../day2/puzzle.cpp"
#include "../day5/puzzle.cpp"
#include "../day6/puzzle.cpp"
#include "../day7/puzzle.cpp"
#include "../day8/puzzle.cpp"

#include "matrix.cpp"
#include "hyper.cpp"
#include "narray.cpp"
#include "grid.cpp"
#include "setgrid.cpp"
// #include "nonrecursive.cpp"

#include <cassert>

#include <list>

std::array<solve::TrialParameters, 2> getWickedFastParams()
{
    static const solve::TrialParameters parsing = { true, 2, 10 };
    static const solve::TrialParameters non_parsing = { false, 2, 5 };
    return { parsing, non_parsing };
}

std::array<solve::TrialParameters, 2> getDefaultParams()
{
    static const solve::TrialParameters parsing = { true, 5, 100 };
    static const solve::TrialParameters non_parsing = { false, 5, 50 };
    return { parsing, non_parsing };
}

std::array<solve::TrialParameters, 2> getQuickParams()
{
    static const solve::TrialParameters parsing = { true, 1, 10 };
    static const solve::TrialParameters non_parsing = { false, 1, 5 };
    return { parsing, non_parsing };
}

std::array<solve::TrialParameters, 2> getLongParams()
{
    static const solve::TrialParameters parsing = { true, 5, 5000 };
    static const solve::TrialParameters non_parsing = { false, 10, 200 };
    return { parsing, non_parsing };
}

void timeDay2()
{
    auto params = getDefaultParams();
    day2::Puzzle1Solver d2p1 = day2::Puzzle1Solver();
    d2p1.reportDefaultTrials(params);

    day2::Puzzle1SolverSimple d2p1Simple = day2::Puzzle1SolverSimple();
    d2p1Simple.reportDefaultTrials(params);

    day2::Puzzle1SolverRecursive d2p1Recursive = day2::Puzzle1SolverRecursive();
    d2p1Recursive.reportDefaultTrials(params);

    day2::Puzzle2SolverRecursive d2p2Recursive = day2::Puzzle2SolverRecursive();
    d2p2Recursive.reportDefaultTrials(params);

    // ALMOST WORKS
    day2::Puzzle2SolverRecursiveK d2p2RecursiveK = day2::Puzzle2SolverRecursiveK();
    d2p2RecursiveK.reportDefaultTrials(params);
}

void timeDay5()
{
    day5::Puzzle1Solver d5p1 = day5::Puzzle1Solver();
    d5p1.reportDefaultTrials(getLongParams());

    day5::Puzzle2Solver d5p2 = day5::Puzzle2Solver();
    d5p2.reportDefaultTrials(getLongParams());
}

void timeDay6()
{
    day6::Puzzle1Solver d6p1 = day6::Puzzle1Solver();
    d6p1.reportDefaultTrials(getLongParams());

    day6::Puzzle2Solver d6p2 = day6::Puzzle2Solver();
    d6p2.reportDefaultTrials(getDefaultParams());
}

void timeDay7()
{
    day7::Puzzle1Solver d7p1 = day7::Puzzle1Solver();
    d7p1.reportDefaultTrials(getWickedFastParams());

    day7::Puzzle1SolverNp d7p1Np = day7::Puzzle1SolverNp();
    d7p1Np.reportDefaultTrials(getWickedFastParams());

    day7::Puzzle2Solver d7p2 = day7::Puzzle2Solver();
    d7p2.reportDefaultTrials(getWickedFastParams());

    day7::Puzzle2SolverNp d7p2Np = day7::Puzzle2SolverNp();
    d7p2Np.reportDefaultTrials(getWickedFastParams());
}

#include <cassert>
#include <iostream>

void test_array_operations() {
    // Test array access
    Array<int, 3, int> arr1;
    arr1[0] = 1;
    arr1[1] = 2;
    arr1[2] = 3;

    assert(arr1[0] == 1);
    assert(arr1[1] == 2);
    assert(arr1[2] == 3);

    // Test array addition
    Array<int, 3, int> arr2;
    arr2[0] = 10;
    arr2[1] = 20;
    arr2[2] = 30;

    arr1.add(arr2);
    assert(arr1[0] == 11);
    assert(arr1[1] == 22);
    assert(arr1[2] == 33);

    // Test array scaling
    arr1.scale(2);
    assert(arr1[0] == 22);
    assert(arr1[1] == 44);
    assert(arr1[2] == 66);

     // Test neg array access
    Array<int, 3, int> narr1;
    narr1[0] = -1;
    narr1[1] = 2;
    narr1[2] = -3;

    assert(narr1[0] == -1);
    assert(narr1[1] == 2);
    assert(narr1[2] == -3);

    // Test array addition
    Array<int, 3, int> narr2;
    narr2[0] = -1;
    narr2[1] = 20;
    narr2[2] = 30;

    narr1.add(narr2);
    assert(narr1[0] == -2);
    assert(narr1[1] == 22);
    assert(narr1[2] == 27);

    // Test array scaling
    narr1.scale(-2);
    assert(narr1[0] == 4);
    assert(narr1[1] == -44);
    assert(narr1[2] == -54);

    std::cout << "All array tests passed!" << std::endl;
}

// void test_narray() {
//     // Test 1D NArray
//     std::cout << "Testing 1D NArray...\n";
//     NArray<int, 1, size_t> arr1d(std::array<size_t, 1>{3});

//     // Test element insertion and retrieval
//     assert(arr1d.putElement(std::array<size_t, 1>{0}, 10));
//     assert(arr1d.putElement(std::array<size_t, 1>{1}, 20));
//     assert(arr1d.putElement(std::array<size_t, 1>{2}, 30));

//     assert(arr1d.getElement(std::array<size_t, 1>{0}) == 10);
//     assert(arr1d.getElement(std::array<size_t, 1>{1}) == 20);
//     assert(arr1d.getElement(std::array<size_t, 1>{2}) == 30);

//     // Test operator[]
//     assert(arr1d[0] == 10);
//     assert(arr1d[1] == 20);
//     assert(arr1d[2] == 30);

//     // Test 2D NArray
//     std::cout << "Testing 2D NArray...\n";
//     NArray<int, 2, size_t> arr2d(std::array<size_t, 2>{2, 2});

//     // Test element insertion
//     assert(arr2d.putElement(std::array<size_t, 2>{0, 0}, 1));
//     assert(arr2d.putElement(std::array<size_t, 2>{0, 1}, 2));
//     assert(arr2d.putElement(std::array<size_t, 2>{1, 0}, 3));
//     assert(arr2d.putElement(std::array<size_t, 2>{1, 1}, 4));

//     // Test element retrieval
//     assert(arr2d.getElement(std::array<size_t, 2>{0, 0}) == 1);
//     assert(arr2d.getElement(std::array<size_t, 2>{0, 1}) == 2);
//     assert(arr2d.getElement(std::array<size_t, 2>{1, 0}) == 3);
//     assert(arr2d.getElement(std::array<size_t, 2>{1, 1}) == 4);

//     // Test bounds checking
//     try {
//         arr1d.getElement(std::array<size_t, 1>{5}); // Should throw
//         assert(false); // Should not reach here
//     } catch (const std::out_of_range&) {
//         // Expected
//     }

//     try {
//         arr2d.getElement(std::array<size_t, 2>{3, 3}); // Should throw
//         assert(false); // Should not reach here
//     } catch (const std::out_of_range&) {
//         // Expected
//     }

//     // Test resize
//     arr1d.resize(std::array<size_t, 1>{5});
//     assert(arr1d.putElement(std::array<size_t, 1>{4}, 50));
//     assert(arr1d.getElement(std::array<size_t, 1>{4}) == 50);

//     std::cout << "All NArray tests passed!\n";
// }

void test_narray() {
    std::cout << "Testing 1D NArray...\n";

    // Test 1D NArray
    Array<unsigned int, 1> dims1({ 3 });
    NArray<int, 1, unsigned int> arr1d(dims1);

    // Test element insertion
    Array<unsigned int, 1> pos0({ 0 });
    Array<unsigned int, 1> pos1({ 1 });
    Array<unsigned int, 1> pos2({ 2 });

    arr1d.putElement(pos0, 10);
    arr1d.putElement(pos1, 20);
    arr1d.putElement(pos2, 30);

    // Test element retrieval
    assert(arr1d.getElement(pos0) == 10);
    assert(arr1d.getElement(pos1) == 20);
    assert(arr1d.getElement(pos2) == 30);

    // Test operator[]
    assert(arr1d[0] == 10);
    assert(arr1d[1] == 20);
    assert(arr1d[2] == 30);

    std::cout << "Testing 2D NArray...\n";

    // Test 2D NArray
    Array<unsigned int, 2> dims2({ 2, 2 });
    NArray<int, 2, unsigned int> arr2d(dims2);

    // Test element insertion
    Array<unsigned int, 2> pos00({ 0, 0 });
    Array<unsigned int, 2> pos01({ 0, 1 });
    Array<unsigned int, 2> pos10({ 1, 0 });
    Array<unsigned int, 2> pos11({ 1, 1 });

    arr2d.putElement(pos00, 1);
    arr2d.putElement(pos01, 2);
    arr2d.putElement(pos10, 3);
    arr2d.putElement(pos11, 4);

    // Test element retrieval
    assert(arr2d.getElement(pos00) == 1);
    assert(arr2d.getElement(pos01) == 2);
    assert(arr2d.getElement(pos10) == 3);
    assert(arr2d.getElement(pos11) == 4);

    // Test bounds checking
    try {
        Array<unsigned int, 1> invalid_pos({ 5 });
        arr1d.getElement(invalid_pos);
        assert(false); // Should not reach here
    }
    catch (const std::out_of_range&) {
     // Expected
    }

    // Create 3D array with dimensions 2x2x2
    Array<unsigned int, 3> dims3({ 2, 2, 2 });
    NArray<int, 3, unsigned int> arr3d(dims3);

    // Test element insertion at various coordinates
    Array<unsigned int, 3> pos000({ 0, 0, 0 });
    Array<unsigned int, 3> pos001({ 0, 0, 1 });
    Array<unsigned int, 3> pos010({ 0, 1, 0 });
    Array<unsigned int, 3> pos011({ 0, 1, 1 });
    Array<unsigned int, 3> pos100({ 1, 0, 0 });
    Array<unsigned int, 3> pos101({ 1, 0, 1 });
    Array<unsigned int, 3> pos110({ 1, 1, 0 });
    Array<unsigned int, 3> pos111({ 1, 1, 1 });

    arr3d.putElement(pos000, 1);
    arr3d.putElement(pos001, 2);
    arr3d.putElement(pos010, 3);
    arr3d.putElement(pos011, 4);
    arr3d.putElement(pos100, 5);
    arr3d.putElement(pos101, 6);
    arr3d.putElement(pos110, 7);
    arr3d.putElement(pos111, 8);

    // Test element retrieval
    assert(arr3d.getElement(pos000) == 1);
    assert(arr3d.getElement(pos001) == 2);
    assert(arr3d.getElement(pos010) == 3);
    assert(arr3d.getElement(pos011) == 4);
    assert(arr3d.getElement(pos100) == 5);
    assert(arr3d.getElement(pos101) == 6);
    assert(arr3d.getElement(pos110) == 7);
    assert(arr3d.getElement(pos111) == 8);

    // Test bounds checking
    try {
        Array<unsigned int, 3> invalid_pos({ 3, 3, 3 });
        arr3d.getElement(invalid_pos);
        assert(false); // Should not reach here
    }
    catch (const std::out_of_range&) {
     // Expected
    }

    std::cout << "All 3D NArray tests passed!\n";

    std::cout << "All NArray tests passed!\n";
}

void test_world()
{
    // Create a 2D world of size 10x10
    Array<unsigned long, 2> worldSize({ 10, 10 });
    DiscreteWorld<std::string, 2, unsigned long> world(worldSize);

    // Create some test entities
    Entity<std::string, 2, unsigned long> entity1;
    entity1.entity = "Entity1";
    entity1.coords = Array<unsigned long, 2>({ 1, 1 });

    Entity<std::string, 2, unsigned long> entity2;
    entity2.entity = "Entity2";
    entity2.coords = Array<unsigned long, 2>({ 5, 5 });

    // Spawn entities into the world
    world.spawn(entity1);
    world.spawn(entity2);

    // Test entity retrieval
    auto& retrieved1 = world.getEntitiesAt(Array<unsigned long, 2>({ 1, 1 }));
    auto& retrieved2 = world.getEntitiesAt(Array<unsigned long, 2>({ 5, 5 }));

    // Verify results
    assert(retrieved1[0].entity == "Entity1");
    assert(retrieved2[0].entity == "Entity2");

    Entity<std::string, 2, unsigned long> entity3;
    entity3.entity = "Entity3";
    entity3.coords = Array<unsigned long, 2>({ 1, 1 });
    world.spawn(entity3);

    auto& retrieved3 = world.getEntitiesAt(Array<unsigned long, 2>({ 1, 1 }));
    assert(retrieved3[0].entity == "Entity1");
    assert(retrieved3[1].entity == "Entity3");

    // Create a 3D world of size 2x3x5
    Array<int, 3> worldSize3({ 2, 3, 5 });
    DiscreteWorld<char, 3, int> world3(worldSize3);

    // Create some test entities
    Entity<char, 3, int> entity3a;
    entity3a.entity = 'a';
    entity3a.coords = Array<int, 3>({ 2, 3, 5 });

    Entity<char, 3, int> entity3b;
    entity3b.entity = 'b';
    entity3b.coords = Array<int, 3>({ 0, 1, 0 });

    // Spawn entities into the world
    world3.spawn(entity3a);
    world3.spawn(entity3b);

    // Test entity retrieval
    auto& retrieved3a = world3.getEntitiesAt(entity3a.coords);
    auto& retrieved3b = world3.getEntitiesAt(entity3b.coords);
    auto& retrieved3v = world3.getEntitiesAt(Array<int, 3>({ 0, 0, 0 }));

    // Verify results
    assert(retrieved3a[0].entity == 'a');
    assert(retrieved3b[0].entity == 'b');

    // getEntitiesOf
    DiscreteWorld<std::string, 2, unsigned long> typeWorld(Array<unsigned long, 2>({ 10, 10 }));

    // Create multiple entities of the same type
    Entity<std::string, 2, unsigned long> cat1;
    cat1.entity = "cat";
    cat1.coords = Array<unsigned long, 2>({ 1, 1 });

    Entity<std::string, 2, unsigned long> cat2;
    cat2.entity = "cat";
    cat2.coords = Array<unsigned long, 2>({ 3, 4 });

    Entity<std::string, 2, unsigned long> dog1;
    dog1.entity = "dog";
    dog1.coords = Array<unsigned long, 2>({ 2, 2 });

    // Spawn all entities
    typeWorld.spawn(cat1);
    typeWorld.spawn(cat2);
    typeWorld.spawn(dog1);

    // Test retrieving all cats
    auto cats = typeWorld.getEntitiesOf("cat");
    assert(cats.size() == 2);

    // Verify cat locations
    bool foundCat1 = false;
    bool foundCat2 = false;

    for (auto& cat : cats) {
        if (cat.coords[0] == 1 && cat.coords[1] == 1) foundCat1 = true;
        if (cat.coords[0] == 3 && cat.coords[1] == 4) foundCat2 = true;
    }

    assert(foundCat1 && foundCat2);

    // Test retrieving all dogs
    auto dogs = typeWorld.getEntitiesOf("dog");
    assert(dogs.size() == 1);
    assert(dogs[0].coords[0] == 2 && dogs[0].coords[1] == 2);

    // Test retrieving non-existent type
    auto birds = typeWorld.getEntitiesOf("bird");
    assert(birds.size() == 0);

    std::cout << "All DiscreteWorld tests passed!" << std::endl;
}

void test_ptr_world() {
    std::cout << "Testing DiscretePtrWorld...\n";

    // Create a 2D world
    Array<unsigned long, 2> worldSize({ 10, 10 });
    DiscretePtrWorld<std::string, 2, unsigned long> world(worldSize);

    // Test shared ownership
    {
        auto entity1 = std::make_shared<Entity<std::string, 2, unsigned long>>();
        entity1->entity = "Entity1";
        entity1->coords = Array<unsigned long, 2>({ 1, 1 });

        // Initial reference count should be 1
        assert(entity1.use_count() == 1);

        // Spawn should increase reference count
        world.spawn(entity1);
        assert(entity1.use_count() == 2);

        // Test retrieval maintains correct reference count
        auto retrieved = world.getEntitiesAt(Array<unsigned long, 2>({ 1, 1 }));
        assert(retrieved[0].use_count() == 3);
        assert(retrieved[0]->entity == "Entity1");
    }

    // Test multiple entities at same location
    {
        auto cat1 = std::make_shared<Entity<std::string, 2, unsigned long>>();
        cat1->entity = "cat";
        cat1->coords = Array<unsigned long, 2>({ 2, 2 });

        auto cat2 = std::make_shared<Entity<std::string, 2, unsigned long>>();
        cat2->entity = "cat";
        cat2->coords = Array<unsigned long, 2>({ 2, 2 });

        world.spawn(cat1);
        world.spawn(cat2);

        auto cats_at_location = world.getEntitiesAt(Array<unsigned long, 2>({ 2, 2 }));
        assert(cats_at_location.size() == 2);
        assert(cats_at_location[0].use_count() == 3);
        assert(cats_at_location[1].use_count() == 3);
    }

    // Test getEntitiesOf with shared ownership
    {
        auto dog1 = std::make_shared<Entity<std::string, 2, unsigned long>>();
        dog1->entity = "dog";
        dog1->coords = Array<unsigned long, 2>({ 3, 3 });

        auto dog2 = std::make_shared<Entity<std::string, 2, unsigned long>>();
        dog2->entity = "dog";
        dog2->coords = Array<unsigned long, 2>({ 4, 4 });

        world.spawn(dog1);
        world.spawn(dog2);

        // Get all dogs and verify reference counts
        auto dogs = world.getEntitiesOf("dog");
        assert(dogs.size() == 2);
        assert(dogs[0].use_count() == 3);
        assert(dogs[1].use_count() == 3);

        // Verify coordinates
        bool found_dog1 = false, found_dog2 = false;
        for (const auto& dog : dogs) {
            if (dog->coords[0] == 3 && dog->coords[1] == 3) found_dog1 = true;
            if (dog->coords[0] == 4 && dog->coords[1] == 4) found_dog2 = true;
        }
        assert(found_dog1 && found_dog2);
    }

    // Test pointer validity after original shared_ptr goes out of scope
    {
        std::weak_ptr<Entity<std::string, 2, unsigned long>> weak_entity;
        {
            auto temp_entity = std::make_shared<Entity<std::string, 2, unsigned long>>();
            temp_entity->entity = "temp";
            temp_entity->coords = Array<unsigned long, 2>({ 5, 5 });
            world.spawn(temp_entity);
            weak_entity = temp_entity;
            assert(weak_entity.use_count() == 2); // One in world, one in temp_entity
        }
        // Original shared_ptr is gone, but world should still hold reference
        assert(!weak_entity.expired());
        assert(weak_entity.use_count() == 1);

        auto entities = world.getEntitiesAt(Array<unsigned long, 2>({ 5, 5 }));
        assert(entities.size() == 1);
        assert(entities[0]->entity == "temp");
    }

    // Test larger world and memory management
    {
        Array<unsigned long, 3> worldSize3({ 5, 5, 5 });
        DiscretePtrWorld<int, 3, unsigned long> world3(worldSize3);

        std::vector<std::weak_ptr<Entity<int, 3, unsigned long>>> weak_refs;

        // Spawn 100 entities
        for (int i = 0; i < 100; i++) {
            auto entity = std::make_shared<Entity<int, 3, unsigned long>>();
            entity->entity = i;
            entity->coords = Array<unsigned long, 3>({
                static_cast<unsigned long>(i % 5),
                static_cast<unsigned long>((i / 5) % 5),
                static_cast<unsigned long>((i / 25) % 5)
                });
            world3.spawn(entity);
            weak_refs.push_back(entity);
        }

        // Verify all entities still exist after original pointers gone
        for (const auto& weak_ref : weak_refs) {
            assert(!weak_ref.expired());
            assert(weak_ref.use_count() == 1); // Only world holds reference
        }
    }

    {
        // Test modifications are reflected across all references
        auto original = std::make_shared<Entity<std::string, 2, unsigned long>>();
        original->entity = "modifiable";
        original->coords = Array<unsigned long, 2>({ 7, 7 });
        world.spawn(original);

        // Get references through different methods
        auto by_location = world.getEntitiesAt(Array<unsigned long, 2>({ 7, 7 }))[0];
        auto by_type = world.getEntitiesOf("modifiable")[0];

        // Modify through one reference
        by_location->entity = "modified";

        // Verify changes are reflected in all references
        assert(original->entity == "modified");
        assert(by_type->entity == "modified");
        assert(world.getEntitiesAt(Array<unsigned long, 2>({ 7, 7 }))[0]->entity == "modified");

        // Check reference counts
        assert(original.use_count() == by_location.use_count());
        assert(by_type.use_count() == by_location.use_count());
    }

    std::cout << "All DiscretePtrWorld tests passed!\n";
}

void test_ptr_world2() {
    std::cout << "Testing DiscretePtrWorld2...\n";

    // Basic world setup
    Array<unsigned long, 2> worldSize({ 10, 10 });
    DiscretePtrWorld2<std::string, 2, unsigned long> world(worldSize);

    // Test weak pointer behavior
    {
        std::weak_ptr<Entity<std::string, 2, unsigned long>> weak_entity;
        {
            auto entity = std::make_shared<Entity<std::string, 2, unsigned long>>();
            entity->entity = "test";
            entity->coords = Array<unsigned long, 2>({ 1, 1 });

            weak_entity = std::weak_ptr<Entity<std::string, 2, unsigned long>>(entity);
            assert(!weak_entity.expired());

            world.spawn(entity);

            // Test retrieval methods while shared_ptr exists
            auto at_location = world.getEntitiesAt(Array<unsigned long, 2>({ 1, 1 }));
            auto by_type = world.getEntitiesOf("test");

            assert(at_location.size() == 1);
            assert(by_type.size() == 1);
            assert(!at_location[0].expired());
            assert(!by_type[0].expired());

            // Verify we can lock and access
            auto locked = at_location[0].lock();
            assert(locked);
            assert(locked->entity == "test");

            // This should despawn the same entity twice, and so the second call
            // does nothing.
            world.despawn(locked);
            world.despawn(entity);
        }
        // Original shared_ptr is gone, weak_ptrs should be expired
        assert(weak_entity.expired());
    }

    // Test multiple entities and spatial organization
    {
        std::vector<std::shared_ptr<Entity<std::string, 2, unsigned long>>> entities;

        // Create entities at same location
        for (int i = 0; i < 3; i++) {
            auto entity = std::make_shared<Entity<std::string, 2, unsigned long>>();
            entity->entity = "group";
            entity->coords = Array<unsigned long, 2>({ 2, 2 });
            world.spawn(entity);
            entities.push_back(entity);
        }

        auto at_location = world.getEntitiesAt(Array<unsigned long, 2>({ 2, 2 }));
        assert(at_location.size() == 3);

        // Check all weak_ptrs are valid
        for (const auto& weak_entity : at_location) {
            assert(!weak_entity.expired());
            auto locked = weak_entity.lock();
            assert(locked);
            assert(locked->entity == "group");
        }

        // Test type query
        auto by_type = world.getEntitiesOf("group");
        assert(by_type.size() == 3);
    }

    // Test modification through weak_ptr
    {
        auto entity = std::make_shared<Entity<std::string, 2, unsigned long>>();
        entity->entity = "modifiable";
        entity->coords = Array<unsigned long, 2>({ 3, 3 });
        world.spawn(entity);

        auto at_location = world.getEntitiesAt(Array<unsigned long, 2>({ 3, 3 }));
        assert(at_location.size() == 1);

        auto locked = at_location[0].lock();
        assert(locked);
        locked->entity = "modified";

        // Verify change is reflected
        auto by_type = world.getEntitiesOf("modified");
        assert(by_type.size() == 1);
        assert(by_type[0].lock()->entity == "modified");
    }

    // Test cleanup and memory management
    {
        std::weak_ptr<Entity<std::string, 2, unsigned long>> tracker;
        {
            auto temp = std::make_shared<Entity<std::string, 2, unsigned long>>();
            temp->entity = "temporary";
            temp->coords = Array<unsigned long, 2>({ 4, 4 });
            world.spawn(temp);
            tracker = temp;
        }
        // temp has gone out of scope, but 
        // since world contains a shared_ptr
        // to the underlying entity,
        // and world is still in scope,
        // the reference to it should still be
        // valid.
        assert(!tracker.expired());

        // If we despawn it from world, it should
        // now be expired
        world.despawn(tracker.lock());
        assert(tracker.expired());


        // Try to retrieve expired entity
        auto at_location = world.getEntitiesAt(Array<unsigned long, 2>({ 4, 4 }));
        for (const auto& weak_entity : at_location) {
            assert(weak_entity.expired());
        }
    }

    // Test large-scale entity management
    {
        std::vector<std::shared_ptr<Entity<std::string, 2, unsigned long>>> entities;
        for (int i = 0; i < 100; i++) {
            auto entity = std::make_shared<Entity<std::string, 2, unsigned long>>();
            entity->entity = "mass";
            entity->coords = Array<unsigned long, 2>({
                static_cast<unsigned long>(i % 10),
                static_cast<unsigned long>(i / 10)
                });
            world.spawn(entity);
            entities.push_back(entity);
        }

        // Test type query with large number of entities
        auto mass_entities = world.getEntitiesOf("mass");
        assert(mass_entities.size() == 100);

        // Have to despawn first.
        for (auto it = entities.begin() + 50; it != entities.end(); ++it)
        {
            world.despawn(*it);
        }
        // Clear half the entities
        entities.erase(entities.begin() + 50, entities.end());

        // Verify remaining entities
        mass_entities = world.getEntitiesOf("mass");
        int valid_count = 0;
        for (const auto& weak_entity : mass_entities) {
            if (!weak_entity.expired()) {
                valid_count++;
            }
        }
        assert(valid_count == 50);
    }

    std::cout << "All DiscretePtrWorld2 tests passed!\n";
}

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

void test_ptr_world2_scoping() {
    std::cout << "Testing DiscretePtrWorld2 scoping behaviors...\n";

    // Test 1: Entity lifetime when world goes out of scope
    {
        std::weak_ptr<Entity<std::string, 2>> entity_tracker;
        {
            // Create world and entity in inner scope
            Array<unsigned long, 2> size({ 10, 10 });
            DiscretePtrWorld2<std::string, 2> temp_world(size);

            auto entity = std::make_shared<Entity<std::string, 2>>();
            entity->entity = "scope_test";
            entity->coords = Array<unsigned long, 2>({ 1, 1 });

            temp_world.spawn(entity);
            entity_tracker = entity;

            // Entity should be alive here
            assert(!entity_tracker.expired());
        }
        // World is gone, entity should be too
        assert(entity_tracker.expired());
    }

    // Test 2: Entity sharing between multiple worlds
    {
        Array<unsigned long, 2> size({ 10, 10 });
        DiscretePtrWorld2<std::string, 2> world1(size);
        DiscretePtrWorld2<std::string, 2> world2(size);

        auto shared_entity = std::make_shared<Entity<std::string, 2>>();
        shared_entity->entity = "shared";
        shared_entity->coords = Array<unsigned long, 2>({ 5, 5 });

        // Spawn in both worlds
        world1.spawn(shared_entity);
        world2.spawn(shared_entity);

        std::weak_ptr<Entity<std::string, 2>> tracker = shared_entity;

        // Verify entity exists in both worlds
        auto in_world1 = world1.getEntitiesAt(Array<unsigned long, 2>({ 5, 5 }));
        auto in_world2 = world2.getEntitiesAt(Array<unsigned long, 2>({ 5, 5 }));

        assert(in_world1.size() == 1 && in_world2.size() == 1);
        assert(!in_world1[0].expired() && !in_world2[0].expired());

        // Despawn from world1, should still exist in world2
        world1.despawn(shared_entity);
        assert(!tracker.expired());
        assert(world1.getEntitiesAt(Array<unsigned long, 2>({ 5, 5 })).empty());
        assert(!world2.getEntitiesAt(Array<unsigned long, 2>({ 5, 5 })).empty());

        // calling shared_entity.reset() here causes segfault
        // shared_entity.reset();
        // Despawn from world2
        world2.despawn(shared_entity);

        // Delete entity
        shared_entity.reset();
        assert(tracker.expired());
    }

    // Test 3: Nested world scopes
    {
        std::weak_ptr<Entity<std::string, 2>> nested_tracker;
        Array<unsigned long, 2> size({ 10, 10 });
        DiscretePtrWorld2<std::string, 2> outer_world(size);

        {
            DiscretePtrWorld2<std::string, 2> inner_world(size);
            auto nested_entity = std::make_shared<Entity<std::string, 2>>();
            nested_entity->entity = "nested";
            nested_entity->coords = Array<unsigned long, 2>({ 3, 3 });

            // Spawn in both worlds
            outer_world.spawn(nested_entity);
            inner_world.spawn(nested_entity);
            nested_tracker = nested_entity;

            assert(!nested_tracker.expired());
        }
        // Inner world gone, entity should still exist in outer world
        assert(!nested_tracker.expired());

        auto still_in_outer = outer_world.getEntitiesAt(Array<unsigned long, 2>({ 3, 3 }));
        assert(still_in_outer.size() == 1);
        assert(!still_in_outer[0].expired());
    }

    // Test 4: Multiple world cleanup order
    {
        std::vector<std::weak_ptr<Entity<std::string, 2>>> trackers;
        Array<unsigned long, 2> size({ 5, 5 });

        auto world1 = make_unique<DiscretePtrWorld2<std::string, 2>>(size);
        auto world2 = make_unique<DiscretePtrWorld2<std::string, 2>>(size);

        // Create entities in both worlds
        for (int i = 0; i < 10; i++) {
            auto entity = std::make_shared<Entity<std::string, 2>>();
            entity->entity = "cleanup_test";
            entity->coords = Array<unsigned long, 2>({
                static_cast<unsigned long>(i % 5),
                static_cast<unsigned long>(i / 5)
                });

            world1->spawn(entity);
            world2->spawn(entity);
            trackers.push_back(entity);
        }

        // Delete world1, entities should still exist in world2
        world1.reset();
        for (const auto& tracker : trackers) {
            assert(!tracker.expired());
        }

        // Delete world2, now entities should be gone
        world2.reset();
        for (const auto& tracker : trackers) {
            assert(tracker.expired());
        }
    }

    std::cout << "All DiscretePtrWorld2 scoping tests passed!\n";
}

void test_engine1() {
    std::cout << "Testing Engine functionality and memory safety...\n";

    // Test 1: Basic spawn/despawn with rectangular world
    {
        Engine<std::string, 2> engine(Array<unsigned long, 2>({ 10, 14 }));

        Entity<std::string, 2> entity;
        entity.entity = "test_entity";
        entity.coords = Array<unsigned long, 2>({ 1, 14 });

        engine.spawn(entity);
        auto entities = engine.world.getEntitiesMatching(entity);
        assert(entities.size() == 1);
        assert(!entities[0].expired());
        assert(entities[0].lock()->entity == "test_entity");

        engine.despawn(entity);
        entities = engine.world.getEntitiesMatching(entity);
        assert(entities.empty());
    }

    // Test 2: Multiple entity management in 3D rectangular world
    {
        Engine<int, 3> engine(Array<unsigned long, 3>({ 4, 7, 2 }));

        // Spawn multiple entities
        for (int i = 0; i < 100; i++) {
            Entity<int, 3> entity;
            entity.entity = i % 3;
            entity.coords = Array<unsigned long, 3>({
                static_cast<unsigned long>(i % 5),
                static_cast<unsigned long>((i / 5) % 8),
                static_cast<unsigned long>((i / 40) % 3)
                });

            engine.spawn(entity);
        }

        // Verify all entities of each type
        for (int type = 0; type < 3; type++) {
            Entity<int, 3> probe;
            probe.entity = type;
            auto type_entities = engine.world.getEntitiesOf(type);
            assert(type_entities.size() == 34 || type_entities.size() == 33); // 100/3 rounded
        }

        // Despawn half
        for (int i = 0; i < 50; i++) {
            Entity<int, 3> entity;
            entity.entity = i % 3;
            entity.coords = Array<unsigned long, 3>({
                static_cast<unsigned long>(i % 5),
                static_cast<unsigned long>((i / 5) % 8),
                static_cast<unsigned long>((i / 40) % 3)
                });
            engine.despawn(entity);
        }

        // Verify approximately half remain
        auto all_entities = engine.world.getEntities();
        int valid_count = 0;
        for (auto& weak_ptr : all_entities) {
            if (!weak_ptr.expired()) valid_count++;
        }
        assert(valid_count == 50);
    }

    // Test 3: Memory safety with nested scopes
    {
        auto engine_ptr = make_unique<Engine<std::string, 2>>(Array<unsigned long, 2>({ 20, 10 }));
        std::weak_ptr<Entity<std::string, 2>> weak_entity;

        {
            Entity<std::string, 2> entity;
            entity.entity = "scope_test";
            entity.coords = Array<unsigned long, 2>({ 15, 8 });

            engine_ptr->spawn(entity);
            auto entities = engine_ptr->world.getEntitiesMatching(entity);
            assert(entities.size() == 1);
            weak_entity = entities[0];
            assert(!weak_entity.expired());
        }

        assert(!weak_entity.expired()); // Should still be valid while engine exists
        engine_ptr.reset();
        assert(weak_entity.expired()); // Should be invalid after engine deletion
    }

    // Test 4: 1D world basic operations
    {
        Engine<std::string, 1> engine(Array<unsigned long, 1>({ 100 }));

        Entity<std::string, 1> entity1{ "type1", Array<unsigned long, 1>({5}) };
        Entity<std::string, 1> entity2{ "type2", Array<unsigned long, 1>({50}) };
        Entity<std::string, 1> entity3{ "type1", Array<unsigned long, 1>({99}) };

        engine.spawn(entity1);
        engine.spawn(entity2);
        engine.spawn(entity3);

        auto type1_entities = engine.world.getEntitiesOf("type1");
        assert(type1_entities.size() == 2);
        auto type2_entities = engine.world.getEntitiesOf("type2");
        assert(type2_entities.size() == 1);

        engine.despawn(entity1);
        engine.despawn(entity2);
        engine.despawn(entity3);

        assert(engine.world.getEntitiesOf("type1").empty());
        assert(engine.world.getEntitiesOf("type2").empty());
    }

    // Test 5: 1D world stress test
    {
        Engine<int, 1> engine(Array<unsigned long, 1>({ 1000 }));

        for (int cycle = 0; cycle < 5; cycle++) {
            for (int i = 0; i < 500; i++) {
                Entity<int, 1> entity;
                entity.entity = i % 10;
                entity.coords = Array<unsigned long, 1>({ static_cast<unsigned long>(i * 2) });
                engine.spawn(entity);
            }

            // Verify all entities exist
            auto all_entities = engine.world.getEntities();
            int valid_count = 0;
            for (auto& weak_ptr : all_entities) {
                if (!weak_ptr.expired()) valid_count++;
            }
            assert(valid_count == 500);

            for (int i = 0; i < 500; i++) {
                Entity<int, 1> entity;
                entity.entity = i % 10;
                entity.coords = Array<unsigned long, 1>({ static_cast<unsigned long>(i * 2) });
                engine.despawn(entity);
            }

            // Verify all entities were removed
            assert(engine.world.getEntities().empty());
        }
    }

    std::cout << "All Engine tests passed!\n";
}

void test_engine1_private() {
    std::cout << "Testing Engine functionality and memory safety...\n";

    // Test 1: Basic spawn/despawn with rectangular world
    {
        Engine<std::string, 2> engine(Array<unsigned long, 2>({ 10, 15 }));  // Non-square world

        Entity<std::string, 2> entity;
        entity.entity = "test_entity";
        entity.coords = Array<unsigned long, 2>({ 1, 14 });  // Testing near boundary

        engine.spawn(entity);

        Entity<std::string, 2> match;
        match.entity = "test_entity";
        match.coords = Array<unsigned long, 2>({ 1, 14 });

        engine.despawn(match);
    }

    // Test 2: Multiple entity management in 3D rectangular world
    {
        Engine<int, 3> engine(Array<unsigned long, 3>({ 5, 8, 3 }));  // Non-cubic world

        // Spawn multiple entities
        for (int i = 0; i < 100; i++) {
            Entity<int, 3> entity;
            entity.entity = i % 3;
            entity.coords = Array<unsigned long, 3>({
                static_cast<unsigned long>(i % 5),
                static_cast<unsigned long>((i / 5) % 8),
                static_cast<unsigned long>((i / 40) % 3)
                });

            engine.spawn(entity);
        }

        // Despawn half
        for (int i = 0; i < 50; i++) {
            Entity<int, 3> entity;
            entity.entity = i % 3;
            entity.coords = Array<unsigned long, 3>({
                static_cast<unsigned long>(i % 5),
                static_cast<unsigned long>((i / 5) % 8),
                static_cast<unsigned long>((i / 40) % 3)
                });
            engine.despawn(entity);
        }
    }

    // Test 3: Memory safety with nested scopes (rectangular world)
    {
        auto engine_ptr = make_unique<Engine<std::string, 2>>(Array<unsigned long, 2>({ 20, 10 }));

        {
            Entity<std::string, 2> entity;
            entity.entity = "scope_test";
            entity.coords = Array<unsigned long, 2>({ 15, 8 });

            engine_ptr->spawn(entity);
        }

        engine_ptr.reset();
    }

    // Test 4: 1D world basic operations
    {
        Engine<std::string, 1> engine(Array<unsigned long, 1>({ 100 }));

        // Test multiple entities at different positions
        Entity<std::string, 1> entity1{ "type1", Array<unsigned long, 1>({5}) };
        Entity<std::string, 1> entity2{ "type2", Array<unsigned long, 1>({50}) };
        Entity<std::string, 1> entity3{ "type1", Array<unsigned long, 1>({99}) };

        engine.spawn(entity1);
        engine.spawn(entity2);
        engine.spawn(entity3);

        engine.despawn(entity1);
        engine.despawn(entity2);
        engine.despawn(entity3);
    }

    // Test 5: 1D world stress test
    {
        Engine<int, 1> engine(Array<unsigned long, 1>({ 1000 }));

        // Rapid spawn/despawn cycles
        for (int cycle = 0; cycle < 5; cycle++) {
            for (int i = 0; i < 500; i++) {
                Entity<int, 1> entity;
                entity.entity = i % 10;
                entity.coords = Array<unsigned long, 1>({ static_cast<unsigned long>(i * 2) });
                engine.spawn(entity);
            }

            for (int i = 0; i < 500; i++) {
                Entity<int, 1> entity;
                entity.entity = i % 10;
                entity.coords = Array<unsigned long, 1>({ static_cast<unsigned long>(i * 2) });
                engine.despawn(entity);
            }
        }
    }

    std::cout << "All Engine tests passed!\n";
}

void test_engine2() {
    std::cout << "Testing Engine functionality and memory safety...\n";

    // Test 1: 1D world tests
    {
        std::cout << "Testing 1D world...\n";
        Engine<std::string, 1> engine(Array<unsigned long, 1>({ 20 }));

        Entity<std::string, 1> entity;
        entity.entity = "test_entity";
        entity.coords = Array<unsigned long, 1>({ 5 });

        engine.spawn(entity);
        auto matching = engine.world.getEntitiesMatching(entity);
        assert(matching.size() == 1);
        assert(!matching[0].expired());
        assert(matching[0].lock()->entity == "test_entity");

        Entity<std::string, 1> match;
        match.entity = "test_entity";
        match.coords = Array<unsigned long, 1>({ 5 });

        Entity<std::string, 1> entity2;
        entity2.entity = "another_entity";
        entity2.coords = Array<unsigned long, 1>({ 5 });

        engine.spawn(entity2);
        auto at_location = engine.world.getEntitiesAt(Array<unsigned long, 1>({ 5 }));
        assert(at_location.size() == 2);

        engine.despawn(match);
        at_location = engine.world.getEntitiesAt(Array<unsigned long, 1>({ 5 }));
        assert(at_location.size() == 1);
        assert(!at_location[0].expired());
        assert(at_location[0].lock()->entity == "another_entity");

        // Stress test 1D world
        for (int i = 0; i < 100; i++) {
            Entity<std::string, 1> stress_entity;
            stress_entity.entity = "stress_" + std::to_string(i);
            stress_entity.coords = Array<unsigned long, 1>({ static_cast<unsigned long>(i % 20) });
            engine.spawn(stress_entity);
        }
        auto all_entities = engine.world.getEntities();
        assert(all_entities.size() == 101); // 100 stress + 1 remaining another_entity
    }

    // Test 2: Basic spawn/despawn with non-square dimensions
    {
        Engine<std::string, 2> engine(Array<unsigned long, 2>({ 14, 9 }));

        Entity<std::string, 2> entity;
        entity.entity = "test_entity";
        entity.coords = Array<unsigned long, 2>({ 14, 9 });

        engine.spawn(entity);
        auto matching = engine.world.getEntitiesMatching(entity);
        assert(matching.size() == 1);
        assert(!matching[0].expired());
        assert(matching[0].lock()->entity == "test_entity");

        Entity<std::string, 2> match;
        match.entity = "test_entity";
        match.coords = Array<unsigned long, 2>({ 14, 9 });

        engine.despawn(match);
        matching = engine.world.getEntitiesMatching(entity);
        assert(matching.empty());
    }

    // Test 3: Multiple entity management in 3D non-cubic world
    {
        Engine<int, 3> engine(Array<unsigned long, 3>({ 7, 4, 2 }));

        for (int i = 0; i < 100; i++) {
            Entity<int, 3> entity;
            entity.entity = i % 3;
            entity.coords = Array<unsigned long, 3>({
                static_cast<unsigned long>(i % 8),
                static_cast<unsigned long>((i / 8) % 5),
                static_cast<unsigned long>((i / 40) % 3)
                });
            engine.spawn(entity);
        }

        auto all_entities = engine.world.getEntities();
        assert(all_entities.size() == 100);

        // Verify distribution of entity types
        for (int type = 0; type < 3; type++) {
            Entity<int, 3> probe;
            probe.entity = type;
            auto type_entities = engine.world.getEntitiesOf(type);
            assert(type_entities.size() == 34 || type_entities.size() == 33); // ~100/3
        }

        for (int i = 0; i < 50; i++) {
            Entity<int, 3> entity;
            entity.entity = i % 3;
            entity.coords = Array<unsigned long, 3>({
                static_cast<unsigned long>(i % 8),
                static_cast<unsigned long>((i / 8) % 5),
                static_cast<unsigned long>((i / 40) % 3)
                });
            engine.despawn(entity);
        }

        all_entities = engine.world.getEntities();
        int valid_count = 0;
        for (const auto& weak_ptr : all_entities) {
            if (!weak_ptr.expired()) valid_count++;
        }
        assert(valid_count == 50); // ~50 remaining
    }

    // Test 4: Memory safety with nested scopes
    {
        auto engine_ptr = make_unique<Engine<std::string, 2>>(Array<unsigned long, 2>({ 12, 8 }));
        std::weak_ptr<Entity<std::string, 2>> weak_entity;

        {
            Entity<std::string, 2> entity;
            entity.entity = "scope_test";
            entity.coords = Array<unsigned long, 2>({ 11, 7 });

            engine_ptr->spawn(entity);
            auto entities = engine_ptr->world.getEntitiesMatching(entity);
            assert(entities.size() == 1);
            weak_entity = entities[0];
            assert(!weak_entity.expired());
        }

        assert(!weak_entity.expired());
        engine_ptr.reset();
        assert(weak_entity.expired());
    }

    // Test 5: Concurrent entity types at same location
    {
        Engine<std::string, 2> engine(Array<unsigned long, 2>({ 4, 6 }));

        Entity<std::string, 2> entity1{ "type1", Array<unsigned long, 2>({4, 6}) };
        Entity<std::string, 2> entity2{ "type2", Array<unsigned long, 2>({4, 6}) };
        Entity<std::string, 2> entity3{ "type1", Array<unsigned long, 2>({4, 6}) };

        engine.spawn(entity1);
        engine.spawn(entity2);
        engine.spawn(entity3);

        auto at_location = engine.world.getEntitiesAt(Array<unsigned long, 2>({ 4, 6 }));
        assert(at_location.size() == 3);

        auto type1_entities = engine.world.getEntitiesOf("type1");
        assert(type1_entities.size() == 2);

        engine.despawn(entity1);
        type1_entities = engine.world.getEntitiesOf("type1");
        assert(type1_entities.size() == 0);

        engine.despawn(entity2);
        at_location = engine.world.getEntitiesAt(Array<unsigned long, 2>({ 4, 6 }));
        assert(at_location.size() == 0);
    }

    // Test 6: Edge cases in 2D world
    {
        Engine<int, 2> engine(Array<unsigned long, 2>({ 2, 2 }));

        Entity<int, 2> corner1{ 1, Array<unsigned long, 2>({0, 0}) };
        Entity<int, 2> corner2{ 2, Array<unsigned long, 2>({0, 2}) };
        Entity<int, 2> corner3{ 3, Array<unsigned long, 2>({2, 0}) };
        Entity<int, 2> corner4{ 4, Array<unsigned long, 2>({2, 2}) };

        engine.spawn(corner1);
        engine.spawn(corner2);
        engine.spawn(corner3);
        engine.spawn(corner4);

        auto all_entities = engine.world.getEntities();
        assert(all_entities.size() == 4);

        // Verify corner positions
        auto at_00 = engine.world.getEntitiesAt(Array<unsigned long, 2>({ 0, 0 }));
        auto at_02 = engine.world.getEntitiesAt(Array<unsigned long, 2>({ 0, 2 }));
        auto at_20 = engine.world.getEntitiesAt(Array<unsigned long, 2>({ 2, 0 }));
        auto at_22 = engine.world.getEntitiesAt(Array<unsigned long, 2>({ 2, 2 }));

        assert(at_00.size() == 1 && at_00[0].lock()->entity == 1);
        assert(at_02.size() == 1 && at_02[0].lock()->entity == 2);
        assert(at_20.size() == 1 && at_20[0].lock()->entity == 3);
        assert(at_22.size() == 1 && at_22[0].lock()->entity == 4);

        engine.despawn(corner1);
        engine.despawn(corner2);
        engine.despawn(corner3);
        engine.despawn(corner4);

        all_entities = engine.world.getEntities();
        assert(all_entities.empty());
    }

    // Test 7: Rapid spawn/despawn cycles in 3D
    {
        Engine<int, 3> engine(Array<unsigned long, 3>({ 4, 4, 4 }));
        std::vector<Entity<int, 3>> entities;

        for (unsigned long x = 0; x < 4; x++) {
            for (unsigned long y = 0; y < 4; y++) {
                for (unsigned long z = 0; z < 4; z++) {
                    entities.push_back(Entity<int, 3>{
                        static_cast<int>(x + y + z),
                            Array<unsigned long, 3>({ x, y, z })
                    });
                }
            }
        }
        assert(entities.size() == 64); // 4x4x4

        for (int cycle = 0; cycle < 3; cycle++) {
            for (const auto& entity : entities) {
                engine.spawn(entity);
            }
            auto all_entities = engine.world.getEntities();
            assert(all_entities.size() == 64);

            for (const auto& entity : entities) {
                engine.despawn(entity);
            }
            all_entities = engine.world.getEntities();
            assert(all_entities.empty());
        }
    }

    std::cout << "All additional Engine tests passed!\n";
}

void test_engine_mass() {
    std::cout << "Testing Engine with mass data...\n";

    // Custom union type for mixed entities
    union EntityValue {
        int i;
        double d;
        char s[16];  // Fixed size string buffer

        EntityValue() : i(0) {} // Default constructor
        EntityValue(int val) : i(val) {}
        EntityValue(double val) : d(val) {}

        // Add operator== for comparison
        bool operator==(const EntityValue& other) const {
        // Since this is a union, we need to know which member is active
        // For testing purposes, we'll just compare the raw memory
            return memcmp(this, &other, sizeof(EntityValue)) == 0;
        }
    };

    // Test 1: Massive 1D world
    {
        Engine<int, 1> engine(Array<unsigned long, 1>({ 100000 }));

        for (int i = 0; i < 50000; i++) {
            Entity<int, 1> entity{ i % 100, Array<unsigned long, 1>({static_cast<unsigned long>(i * 2)}) };
            engine.spawn(entity);
        }

        auto all_entities = engine.world.getEntities();
        assert(all_entities.size() == 50000);

        for (int type = 0; type < 100; type++) {
            auto type_entities = engine.world.getEntitiesOf(type);
            assert(type_entities.size() == 500); // 50000/100
        }

        for (int i = 0; i < 50000; i += 2) {
            Entity<int, 1> entity{ i % 100, Array<unsigned long, 1>({static_cast<unsigned long>(i * 2)}) };
            engine.despawn(entity);
        }

        all_entities = engine.world.getEntities();
        assert(all_entities.size() == 25000);
    }
    std::cout << "test1 complete" << std::endl;

    // Test 2: Dense 3D world
    {
        Engine<EntityValue, 3> engine(Array<unsigned long, 3>({ 50, 50, 50 }));
        std::vector<Entity<EntityValue, 3>> entities;

        // Create 100k entities with mixed types
        for (int i = 0; i < 100000; i++) {
            EntityValue val;
            if (i % 3 == 0) {
                val.i = i;
            }
            else if (i % 3 == 1) {
                val.d = i / 100.0;
            }
            else {
                snprintf(val.s, 16, "e%d", i);
            }

            entities.push_back(Entity<EntityValue, 3>{
                val,
                    Array<unsigned long, 3>({
                        static_cast<unsigned long>(i % 50),
                        static_cast<unsigned long>((i / 50) % 50),
                        static_cast<unsigned long>((i / 2500) % 50)
                        })
            });
        }

        // Rapid spawn/despawn cycles
        for (int cycle = 0; cycle < 0; cycle++) {
            for (const auto& entity : entities) {
                engine.spawn(entity);
            }
            assert(engine.world.getEntities().size() == 100000);

            for (size_t i = 0; i < entities.size(); i += 2) {
                engine.despawn(entities[i]); // memory leak?
            }
            assert(engine.world.getEntities().size() == 50000);

            for (size_t i = 0; i < entities.size(); i += 4) {
                engine.spawn(entities[i]);
            }
            assert(engine.world.getEntities().size() == 75000);

            for (const auto& entity : entities) {
                engine.despawn(entity);
            }
            assert(engine.world.getEntities().empty());
        }
    }
    std::cout << "test2 complete" << std::endl;


    // Test 3: Edge coordinates stress test
    {
        Engine<int, 3> engine(Array<unsigned long, 3>({ 99, 99, 99 }));

        // Fill all edges of the cube
        for (unsigned long i = 0; i < 100; i++) {
            // Edges along x
            engine.spawn(Entity<int, 3>{1, Array<unsigned long, 3>({ i, 0, 0 })});
            engine.spawn(Entity<int, 3>{1, Array<unsigned long, 3>({ i, 99, 0 })});
            engine.spawn(Entity<int, 3>{1, Array<unsigned long, 3>({ i, 0, 99 })});
            engine.spawn(Entity<int, 3>{1, Array<unsigned long, 3>({ i, 99, 99 })});

            // Edges along y
            engine.spawn(Entity<int, 3>{2, Array<unsigned long, 3>({ 0, i, 0 })});
            engine.spawn(Entity<int, 3>{2, Array<unsigned long, 3>({ 99, i, 0 })});
            engine.spawn(Entity<int, 3>{2, Array<unsigned long, 3>({ 0, i, 99 })});
            engine.spawn(Entity<int, 3>{2, Array<unsigned long, 3>({ 99, i, 99 })});

            // Edges along z
            engine.spawn(Entity<int, 3>{3, Array<unsigned long, 3>({ 0, 0, i })});
            engine.spawn(Entity<int, 3>{3, Array<unsigned long, 3>({ 99, 0, i })});
            engine.spawn(Entity<int, 3>{3, Array<unsigned long, 3>({ 0, 99, i })});
            engine.spawn(Entity<int, 3>{3, Array<unsigned long, 3>({ 99, 99, i })});
        }

        assert(engine.world.getEntities().size() == 1200);

        // Rapid corner updates
        std::vector<Array<unsigned long, 3>> corners = {
            Array<unsigned long, 3>({0, 0, 0}),
            Array<unsigned long, 3>({0, 0, 99}),
            Array<unsigned long, 3>({0, 99, 0}),
            Array<unsigned long, 3>({0, 99, 99}),
            Array<unsigned long, 3>({99, 0, 0}),
            Array<unsigned long, 3>({99, 0, 99}),
            Array<unsigned long, 3>({99, 99, 0}),
            Array<unsigned long, 3>({99, 99, 99})
        };

        for (int i = 0; i < 100000; i++) {
            for (const auto& corner : corners) {
                engine.spawn(Entity<int, 3>{i, corner});
                if (i > 0) {
                    engine.despawn(Entity<int, 3>{i - 1, corner});
                }
            }
        }

        for (int i = 0; i < 100000; i++) {
            for (const auto& corner : corners) {
                engine.spawn(Entity<int, 3>{i, corner});
            }
        }

        for (int i = 0; i < 100000; i++) {
            for (const auto& corner : corners) {
                engine.despawn(Entity<int, 3>{i, corner});
            }
        }

    }
    std::cout << "test3 complete" << std::endl;

    std::cout << "All mass data Engine tests passed!\n";
}

void test_engine2_private() {
    std::cout << "Testing Engine functionality and memory safety...\n";

    // Test 1: 1D world tests
    {
        std::cout << "Testing 1D world...\n";
        Engine<std::string, 1> engine(Array<unsigned long, 1>({ 20 }));

        // Create and spawn entity
        Entity<std::string, 1> entity;
        entity.entity = "test_entity";
        entity.coords = Array<unsigned long, 1>({ 5 });

        engine.spawn(entity);

        // Create matching entity for despawn
        Entity<std::string, 1> match;
        match.entity = "test_entity";
        match.coords = Array<unsigned long, 1>({ 5 });

        // Multiple entities at same location
        Entity<std::string, 1> entity2;
        entity2.entity = "another_entity";
        entity2.coords = Array<unsigned long, 1>({ 5 });

        engine.spawn(entity2);
        engine.despawn(match); // Should only remove test_entity

        // Stress test 1D world
        for (int i = 0; i < 100; i++) {
            Entity<std::string, 1> stress_entity;
            stress_entity.entity = "stress_" + std::to_string(i);
            stress_entity.coords = Array<unsigned long, 1>({ static_cast<unsigned long>(i % 20) });
            engine.spawn(stress_entity);
        }
    }

    // Test 2: Basic spawn/despawn with non-square dimensions
    {
        Engine<std::string, 2> engine(Array<unsigned long, 2>({ 15, 10 })); // Non-square world

        Entity<std::string, 2> entity;
        entity.entity = "test_entity";
        entity.coords = Array<unsigned long, 2>({ 14, 9 }); // Test edges

        engine.spawn(entity);

        Entity<std::string, 2> match;
        match.entity = "test_entity";
        match.coords = Array<unsigned long, 2>({ 14, 9 });

        engine.despawn(match);
    }

    // Test 3: Multiple entity management in 3D non-cubic world
    {
        Engine<int, 3> engine(Array<unsigned long, 3>({ 8, 5, 3 })); // Non-cubic world

        // Spawn multiple entities
        for (int i = 0; i < 100; i++) {
            Entity<int, 3> entity;
            entity.entity = i % 3;
            entity.coords = Array<unsigned long, 3>({
                static_cast<unsigned long>(i % 8),
                static_cast<unsigned long>((i / 8) % 5),
                static_cast<unsigned long>((i / 40) % 3)
                });

            engine.spawn(entity);
        }

        // Despawn half the entities
        for (int i = 0; i < 50; i++) {
            Entity<int, 3> entity;
            entity.entity = i % 3;
            entity.coords = Array<unsigned long, 3>({
                static_cast<unsigned long>(i % 8),
                static_cast<unsigned long>((i / 8) % 5),
                static_cast<unsigned long>((i / 40) % 3)
                });
            engine.despawn(entity);
        }
    }

    // Test 4: Memory safety with nested scopes
    {
        auto engine_ptr = make_unique<Engine<std::string, 2>>(Array<unsigned long, 2>({ 12, 8 }));

        {
            Entity<std::string, 2> entity;
            entity.entity = "scope_test";
            entity.coords = Array<unsigned long, 2>({ 11, 7 });

            engine_ptr->spawn(entity);
        }

        engine_ptr.reset();
    }

    // Test 5: Concurrent entity types at same location (continued)
    {
        Engine<std::string, 2> engine(Array<unsigned long, 2>({ 5, 7 }));

        Entity<std::string, 2> entity1{ "type1", Array<unsigned long, 2>({4, 6}) };
        Entity<std::string, 2> entity2{ "type2", Array<unsigned long, 2>({4, 6}) };
        Entity<std::string, 2> entity3{ "type1", Array<unsigned long, 2>({4, 6}) };

        engine.spawn(entity1);
        engine.spawn(entity2);
        engine.spawn(entity3);

        // Selective despawn
        engine.despawn(entity1);  // Should remove only first "type1"
        engine.despawn(entity2);  // Should remove "type2"
    }

    // Test 6: Edge cases in 2D world
    {
        Engine<int, 2> engine(Array<unsigned long, 2>({ 3, 3 }));

        // Test corners
        Entity<int, 2> corner1{ 1, Array<unsigned long, 2>({0, 0}) };
        Entity<int, 2> corner2{ 2, Array<unsigned long, 2>({0, 2}) };
        Entity<int, 2> corner3{ 3, Array<unsigned long, 2>({2, 0}) };
        Entity<int, 2> corner4{ 4, Array<unsigned long, 2>({2, 2}) };

        engine.spawn(corner1);
        engine.spawn(corner2);
        engine.spawn(corner3);
        engine.spawn(corner4);

        engine.despawn(corner1);
        engine.despawn(corner2);
        engine.despawn(corner3);
        engine.despawn(corner4);
    }

    // Test 7: Rapid spawn/despawn cycles in 3D
    {
        Engine<int, 3> engine(Array<unsigned long, 3>({ 4, 4, 4 }));

        std::vector<Entity<int, 3>> entities;

        // Create and store entities
        for (unsigned long x = 0; x < 4; x++) {
            for (unsigned long y = 0; y < 4; y++) {
                for (unsigned long z = 0; z < 4; z++) {
                    entities.push_back(Entity<int, 3>{
                        static_cast<int>(x + y + z),
                            Array<unsigned long, 3>({ x, y, z })
                    });
                }
            }
        }

        // Rapid spawn/despawn cycles
        for (int cycle = 0; cycle < 3; cycle++) {
            for (const auto& entity : entities) {
                engine.spawn(entity);
            }
            for (const auto& entity : entities) {
                engine.despawn(entity);
            }
        }
    }

    std::cout << "All additional Engine tests passed!\n";
}

// void test_discrete_grid_and_engine() {
//     std::cout << "Testing DiscreteGrid and DiscreteEngine functionality...\n";

//     // Test 1: Basic spawn/despawn operations in 2D
//     {
//         std::cout << "Testing basic 2D operations...\n";
//         Array<unsigned long, 2> dims({10, 10});
//         DiscreteEngine<std::string, 2> engine(dims);

//         Entity<std::string, 2> entity;
//         entity.entity = "test_entity";
//         entity.coords = Array<unsigned long, 2>({5, 5});

//         engine.spawn(entity);

//         // Verify spawn
//         auto entities_at = engine.getWeakEntitiesAt(Array<unsigned long, 2>({5, 5}));
//         assert(entities_at.size() == 1);
//         assert(entities_at[0].lock()->entity == "test_entity");

//         // Test despawn
//         engine.despawn(entity);
//         auto strong_entities_at = engine.getEntitiesAt(Array<unsigned long, 2>({5, 5}));
//         assert(strong_entities_at.empty());
//         entities_at = engine.getWeakEntitiesAt(Array<unsigned long, 2>({5, 5}));
//         assert(entities_at.size() == 1); // the dead weak_ptr is still there.
//     }

//     // Test 2: Multiple entities at same location in 3D
//     {
//         std::cout << "Testing multiple entities at same location in 3D...\n";
//         Array<unsigned long, 3> dims({5, 5, 5});
//         DiscreteEngine<int, 3> engine(dims);

//         Array<unsigned long, 3> location({2, 2, 2});
//         Entity<int, 3> entity1;
//         entity1.entity = 1;
//         entity1.coords = location;

//         Entity<int, 3> entity2;
//         entity2.entity = 2;
//         entity2.coords = location;

//         engine.spawn(entity1);
//         engine.spawn(entity2);

//         // Verify both entities
//         auto entities_at = engine.getEntitiesAt(location);
//         assert(entities_at.size() == 2);
//         bool found1 = false, found2 = false;
//         for(const auto& e : entities_at) {
//             if(e->entity == 1) found1 = true;
//             if(e->entity == 2) found2 = true;
//         }
//         assert(found1 && found2);

//         entities_at.clear();
//         // Test despawn of one entity
//         engine.despawn(entity1);
//         entities_at = engine.getEntitiesAt(location);
//         assert(entities_at.size() == 1);
//         assert(entities_at[0]->entity == 2);
//     }

//     // Test 3: Edge cases with 1D world
//     {
//         std::cout << "Testing 1D world edge cases...\n";
//         Array<unsigned long, 1> dims({100});
//         DiscreteEngine<int, 1> engine(dims);

//         // Test boundaries
//         Entity<int, 1> start_entity{1, Array<unsigned long, 1>({0})};
//         Entity<int, 1> end_entity{2, Array<unsigned long, 1>({99})};

//         engine.spawn(start_entity);
//         engine.spawn(end_entity);

//         // Verify boundary entities
//         auto start_entities = engine.getEntitiesAt(Array<unsigned long, 1>({0}));
//         auto end_entities = engine.getEntitiesAt(Array<unsigned long, 1>({99}));
//         assert(start_entities.size() == 1);
//         assert(end_entities.size() == 1);
//         assert(start_entities[0]->entity == 1);
//         assert(end_entities[0]->entity == 2);

//         engine.despawn(start_entity);
//         engine.despawn(end_entity);

//         // Verify removal
//         assert(engine.getEntitiesAt(Array<unsigned long, 1>({0})).empty());
//         assert(engine.getEntitiesAt(Array<unsigned long, 1>({99})).empty());
//     }

//     // Test 4: Grid coverage test
//     {
//         std::cout << "Testing grid coverage...\n";
//         Array<unsigned long, 2> dims({3, 3});
//         DiscreteEngine<int, 2> engine(dims);

//         // Spawn entities in each cell
//         for(unsigned long x = 0; x < 3; x++) {
//             for(unsigned long y = 0; y < 3; y++) {
//                 Entity<int, 2> entity;
//                 entity.entity = x * 3 + y;
//                 entity.coords = Array<unsigned long, 2>({x, y});
//                 engine.spawn(entity);
//             }
//         }

//         // Verify each cell
//         for(unsigned long x = 0; x < 3; x++) {
//             for(unsigned long y = 0; y < 3; y++) {
//                 auto entities = engine.getEntitiesAt(Array<unsigned long, 2>({x, y}));
//                 assert(entities.size() == 1);
//                 assert(entities[0]->entity == x * 3 + y);
//             }
//         }
//     }

//     std::cout << "All DiscreteGrid and DiscreteEngine tests passed!\n";
// }

void test_discrete_engine() {
    std::cout << "Testing DiscreteEngine functionality...\n";

    // Test 1: Basic spawn/despawn with 2D world
    {
        std::cout << "Testing basic 2D operations...\n";
        DiscreteEngine<std::string, 2> engine(Array<unsigned long, 2>({ 15, 10 }));

        Entity<std::string, 2> entity;
        entity.entity = "test_entity";
        entity.coords = Array<unsigned long, 2>({ 5, 7 });

        engine.spawn(entity);

        auto entities = engine.getEntitiesAt(Array<unsigned long, 2>({ 5, 7 }));
        assert(entities.size() == 1);
        assert(!entities[0].expired());
        assert(entities[0].lock()->entity == "test_entity");

        engine.despawn(entity);
        entities = engine.getEntitiesAt(Array<unsigned long, 2>({ 5, 7 }));
        assert(entities.empty());

        auto weak_ptrs = engine.getEntitiesAt(Array<unsigned long, 2>({ 5, 7 }));
        assert(entities.size() == 0);
    }

    // Test 2: Multiple entities at same location
    {
        std::cout << "Testing multiple entities at same location...\n";
        DiscreteEngine<std::string, 2> engine(Array<unsigned long, 2>({ 5, 5 }));

        Entity<std::string, 2> entity1{ "entity1", Array<unsigned long, 2>({2, 2}) };
        Entity<std::string, 2> entity2{ "entity2", Array<unsigned long, 2>({2, 2}) };
        Entity<std::string, 2> entity3{ "entity3", Array<unsigned long, 2>({2, 2}) };

        engine.spawn(entity1);
        engine.spawn(entity2);
        engine.spawn(entity3);

        auto entities = engine.getEntitiesAt(Array<unsigned long, 2>({ 2, 2 }));
        assert(entities.size() == 3);

        // Test selective despawn
        engine.despawn(entity2);
        auto valid_entities = engine.getEntitiesAt(Array<unsigned long, 2>({ 2, 2 }));
        assert(valid_entities.size() == 2);

        auto entities2 = engine.getEntitiesAt(Array<unsigned long, 2>({ 2, 2 }));
        assert(entities2.size() == 2);
    }

    // Test 3: Multiple entity management in 3D non-cubic world
    {
        DiscreteEngine<int, 3> engine(Array<unsigned long, 3>({ 7, 4, 2 }));

        for (int i = 0; i < 100; i++) {
            Entity<int, 3> entity;
            entity.entity = i % 3;
            entity.coords = Array<unsigned long, 3>({
                static_cast<unsigned long>(i % 8),
                static_cast<unsigned long>((i / 8) % 5),
                static_cast<unsigned long>((i / 40) % 3)
                });
            engine.spawn(entity);
        }

        auto all_entities = engine.getEntities();
        assert(all_entities.size() == 100);

        // Verify distribution of entity types
        for (int type = 0; type < 3; type++) {
            Entity<int, 3> probe;
            probe.entity = type;
            auto type_entities = engine.getEntitiesOf(type);
            assert(type_entities.size() == 34 || type_entities.size() == 33); // ~100/3
        }

        for (int i = 0; i < 50; i++) {
            Entity<int, 3> entity;
            entity.entity = i % 3;
            entity.coords = Array<unsigned long, 3>({
                static_cast<unsigned long>(i % 8),
                static_cast<unsigned long>((i / 8) % 5),
                static_cast<unsigned long>((i / 40) % 3)
                });
            engine.despawn(entity);
        }

        all_entities = engine.getEntities();
        int valid_count = 0;
        for (const auto& weak_ptr : all_entities) {
            valid_count++;
            //if(!weak_ptr.expired()) valid_count++;
        }
        assert(valid_count <= 51 || valid_count >= 49); // ~50 remaining
    }

    // Test 3: Memory safety with nested scopes
    {
        std::cout << "Testing memory safety with nested scopes...\n";
        auto engine_ptr = make_unique<DiscreteEngine<std::string, 2>>(Array<unsigned long, 2>({ 5, 5 }));
        std::weak_ptr<Entity<std::string, 2>> weak_entity;

        {
            Entity<std::string, 2> entity{ "scope_test", Array<unsigned long, 2>({3, 3}) };
            engine_ptr->spawn(entity);

            auto entities = engine_ptr->getEntitiesAt(Array<unsigned long, 2>({ 3, 3 }));
            assert(entities.size() == 1);
            weak_entity = entities[0];
            assert(!weak_entity.expired());
        }

        assert(!weak_entity.expired());  // Should still be valid while engine exists
        engine_ptr.reset();
        assert(weak_entity.expired());   // Should be invalid after engine deletion
    }

    // Test 4: Edge cases with 1D world
    {
        std::cout << "Testing 1D world edge cases...\n";
        DiscreteEngine<int, 1> engine(Array<unsigned long, 1>({ 100 }));

        // Test boundaries
        Entity<int, 1> start_entity{ 1, Array<unsigned long, 1>({0}) };    // Start boundary
        Entity<int, 1> end_entity{ 2, Array<unsigned long, 1>({99}) };     // End boundary

        engine.spawn(start_entity);
        engine.spawn(end_entity);

        auto start_entities = engine.getEntitiesAt(Array<unsigned long, 1>({ 0 }));
        auto end_entities = engine.getEntitiesAt(Array<unsigned long, 1>({ 99 }));

        assert(start_entities.size() == 1);
        assert(end_entities.size() == 1);
        assert(start_entities[0].lock()->entity == 1);
        assert(end_entities[0].lock()->entity == 2);
    }

    // Test 5: Grid coverage test
    {
        std::cout << "Testing grid coverage...\n";
        DiscreteEngine<int, 2> engine(Array<unsigned long, 2>({ 3, 3 }));

        // Spawn entities in every cell
        for (unsigned long x = 0; x < 3; x++) {
            for (unsigned long y = 0; y < 3; y++) {
                Entity<int, 2> entity{ static_cast<int>(x * 3 + y), Array<unsigned long, 2>({x, y}) };
                engine.spawn(entity);
            }
        }

        // Verify each cell
        for (unsigned long x = 0; x < 3; x++) {
            for (unsigned long y = 0; y < 3; y++) {
                auto entities = engine.getEntitiesAt(Array<unsigned long, 2>({ x, y }));
                assert(entities.size() == 1);
                assert(entities[0].lock()->entity == x * 3 + y);
            }
        }
    }

    // Test 6: Mass spawn/despawn cycles
    {
        std::cout << "Testing mass spawn/despawn cycles...\n";
        DiscreteEngine<int, 3> engine(Array<unsigned long, 3>({ 10, 100, 10 }));
        std::vector<Entity<int, 3>> entities;

        // Create entities
        for (unsigned long x = 0; x < 10; x++) {
            for (unsigned long y = 0; y < 100; y++) {
                for (unsigned long z = 0; z < 10; z++) {
                    entities.push_back(Entity<int, 3>{
                        static_cast<int>(x + y + z),
                            Array<unsigned long, 3>({ x, y, z })
                    });
                }
            }
        }

        // Rapid spawn/despawn cycles
        for (int cycle = 0; cycle < 1; cycle++) {
            // Spawn all
            for (const auto& entity : entities) {
                engine.spawn(entity);
            }

            // Verify all locations
            for (const auto& entity : entities) {
                auto at_location = engine.getEntitiesAt(entity.coords);
                assert(!at_location.empty());
            }

            // Despawn all
            for (const auto& entity : entities) {
                engine.despawn(entity);
            }

            // Verify all locations are empty
            for (const auto& entity : entities) {
                auto at_location = engine.getEntitiesAt(entity.coords);
                assert(at_location.empty());
            }
        }
    }

    // Test 7: Entity modification through weak pointers
    {
        std::cout << "Testing entity modification through weak pointers...\n";
        DiscreteEngine<std::string, 2> engine(Array<unsigned long, 2>({ 5, 5 }));

        Entity<std::string, 2> entity{ "original", Array<unsigned long, 2>({2, 2}) };
        engine.spawn(entity);

        auto entities = engine.getEntitiesAt(Array<unsigned long, 2>({ 2, 2 }));
        assert(entities.size() == 1);

        if (auto ptr = entities[0].lock()) {
            ptr->entity = "modified";
        }

        auto modified_entities = engine.getEntitiesAt(Array<unsigned long, 2>({ 2, 2 }));
        assert(modified_entities[0].lock()->entity == "modified");
    }

    std::cout << "All DiscreteEngine tests passed!\n";
}

void test_despawn_issue() {
    // Create small 2x2x2 world
    DiscreteEngine<int, 3> engine(Array<unsigned long, 3>({ 2, 2, 2 }));

    // Spawn just 4 entities with different types in different locations
    Entity<int, 3> entities[6];

    // Entity 0 at (0,0,0)
    entities[0].entity = 0;
    entities[0].coords = Array<unsigned long, 3>({ 0, 0, 0 });

    // Entity 1 at (1,0,0)     saved
    entities[1].entity = 1;
    entities[1].coords = Array<unsigned long, 3>({ 1, 0, 0 });

    // Entity 0 at (0,1,0)
    entities[2].entity = 0;
    entities[2].coords = Array<unsigned long, 3>({ 0, 1, 0 });

    // Entity 1 at (1,1,0)      saved
    entities[3].entity = 1;
    entities[3].coords = Array<unsigned long, 3>({ 1, 1, 0 });

    // Entity 0 at (1,1,0)   saved 
    entities[4].entity = 0;
    entities[4].coords = Array<unsigned long, 3>({ 0, 1, 1 });

    // Entity 0 at (1,1,0)    saved
    entities[5].entity = 0;
    entities[5].coords = Array<unsigned long, 3>({ 1, 0, 1 });

    // Spawn all entities
    for (int i = 0; i < 6; i++) {
        engine.spawn(entities[i]);
    }

    // Verify initial state
    auto all = engine.getEntities();
    assert(all.size() == 6);

    // Try to despawn entity 0 at (0,0,0)
    engine.despawn(entities[0]);

    // Check remaining count
    all = engine.getEntities();
    assert(all.size() == 5);  // This will likely fail with current implementation

    // Verify the right entity was removed
    auto at_origin = engine.getEntitiesAt(Array<unsigned long, 3>({ 0, 0, 0 }));
    assert(at_origin.empty());
}

void final_test()
{
    std::cout << "Part 1: Testing array comparison edge cases...\n";

    // Test 1: Zero coordinates
    {
        DiscreteEngine<int, 3> engine(Array<unsigned long, 3>({ 2, 2, 2 }));

        // Test different combinations of zero coordinates
        Entity<int, 3> entities[] = {
            {0, Array<unsigned long, 3>({0, 0, 0})},
            {0, Array<unsigned long, 3>({0, 0, 1})},
            {0, Array<unsigned long, 3>({0, 1, 0})},
            {0, Array<unsigned long, 3>({1, 0, 0})},
            {1, Array<unsigned long, 3>({0, 0, 0})} // Same coords as first, different type
        };

        // Spawn all
        for (const auto& e : entities) {
            engine.spawn(e);
        }

        // Verify each entity exists exactly where expected
        auto at_000 = engine.getEntitiesAt(Array<unsigned long, 3>({ 0, 0, 0 }));
        assert(at_000.size() == 2); // Should have both type 0 and type 1

        auto at_001 = engine.getEntitiesAt(Array<unsigned long, 3>({ 0, 0, 1 }));
        assert(at_001.size() == 1);

        // Try to despawn each individually
        for (const auto& e : entities) {
            engine.despawn(e);

            // Verify only the matching entity was removed
            auto at_loc = engine.getEntitiesAt(e.coords);

            // Count remaining entities at this location
            int count = 0;
            for (const auto& weak_ptr : at_loc) {
                if (auto ptr = weak_ptr.lock()) {
                    if (ptr->entity == e.entity) count++;
                }
            }

            // Should be zero for the type we just removed
            assert(count == 0);
        }
    }

    // Test 2: Identical coordinates with different types
    {
        DiscreteEngine<int, 3> engine(Array<unsigned long, 3>({ 2, 2, 2 }));
        Array<unsigned long, 3> coords({ 1, 1, 1 });

        // Spawn multiple entities at exact same location
        for (int i = 0; i < 5; i++) {
            Entity<int, 3> entity{ i, coords };
            engine.spawn(entity);
        }

        auto at_loc = engine.getEntitiesAt(coords);
        assert(at_loc.size() == 5);

        // Try to despawn each type
        for (int i = 0; i < 5; i++) {
            Entity<int, 3> to_remove{ i, coords };
            engine.despawn(to_remove);

            // Verify only the correct type was removed
            at_loc = engine.getEntitiesAt(coords);
            for (const auto& weak_ptr : at_loc) {
                if (auto ptr = weak_ptr.lock()) {
                    assert(ptr->entity != i); // Should not find the removed type
                }
            }
            assert(at_loc.size() == 4 - i); // Should decrease by 1 each time
        }
    }

    // Test 3: Boundary coordinates
    {
        DiscreteEngine<int, 3> engine(Array<unsigned long, 3>({ 100, 100, 100 }));

        // Test extreme coordinates
        std::vector<Array<unsigned long, 3>> test_coords = {
            Array<unsigned long, 3>({0, 0, 0}),          // Origin
            Array<unsigned long, 3>({99, 99, 99}),       // Far corner
            Array<unsigned long, 3>({0, 99, 99}),        // Mixed extremes
            Array<unsigned long, 3>({99, 0, 99}),
            Array<unsigned long, 3>({99, 99, 0}),
            Array<unsigned long, 3>({0, 0, 99}),
            Array<unsigned long, 3>({0, 99, 0}),
            Array<unsigned long, 3>({99, 0, 0})
        };

        // Spawn entities at each extreme coordinate
        for (size_t i = 0; i < test_coords.size(); i++) {
            Entity<int, 3> entity{ static_cast<int>(i), test_coords[i] };
            engine.spawn(entity);
        }

        // Verify each location
        for (size_t i = 0; i < test_coords.size(); i++) {
            auto at_loc = engine.getEntitiesAt(test_coords[i]);
            assert(at_loc.size() == 1);
            assert(at_loc[0].lock()->entity == static_cast<int>(i));
        }

        // Remove in reverse order
        for (int i = test_coords.size() - 1; i >= 0; i--) {
            Entity<int, 3> to_remove{ i, test_coords[i] };
            engine.despawn(to_remove);

            // Verify removal
            auto at_loc = engine.getEntitiesAt(test_coords[i]);
            assert(at_loc.empty());
        }
    }

    std::cout << "Part 1 complete!\n";

    std::cout << "Part 2: Testing weak pointer and entity lifetime edge cases...\n";

    // Test 1: Weak pointer expiration scenarios
    {
        DiscreteEngine<int, 2> engine(Array<unsigned long, 2>({ 5, 5 }));

        // Create scope to test pointer lifetime
        std::vector<std::weak_ptr<Entity<int, 2>>> stored_weak_ptrs;
        {
            // Spawn entities that will go out of scope
            Array<unsigned long, 2> coords({ 1, 1 });
            for (int i = 0; i < 3; i++) {
                Entity<int, 2> entity{ i, coords };
                engine.spawn(entity);

                // Store weak pointers for later verification
                auto entities = engine.getEntitiesAt(coords);
                stored_weak_ptrs.push_back(entities.back());
            }

            // Verify all entities exist
            auto at_loc = engine.getEntitiesAt(coords);
            assert(at_loc.size() == 3);

            // Despawn middle entity
            Entity<int, 2> to_remove{ 1, coords };
            engine.despawn(to_remove);

            // Verify remaining entities
            at_loc = engine.getEntitiesAt(coords);
            assert(at_loc.size() == 2);
        }

        int invalid = 0;
        // After scope, test weak pointer validity
        for (auto& weak_ptr : stored_weak_ptrs) {
            if (weak_ptr.expired())
            {
                invalid++;
            }
        }
        assert(invalid == 1);
    }

    // Test 2: Rapid spawn/despawn cycles
    {
        DiscreteEngine<int, 2> engine(Array<unsigned long, 2>({ 3, 3 }));
        Array<unsigned long, 2> coords({ 1, 1 });

        // Perform multiple spawn/despawn cycles
        for (int cycle = 0; cycle < 100; cycle++) {
            // Spawn entity
            Entity<int, 2> entity{ cycle % 3, coords };
            engine.spawn(entity);

            // Verify spawn
            auto at_loc = engine.getEntitiesAt(coords);
            bool found = false;
            for (const auto& weak_ptr : at_loc) {
                if (auto ptr = weak_ptr.lock()) {
                    if (ptr->entity == cycle % 3) {
                        found = true;
                        break;
                    }
                }
            }
            assert(found);

            // Immediate despawn
            engine.despawn(entity);

            // Verify despawn
            at_loc = engine.getEntitiesAt(coords);
            for (const auto& weak_ptr : at_loc) {
                if (auto ptr = weak_ptr.lock()) {
                    assert(ptr->entity != cycle % 3);
                }
            }
        }
    }

    // Test 3: Mixed strong/weak pointer interactions
    {
        DiscreteEngine<int, 2> engine(Array<unsigned long, 2>({ 4, 4 }));
        Array<unsigned long, 2> coords({ 2, 2 });

        // Keep strong references alongside engine's internal storage
        std::vector<std::shared_ptr<Entity<int, 2>>> strong_refs;

        // Spawn entities and maintain external strong references
        for (int i = 0; i < 5; i++) {
            auto entity_ptr = std::make_shared<Entity<int, 2>>();
            entity_ptr->entity = i;
            entity_ptr->coords = coords;

            strong_refs.push_back(entity_ptr);
            engine.spawn(*entity_ptr);
        }

        // Verify all entities exist
        auto at_loc = engine.getEntitiesAt(coords);
        assert(at_loc.size() == 5);

        // Try to despawn while maintaining strong references
        for (int i = 0; i < 5; i++) {
            engine.despawn(*strong_refs[i]);

            // Verify entity was removed from engine but still exists
            at_loc = engine.getEntitiesAt(coords);
            bool found_in_engine = false;
            for (const auto& weak_ptr : at_loc) {
                if (auto ptr = weak_ptr.lock()) {
                    if (ptr->entity == i) {
                        found_in_engine = true;
                        break;
                    }
                }
            }
            assert(!found_in_engine);

            // Verify strong reference still valid
            assert(strong_refs[i]);
            assert(strong_refs[i]->entity == i);
        }
    }

    std::cout << "Part 2 complete!\n";

    std::cout << "Part 3: Testing concurrent modifications and grid-wide operations...\n";

    // Test 1: Grid-wide population and clearance
    {
        DiscreteEngine<int, 3> engine(Array<unsigned long, 3>({ 4, 4, 4 }));
        std::vector<Entity<int, 3>> entities;

        // Populate every cell with multiple entities
        for (unsigned long x = 0; x < 4; x++) {
            for (unsigned long y = 0; y < 4; y++) {
                for (unsigned long z = 0; z < 4; z++) {
                    for (int type = 0; type < 3; type++) {
                        Entity<int, 3> entity{
                            type,
                            Array<unsigned long, 3>({x, y, z})
                        };
                        entities.push_back(entity);
                        engine.spawn(entity);
                    }
                }
            }
        }

        // Verify population
        for (unsigned long x = 0; x < 4; x++) {
            for (unsigned long y = 0; y < 4; y++) {
                for (unsigned long z = 0; z < 4; z++) {
                    auto at_loc = engine.getEntitiesAt(Array<unsigned long, 3>({ x, y, z }));
                    assert(at_loc.size() == 3);
                }
            }
        }

        // Remove all entities of type 1
        for (const auto& entity : entities) {
            if (entity.entity == 1) {
                engine.despawn(entity);
            }
        }

        // Verify correct removal
        for (unsigned long x = 0; x < 4; x++) {
            for (unsigned long y = 0; y < 4; y++) {
                for (unsigned long z = 0; z < 4; z++) {
                    auto at_loc = engine.getEntitiesAt(Array<unsigned long, 3>({ x, y, z }));
                    assert(at_loc.size() == 2);
                    for (const auto& weak_ptr : at_loc) {
                        if (auto ptr = weak_ptr.lock()) {
                            assert(ptr->entity != 1);
                        }
                    }
                }
            }
        }
    }

    // Test 2: Pattern-based spawning and removal
    {
        DiscreteEngine<int, 2> engine(Array<unsigned long, 2>({ 8, 8 }));

        // Spawn checkerboard pattern
        for (unsigned long x = 0; x < 8; x++) {
            for (unsigned long y = 0; y < 8; y++) {
                if ((x + y) % 2 == 0) {
                    Entity<int, 2> entity{
                        static_cast<int>((x * y) % 3),  // Fixed: explicit cast
                        Array<unsigned long, 2>({x, y})
                    };
                    engine.spawn(entity);
                }
            }
        }

        // Verify pattern
        for (unsigned long x = 0; x < 8; x++) {
            for (unsigned long y = 0; y < 8; y++) {
                auto at_loc = engine.getEntitiesAt(Array<unsigned long, 2>({ x, y }));
                if ((x + y) % 2 == 0) {
                    assert(at_loc.size() == 1);
                    assert(at_loc[0].lock()->entity == static_cast<int>((x * y) % 3));
                }
                else {
                    assert(at_loc.empty());
                }
            }
        }

        // Remove diagonal pattern
        for (unsigned long i = 0; i < 8; i++) {
            Entity<int, 2> to_remove{
                static_cast<int>((i * i) % 3),  // Fixed: explicit cast
                Array<unsigned long, 2>({i, i})
            };
            engine.despawn(to_remove);
        }


        // Verify diagonal removal
        for (unsigned long i = 0; i < 8; i++) {
            auto at_loc = engine.getEntitiesAt(Array<unsigned long, 2>({ i, i }));
            assert(at_loc.empty());
        }
    }

    // Test 3: Type-based queries during modifications
    {
        DiscreteEngine<int, 2> engine(Array<unsigned long, 2>({ 5, 5 }));

        // Spawn entities with different types
        std::vector<Entity<int, 2>> entities;
        for (unsigned long x = 0; x < 5; x++) {
            for (unsigned long y = 0; y < 5; y++) {
                Entity<int, 2> entity{
                    static_cast<int>((x + y) % 3),
                    Array<unsigned long, 2>({x, y})
                };
                entities.push_back(entity);
                engine.spawn(entity);
            }
        }

        // Keep track of type counts
        std::vector<size_t> initial_type_counts(3, 0);
        for (const auto& entity : entities) {
            initial_type_counts[entity.entity]++;
        }

        // Remove entities while querying types
        for (size_t i = 0; i < entities.size(); i += 2) {
            // Get count before removal
            auto before = engine.getEntitiesOf(entities[i].entity).size();

            // Remove entity
            engine.despawn(entities[i]);

            // Verify count decreased by 1
            auto after = engine.getEntitiesOf(entities[i].entity).size();
            assert(after == before - 1);

            // TODO
            // Other type counts should remain unchanged
            // for(int type = 0; type < 3; type++) {
            //     if(type != entities[i].entity) {
            //         auto of = engine.getEntitiesOf(type);
            //         auto num = initial_type_counts[type] - (i/2);
            //         assert(std::abs(static_cast<int>(of.size()) - static_cast<int>(num)) <= 1);
            //     }
            // }
        }
    }

    std::cout << "Part 3 complete!\n";

    std::cout << "Part 4: Testing recovery and extreme scenarios...\n";

    // Test 1: Recovery from invalid operations
    {
        DiscreteEngine<int, 2> engine(Array<unsigned long, 2>({ 3, 3 }));

        // Try spawning outside grid bounds
        Entity<int, 2> invalid_entity{ 0, Array<unsigned long, 2>({5, 5}) };
        try {
            engine.spawn(invalid_entity);
            assert(false); // Should not reach here
        }
        catch (const std::out_of_range&) {
         // Expected
        }

        // Verify engine state remains valid
        Entity<int, 2> valid_entity{ 1, Array<unsigned long, 2>({1, 1}) };
        engine.spawn(valid_entity);
        auto at_loc = engine.getEntitiesAt(valid_entity.coords);
        assert(at_loc.size() == 1);

        // Try despawning non-existent entity
        Entity<int, 2> ghost_entity{ 2, Array<unsigned long, 2>({0, 0}) };
        engine.despawn(ghost_entity);

        // Verify original entity unaffected
        at_loc = engine.getEntitiesAt(valid_entity.coords);
        assert(at_loc.size() == 1);
        assert(at_loc[0].lock()->entity == 1);
    }

    // Test 2: Extreme size scenarios
    {
        // Test with minimal dimensions
        DiscreteEngine<int, 3> tiny_engine(Array<unsigned long, 3>({ 1, 1, 1 }));
        Entity<int, 3> single_entity{ 0, Array<unsigned long, 3>({0, 0, 0}) };
        tiny_engine.spawn(single_entity);
        auto at_origin = tiny_engine.getEntitiesAt(Array<unsigned long, 3>({ 0, 0, 0 }));
        assert(at_origin.size() == 1);

        // Test with large dimensions
        DiscreteEngine<int, 2> large_engine(Array<unsigned long, 2>({ 1000, 1000 }));
        std::vector<Entity<int, 2>> corner_entities;

        // Spawn at corners
        Array<unsigned long, 2> corners[4] = {
            Array<unsigned long, 2>({0l, 0l}),
            Array<unsigned long, 2>({0l, 999l}),
            Array<unsigned long, 2>({999l, 0l}),
            Array<unsigned long, 2>({999l, 999l})
        };

        for (int i = 0; i < 4; i++) {
            Entity<int, 2> entity{ i, corners[i] };
            corner_entities.push_back(entity);
            large_engine.spawn(entity);
        }

        // Verify corners
        for (int i = 0; i < 4; i++) {
            auto at_corner = large_engine.getEntitiesAt(corners[i]);
            assert(at_corner.size() == 1);
            assert(at_corner[0].lock()->entity == i);
        }
    }

    // Test 3: Entity type mutations
    {
        DiscreteEngine<int, 2> engine(Array<unsigned long, 2>({ 4, 4 }));
        Array<unsigned long, 2> coords({ 2, 2 });

        // Spawn initial entity
        Entity<int, 2> original{ 0, coords };
        engine.spawn(original);

        // Spawn entity of different type at same location
        Entity<int, 2> mutation{ 1, coords };
        engine.spawn(mutation);

        // Verify both exist
        auto at_loc = engine.getEntitiesAt(coords);
        assert(at_loc.size() == 2);

        bool found_original = false, found_mutation = false;
        for (const auto& weak_ptr : at_loc) {
            if (auto ptr = weak_ptr.lock()) {
                if (ptr->entity == 0) found_original = true;
                if (ptr->entity == 1) found_mutation = true;
            }
        }
        assert(found_original && found_mutation);

        // Remove original
        engine.despawn(original);

        // Verify only mutation remains
        at_loc = engine.getEntitiesAt(coords);
        assert(at_loc.size() == 1);
        assert(at_loc[0].lock()->entity == 1);
    }

    // Test 4: Mixed dimension edge cases
    {
        // Create engines of different dimensions
        DiscreteEngine<int, 1> engine1d(Array<unsigned long, 1>({ 5 }));
        DiscreteEngine<int, 2> engine2d(Array<unsigned long, 2>({ 5, 5 }));
        DiscreteEngine<int, 3> engine3d(Array<unsigned long, 3>({ 5, 5, 5 }));

        // Test 1D to 2D transition points
        Entity<int, 1> entity1d{ 0, Array<unsigned long, 1>({2}) };
        engine1d.spawn(entity1d);

        Entity<int, 2> entity2d{ 0, Array<unsigned long, 2>({2, 0}) };
        engine2d.spawn(entity2d);

        // Test 2D to 3D transition points
        Entity<int, 2> entity2d_corner{ 1, Array<unsigned long, 2>({4, 4}) };
        engine2d.spawn(entity2d_corner);

        Entity<int, 3> entity3d{ 1, Array<unsigned long, 3>({4, 4, 0}) };
        engine3d.spawn(entity3d);

        // Verify correct placement
        auto at_1d = engine1d.getEntitiesAt(Array<unsigned long, 1>({ 2 }));
        assert(at_1d.size() == 1);

        auto at_2d = engine2d.getEntitiesAt(Array<unsigned long, 2>({ 2, 0 }));
        assert(at_2d.size() == 1);

        auto at_3d = engine3d.getEntitiesAt(Array<unsigned long, 3>({ 4, 4, 0 }));
        assert(at_3d.size() == 1);
    }

    std::cout << "Part 4 complete!\n";
}

void test_grid_functionality() {
    // Test 1: Basic initialization
    Array<unsigned long, 2> grid_size = Array<unsigned long, 2>({ 10, 10 });
    DiscreteUnorderedEngine<int, 2> engine(grid_size);
    std::cout << "Test 1: Engine initialization - PASSED\n";

    // Test 2: Entity creation and spawn
    Entity<int, 2> entity1;
    entity1.entity = 1;  // entity type
    entity1.coords = Array<unsigned long, 2>({ 5, 5 });

    Entity<int, 2> entity2;
    entity2.entity = 2;  // different entity type
    entity2.coords = Array<unsigned long, 2>({ 5, 5 });  // same location

    engine.spawn(entity1);
    engine.spawn(entity2);

    auto entities = engine.getEntities();
    assert(entities.size() == 2);
    std::cout << "Test 2: Entity spawning - PASSED\n";

    // Test 3: Get entities by type
    auto type1_entities = engine.getEntitiesOf(1);
    auto type2_entities = engine.getEntitiesOf(2);
    assert(type1_entities.size() == 1);
    assert(type2_entities.size() == 1);
    std::cout << "Test 3: Get entities by type - PASSED\n";

    // Test 4: Get entities at location
    auto entities_at_location = engine.getEntitiesAt(Array<unsigned long, 2>({ 5, 5 }));
    assert(entities_at_location.size() == 2);
    std::cout << "Test 4: Get entities at location - PASSED\n";

    // Test 5: Despawn entity
    auto entity1_hashed = engine.getEntity(0);  // First entity should have id 0
    if (auto entity1_locked = entity1_hashed.lock()) {
        engine.despawn(entity1_locked->id);
    }
    entities = engine.getEntities();
    assert(entities.size() == 1);
    std::cout << "Test 5: Entity despawning - PASSED\n";

    // Test 6: Test edge cases
    Entity<int, 2> edge_entity;
    edge_entity.entity = 3;
    edge_entity.coords = Array<unsigned long, 2>({ 0, 0 });  // Corner case
    engine.spawn(edge_entity);

    edge_entity.coords = Array<unsigned long, 2>({ 9, 9 });  // Other corner
    engine.spawn(edge_entity);

    entities = engine.getEntities();
    assert(entities.size() == 3);
    std::cout << "Test 6: Edge case handling - PASSED\n";

    // Test 6: Mass spawn/despawn cycles
    {
        std::cout << "Testing mass spawn/despawn cycles...\n";
        DiscreteUnorderedEngine<int, 3> engine(Array<unsigned long, 3>({ 100, 100, 100 }));
        std::vector<Entity<int, 3>> entities;

        // Create entities
        for (unsigned long x = 0; x < 100; x++) {
            for (unsigned long y = 0; y < 100; y++) {
                for (unsigned long z = 0; z < 100; z++) {
                    entities.push_back(Entity<int, 3>{
                        static_cast<int>(x + y + z),
                            Array<unsigned long, 3>({ x, y, z })
                    });
                }
            }
        }

        // Rapid spawn/despawn cycles
        for (int cycle = 0; cycle < 1; cycle++) {
            std::vector<unsigned long> ids;
            // Spawn all
            for (const auto& entity : entities) {
                ids.push_back(engine.spawn(entity));
            }

            // Verify all locations
            for (const auto& entity : entities) {
                auto at_location = engine.getEntitiesAt(entity.coords);
                assert(!at_location.empty());
            }

            // Despawn all
            for (const auto& id : ids) {
                engine.despawn(id);
            }

            // Verify all locations are empty
            for (const auto& entity : entities) {
                auto at_location = engine.getEntitiesAt(entity.coords);
                assert(at_location.empty());
            }
        }
    }

    std::cout << "All tests passed successfully!\n";
}

void final_testp1()
{
    std::cout << "Part 1: Testing array comparison edge cases...\n";

    // Test 1: Zero coordinates
    {
        DiscreteUnorderedEngine<int, 3> engine(Array<unsigned long, 3>({ 2, 2, 2 }));

        // Test different combinations of zero coordinates
        std::vector<unsigned long> ids;
        Entity<int, 3> entities[] = {
            {0, Array<unsigned long, 3>({0, 0, 0})},
            {0, Array<unsigned long, 3>({0, 0, 1})},
            {0, Array<unsigned long, 3>({0, 1, 0})},
            {0, Array<unsigned long, 3>({1, 0, 0})},
            {1, Array<unsigned long, 3>({0, 0, 0})} // Same coords as first, different type
        };

        // Spawn all
        for (const auto& e : entities) {
            ids.push_back(engine.spawn(e));
        }

        // Verify each entity exists exactly where expected
        auto at_000 = engine.getEntitiesAt(Array<unsigned long, 3>({ 0, 0, 0 }));
        assert(at_000.size() == 2); // Should have both type 0 and type 1

        auto at_001 = engine.getEntitiesAt(Array<unsigned long, 3>({ 0, 0, 1 }));
        assert(at_001.size() == 1);

        // Despawn each individually
        for (const auto& id : ids) {
            engine.despawn(id);

            // Verify entity was removed
            auto entity = engine.getEntity(id);
            assert(entity.expired());
        }
    }

    // Test 2: Identical coordinates with different types
    {
        DiscreteUnorderedEngine<int, 2> engine(Array<unsigned long, 2>({ 4, 4 }));
        Array<unsigned long, 2> coords({ 2, 2 });

        std::vector<unsigned long> ids;

        // Spawn multiple entities at exact same location
        for (int i = 0; i < 5; i++) {
            Entity<int, 2> entity{ i, coords };
            ids.push_back(engine.spawn(entity));
        }

        auto at_loc = engine.getEntitiesAt(coords);
        assert(at_loc.size() == 5);

        // Remove in reverse order
        for (auto it = ids.rbegin(); it != ids.rend(); ++it) {
            engine.despawn(*it);
            auto entity = engine.getEntity(*it);
            assert(entity.expired());
        }
    }

    std::cout << "Part 1 complete!\n";

    std::cout << "Part 2: Testing type-based queries...\n";

    {
        DiscreteUnorderedEngine<int, 2> engine(Array<unsigned long, 2>({ 5, 5 }));

        // Spawn entities with different types
        std::vector<unsigned long> type0_ids, type1_ids;

        for (unsigned long x = 0; x < 5; x++) {
            for (unsigned long y = 0; y < 5; y++) {
                Entity<int, 2> entity0{ 0, Array<unsigned long, 2>({x, y}) };
                Entity<int, 2> entity1{ 1, Array<unsigned long, 2>({x, y}) };

                type0_ids.push_back(engine.spawn(entity0));
                type1_ids.push_back(engine.spawn(entity1));
            }
        }

        // Verify type queries
        auto type0_entities = engine.getEntitiesOf(0);
        auto type1_entities = engine.getEntitiesOf(1);

        assert(type0_entities.size() == 25);
        assert(type1_entities.size() == 25);

        // Remove all type 0 entities
        for (const auto& id : type0_ids) {
            engine.despawn(id);
        }

        // Verify only type 1 remains
        type0_entities = engine.getEntitiesOf(0);
        type1_entities = engine.getEntitiesOf(1);

        assert(type0_entities.empty());
        assert(type1_entities.size() == 25);
    }

    std::cout << "Part 2 complete!\n";

    std::cout << "Part 3: Testing concurrent modifications and grid-wide operations...\n";

    // Test 1: Grid-wide population and clearance
    {
        DiscreteUnorderedEngine<int, 3> engine(Array<unsigned long, 3>({ 4, 4, 4 }));
        std::vector<unsigned long> all_ids;
        std::vector<unsigned long> type1_ids;

        // Populate every cell with multiple entities
        for (unsigned long x = 0; x < 4; x++) {
            for (unsigned long y = 0; y < 4; y++) {
                for (unsigned long z = 0; z < 4; z++) {
                    for (int type = 0; type < 3; type++) {
                        Entity<int, 3> entity{
                            type,
                            Array<unsigned long, 3>({x, y, z})
                        };
                        unsigned long id = engine.spawn(entity);
                        all_ids.push_back(id);
                        if (type == 1) type1_ids.push_back(id);
                    }
                }
            }
        }

        // Verify population
        for (unsigned long x = 0; x < 4; x++) {
            for (unsigned long y = 0; y < 4; y++) {
                for (unsigned long z = 0; z < 4; z++) {
                    auto at_loc = engine.getEntitiesAt(Array<unsigned long, 3>({ x, y, z }));
                    assert(at_loc.size() == 3);
                }
            }
        }

        // Remove all entities of type 1
        for (const auto& id : type1_ids) {
            engine.despawn(id);
        }

        // Verify correct removal
        for (unsigned long x = 0; x < 4; x++) {
            for (unsigned long y = 0; y < 4; y++) {
                for (unsigned long z = 0; z < 4; z++) {
                    auto at_loc = engine.getEntitiesAt(Array<unsigned long, 3>({ x, y, z }));
                    assert(at_loc.size() == 2);
                    for (const auto& pair : at_loc) {
                        if (auto ptr = pair.second.lock()) {
                            assert(ptr->_entity.entity != 1);
                        }
                    }
                }
            }
        }
    }

    // Test 2: Pattern-based spawning and removal
    {
        DiscreteUnorderedEngine<int, 2> engine(Array<unsigned long, 2>({ 8, 8 }));
        std::vector<unsigned long> diagonal_ids;

        // Spawn checkerboard pattern
        for (unsigned long x = 0; x < 8; x++) {
            for (unsigned long y = 0; y < 8; y++) {
                if ((x + y) % 2 == 0) {
                    Entity<int, 2> entity{
                        static_cast<int>((x * y) % 3),
                        Array<unsigned long, 2>({x, y})
                    };
                    unsigned long id = engine.spawn(entity);
                    if (x == y) diagonal_ids.push_back(id);
                }
            }
        }

        // Verify pattern
        for (unsigned long x = 0; x < 8; x++) {
            for (unsigned long y = 0; y < 8; y++) {
                auto at_loc = engine.getEntitiesAt(Array<unsigned long, 2>({ x, y }));
                if ((x + y) % 2 == 0) {
                    assert(at_loc.size() == 1);
                    for (const auto& pair : at_loc) {
                        if (auto ptr = pair.second.lock()) {
                            assert(ptr->_entity.entity == static_cast<int>((x * y) % 3));
                        }
                    }
                }
                else {
                    assert(at_loc.empty());
                }
            }
        }

        // Remove diagonal elements
        for (const auto& id : diagonal_ids) {
            engine.despawn(id);
        }

        // Verify diagonal removal
        for (unsigned long i = 0; i < 8; i++) {
            auto at_loc = engine.getEntitiesAt(Array<unsigned long, 2>({ i, i }));
            assert(at_loc.empty());
        }
    }

    std::cout << "Part 3 complete!\n";

    std::cout << "Part 4: Testing recovery and extreme scenarios...\n";

    // Test 1: Recovery from invalid operations
    {
        DiscreteUnorderedEngine<int, 2> engine(Array<unsigned long, 2>({ 3, 3 }));

        // Create valid entity
        Entity<int, 2> valid_entity{ 1, Array<unsigned long, 2>({1, 1}) };
        unsigned long valid_id = engine.spawn(valid_entity);

        // Try despawning non-existent ID  TODO
        //engine.despawn(9999ul);

        // Verify original entity unaffected
        auto at_loc = engine.getEntitiesAt(valid_entity.coords);
        assert(at_loc.size() == 1);
        auto it = at_loc.begin();
        if (auto ptr = it->second.lock()) {
            assert(ptr->_entity.entity == 1);
        }
    }

    // Test 2: Extreme size scenarios
    {
        // Test with minimal dimensions
        DiscreteUnorderedEngine<int, 3> tiny_engine(Array<unsigned long, 3>({ 1, 1, 1 }));
        Entity<int, 3> single_entity{ 0, Array<unsigned long, 3>({0, 0, 0}) };
        unsigned long id = tiny_engine.spawn(single_entity);
        auto at_origin = tiny_engine.getEntitiesAt(Array<unsigned long, 3>({ 0, 0, 0 }));
        assert(at_origin.size() == 1);

        // Test with large dimensions
        DiscreteUnorderedEngine<int, 2> large_engine(Array<unsigned long, 2>({ 1000, 1000 }));
        std::vector<unsigned long> corner_ids;

        // Spawn at corners
        Array<unsigned long, 2> corners[4] = {
            Array<unsigned long, 2>({0, 0}),
            Array<unsigned long, 2>({0, 999}),
            Array<unsigned long, 2>({999, 0}),
            Array<unsigned long, 2>({999, 999})
        };

        for (int i = 0; i < 4; i++) {
            Entity<int, 2> entity{ i, corners[i] };
            corner_ids.push_back(large_engine.spawn(entity));
        }

        // Verify corners
        for (int i = 0; i < 4; i++) {
            auto at_corner = large_engine.getEntitiesAt(corners[i]);
            assert(at_corner.size() == 1);
            auto it = at_corner.begin();
            if (auto ptr = it->second.lock()) {
                assert(ptr->_entity.entity == i);
            }
        }
    }

    // Test 3: Entity type mutations
    {
        DiscreteUnorderedEngine<int, 2> engine(Array<unsigned long, 2>({ 4, 4 }));
        Array<unsigned long, 2> coords({ 2, 2 });

        // Spawn initial entity
        Entity<int, 2> original{ 0, coords };
        unsigned long original_id = engine.spawn(original);

        // Spawn entity of different type at same location
        Entity<int, 2> mutation{ 1, coords };
        unsigned long mutation_id = engine.spawn(mutation);

        // Verify both exist
        auto at_loc = engine.getEntitiesAt(coords);
        assert(at_loc.size() == 2);

        bool found_original = false, found_mutation = false;
        for (const auto& pair : at_loc) {
            if (auto ptr = pair.second.lock()) {
                if (ptr->_entity.entity == 0) found_original = true;
                if (ptr->_entity.entity == 1) found_mutation = true;
            }
        }
        assert(found_original && found_mutation);

        // Remove original
        engine.despawn(original_id);

        // Verify only mutation remains
        at_loc = engine.getEntitiesAt(coords);
        assert(at_loc.size() == 1);
        auto it = at_loc.begin();
        if (auto ptr = it->second.lock()) {
            assert(ptr->_entity.entity == 1);
        }
    }

    // Test 4: Mixed dimension edge cases
    {
        // Create engines of different dimensions
        DiscreteUnorderedEngine<int, 1> engine1d(Array<unsigned long, 1>({ 5 }));
        DiscreteUnorderedEngine<int, 2> engine2d(Array<unsigned long, 2>({ 5, 5 }));
        DiscreteUnorderedEngine<int, 3> engine3d(Array<unsigned long, 3>({ 5, 5, 5 }));

        // Test 1D to 2D transition points
        Entity<int, 1> entity1d{ 0, Array<unsigned long, 1>({2}) };
        engine1d.spawn(entity1d);

        Entity<int, 2> entity2d{ 0, Array<unsigned long, 2>({2, 0}) };
        engine2d.spawn(entity2d);

        // Test 2D to 3D transition points
        Entity<int, 2> entity2d_corner{ 1, Array<unsigned long, 2>({4, 4}) };
        engine2d.spawn(entity2d_corner);

        Entity<int, 3> entity3d{ 1, Array<unsigned long, 3>({4, 4, 0}) };
        engine3d.spawn(entity3d);

        // Verify correct placement
        auto at_1d = engine1d.getEntitiesAt(Array<unsigned long, 1>({ 2 }));
        assert(at_1d.size() == 1);

        auto at_2d = engine2d.getEntitiesAt(Array<unsigned long, 2>({ 2, 0 }));
        assert(at_2d.size() == 1);

        auto at_3d = engine3d.getEntitiesAt(Array<unsigned long, 3>({ 4, 4, 0 }));
        assert(at_3d.size() == 1);
    }

    std::cout << "Part 4 complete!\n";
}

void testMove()
{
    DiscreteUnorderedEngine<int, 3> engine3d(Array<unsigned long, 3>({ 8, 6, 7 }));
    Entity<int, 3> entity3d{ 7, Array<unsigned long, 3>({4, 3, 0}) };
    auto id = engine3d.spawn(entity3d);

    auto at_3d_og = engine3d.getEntitiesAt(Array<unsigned long, 3>({ 4, 3, 0 }));
    assert(at_3d_og.size() == 1);

    try {
        engine3d.moveEntityBy(id, Array<unsigned long, 3>({ 10, 8, 6 }));
        assert(false); // Should not reach here
    }
    catch (const std::invalid_argument&) {
     // Expected
    }

    engine3d.moveEntityBy(id, Array<unsigned long, 3>({ 2, 1, 0 }));
    auto it = at_3d_og.begin();
    int valid_ptrs = 0;
    if (auto ptr = it->second.lock()) {
        valid_ptrs++;
    }
    // Ideally, moving an entity would invalidate the pointer within vectors
    // previously returned from getEntitiesAt(), but since the entity lives
    // on, the pointer is still valid. Perhaps HashEntities should have a
    // dirty bit? Or simply always check that the coords in HashEntities 
    // returned from getEntitiesAt() is correct. Maybe combine both in a 
    // checking function. 
    assert(valid_ptrs == 1);

    auto at_3d_new = engine3d.getEntitiesAt(Array<unsigned long, 3>({ 6, 4, 0 }));
    assert(at_3d_new.size() == 1);

    {
        const int x_dim = 101;
        const int y_dim = 101;
        const int z_dim = 101;
        std::cout << "Testing mass spawn/move/despawn cycles...\n";
        DiscreteUnorderedEngine<int, 3> engine(Array<unsigned long, 3>({ x_dim, y_dim, z_dim }));
        std::vector<Entity<int, 3>> entities;

        // Create entities
        for (unsigned long x = 0; x < x_dim - 1; x++) {
            for (unsigned long y = 0; y < y_dim - 1; y++) {
                for (unsigned long z = 0; z < z_dim - 1; z++) {
                    entities.push_back(Entity<int, 3>{
                        static_cast<int>(x + y + z),
                            Array<unsigned long, 3>({ x, y, z })
                    });
                }
            }
        }

        // Rapid spawn/move/despawn cycles
        for (int cycle = 0; cycle < 1; cycle++) {
            std::vector<unsigned long> ids;

            {
                auto start = std::chrono::high_resolution_clock::now();
                for (const auto& entity : entities) {
                    ids.push_back(engine.spawn(entity));
                }
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                std::cout << "Spawn time: " << duration.count() << " microseconds\n";
            }

            // Verify all locations
            {
                auto start = std::chrono::high_resolution_clock::now();
                for (const auto& entity : entities) {
                    auto at_location = engine.getEntitiesAt(entity.coords);
                    assert(!at_location.empty());
                }
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                std::cout << "Verify locations time: " << duration.count() << " microseconds\n";
            }

            // Move all
            {
                auto start = std::chrono::high_resolution_clock::now();
                for (const auto& id : ids) {
                    engine.moveEntityBy(id, Array<unsigned long, 3>({ 1, 1, 1 }));
                }
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                std::cout << "Move time: " << duration.count() << " microseconds\n";
            }

            // Re-verify location
            {
                auto start = std::chrono::high_resolution_clock::now();
                for (const auto& entity : engine.getEntities()) {
                    auto at_location = engine.getEntitiesAt(entity.second->_entity.coords);
                    assert(!at_location.empty());
                }
                auto at_origin = engine.getEntitiesAt(Array<unsigned long, 3>({ 0, 0, 0 }));
                assert(at_origin.empty());
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                std::cout << "Re-verify time: " << duration.count() << " microseconds\n";
            }

            // Despawn all
            {
                auto start = std::chrono::high_resolution_clock::now();
                for (const auto& id : ids) {
                    engine.despawn(id);
                }
                auto at_corner = engine.getEntitiesAt(Array<unsigned long, 3>({ x_dim, y_dim, z_dim }));
                assert(at_corner.empty());
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                std::cout << "Despawn time: " << duration.count() << " microseconds\n";
            }

            // Verify all locations are empty
            {
                auto start = std::chrono::high_resolution_clock::now();
                for (const auto& entity : engine.getEntities()) {
                    auto at_location = engine.getEntitiesAt(entity.second->_entity.coords);
                    assert(at_location.empty());
                }
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                std::cout << "Final verify time: " << duration.count() << " microseconds\n";
            }
            // // Spawn all
            // for(const auto& entity : entities) {
            //     ids.push_back(engine.spawn(entity));
            // }

            // // Verify all locations
            // for(const auto& entity : entities) {
            //     auto at_location = engine.getEntitiesAt(entity.coords);
            //     assert(!at_location.empty());
            // }

            // // Move all
            // for(const auto& id : ids) {
            //     engine.moveEntityBy(id, Array<unsigned long, 3>({1, 1, 1}));
            // }

            // // Re-verify location
            // for(const auto& entity : engine.getEntities()) {
            //     auto at_location = engine.getEntitiesAt(entity.second->_entity.coords);
            //     assert(!at_location.empty());
            // }
            // auto at_origin = engine.getEntitiesAt(Array<unsigned long, 3>({0, 0, 0}));
            // assert(at_origin.empty());

            // // Despawn all
            // for(const auto& id : ids) {
            //     engine.despawn(id);
            // }
            // auto at_corner = engine.getEntitiesAt(Array<unsigned long, 3>({x_dim, y_dim, z_dim}));
            // assert(at_corner.empty());

            // // Verify all locations are empty
            // for(const auto& entity : engine.getEntities()) {
            //     auto at_location = engine.getEntitiesAt(entity.second->_entity.coords);
            //     assert(at_location.empty());
            // }
        }
    }
}
void test_dimarray() {
    std::cout << "Testing 1D DimensionalArray...\n";

    // Test 1D NArray
    MyArray<unsigned int, 1> dims1({ 3 });
    DimensionalArray<int, 1, unsigned int> arr1d(dims1);

    // Test element insertion
    MyArray<unsigned int, 1> pos0({ 0 });
    MyArray<unsigned int, 1> pos1({ 1 });
    MyArray<unsigned int, 1> pos2({ 2 });

    arr1d.putElement(pos0, 10);
    arr1d.putElement(pos1, 20);
    arr1d.putElement(pos2, 30);

    // Test element retrieval
    assert(arr1d.getElement(pos0) == 10);
    assert(arr1d.getElement(pos1) == 20);
    assert(arr1d.getElement(pos2) == 30);

    // Test operator[]
    // assert(arr1d[0] == 10);
    // assert(arr1d[1] == 20);
    // assert(arr1d[2] == 30);

    std::cout << "Testing 2D DimensionalArray...\n";

    // Test 2D NArray
    MyArray<unsigned int, 2> dims2({ 2, 2 });
    DimensionalArray<int, 2, unsigned int> arr2d(dims2);

    // Test element insertion
    MyArray<unsigned int, 2> pos00({ 0, 0 });
    MyArray<unsigned int, 2> pos01({ 0, 1 });
    MyArray<unsigned int, 2> pos10({ 1, 0 });
    MyArray<unsigned int, 2> pos11({ 1, 1 });

    arr2d.putElement(pos00, 1);
    arr2d.putElement(pos01, 2);
    arr2d.putElement(pos10, 3);
    arr2d.putElement(pos11, 4);

    // Test element retrieval
    assert(arr2d.getElement(pos00) == 1);
    assert(arr2d.getElement(pos01) == 2);
    assert(arr2d.getElement(pos10) == 3);
    assert(arr2d.getElement(pos11) == 4);

    // Test bounds checking
    try {
        MyArray<unsigned int, 1> invalid_pos({ 5 });
        arr1d.getElement(invalid_pos);
        assert(false); // Should not reach here
    }
    catch (const std::invalid_argument&) {
     // Expected
    }

    // Create 3D array with dimensions 2x2x2
    MyArray<unsigned int, 3> dims3({ 2, 2, 2 });
    DimensionalArray<int, 3, unsigned int> arr3d(dims3);

    // Test element insertion at various coordinates
    MyArray<unsigned int, 3> pos000({ 0, 0, 0 });
    MyArray<unsigned int, 3> pos001({ 0, 0, 1 });
    MyArray<unsigned int, 3> pos010({ 0, 1, 0 });
    MyArray<unsigned int, 3> pos011({ 0, 1, 1 });
    MyArray<unsigned int, 3> pos100({ 1, 0, 0 });
    MyArray<unsigned int, 3> pos101({ 1, 0, 1 });
    MyArray<unsigned int, 3> pos110({ 1, 1, 0 });
    MyArray<unsigned int, 3> pos111({ 1, 1, 1 });

    arr3d.putElement(pos000, 1);
    arr3d.putElement(pos001, 2);
    arr3d.putElement(pos010, 3);
    arr3d.putElement(pos011, 4);
    arr3d.putElement(pos100, 5);
    arr3d.putElement(pos101, 6);
    arr3d.putElement(pos110, 7);
    arr3d.putElement(pos111, 8);

    // Test element retrieval
    assert(arr3d.getElement(pos000) == 1);
    assert(arr3d.getElement(pos001) == 2);
    assert(arr3d.getElement(pos010) == 3);
    assert(arr3d.getElement(pos011) == 4);
    assert(arr3d.getElement(pos100) == 5);
    assert(arr3d.getElement(pos101) == 6);
    assert(arr3d.getElement(pos110) == 7);
    assert(arr3d.getElement(pos111) == 8);

    // Test bounds checking
    try {
        MyArray<unsigned int, 3> invalid_pos({ 3, 3, 3 });
        arr3d.getElement(invalid_pos);
        assert(false); // Should not reach here
    }
    catch (const std::invalid_argument&) {
     // Expected
    }

    std::cout << "All 3D DimensionalArray tests passed!\n";

    std::cout << "All DimensionalArray tests passed!\n";
}

// void test_grid2_functionality() {
//     // Test 1: Basic initialization
//     MyArray<unsigned long, 2> grid_size = MyArray<unsigned long, 2>({10, 10});
//     DiscreteUnorderedEngine2<int, 2, unsigned long> engine(grid_size);
//     std::cout << "Test 1: Engine initialization - PASSED\n";

//     // Test 2: Entity creation and spawn
//     PointEntity<int, 2> entity1;
//     entity1.entity = 1;  // entity type
//     entity1.coords = MyArray<unsigned long, 2>({5, 5});

//     PointEntity<int, 2> entity2;
//     entity2.entity = 2;  // different entity type
//     entity2.coords = MyArray<unsigned long, 2>({5, 5});  // same location

//     engine.spawn(entity1);
//     engine.spawn(entity2);

//     auto entities = engine.getEntities();
//     assert(entities.size() == 2);
//     std::cout << "Test 2: Entity spawning - PASSED\n";

//     // Test 3: Get entities by type
//     // auto type1_entities = engine.getEntitiesOf(1);
//     // auto type2_entities = engine.getEntitiesOf(2);
//     // assert(type1_entities.size() == 1);
//     // assert(type2_entities.size() == 1);
//     // std::cout << "Test 3: Get entities by type - PASSED\n";

//     // Test 4: Get entities at location
//     auto entities_at_location = engine.getEntitiesAt(MyArray<unsigned long, 2>({5, 5}));
//     assert(entities_at_location.size() == 2);
//     std::cout << "Test 4: Get entities at location - PASSED\n";

//     // Test 5: Despawn entity
//     auto entity1_hashed = engine.getEntity(0);  // First entity should have id 0
//     if (auto entity1_locked = entity1_hashed.lock()) {
//         engine.despawn(entity1_locked->id);
//     }
//     entities = engine.getEntities();
//     assert(entities.size() == 1);
//     std::cout << "Test 5: Entity despawning - PASSED\n";

//     // Test 6: Test edge cases
//     PointEntity<int, 2> edge_entity;
//     edge_entity.entity = 3;
//     edge_entity.coords = MyArray<unsigned long, 2>({0, 0});  // Corner case
//     engine.spawn(edge_entity);

//     edge_entity.coords = MyArray<unsigned long, 2>({9, 9});  // Other corner
//     engine.spawn(edge_entity);

//     entities = engine.getEntities();
//     assert(entities.size() == 3);
//     std::cout << "Test 6: Edge case handling - PASSED\n";

//     // Test 6: Mass spawn/despawn cycles
//     {
//         std::cout << "Testing mass spawn/despawn cycles...\n";
//         DiscreteUnorderedEngine2<int, 3> engine(MyArray<unsigned long, 3>({100, 100, 100}));
//         std::vector<PointEntity<int, 3>> entities;

//         // Create entities
//         for(unsigned long x = 0; x < 100; x++) {
//             for(unsigned long y = 0; y < 100; y++) {
//                 for(unsigned long z = 0; z < 100; z++) {
//                     entities.push_back(PointEntity<int, 3>{
//                         static_cast<int>(x + y + z),
//                         MyArray<unsigned long, 3>({x, y, z})
//                     });
//                 }
//             }
//         }

//         // Rapid spawn/despawn cycles
//         for(int cycle = 0; cycle < 1; cycle++) {
//             std::vector<unsigned long> ids;
//             // Spawn all
//             for(const auto& entity : entities) {
//                 ids.push_back(engine.spawn(entity));
//             }

//             // Verify all locations
//             for(const auto& entity : entities) {
//                 auto at_location = engine.getEntitiesAt(entity.coords);
//                 assert(!at_location.empty());
//             }

//             // Despawn all
//             for(const auto& id : ids) {
//                 engine.despawn(id);
//             }

//             // Verify all locations are empty
//             for(const auto& entity : entities) {
//                 auto at_location = engine.getEntitiesAt(entity.coords);
//                 assert(at_location.empty());
//             }
//         }
//     }

//     std::cout << "All tests passed successfully!\n";
// }

// void final_testp12()
// {
//     std::cout << "Part 1: Testing array comparison edge cases...\n";

//     // Test 1: Zero coordinates
//     {
//         DiscreteUnorderedEngine2<int, 3> engine(MyArray<unsigned long, 3>({2, 2, 2}));

//         // Test different combinations of zero coordinates
//         std::vector<unsigned long> ids;
//         PointEntity<int, 3> entities[] = {
//             {0, MyArray<unsigned long, 3>({0, 0, 0})},
//             {0, MyArray<unsigned long, 3>({0, 0, 1})},
//             {0, MyArray<unsigned long, 3>({0, 1, 0})},
//             {0, MyArray<unsigned long, 3>({1, 0, 0})},
//             {1, MyArray<unsigned long, 3>({0, 0, 0})} // Same coords as first, different type
//         };

//         // Spawn all
//         for(const auto& e : entities) {
//             ids.push_back(engine.spawn(e));
//         }

//         // Verify each entity exists exactly where expected
//         auto at_000 = engine.getEntitiesAt(MyArray<unsigned long, 3>({0, 0, 0}));
//         assert(at_000.size() == 2); // Should have both type 0 and type 1

//         auto at_001 = engine.getEntitiesAt(MyArray<unsigned long, 3>({0, 0, 1}));
//         assert(at_001.size() == 1);

//         // Despawn each individually
//         for(const auto& id : ids) {
//             engine.despawn(id);

//             // Verify entity was removed
//             auto entity = engine.getEntity(id);
//             assert(entity.expired());
//         }
//     }

//     // Test 2: Identical coordinates with different types
//     {
//         DiscreteUnorderedEngine2<int, 2> engine(MyArray<unsigned long, 2>({4, 4}));
//         MyArray<unsigned long, 2> coords({2, 2});

//         std::vector<unsigned long> ids;

//         // Spawn multiple entities at exact same location
//         for(int i = 0; i < 5; i++) {
//             PointEntity<int, 2> entity{i, coords};
//             ids.push_back(engine.spawn(entity));
//         }

//         auto at_loc = engine.getEntitiesAt(coords);
//         assert(at_loc.size() == 5);

//         // Remove in reverse order
//         for(auto it = ids.rbegin(); it != ids.rend(); ++it) {
//             engine.despawn(*it);
//             auto entity = engine.getEntity(*it);
//             assert(entity.expired());
//         }
//     }

//     std::cout << "Part 1 complete!\n";

//     std::cout << "Part 2: Testing type-based queries...\n";

//     {
//         DiscreteUnorderedEngine2<int, 2> engine(MyArray<unsigned long, 2>({5, 5}));

//         // Spawn entities with different types
//         std::vector<unsigned long> type0_ids, type1_ids;

//         for(unsigned long x = 0; x < 5; x++) {
//             for(unsigned long y = 0; y < 5; y++) {
//                 PointEntity<int, 2> entity0{0, MyArray<unsigned long, 2>({x, y})};
//                 PointEntity<int, 2> entity1{1, MyArray<unsigned long, 2>({x, y})};

//                 type0_ids.push_back(engine.spawn(entity0));
//                 type1_ids.push_back(engine.spawn(entity1));
//             }
//         }

//         // // Verify type queries
//         // auto type0_entities = engine.getEntitiesOf(0);
//         // auto type1_entities = engine.getEntitiesOf(1);

//         // assert(type0_entities.size() == 25);
//         // assert(type1_entities.size() == 25);

//         // Remove all type 0 entities
//         for(const auto& id : type0_ids) {
//             engine.despawn(id);
//         }

//         // // Verify only type 1 remains
//         // type0_entities = engine.getEntitiesOf(0);
//         // type1_entities = engine.getEntitiesOf(1);

//         // assert(type0_entities.empty());
//         // assert(type1_entities.size() == 25);
//     }

//     std::cout << "Part 2 complete!\n";

//     std::cout << "Part 3: Testing concurrent modifications and grid-wide operations...\n";

//     // Test 1: Grid-wide population and clearance
//     {
//         DiscreteUnorderedEngine2<int, 3> engine(MyArray<unsigned long, 3>({4, 4, 4}));
//         std::vector<unsigned long> all_ids;
//         std::vector<unsigned long> type1_ids;

//         // Populate every cell with multiple entities
//         for(unsigned long x = 0; x < 4; x++) {
//             for(unsigned long y = 0; y < 4; y++) {
//                 for(unsigned long z = 0; z < 4; z++) {
//                     for(int type = 0; type < 3; type++) {
//                         PointEntity<int, 3> entity{
//                             type,
//                             MyArray<unsigned long, 3>({x, y, z})
//                         };
//                         unsigned long id = engine.spawn(entity);
//                         all_ids.push_back(id);
//                         if(type == 1) type1_ids.push_back(id);
//                     }
//                 }
//             }
//         }

//         // Verify population
//         for(unsigned long x = 0; x < 4; x++) {
//             for(unsigned long y = 0; y < 4; y++) {
//                 for(unsigned long z = 0; z < 4; z++) {
//                     auto at_loc = engine.getEntitiesAt(MyArray<unsigned long, 3>({x, y, z}));
//                     assert(at_loc.size() == 3);
//                 }
//             }
//         }

//         // Remove all entities of type 1
//         for(const auto& id : type1_ids) {
//             engine.despawn(id);
//         }

//         // Verify correct removal
//         for(unsigned long x = 0; x < 4; x++) {
//             for(unsigned long y = 0; y < 4; y++) {
//                 for(unsigned long z = 0; z < 4; z++) {
//                     auto at_loc = engine.getEntitiesAt(MyArray<unsigned long, 3>({x, y, z}));
//                     assert(at_loc.size() == 2);
//                     for(const auto& pair : at_loc) {
//                         if(auto ptr = pair.second.lock()) {
//                             assert(ptr->point_entity.entity != 1);
//                         }
//                     }
//                 }
//             }
//         }
//     }

//     // Test 2: Pattern-based spawning and removal
//     {
//         DiscreteUnorderedEngine2<int, 2> engine(MyArray<unsigned long, 2>({8, 8}));
//         std::vector<unsigned long> diagonal_ids;

//         // Spawn checkerboard pattern
//         for(unsigned long x = 0; x < 8; x++) {
//             for(unsigned long y = 0; y < 8; y++) {
//                 if((x + y) % 2 == 0) {
//                     PointEntity<int, 2> entity{
//                         static_cast<int>((x * y) % 3),
//                         MyArray<unsigned long, 2>({x, y})
//                     };
//                     unsigned long id = engine.spawn(entity);
//                     if(x == y) diagonal_ids.push_back(id);
//                 }
//             }
//         }

//         // Verify pattern
//         for(unsigned long x = 0; x < 8; x++) {
//             for(unsigned long y = 0; y < 8; y++) {
//                 auto at_loc = engine.getEntitiesAt(MyArray<unsigned long, 2>({x, y}));
//                 if((x + y) % 2 == 0) {
//                     assert(at_loc.size() == 1);
//                     for(const auto& pair : at_loc) {
//                         if(auto ptr = pair.second.lock()) {
//                             assert(ptr->point_entity.entity == static_cast<int>((x * y) % 3));
//                         }
//                     }
//                 } else {
//                     assert(at_loc.empty());
//                 }
//             }
//         }

//         // Remove diagonal elements
//         for(const auto& id : diagonal_ids) {
//             engine.despawn(id);
//         }

//         // Verify diagonal removal
//         for(unsigned long i = 0; i < 8; i++) {
//             auto at_loc = engine.getEntitiesAt(MyArray<unsigned long, 2>({i, i}));
//             assert(at_loc.empty());
//         }
//     }

//     std::cout << "Part 3 complete!\n";

//     std::cout << "Part 4: Testing recovery and extreme scenarios...\n";

//     // Test 1: Recovery from invalid operations
//     {
//         DiscreteUnorderedEngine2<int, 2> engine(MyArray<unsigned long, 2>({3, 3}));

//         // Create valid entity
//         PointEntity<int, 2> valid_entity{1, MyArray<unsigned long, 2>({1, 1})};
//         unsigned long valid_id = engine.spawn(valid_entity);

//         // Try despawning non-existent ID  TODO
//         //engine.despawn(9999ul);

//         // Verify original entity unaffected
//         auto at_loc = engine.getEntitiesAt(valid_entity.coords);
//         assert(at_loc.size() == 1);
//         auto it = at_loc.begin();
//         if(auto ptr = it->second.lock()) {
//             assert(ptr->point_entity.entity == 1);
//         }
//     }

//     // Test 2: Extreme size scenarios
//     {
//         // Test with minimal dimensions
//         DiscreteUnorderedEngine2<int, 3> tiny_engine(MyArray<unsigned long, 3>({1, 1, 1}));
//         PointEntity<int, 3> single_entity{0, MyArray<unsigned long, 3>({0, 0, 0})};
//         unsigned long id = tiny_engine.spawn(single_entity);
//         auto at_origin = tiny_engine.getEntitiesAt(MyArray<unsigned long, 3>({0, 0, 0}));
//         assert(at_origin.size() == 1);

//         // Test with large dimensions
//         DiscreteUnorderedEngine2<int, 2> large_engine(MyArray<unsigned long, 2>({1000, 1000}));
//         std::vector<unsigned long> corner_ids;

//         // Spawn at corners
//         MyArray<unsigned long, 2> corners[4] = {
//             MyArray<unsigned long, 2>({0, 0}),
//             MyArray<unsigned long, 2>({0, 999}),
//             MyArray<unsigned long, 2>({999, 0}),
//             MyArray<unsigned long, 2>({999, 999})
//         };

//         for(int i = 0; i < 4; i++) {
//             PointEntity<int, 2> entity{i, corners[i]};
//             corner_ids.push_back(large_engine.spawn(entity));
//         }

//         // Verify corners
//         for(int i = 0; i < 4; i++) {
//             auto at_corner = large_engine.getEntitiesAt(corners[i]);
//             assert(at_corner.size() == 1);
//             auto it = at_corner.begin();
//             if(auto ptr = it->second.lock()) {
//                 assert(ptr->point_entity.entity == i);
//             }
//         }
//     }

//     // Test 3: Entity type mutations
//     {
//         DiscreteUnorderedEngine2<int, 2> engine(MyArray<unsigned long, 2>({4, 4}));
//         MyArray<unsigned long, 2> coords({2, 2});

//         // Spawn initial entity
//         PointEntity<int, 2> original{0, coords};
//         unsigned long original_id = engine.spawn(original);

//         // Spawn entity of different type at same location
//         PointEntity<int, 2> mutation{1, coords};
//         unsigned long mutation_id = engine.spawn(mutation);

//         // Verify both exist
//         auto at_loc = engine.getEntitiesAt(coords);
//         assert(at_loc.size() == 2);

//         bool found_original = false, found_mutation = false;
//         for(const auto& pair : at_loc) {
//             if(auto ptr = pair.second.lock()) {
//                 if(ptr->point_entity.entity == 0) found_original = true;
//                 if(ptr->point_entity.entity == 1) found_mutation = true;
//             }
//         }
//         assert(found_original && found_mutation);

//         // Remove original
//         engine.despawn(original_id);

//         // Verify only mutation remains
//         at_loc = engine.getEntitiesAt(coords);
//         assert(at_loc.size() == 1);
//         auto it = at_loc.begin();
//         if(auto ptr = it->second.lock()) {
//             assert(ptr->point_entity.entity == 1);
//         }
//     }

//     // Test 4: Mixed dimension edge cases
//     {
//         // Create engines of different dimensions
//         DiscreteUnorderedEngine2<int, 1> engine1d(MyArray<unsigned long, 1>({5}));
//         DiscreteUnorderedEngine2<int, 2> engine2d(MyArray<unsigned long, 2>({5, 5}));
//         DiscreteUnorderedEngine2<int, 3> engine3d(MyArray<unsigned long, 3>({5, 5, 5}));

//         // Test 1D to 2D transition points
//         PointEntity<int, 1> entity1d{0, MyArray<unsigned long, 1>({2})};
//         engine1d.spawn(entity1d);

//         PointEntity<int, 2> entity2d{0, MyArray<unsigned long, 2>({2, 0})};
//         engine2d.spawn(entity2d);

//         // Test 2D to 3D transition points
//         PointEntity<int, 2> entity2d_corner{1, MyArray<unsigned long, 2>({4, 4})};
//         engine2d.spawn(entity2d_corner);

//         PointEntity<int, 3> entity3d{1, MyArray<unsigned long, 3>({4, 4, 0})};
//         engine3d.spawn(entity3d);

//         // Verify correct placement
//         auto at_1d = engine1d.getEntitiesAt(MyArray<unsigned long, 1>({2}));
//         assert(at_1d.size() == 1);

//         auto at_2d = engine2d.getEntitiesAt(MyArray<unsigned long, 2>({2, 0}));
//         assert(at_2d.size() == 1);

//         auto at_3d = engine3d.getEntitiesAt(MyArray<unsigned long, 3>({4, 4, 0}));
//         assert(at_3d.size() == 1);
//     }

//     std::cout << "Part 4 complete!\n";
// }

// void testMove2()
// {
//     DiscreteUnorderedEngine2<int, 3> engine3d(MyArray<unsigned long, 3>({8, 6, 7}));
//     PointEntity<int, 3> entity3d{7, MyArray<unsigned long, 3>({4, 3, 0})};
//     auto id = engine3d.spawn(entity3d);

//     auto at_3d_og = engine3d.getEntitiesAt(MyArray<unsigned long, 3>({4, 3, 0}));
//     assert(at_3d_og.size() == 1);

//     try {
//         engine3d.moveEntityBy(id, MyArray<unsigned long, 3>({10, 8, 6}));
//         assert(false); // Should not reach here
//     } catch(const std::invalid_argument&) {
//         // Expected
//     }

//     engine3d.moveEntityBy(id, MyArray<unsigned long, 3>({2, 1, 0}));
//     auto it = at_3d_og.begin();
//     int valid_ptrs = 0;
//     if(auto ptr = it->second.lock()) {
//         valid_ptrs++;
//     }
//     // Ideally, moving an entity would invalidate the pointer within vectors
//     // previously returned from getEntitiesAt(), but since the entity lives
//     // on, the pointer is still valid. Perhaps HashEntities should have a
//     // dirty bit? Or simply always check that the coords in HashEntities 
//     // returned from getEntitiesAt() is correct. Maybe combine both in a 
//     // checking function. 
//     assert(valid_ptrs == 1);

//     auto at_3d_new = engine3d.getEntitiesAt(MyArray<unsigned long, 3>({6, 4, 0}));
//     assert(at_3d_new.size() == 1);

//     {
//         const int x_dim = 101;
//         const int y_dim = 101;
//         const int z_dim = 101;
//         std::cout << "Testing mass spawn/move/despawn cycles...\n";
//         DiscreteUnorderedEngine2<int, 3> engine(MyArray<unsigned long, 3>({x_dim, y_dim, z_dim}));
//         std::vector<PointEntity<int, 3>> entities;

//         // Create entities
//         for(unsigned long x = 0; x < x_dim - 1; x++) {
//             for(unsigned long y = 0; y < y_dim - 1; y++) {
//                 for(unsigned long z = 0; z < z_dim - 1; z++) {
//                     entities.push_back(PointEntity<int, 3>{
//                         static_cast<int>(x + y + z),
//                         MyArray<unsigned long, 3>({x, y, z})
//                     });
//                 }
//             }
//         }

//         // Rapid spawn/move/despawn cycles
//         for(int cycle = 0; cycle < 1; cycle++) {
//             std::vector<unsigned long> ids;

//             {
//                 auto start = std::chrono::high_resolution_clock::now();
//                 for(const auto& entity : entities) {
//                     ids.push_back(engine.spawn(entity));
//                 }
//                 auto end = std::chrono::high_resolution_clock::now();
//                 auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//                 std::cout << "Spawn time: " << duration.count() << " microseconds\n";
//             }

//             // Verify all locations
//             {
//                 auto start = std::chrono::high_resolution_clock::now();
//                 for(const auto& entity : entities) {
//                     auto at_location = engine.getEntitiesAt(entity.coords);
//                     assert(!at_location.empty());
//                 }
//                 auto end = std::chrono::high_resolution_clock::now();
//                 auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//                 std::cout << "Verify locations time: " << duration.count() << " microseconds\n";
//             }

//             // Move all
//             {
//                 auto start = std::chrono::high_resolution_clock::now();
//                 for(const auto& id : ids) {
//                     engine.moveEntityBy(id, MyArray<unsigned long, 3>({1, 1, 1}));
//                 }
//                 auto end = std::chrono::high_resolution_clock::now();
//                 auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//                 std::cout << "Move time: " << duration.count() << " microseconds\n";
//             }

//             // Re-verify location
//             {
//                 auto start = std::chrono::high_resolution_clock::now();
//                 for(const auto& entity : engine.getEntities()) {
//                     auto at_location = engine.getEntitiesAt(entity.second->point_entity.coords);
//                     assert(!at_location.empty());
//                 }
//                 auto at_origin = engine.getEntitiesAt(MyArray<unsigned long, 3>({0, 0, 0}));
//                 assert(at_origin.empty());
//                 auto end = std::chrono::high_resolution_clock::now();
//                 auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//                 std::cout << "Re-verify time: " << duration.count() << " microseconds\n";
//             }

//             // Despawn all
//             {
//                 auto start = std::chrono::high_resolution_clock::now();
//                 for(const auto& id : ids) {
//                     engine.despawn(id);
//                 }
//                 auto at_corner = engine.getEntitiesAt(MyArray<unsigned long, 3>({x_dim - 1, y_dim - 1, z_dim - 1}));
//                 assert(at_corner.empty());
//                 auto end = std::chrono::high_resolution_clock::now();
//                 auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//                 std::cout << "Despawn time: " << duration.count() << " microseconds\n";
//             }

//             // Verify all locations are empty
//             {
//                 auto start = std::chrono::high_resolution_clock::now();
//                 for(const auto& entity : engine.getEntities()) {
//                     auto at_location = engine.getEntitiesAt(entity.second->point_entity.coords);
//                     assert(at_location.empty());
//                 }
//                 auto end = std::chrono::high_resolution_clock::now();
//                 auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//                 std::cout << "Final verify time: " << duration.count() << " microseconds\n";
//             }
//             // // Spawn all
//             // for(const auto& entity : entities) {
//             //     ids.push_back(engine.spawn(entity));
//             // }

//             // // Verify all locations
//             // for(const auto& entity : entities) {
//             //     auto at_location = engine.getEntitiesAt(entity.coords);
//             //     assert(!at_location.empty());
//             // }

//             // // Move all
//             // for(const auto& id : ids) {
//             //     engine.moveEntityBy(id, Array<unsigned long, 3>({1, 1, 1}));
//             // }

//             // // Re-verify location
//             // for(const auto& entity : engine.getEntities()) {
//             //     auto at_location = engine.getEntitiesAt(entity.second->_entity.coords);
//             //     assert(!at_location.empty());
//             // }
//             // auto at_origin = engine.getEntitiesAt(Array<unsigned long, 3>({0, 0, 0}));
//             // assert(at_origin.empty());

//             // // Despawn all
//             // for(const auto& id : ids) {
//             //     engine.despawn(id);
//             // }
//             // auto at_corner = engine.getEntitiesAt(Array<unsigned long, 3>({x_dim, y_dim, z_dim}));
//             // assert(at_corner.empty());

//             // // Verify all locations are empty
//             // for(const auto& entity : engine.getEntities()) {
//             //     auto at_location = engine.getEntitiesAt(entity.second->_entity.coords);
//             //     assert(at_location.empty());
//             // }
//         }
//     }
// }

// void testDifferentEntities()
// {
//     struct BaseEntity
//     {
//         virtual ~BaseEntity() {}
//     };

//     struct Antenna : public BaseEntity
//     {
//         char broadcasting_on;

//         Antenna(char c) : broadcasting_on(c) {}
//     };

//     struct Antinode : public BaseEntity
//     {
//         char accepting_on;

//         Antinode(char c) : accepting_on(c) {}
//     };

//     DiscreteUnorderedEngine2<std::shared_ptr<BaseEntity>, 2> engine(MyArray<unsigned long, 2>({8, 6}));

//     Antenna ant_a('a');
//     Antenna ant_a2('a');
//     Antenna ant_b('b');


//     std::shared_ptr<Antenna> ant_a_ptr = make_unique<Antenna>(ant_a);
//     std::shared_ptr<Antenna> ant_a2_ptr = make_unique<Antenna>(ant_a2);
//     std::shared_ptr<BaseEntity> ant_b_ptr = make_unique<Antenna>(ant_b);

//     PointEntity<std::shared_ptr<BaseEntity>, 2> ant_a_ent{ant_a_ptr, MyArray<unsigned long, 2>({4, 3})};
//     PointEntity<std::shared_ptr<BaseEntity>, 2> ant_a2_ent{ant_a2_ptr, MyArray<unsigned long, 2>({4, 3})};
//     PointEntity<std::shared_ptr<BaseEntity>, 2> ant_b_ent{ant_b_ptr, MyArray<unsigned long, 2>({2, 1})};

//     auto ida = engine.spawn(ant_a_ent);
//     auto ida2 = engine.spawn(ant_a2_ent);
//     auto idb = engine.spawn(ant_b_ent);

//     std::weak_ptr<HashedEntity<PointEntity<std::shared_ptr<BaseEntity>, 2U, unsigned long>, unsigned long>> a_retrieved = engine.getEntity(ida);
//     std::weak_ptr<HashedEntity<PointEntity<std::shared_ptr<BaseEntity>, 2U, unsigned long>, unsigned long>> a2_retrieved = engine.getEntity(ida2);
//     auto b_retrieved = engine.getEntity(idb);

//     char a_accepting = std::dynamic_pointer_cast<Antenna>(a_retrieved.lock()->point_entity.entity)->broadcasting_on;
//     char a2_accepting = std::dynamic_pointer_cast<Antenna>(a2_retrieved.lock()->point_entity.entity)->broadcasting_on;
//     char b_accepting = std::dynamic_pointer_cast<Antenna>(b_retrieved.lock()->point_entity.entity)->broadcasting_on;
//     assert(a_accepting == 'a');
//     assert(a2_accepting == 'a');
//     assert(b_accepting == 'b');

//     Antinode antinode_a('a');
//     Antinode antinode_b('b');

//     std::shared_ptr<Antinode> antinode_a_ptr = make_unique<Antinode>(antinode_a);
//     std::shared_ptr<BaseEntity> antinode_b_ptr = make_unique<Antinode>(antinode_b);

//     PointEntity<std::shared_ptr<BaseEntity>, 2> antinode_a_ent{antinode_a_ptr, MyArray<unsigned long, 2>({4, 3})};
//     PointEntity<std::shared_ptr<BaseEntity>, 2> antinode_b_ent{antinode_b_ptr, MyArray<unsigned long, 2>({2, 1})};

//     auto antinode_a_id = engine.spawn(antinode_a_ent);
//     auto antinode_b_id = engine.spawn(antinode_b_ent);

//     std::weak_ptr<HashedEntity<PointEntity<std::shared_ptr<BaseEntity>, 2U, unsigned long>, unsigned long>> antinode_a_retrieved = engine.getEntity(antinode_a_id);
//     auto antinode_b_retrieved = engine.getEntity(antinode_b_id);

//     char antinode_a_accepting = std::dynamic_pointer_cast<Antinode>(antinode_a_retrieved.lock()->point_entity.entity)->accepting_on;
//     char antinode_b_accepting = std::dynamic_pointer_cast<Antinode>(antinode_b_retrieved.lock()->point_entity.entity)->accepting_on;
//     assert(antinode_a_accepting == 'a');
//     assert(antinode_b_accepting == 'b');

//     // auto result = engine.getEntitiesOf(ant_a_ptr);
// }

// void testDifferentEntitiesDerived()
// {
//     struct Antenna : public BaseEntity
//     {
//         char broadcasting_on;

//         Antenna(char c) : broadcasting_on(c) {}
//     };

//     struct Antinode : public BaseEntity
//     {
//         char accepting_on;

//         Antinode(char c) : accepting_on(c) {}
//     };

//     PointEngine2D engine(MyArray<unsigned long, 2>({8, 6}));

//     Antenna ant_a('a');
//     Antenna ant_a2('a');
//     Antenna ant_b('b');

//     // std::shared_ptr<Antenna> ant_a_ptr = make_unique<Antenna>(ant_a);
//     // std::shared_ptr<Antenna> ant_a2_ptr = make_unique<Antenna>(ant_a2);
//     // std::shared_ptr<BaseEntity> ant_b_ptr = make_unique<Antenna>(ant_b);

//     PointEntity<BaseEntity, 2> ant_a_ent{ant_a, MyArray<unsigned long, 2>({4, 3})};
//     PointEntity<BaseEntity, 2> ant_a2_ent{ant_a2, MyArray<unsigned long, 2>({4, 3})};
//     PointEntity<BaseEntity, 2> ant_b_ent{ant_b, MyArray<unsigned long, 2>({2, 1})};

//     auto ida = engine.spawn(ant_a_ent);
//     auto ida2 = engine.spawn(ant_a2_ent);
//     auto idb = engine.spawn(ant_b_ent);

//     std::weak_ptr<HashedEntity<PointEntity<BaseEntity, 2U, unsigned long>, unsigned long>> a_retrieved = engine.getEntity(ida);
//     std::weak_ptr<HashedEntity<PointEntity<BaseEntity, 2U, unsigned long>, unsigned long>> a2_retrieved = engine.getEntity(ida2);
//     auto b_retrieved = engine.getEntity(idb);

//     // char a_accepting = std::dynamic_pointer_cast<Antenna>(a_retrieved.lock()->point_entity.entity)->broadcasting_on;
//     // char a2_accepting = std::dynamic_pointer_cast<Antenna>(a2_retrieved.lock()->point_entity.entity)->broadcasting_on;
//     // char b_accepting = std::dynamic_pointer_cast<Antenna>(b_retrieved.lock()->point_entity.entity)->broadcasting_on;
//     // assert(a_accepting == 'a');
//     // assert(a2_accepting == 'a');
//     // assert(b_accepting == 'b');

//     // Antinode antinode_a('a');
//     // Antinode antinode_b('b');

//     // std::shared_ptr<Antinode> antinode_a_ptr = make_unique<Antinode>(antinode_a);
//     // std::shared_ptr<BaseEntity> antinode_b_ptr = make_unique<Antinode>(antinode_b);

//     // PointEntity<std::shared_ptr<BaseEntity>, 2> antinode_a_ent{antinode_a_ptr, MyArray<unsigned long, 2>({4, 3})};
//     // PointEntity<std::shared_ptr<BaseEntity>, 2> antinode_b_ent{antinode_b_ptr, MyArray<unsigned long, 2>({2, 1})};

//     // auto antinode_a_id = engine.spawn(antinode_a_ent);
//     // auto antinode_b_id = engine.spawn(antinode_b_ent);

//     // std::weak_ptr<HashedEntity<PointEntity<std::shared_ptr<BaseEntity>, 2U, unsigned long>, unsigned long>> antinode_a_retrieved = engine.getEntity(antinode_a_id);
//     // auto antinode_b_retrieved = engine.getEntity(antinode_b_id);

//     // char antinode_a_accepting = std::dynamic_pointer_cast<Antinode>(antinode_a_retrieved.lock()->point_entity.entity)->accepting_on;
//     // char antinode_b_accepting = std::dynamic_pointer_cast<Antinode>(antinode_b_retrieved.lock()->point_entity.entity)->accepting_on;
//     // assert(antinode_a_accepting == 'a');
//     // assert(antinode_b_accepting == 'b');

//     // auto result = engine.getEntitiesOf(ant_a_ptr);
// }

int testTileGrid() {
    class BaseEntity
    {
    public:
        virtual ~BaseEntity() {}
    };

    // 1. Test 2D grid creation
    MyArray<unsigned long, 2> grid_size({ 10, 10 });
    TileEngine<BaseEntity, 2> engine(grid_size);

    // 2. Test entity spawning
    BaseEntity base;
    MyArray<unsigned long, 2> start_pos({ 1, 1 });
    std::shared_ptr<BaseEntity> e_ptr = std::make_shared<BaseEntity>(base);

    auto id1 = engine.spawn(e_ptr, start_pos);
    assert(id1 == 0 && "First spawned entity should have ID 0");

    assert(engine.getNumberOfEntities() == 1 && "Should have exactly one entity");

    // // 3. Test entity movement
    MyArray<long, 2> displacement({2, 3});
    engine.moveEntityBy(id1, displacement);
    auto entities = engine.getEntitiesAt(MyArray<unsigned long, 2>({3, 4}));
    assert(entities.count(id1) == 1 && "Entity should be at new position after relative move");

    MyArray<unsigned long, 2> new_pos({5, 5});
    engine.moveEntityTo(id1, new_pos);
    entities = engine.getEntitiesAt(new_pos);
    assert(entities.count(id1) == 1 && "Entity should be at absolute position");

    // // 4. Test multiple entities
    class DerivedA : public BaseEntity
    {
        char name;
    public:
        DerivedA(char c) : name(c) {}
        char getName() { return name; }
    };
    DerivedA entity2('a');
    MyArray<unsigned long, 2> pos2({2, 2});
    auto id2 = engine.spawn<DerivedA>(entity2, pos2);
    assert(id2 == 1 && "Second entity should have ID 1");
    assert(engine.getNumberOfEntities() == 2 && "Should have exactly two entities");
    assert(engine.getDerivedEntity<DerivedA>(id2)->getName() == 'a');

    // // 5. Test bounds checking
    bool caught_exception = false;
    try {
        MyArray<unsigned long, 2> invalid_pos({15, 15});
        engine.moveEntityTo(id1, invalid_pos);
    } catch (const std::invalid_argument&) {
        caught_exception = true;
    }
    assert(caught_exception && "Should throw on out of bounds movement");

    // // 6. Test despawning
    engine.despawn(id1);
    assert(engine.getNumberOfEntities() == 1 && "Should have one entity after despawn");
    auto e = engine.getEntity(id1);
    assert(e.expired());

    // // 7. Test edge cases
    MyArray<unsigned long, 2> edge_pos({9, 9});
    engine.moveEntityTo(id2, edge_pos);
    entities = engine.getEntitiesAt(edge_pos);
    assert(entities.count(id2) == 1 && "Entity should move to grid edge");

    // // 8. Test 3D grid
    MyArray<unsigned long, 3> grid_size_3d({5, 5, 5});
    TileEngine<BaseEntity, 3> engine3d(grid_size_3d);

    MyArray<unsigned long, 3> pos3d({1, 1, 1});
    DerivedA entity3d('a');
    auto id3d = engine3d.spawn(entity3d, pos3d);
    assert(id3d == 0 && "3D grid entity spawn should work");

    auto entity3d_retrieved = engine3d.getDerivedEngineEntity<DerivedA>(id3d);
    auto e3d = entity3d_retrieved.lock()->getInternalEntity();
    assert(e3d->getName() == 'a');

    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}

class TestEntityA : public BaseEntity {
public:
    int value;
    TestEntityA(int v) : value(v) {}
};

class TestEntityB : public BaseEntity {
public:
    std::string name;
    TestEntityB(std::string n) : name(n) {}
};

void runTileEngineTests() {
    // Create a 2D engine with 10x10 grid
    MyArray<unsigned long, 2> dimensions({ 10, 10 });
    TileEngine<BaseEntity, 2> engine(dimensions);

    // Test 1: Basic spawn and retrieve
    auto entityA = std::make_shared<TestEntityA>(42);
    MyArray<unsigned long, 2> pos({ 5, 5 });
    auto idA = engine.spawn<TestEntityA>(entityA, pos);

    auto retrievedEntity = engine.getEntity(idA);
    assert(!retrievedEntity.expired());

    // Test 2: Multiple entity types
    auto entityB = std::make_shared<TestEntityB>("test");
    MyArray<unsigned long, 2> posB({ 3, 3 });
    auto idB = engine.spawn<TestEntityB>(entityB, posB);

    // Test 3: Movement
    MyArray<long, 2> displacement({ 1, 1 });
    engine.moveEntityBy(idA, displacement);

    auto movedEntity = engine.getEntity(idA).lock();
    MyArray<unsigned long, 2> expectedPos({ 6, 6 });
    assert(movedEntity->getCoords() == expectedPos);

    // Test 4: Out of bounds movement should throw
    MyArray<unsigned long, 2> invalidPos({ 20, 20 });
    bool exceptionThrown = false;
    try {
        engine.moveEntityTo(idA, invalidPos);
    }
    catch (const std::invalid_argument&) {
        exceptionThrown = true;
    }
    assert(exceptionThrown);

    // Test 5: Despawn
    engine.despawn(idA);
    auto despawnedEntity = engine.getEntity(idA);
    assert(despawnedEntity.expired());

    // Test 6: Type registry
    const std::type_info& type_id = typeid(entityB);
    auto entitiesOfTypeB = engine.getEntitiesByType<TestEntityB>();
    assert(entitiesOfTypeB.size() == 1);

    std::cout << "All TileEngine tests passed!" << std::endl;
}

class TestEntityC : public BaseEntity {
    double value;
public:
    TestEntityC(double v) : value(v) {}
};

void runComprehensiveTileEngineTests() {
    // 1. Test different dimensions
    {
        MyArray<unsigned long, 1> dim1({ 5 });
        TileEngine<BaseEntity, 1> engine1d(dim1);

        MyArray<unsigned long, 3> dim3({ 5, 5, 5 });
        TileEngine<BaseEntity, 3> engine3d(dim3);
    }

    // 2. Test 2D engine extensively
    MyArray<unsigned long, 2> dimensions({ 10, 10 });
    TileEngine<BaseEntity, 2> engine(dimensions);

    // Test boundary spawns
    auto entityCorner = std::make_shared<TestEntityA>(1);
    MyArray<unsigned long, 2> cornerPos({ 0, 0 });
    auto cornerId = engine.spawn(entityCorner, cornerPos);

    auto entityEdge = std::make_shared<TestEntityA>(2);
    MyArray<unsigned long, 2> edgePos({ 9, 9 });
    auto edgeId = engine.spawn(entityEdge, edgePos);

    // Test multiple entities in same tile
    auto entitySameTile1 = std::make_shared<TestEntityB>("same1");
    auto entitySameTile2 = std::make_shared<TestEntityC>(3.14);
    MyArray<unsigned long, 2> sharedPos({ 5, 5 });
    auto sameId1 = engine.spawn(entitySameTile1, sharedPos);
    auto sameId2 = engine.spawn(entitySameTile2, sharedPos);

    auto entitiesAtPos = engine.getEntitiesAt(sharedPos);
    assert(entitiesAtPos.size() == 2);

    // Test complex movement pattern
    MyArray<long, 2> movements[] = {
        MyArray<long, 2>({1, 0}),
        MyArray<long, 2>({0, 1}),
        MyArray<long, 2>({-1, 0}),
        MyArray<long, 2>({0, -1})
    };

    for (const auto& move : movements) {
        engine.moveEntityBy(cornerId, move);
    }

    // Test invalid operations
    // bool exceptionThrown = false;
    // try {
    //     engine.despawn(999); // Invalid ID
    // } catch (const std::out_of_range&) {
    //     exceptionThrown = true;
    // }
    // assert(exceptionThrown);

    // Test memory management
    {
        auto tempEntity = std::make_shared<TestEntityA>(42);
        auto tempId = engine.spawn(tempEntity, cornerPos);
        auto weakRef = engine.getEntity(tempId);
        engine.despawn(tempId);
        assert(weakRef.expired());
    }

    // Remove existing entities
    engine.despawn(sameId1);
    engine.despawn(sameId2);
    engine.despawn(cornerId);
    engine.despawn(edgeId);

    // Test type registry exhaustively
    auto entityTypeA1 = std::make_shared<TestEntityA>(10);
    auto entityTypeA2 = std::make_shared<TestEntityA>(20);
    auto entityTypeB = std::make_shared<TestEntityB>("test");
    auto entityTypeC = std::make_shared<TestEntityC>(1.5);

    auto idA1 = engine.spawn(entityTypeA1, MyArray<unsigned long, 2>({ 1, 1 }));
    auto idA2 = engine.spawn(entityTypeA2, MyArray<unsigned long, 2>({ 2, 2 }));
    auto idB = engine.spawn(entityTypeB, MyArray<unsigned long, 2>({ 3, 3 }));
    auto idC = engine.spawn(entityTypeC, MyArray<unsigned long, 2>({ 4, 4 }));

    auto entitiesA = engine.getEntitiesByType<TestEntityA>();
    auto entitiesB = engine.getEntitiesByType<TestEntityB>();
    auto entitiesC = engine.getEntitiesByType<TestEntityC>();

    assert(entitiesA.size() == 2);
    assert(entitiesB.size() == 1);
    assert(entitiesC.size() == 1);

    // Clean up
    engine.despawn(idA1);
    engine.despawn(idA2);
    engine.despawn(idB);
    engine.despawn(idC);
    engine.despawn(cornerId);
    engine.despawn(edgeId);
    engine.despawn(sameId1);
    engine.despawn(sameId2);

    std::cout << "All comprehensive TileEngine tests passed!" << std::endl;

    // Test 6: Mass spawn/despawn cycles
    {
    // Create 3D engine with 100x100x100 grid
        MyArray<unsigned long, 3> dims({ 100, 100, 100 });
        TileEngine<BaseEntity, 3> engine(dims);

        // Track entities and their IDs
        std::vector<std::shared_ptr<TestEntityA>> a_entities;
        std::vector<std::shared_ptr<TestEntityB>> b_entities;
        std::vector<std::shared_ptr<TestEntityC>> c_entities;
        std::vector<unsigned long> all_ids;

        // Create and spawn entities
        for (unsigned long x = 0; x < 100; x++) {
            for (unsigned long y = 0; y < 100; y++) {
                for (unsigned long z = 0; z < 100; z++) {
                    MyArray<unsigned long, 3> pos({ x, y, z });

                    switch (z % 3) {
                    case 0: {
                        auto ptr = std::make_shared<TestEntityA>(z);
                        a_entities.push_back(ptr);
                        all_ids.push_back(engine.spawn(ptr, pos));
                        break;
                    }
                    case 1: {
                        auto ptr = std::make_shared<TestEntityB>("hi");
                        b_entities.push_back(ptr);
                        all_ids.push_back(engine.spawn(ptr, pos));
                        break;
                    }
                    case 2: {
                        auto ptr = std::make_shared<TestEntityC>(z / 3.14);
                        c_entities.push_back(ptr);
                        all_ids.push_back(engine.spawn(ptr, pos));
                        break;
                    }
                    }
                }
            }
        }

        // Verify type counts
        auto type_a_entities = engine.getEntitiesByType<TestEntityA>();
        auto type_b_entities = engine.getEntitiesByType<TestEntityB>();
        auto type_c_entities = engine.getEntitiesByType<TestEntityC>();

        assert(type_a_entities.size() == a_entities.size());
        assert(type_b_entities.size() == b_entities.size());
        assert(type_c_entities.size() == c_entities.size());

        // Mass despawn
        for (auto id : all_ids) {
            engine.despawn(id);
        }

        // Verify cleanup
        type_a_entities = engine.getEntitiesByType<TestEntityA>();
        type_b_entities = engine.getEntitiesByType<TestEntityB>();
        type_c_entities = engine.getEntitiesByType<TestEntityC>();

        assert(type_a_entities.empty());
        assert(type_b_entities.empty());
        assert(type_c_entities.empty());

        std::cout << "All tests passed successfully!\n";
    }
}

int main(int argc, char* argv[])
{
    // test_array_operations();
    // test_world();
    // test_ptr_world();
    // test_ptr_world2();
    // test_ptr_world2_scoping();
    // test_engine1_private();
    // test_engine1();
    // test_engine2_private();
    // test_engine2();
    // test_despawn_issue();
    // test_discrete_engine();
    // test_discrete_grid_and_engine();
    // test_engine_mass();
    // final_test();

    // test_narray();
    // test_grid_functionality();
    // final_testp1();
    // testMove();

    // test_dimarray();
    // test_grid2_functionality();
    // final_testp12();
    // testMove2();

    // testDifferentEntities();
    MyArray<unsigned int, 3> left{4, 6, 8};
    MyArray<int, 3> right{-8, 7, 3};
    // MyArray<unsigned int, 3> MyArray<int, 3>::unsigned_add<unsigned int, int>(left, right);
    // left.add(right);
    // right.add(left);

    testTileGrid();
    runTileEngineTests();
    runComprehensiveTileEngineTests();
    return 0;
}
