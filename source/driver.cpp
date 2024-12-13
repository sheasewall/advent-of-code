#include "../day2/puzzle.cpp"
#include "../day5/puzzle.cpp"
#include "../day6/puzzle.cpp"
#include "../day7/puzzle.cpp"
#include "../day8/puzzle.cpp"

#include "matrix.cpp"
#include "hyper.cpp"
#include "narray.cpp"
#include "grid.cpp"

#include <cassert>

#include <list>

std::array<solve::TrialParameters, 2> getWickedFastParams()
{
    static const solve::TrialParameters parsing = {true, 2, 10};
    static const solve::TrialParameters non_parsing = {false, 2, 5};
    return {parsing, non_parsing};
}

std::array<solve::TrialParameters, 2> getDefaultParams()
{
    static const solve::TrialParameters parsing = {true, 5, 100};
    static const solve::TrialParameters non_parsing = {false, 5, 50};
    return {parsing, non_parsing};
}

std::array<solve::TrialParameters, 2> getQuickParams()
{
    static const solve::TrialParameters parsing = {true, 1, 10};
    static const solve::TrialParameters non_parsing = {false, 1, 5};
    return {parsing, non_parsing};
}

std::array<solve::TrialParameters, 2> getLongParams()
{
    static const solve::TrialParameters parsing = {true, 5, 5000};
    static const solve::TrialParameters non_parsing = {false, 10, 200};
    return {parsing, non_parsing};
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
    Array<unsigned int, 1> dims1({3});
    NArray<int, 1, unsigned int> arr1d(dims1);
    
    // Test element insertion
    Array<unsigned int, 1> pos0({0});
    Array<unsigned int, 1> pos1({1});
    Array<unsigned int, 1> pos2({2});
    
    assert(arr1d.putElement(pos0, 10));
    assert(arr1d.putElement(pos1, 20));
    assert(arr1d.putElement(pos2, 30));
    
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
    Array<unsigned int, 2> dims2({2, 2});
    NArray<int, 2, unsigned int> arr2d(dims2);
    
    // Test element insertion
    Array<unsigned int, 2> pos00({0, 0});
    Array<unsigned int, 2> pos01({0, 1});
    Array<unsigned int, 2> pos10({1, 0});
    Array<unsigned int, 2> pos11({1, 1});
    
    assert(arr2d.putElement(pos00, 1));
    assert(arr2d.putElement(pos01, 2));
    assert(arr2d.putElement(pos10, 3));
    assert(arr2d.putElement(pos11, 4));
    
    // Test element retrieval
    assert(arr2d.getElement(pos00) == 1);
    assert(arr2d.getElement(pos01) == 2);
    assert(arr2d.getElement(pos10) == 3);
    assert(arr2d.getElement(pos11) == 4);

    // Test bounds checking
    try {
        Array<unsigned int, 1> invalid_pos({5});
        arr1d.getElement(invalid_pos);
        assert(false); // Should not reach here
    } catch (const std::out_of_range&) {
        // Expected
    }

    // Create 3D array with dimensions 2x2x2
    Array<unsigned int, 3> dims3({2, 2, 2});
    NArray<int, 3, unsigned int> arr3d(dims3);
    
    // Test element insertion at various coordinates
    Array<unsigned int, 3> pos000({0, 0, 0});
    Array<unsigned int, 3> pos001({0, 0, 1});
    Array<unsigned int, 3> pos010({0, 1, 0});
    Array<unsigned int, 3> pos011({0, 1, 1});
    Array<unsigned int, 3> pos100({1, 0, 0});
    Array<unsigned int, 3> pos101({1, 0, 1});
    Array<unsigned int, 3> pos110({1, 1, 0});
    Array<unsigned int, 3> pos111({1, 1, 1});
    
    assert(arr3d.putElement(pos000, 1));
    assert(arr3d.putElement(pos001, 2));
    assert(arr3d.putElement(pos010, 3));
    assert(arr3d.putElement(pos011, 4));
    assert(arr3d.putElement(pos100, 5));
    assert(arr3d.putElement(pos101, 6));
    assert(arr3d.putElement(pos110, 7));
    assert(arr3d.putElement(pos111, 8));
    
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
        Array<unsigned int, 3> invalid_pos({3, 3, 3});
        arr3d.getElement(invalid_pos);
        assert(false); // Should not reach here
    } catch (const std::out_of_range&) {
        // Expected
    }

    std::cout << "All 3D NArray tests passed!\n";

    std::cout << "All NArray tests passed!\n";
}

void test_world()
{
    // Create a 2D world of size 10x10
    Array<unsigned long, 2> worldSize({10, 10});
    DiscreteWorld<std::string, 2, unsigned long> world(worldSize);

    // Create some test entities
    Entity<std::string, 2, unsigned long> entity1;
    entity1.entity = "Entity1";
    entity1.coords = Array<unsigned long, 2>({1, 1});

    Entity<std::string, 2, unsigned long> entity2;
    entity2.entity = "Entity2";
    entity2.coords = Array<unsigned long, 2>({5, 5});

    // Spawn entities into the world
    world.spawn(entity1);
    world.spawn(entity2);

    // Test entity retrieval
    auto& retrieved1 = world.getEntitiesAt(Array<unsigned long, 2>({1, 1}));
    auto& retrieved2 = world.getEntitiesAt(Array<unsigned long, 2>({5, 5}));

    // Verify results
    assert(retrieved1[0].entity == "Entity1");
    assert(retrieved2[0].entity == "Entity2");

    Entity<std::string, 2, unsigned long> entity3;
    entity3.entity = "Entity3";
    entity3.coords = Array<unsigned long, 2>({1, 1});
    world.spawn(entity3);

    auto& retrieved3 = world.getEntitiesAt(Array<unsigned long, 2>({1, 1}));
    assert(retrieved3[0].entity == "Entity1");
    assert(retrieved3[1].entity == "Entity3");

    // Create a 3D world of size 2x3x5
    Array<int, 3> worldSize3({2, 3, 5});
    DiscreteWorld<char, 3, int> world3(worldSize3);

    // Create some test entities
    Entity<char, 3, int> entity3a;
    entity3a.entity = 'a';
    entity3a.coords = Array<int, 3>({2, 3, 5});

    Entity<char, 3, int> entity3b;
    entity3b.entity = 'b';
    entity3b.coords = Array<int, 3>({0, 1, 0});

    // Spawn entities into the world
    world3.spawn(entity3a);
    world3.spawn(entity3b);

    // Test entity retrieval
    auto& retrieved3a = world3.getEntitiesAt(entity3a.coords);
    auto& retrieved3b = world3.getEntitiesAt(entity3b.coords);
    auto& retrieved3v = world3.getEntitiesAt(Array<int, 3>({0, 0, 0}));

    // Verify results
    assert(retrieved3a[0].entity == 'a');
    assert(retrieved3b[0].entity == 'b');

    // getEntitiesOf
    DiscreteWorld<std::string, 2, unsigned long> typeWorld(Array<unsigned long, 2>({10, 10}));

    // Create multiple entities of the same type
    Entity<std::string, 2, unsigned long> cat1;
    cat1.entity = "cat";
    cat1.coords = Array<unsigned long, 2>({1, 1});

    Entity<std::string, 2, unsigned long> cat2;
    cat2.entity = "cat";
    cat2.coords = Array<unsigned long, 2>({3, 4});

    Entity<std::string, 2, unsigned long> dog1;
    dog1.entity = "dog";
    dog1.coords = Array<unsigned long, 2>({2, 2});

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
    Array<unsigned long, 2> worldSize({10, 10});
    DiscretePtrWorld<std::string, 2, unsigned long> world(worldSize);

    // Test shared ownership
    {
        auto entity1 = std::make_shared<Entity<std::string, 2, unsigned long>>();
        entity1->entity = "Entity1";
        entity1->coords = Array<unsigned long, 2>({1, 1});
        
        // Initial reference count should be 1
        assert(entity1.use_count() == 1);
        
        // Spawn should increase reference count
        world.spawn(entity1);
        assert(entity1.use_count() == 2);
        
        // Test retrieval maintains correct reference count
        auto retrieved = world.getEntitiesAt(Array<unsigned long, 2>({1, 1}));
        assert(retrieved[0].use_count() == 3);
        assert(retrieved[0]->entity == "Entity1");
    }

    // Test multiple entities at same location
    {
        auto cat1 = std::make_shared<Entity<std::string, 2, unsigned long>>();
        cat1->entity = "cat";
        cat1->coords = Array<unsigned long, 2>({2, 2});
        
        auto cat2 = std::make_shared<Entity<std::string, 2, unsigned long>>();
        cat2->entity = "cat";
        cat2->coords = Array<unsigned long, 2>({2, 2});
        
        world.spawn(cat1);
        world.spawn(cat2);
        
        auto cats_at_location = world.getEntitiesAt(Array<unsigned long, 2>({2, 2}));
        assert(cats_at_location.size() == 2);
        assert(cats_at_location[0].use_count() == 3);
        assert(cats_at_location[1].use_count() == 3);
    }

    // Test getEntitiesOf with shared ownership
    {
        auto dog1 = std::make_shared<Entity<std::string, 2, unsigned long>>();
        dog1->entity = "dog";
        dog1->coords = Array<unsigned long, 2>({3, 3});
        
        auto dog2 = std::make_shared<Entity<std::string, 2, unsigned long>>();
        dog2->entity = "dog";
        dog2->coords = Array<unsigned long, 2>({4, 4});
        
        world.spawn(dog1);
        world.spawn(dog2);
        
        // Get all dogs and verify reference counts
        auto dogs = world.getEntitiesOf("dog");
        assert(dogs.size() == 2);
        assert(dogs[0].use_count() == 3);
        assert(dogs[1].use_count() == 3);
        
        // Verify coordinates
        bool found_dog1 = false, found_dog2 = false;
        for(const auto& dog : dogs) {
            if(dog->coords[0] == 3 && dog->coords[1] == 3) found_dog1 = true;
            if(dog->coords[0] == 4 && dog->coords[1] == 4) found_dog2 = true;
        }
        assert(found_dog1 && found_dog2);
    }

    // Test pointer validity after original shared_ptr goes out of scope
    {
        std::weak_ptr<Entity<std::string, 2, unsigned long>> weak_entity;
        {
            auto temp_entity = std::make_shared<Entity<std::string, 2, unsigned long>>();
            temp_entity->entity = "temp";
            temp_entity->coords = Array<unsigned long, 2>({5, 5});
            world.spawn(temp_entity);
            weak_entity = temp_entity;
            assert(weak_entity.use_count() == 2); // One in world, one in temp_entity
        }
        // Original shared_ptr is gone, but world should still hold reference
        assert(!weak_entity.expired());
        assert(weak_entity.use_count() == 1);
        
        auto entities = world.getEntitiesAt(Array<unsigned long, 2>({5, 5}));
        assert(entities.size() == 1);
        assert(entities[0]->entity == "temp");
    }

    // Test larger world and memory management
    {
        Array<unsigned long, 3> worldSize3({5, 5, 5});
        DiscretePtrWorld<int, 3, unsigned long> world3(worldSize3);
        
        std::vector<std::weak_ptr<Entity<int, 3, unsigned long>>> weak_refs;
        
        // Spawn 100 entities
        for(int i = 0; i < 100; i++) {
            auto entity = std::make_shared<Entity<int, 3, unsigned long>>();
            entity->entity = i;
            entity->coords = Array<unsigned long, 3>({
                static_cast<unsigned long>(i % 5),
                static_cast<unsigned long>((i/5) % 5),
                static_cast<unsigned long>((i/25) % 5)
            });
            world3.spawn(entity);
            weak_refs.push_back(entity);
        }
        
        // Verify all entities still exist after original pointers gone
        for(const auto& weak_ref : weak_refs) {
            assert(!weak_ref.expired());
            assert(weak_ref.use_count() == 1); // Only world holds reference
        }
    }

    {
        // Test modifications are reflected across all references
        auto original = std::make_shared<Entity<std::string, 2, unsigned long>>();
        original->entity = "modifiable";
        original->coords = Array<unsigned long, 2>({7, 7});
        world.spawn(original);
        
        // Get references through different methods
        auto by_location = world.getEntitiesAt(Array<unsigned long, 2>({7, 7}))[0];
        auto by_type = world.getEntitiesOf("modifiable")[0];
        
        // Modify through one reference
        by_location->entity = "modified";
        
        // Verify changes are reflected in all references
        assert(original->entity == "modified");
        assert(by_type->entity == "modified");
        assert(world.getEntitiesAt(Array<unsigned long, 2>({7, 7}))[0]->entity == "modified");
        
        // Check reference counts
        assert(original.use_count() == by_location.use_count());
        assert(by_type.use_count() == by_location.use_count());
    }

    std::cout << "All DiscretePtrWorld tests passed!\n";
}

void test_ptr_world2() {
    std::cout << "Testing DiscretePtrWorld2...\n";

    // Basic world setup
    Array<unsigned long, 2> worldSize({10, 10});
    DiscretePtrWorld2<std::string, 2, unsigned long> world(worldSize);

    // Test weak pointer behavior
    {
        std::weak_ptr<Entity<std::string, 2, unsigned long>> weak_entity;
        {
            auto entity = std::make_shared<Entity<std::string, 2, unsigned long>>();
            entity->entity = "test";
            entity->coords = Array<unsigned long, 2>({1, 1});
            
            weak_entity = std::weak_ptr<Entity<std::string, 2, unsigned long>>(entity);
            assert(!weak_entity.expired());
            
            world.spawn(entity);
            
            // Test retrieval methods while shared_ptr exists
            auto at_location = world.getEntitiesAt(Array<unsigned long, 2>({1, 1}));
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
        for(int i = 0; i < 3; i++) {
            auto entity = std::make_shared<Entity<std::string, 2, unsigned long>>();
            entity->entity = "group";
            entity->coords = Array<unsigned long, 2>({2, 2});
            world.spawn(entity);
            entities.push_back(entity);
        }

        auto at_location = world.getEntitiesAt(Array<unsigned long, 2>({2, 2}));
        assert(at_location.size() == 3);
        
        // Check all weak_ptrs are valid
        for(const auto& weak_entity : at_location) {
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
        entity->coords = Array<unsigned long, 2>({3, 3});
        world.spawn(entity);

        auto at_location = world.getEntitiesAt(Array<unsigned long, 2>({3, 3}));
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
            temp->coords = Array<unsigned long, 2>({4, 4});
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
        auto at_location = world.getEntitiesAt(Array<unsigned long, 2>({4, 4}));
        for(const auto& weak_entity : at_location) {
            assert(weak_entity.expired());
        }
    }

    // Test large-scale entity management
    {
        std::vector<std::shared_ptr<Entity<std::string, 2, unsigned long>>> entities;
        for(int i = 0; i < 100; i++) {
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
        for(const auto& weak_entity : mass_entities) {
            if(!weak_entity.expired()) {
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
            Array<unsigned long, 2> size({10, 10});
            DiscretePtrWorld2<std::string, 2> temp_world(size);
            
            auto entity = std::make_shared<Entity<std::string, 2>>();
            entity->entity = "scope_test";
            entity->coords = Array<unsigned long, 2>({1, 1});
            
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
        Array<unsigned long, 2> size({10, 10});
        DiscretePtrWorld2<std::string, 2> world1(size);
        DiscretePtrWorld2<std::string, 2> world2(size);
        
        auto shared_entity = std::make_shared<Entity<std::string, 2>>();
        shared_entity->entity = "shared";
        shared_entity->coords = Array<unsigned long, 2>({5, 5});
        
        // Spawn in both worlds
        world1.spawn(shared_entity);
        world2.spawn(shared_entity);
        
        std::weak_ptr<Entity<std::string, 2>> tracker = shared_entity;
        
        // Verify entity exists in both worlds
        auto in_world1 = world1.getEntitiesAt(Array<unsigned long, 2>({5, 5}));
        auto in_world2 = world2.getEntitiesAt(Array<unsigned long, 2>({5, 5}));
        
        assert(in_world1.size() == 1 && in_world2.size() == 1);
        assert(!in_world1[0].expired() && !in_world2[0].expired());
        
        // Despawn from world1, should still exist in world2
        world1.despawn(shared_entity);
        assert(!tracker.expired());
        assert(world1.getEntitiesAt(Array<unsigned long, 2>({5, 5})).empty());
        assert(!world2.getEntitiesAt(Array<unsigned long, 2>({5, 5})).empty());
        
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
        Array<unsigned long, 2> size({10, 10});
        DiscretePtrWorld2<std::string, 2> outer_world(size);
        
        {
            DiscretePtrWorld2<std::string, 2> inner_world(size);
            auto nested_entity = std::make_shared<Entity<std::string, 2>>();
            nested_entity->entity = "nested";
            nested_entity->coords = Array<unsigned long, 2>({3, 3});
            
            // Spawn in both worlds
            outer_world.spawn(nested_entity);
            inner_world.spawn(nested_entity);
            nested_tracker = nested_entity;
            
            assert(!nested_tracker.expired());
        }
        // Inner world gone, entity should still exist in outer world
        assert(!nested_tracker.expired());
        
        auto still_in_outer = outer_world.getEntitiesAt(Array<unsigned long, 2>({3, 3}));
        assert(still_in_outer.size() == 1);
        assert(!still_in_outer[0].expired());
    }

    // Test 4: Multiple world cleanup order
    {
        std::vector<std::weak_ptr<Entity<std::string, 2>>> trackers;
        Array<unsigned long, 2> size({5, 5});
        
        auto world1 = make_unique<DiscretePtrWorld2<std::string, 2>>(size);
        auto world2 = make_unique<DiscretePtrWorld2<std::string, 2>>(size);
        
        // Create entities in both worlds
        for(int i = 0; i < 10; i++) {
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
        for(const auto& tracker : trackers) {
            assert(!tracker.expired());
        }
        
        // Delete world2, now entities should be gone
        world2.reset();
        for(const auto& tracker : trackers) {
            assert(tracker.expired());
        }
    }

    std::cout << "All DiscretePtrWorld2 scoping tests passed!\n";
}

void test_engine1() {
    std::cout << "Testing Engine functionality and memory safety...\n";

    // Test 1: Basic spawn/despawn with rectangular world
    {
        Engine<std::string, 2> engine(Array<unsigned long, 2>({10, 14}));
        
        Entity<std::string, 2> entity;
        entity.entity = "test_entity";
        entity.coords = Array<unsigned long, 2>({1, 14});
        
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
        Engine<int, 3> engine(Array<unsigned long, 3>({4, 7, 2}));

        // Spawn multiple entities
        for(int i = 0; i < 100; i++) {
            Entity<int, 3> entity;
            entity.entity = i % 3;
            entity.coords = Array<unsigned long, 3>({
                static_cast<unsigned long>(i % 5),
                static_cast<unsigned long>((i/5) % 8),
                static_cast<unsigned long>((i/40) % 3)
            });
            
            engine.spawn(entity);
        }
        
        // Verify all entities of each type
        for(int type = 0; type < 3; type++) {
            Entity<int, 3> probe;
            probe.entity = type;
            auto type_entities = engine.world.getEntitiesOf(type);
            assert(type_entities.size() == 34 || type_entities.size() == 33); // 100/3 rounded
        }

        // Despawn half
        for(int i = 0; i < 50; i++) {
            Entity<int, 3> entity;
            entity.entity = i % 3;
            entity.coords = Array<unsigned long, 3>({
                static_cast<unsigned long>(i % 5),
                static_cast<unsigned long>((i/5) % 8),
                static_cast<unsigned long>((i/40) % 3)
            });
            engine.despawn(entity);
        }

        // Verify approximately half remain
        auto all_entities = engine.world.getEntities();
        int valid_count = 0;
        for(auto& weak_ptr : all_entities) {
            if(!weak_ptr.expired()) valid_count++;
        }
        assert(valid_count == 50);
    }

    // Test 3: Memory safety with nested scopes
    {
        auto engine_ptr = make_unique<Engine<std::string, 2>>(Array<unsigned long, 2>({20, 10}));
        std::weak_ptr<Entity<std::string, 2>> weak_entity;
        
        {
            Entity<std::string, 2> entity;
            entity.entity = "scope_test";
            entity.coords = Array<unsigned long, 2>({15, 8});
            
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
        Engine<std::string, 1> engine(Array<unsigned long, 1>({100}));
        
        Entity<std::string, 1> entity1{"type1", Array<unsigned long, 1>({5})};
        Entity<std::string, 1> entity2{"type2", Array<unsigned long, 1>({50})};
        Entity<std::string, 1> entity3{"type1", Array<unsigned long, 1>({99})};

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
        Engine<int, 1> engine(Array<unsigned long, 1>({1000}));
        
        for(int cycle = 0; cycle < 5; cycle++) {
            for(int i = 0; i < 500; i++) {
                Entity<int, 1> entity;
                entity.entity = i % 10;
                entity.coords = Array<unsigned long, 1>({static_cast<unsigned long>(i * 2)});
                engine.spawn(entity);
            }
            
            // Verify all entities exist
            auto all_entities = engine.world.getEntities();
            int valid_count = 0;
            for(auto& weak_ptr : all_entities) {
                if(!weak_ptr.expired()) valid_count++;
            }
            assert(valid_count == 500);
            
            for(int i = 0; i < 500; i++) {
                Entity<int, 1> entity;
                entity.entity = i % 10;
                entity.coords = Array<unsigned long, 1>({static_cast<unsigned long>(i * 2)});
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
        Engine<std::string, 2> engine(Array<unsigned long, 2>({10, 15}));  // Non-square world
        
        Entity<std::string, 2> entity;
        entity.entity = "test_entity";
        entity.coords = Array<unsigned long, 2>({1, 14});  // Testing near boundary
        
        engine.spawn(entity);
        
        Entity<std::string, 2> match;
        match.entity = "test_entity";
        match.coords = Array<unsigned long, 2>({1, 14});
        
        engine.despawn(match);
    }

    // Test 2: Multiple entity management in 3D rectangular world
    {
        Engine<int, 3> engine(Array<unsigned long, 3>({5, 8, 3}));  // Non-cubic world

        // Spawn multiple entities
        for(int i = 0; i < 100; i++) {
            Entity<int, 3> entity;
            entity.entity = i % 3;
            entity.coords = Array<unsigned long, 3>({
                static_cast<unsigned long>(i % 5),
                static_cast<unsigned long>((i/5) % 8),
                static_cast<unsigned long>((i/40) % 3)
            });
            
            engine.spawn(entity);
        }

        // Despawn half
        for(int i = 0; i < 50; i++) {
            Entity<int, 3> entity;
            entity.entity = i % 3;
            entity.coords = Array<unsigned long, 3>({
                static_cast<unsigned long>(i % 5),
                static_cast<unsigned long>((i/5) % 8),
                static_cast<unsigned long>((i/40) % 3)
            });
            engine.despawn(entity);
        }
    }

    // Test 3: Memory safety with nested scopes (rectangular world)
    {
        auto engine_ptr = make_unique<Engine<std::string, 2>>(Array<unsigned long, 2>({20, 10}));
        
        {
            Entity<std::string, 2> entity;
            entity.entity = "scope_test";
            entity.coords = Array<unsigned long, 2>({15, 8});
            
            engine_ptr->spawn(entity);
        }
        
        engine_ptr.reset();
    }

    // Test 4: 1D world basic operations
    {
        Engine<std::string, 1> engine(Array<unsigned long, 1>({100}));
        
        // Test multiple entities at different positions
        Entity<std::string, 1> entity1{"type1", Array<unsigned long, 1>({5})};
        Entity<std::string, 1> entity2{"type2", Array<unsigned long, 1>({50})};
        Entity<std::string, 1> entity3{"type1", Array<unsigned long, 1>({99})};

        engine.spawn(entity1);
        engine.spawn(entity2);
        engine.spawn(entity3);

        engine.despawn(entity1);
        engine.despawn(entity2);
        engine.despawn(entity3);
    }

    // Test 5: 1D world stress test
    {
        Engine<int, 1> engine(Array<unsigned long, 1>({1000}));
        
        // Rapid spawn/despawn cycles
        for(int cycle = 0; cycle < 5; cycle++) {
            for(int i = 0; i < 500; i++) {
                Entity<int, 1> entity;
                entity.entity = i % 10;
                entity.coords = Array<unsigned long, 1>({static_cast<unsigned long>(i * 2)});
                engine.spawn(entity);
            }
            
            for(int i = 0; i < 500; i++) {
                Entity<int, 1> entity;
                entity.entity = i % 10;
                entity.coords = Array<unsigned long, 1>({static_cast<unsigned long>(i * 2)});
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
        Engine<std::string, 1> engine(Array<unsigned long, 1>({20}));
        
        Entity<std::string, 1> entity;
        entity.entity = "test_entity";
        entity.coords = Array<unsigned long, 1>({5});
        
        engine.spawn(entity);
        auto matching = engine.world.getEntitiesMatching(entity);
        assert(matching.size() == 1);
        assert(!matching[0].expired());
        assert(matching[0].lock()->entity == "test_entity");
        
        Entity<std::string, 1> match;
        match.entity = "test_entity";
        match.coords = Array<unsigned long, 1>({5});
        
        Entity<std::string, 1> entity2;
        entity2.entity = "another_entity";
        entity2.coords = Array<unsigned long, 1>({5});
        
        engine.spawn(entity2);
        auto at_location = engine.world.getEntitiesAt(Array<unsigned long, 1>({5}));
        assert(at_location.size() == 2);
        
        engine.despawn(match);
        at_location = engine.world.getEntitiesAt(Array<unsigned long, 1>({5}));
        assert(at_location.size() == 1);
        assert(!at_location[0].expired());
        assert(at_location[0].lock()->entity == "another_entity");
        
        // Stress test 1D world
        for(int i = 0; i < 100; i++) {
            Entity<std::string, 1> stress_entity;
            stress_entity.entity = "stress_" + std::to_string(i);
            stress_entity.coords = Array<unsigned long, 1>({static_cast<unsigned long>(i % 20)});
            engine.spawn(stress_entity);
        }
        auto all_entities = engine.world.getEntities();
        assert(all_entities.size() == 101); // 100 stress + 1 remaining another_entity
    }

    // Test 2: Basic spawn/despawn with non-square dimensions
    {
        Engine<std::string, 2> engine(Array<unsigned long, 2>({14, 9}));
        
        Entity<std::string, 2> entity;
        entity.entity = "test_entity";
        entity.coords = Array<unsigned long, 2>({14, 9});
        
        engine.spawn(entity);
        auto matching = engine.world.getEntitiesMatching(entity);
        assert(matching.size() == 1);
        assert(!matching[0].expired());
        assert(matching[0].lock()->entity == "test_entity");
        
        Entity<std::string, 2> match;
        match.entity = "test_entity";
        match.coords = Array<unsigned long, 2>({14, 9});
        
        engine.despawn(match);
        matching = engine.world.getEntitiesMatching(entity);
        assert(matching.empty());
    }

    // Test 3: Multiple entity management in 3D non-cubic world
    {
        Engine<int, 3> engine(Array<unsigned long, 3>({7, 4, 2}));

        for(int i = 0; i < 100; i++) {
            Entity<int, 3> entity;
            entity.entity = i % 3;
            entity.coords = Array<unsigned long, 3>({
                static_cast<unsigned long>(i % 8),
                static_cast<unsigned long>((i/8) % 5),
                static_cast<unsigned long>((i/40) % 3)
            });
            engine.spawn(entity);
        }
        
        auto all_entities = engine.world.getEntities();
        assert(all_entities.size() == 100);
        
        // Verify distribution of entity types
        for(int type = 0; type < 3; type++) {
            Entity<int, 3> probe;
            probe.entity = type;
            auto type_entities = engine.world.getEntitiesOf(type);
            assert(type_entities.size() == 34 || type_entities.size() == 33); // ~100/3
        }

        for(int i = 0; i < 50; i++) {
            Entity<int, 3> entity;
            entity.entity = i % 3;
            entity.coords = Array<unsigned long, 3>({
                static_cast<unsigned long>(i % 8),
                static_cast<unsigned long>((i/8) % 5),
                static_cast<unsigned long>((i/40) % 3)
            });
            engine.despawn(entity);
        }
        
        all_entities = engine.world.getEntities();
        int valid_count = 0;
        for(const auto& weak_ptr : all_entities) {
            if(!weak_ptr.expired()) valid_count++;
        }
        assert(valid_count == 50); // ~50 remaining
    }

    // Test 4: Memory safety with nested scopes
    {
        auto engine_ptr = make_unique<Engine<std::string, 2>>(Array<unsigned long, 2>({12, 8}));
        std::weak_ptr<Entity<std::string, 2>> weak_entity;
        
        {
            Entity<std::string, 2> entity;
            entity.entity = "scope_test";
            entity.coords = Array<unsigned long, 2>({11, 7});
            
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
        Engine<std::string, 2> engine(Array<unsigned long, 2>({4, 6}));
        
        Entity<std::string, 2> entity1{"type1", Array<unsigned long, 2>({4, 6})};
        Entity<std::string, 2> entity2{"type2", Array<unsigned long, 2>({4, 6})};
        Entity<std::string, 2> entity3{"type1", Array<unsigned long, 2>({4, 6})};

        engine.spawn(entity1);
        engine.spawn(entity2);
        engine.spawn(entity3);

        auto at_location = engine.world.getEntitiesAt(Array<unsigned long, 2>({4, 6}));
        assert(at_location.size() == 3);
        
        auto type1_entities = engine.world.getEntitiesOf("type1");
        assert(type1_entities.size() == 2);

        engine.despawn(entity1);
        type1_entities = engine.world.getEntitiesOf("type1");
        assert(type1_entities.size() == 0);
        
        engine.despawn(entity2);
        at_location = engine.world.getEntitiesAt(Array<unsigned long, 2>({4, 6}));
        assert(at_location.size() == 0);
    }

    // Test 6: Edge cases in 2D world
    {
        Engine<int, 2> engine(Array<unsigned long, 2>({2, 2}));
        
        Entity<int, 2> corner1{1, Array<unsigned long, 2>({0, 0})};
        Entity<int, 2> corner2{2, Array<unsigned long, 2>({0, 2})};
        Entity<int, 2> corner3{3, Array<unsigned long, 2>({2, 0})};
        Entity<int, 2> corner4{4, Array<unsigned long, 2>({2, 2})};

        engine.spawn(corner1);
        engine.spawn(corner2);
        engine.spawn(corner3);
        engine.spawn(corner4);

        auto all_entities = engine.world.getEntities();
        assert(all_entities.size() == 4);

        // Verify corner positions
        auto at_00 = engine.world.getEntitiesAt(Array<unsigned long, 2>({0, 0}));
        auto at_02 = engine.world.getEntitiesAt(Array<unsigned long, 2>({0, 2}));
        auto at_20 = engine.world.getEntitiesAt(Array<unsigned long, 2>({2, 0}));
        auto at_22 = engine.world.getEntitiesAt(Array<unsigned long, 2>({2, 2}));
        
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
        Engine<int, 3> engine(Array<unsigned long, 3>({4, 4, 4}));
        std::vector<Entity<int, 3>> entities;
        
        for(unsigned long x = 0; x < 4; x++) {
            for(unsigned long y = 0; y < 4; y++) {
                for(unsigned long z = 0; z < 4; z++) {
                    entities.push_back(Entity<int, 3>{
                        static_cast<int>(x + y + z),
                        Array<unsigned long, 3>({x, y, z})
                    });
                }
            }
        }
        assert(entities.size() == 64); // 4x4x4

        for(int cycle = 0; cycle < 3; cycle++) {
            for(const auto& entity : entities) {
                engine.spawn(entity);
            }
            auto all_entities = engine.world.getEntities();
            assert(all_entities.size() == 64);
            
            for(const auto& entity : entities) {
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
        Engine<int, 1> engine(Array<unsigned long, 1>({100000}));
        
        for(int i = 0; i < 50000; i++) {
            Entity<int, 1> entity{i % 100, Array<unsigned long, 1>({static_cast<unsigned long>(i * 2)})};
            engine.spawn(entity);
        }
        
        auto all_entities = engine.world.getEntities();
        assert(all_entities.size() == 50000);
        
        for(int type = 0; type < 100; type++) {
            auto type_entities = engine.world.getEntitiesOf(type);
            assert(type_entities.size() == 500); // 50000/100
        }

        for(int i = 0; i < 50000; i += 2) {
            Entity<int, 1> entity{i % 100, Array<unsigned long, 1>({static_cast<unsigned long>(i * 2)})};
            engine.despawn(entity);
        }
        
        all_entities = engine.world.getEntities();
        assert(all_entities.size() == 25000);
    }
    std::cout << "test1 complete" << std::endl;

    // Test 2: Dense 3D world
    {
        Engine<EntityValue, 3> engine(Array<unsigned long, 3>({50, 50, 50}));
        std::vector<Entity<EntityValue, 3>> entities;
        
        // Create 100k entities with mixed types
        for(int i = 0; i < 100000; i++) {
            EntityValue val;
            if (i % 3 == 0) {
                val.i = i;
            } else if (i % 3 == 1) {
                val.d = i / 100.0;
            } else {
                snprintf(val.s, 16, "e%d", i);
            }
            
            entities.push_back(Entity<EntityValue, 3>{
                val,
                Array<unsigned long, 3>({
                    static_cast<unsigned long>(i % 50),
                    static_cast<unsigned long>((i/50) % 50),
                    static_cast<unsigned long>((i/2500) % 50)
                })
            });
        }

        // Rapid spawn/despawn cycles
        for(int cycle = 0; cycle < 0; cycle++) {
            for(const auto& entity : entities) {
                engine.spawn(entity);
            }
            assert(engine.world.getEntities().size() == 100000);
            
            for(size_t i = 0; i < entities.size(); i += 2) {
                engine.despawn(entities[i]); // memory leak?
            }
            assert(engine.world.getEntities().size() == 50000);
            
            for(size_t i = 0; i < entities.size(); i += 4) {
                engine.spawn(entities[i]);
            }
            assert(engine.world.getEntities().size() == 75000);
            
            for(const auto& entity : entities) {
                engine.despawn(entity);
            }
            assert(engine.world.getEntities().empty());
        }
    }
    std::cout << "test2 complete" << std::endl;


    // Test 3: Edge coordinates stress test
    {
        Engine<int, 3> engine(Array<unsigned long, 3>({99, 99, 99}));
        
        // Fill all edges of the cube
        for(unsigned long i = 0; i < 100; i++) {
            // Edges along x
            engine.spawn(Entity<int, 3>{1, Array<unsigned long, 3>({i, 0, 0})});
            engine.spawn(Entity<int, 3>{1, Array<unsigned long, 3>({i, 99, 0})});
            engine.spawn(Entity<int, 3>{1, Array<unsigned long, 3>({i, 0, 99})});
            engine.spawn(Entity<int, 3>{1, Array<unsigned long, 3>({i, 99, 99})});
            
            // Edges along y
            engine.spawn(Entity<int, 3>{2, Array<unsigned long, 3>({0, i, 0})});
            engine.spawn(Entity<int, 3>{2, Array<unsigned long, 3>({99, i, 0})});
            engine.spawn(Entity<int, 3>{2, Array<unsigned long, 3>({0, i, 99})});
            engine.spawn(Entity<int, 3>{2, Array<unsigned long, 3>({99, i, 99})});
            
            // Edges along z
            engine.spawn(Entity<int, 3>{3, Array<unsigned long, 3>({0, 0, i})});
            engine.spawn(Entity<int, 3>{3, Array<unsigned long, 3>({99, 0, i})});
            engine.spawn(Entity<int, 3>{3, Array<unsigned long, 3>({0, 99, i})});
            engine.spawn(Entity<int, 3>{3, Array<unsigned long, 3>({99, 99, i})});
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
        
        for(int i = 0; i < 100000; i++) {
            for(const auto& corner : corners) {
                engine.spawn(Entity<int, 3>{i, corner});
                if(i > 0) {
                    engine.despawn(Entity<int, 3>{i-1, corner});
                }
            }
        }

        for(int i = 0; i < 100000; i++) {
            for(const auto& corner : corners) {
                engine.spawn(Entity<int, 3>{i, corner});
            }
        }

        for(int i = 0; i < 100000; i++) {
            for(const auto& corner : corners) {
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
        Engine<std::string, 1> engine(Array<unsigned long, 1>({20}));
        
        // Create and spawn entity
        Entity<std::string, 1> entity;
        entity.entity = "test_entity";
        entity.coords = Array<unsigned long, 1>({5});
        
        engine.spawn(entity);
        
        // Create matching entity for despawn
        Entity<std::string, 1> match;
        match.entity = "test_entity";
        match.coords = Array<unsigned long, 1>({5});
        
        // Multiple entities at same location
        Entity<std::string, 1> entity2;
        entity2.entity = "another_entity";
        entity2.coords = Array<unsigned long, 1>({5});
        
        engine.spawn(entity2);
        engine.despawn(match); // Should only remove test_entity
        
        // Stress test 1D world
        for(int i = 0; i < 100; i++) {
            Entity<std::string, 1> stress_entity;
            stress_entity.entity = "stress_" + std::to_string(i);
            stress_entity.coords = Array<unsigned long, 1>({static_cast<unsigned long>(i % 20)});
            engine.spawn(stress_entity);
        }
    }

    // Test 2: Basic spawn/despawn with non-square dimensions
    {
        Engine<std::string, 2> engine(Array<unsigned long, 2>({15, 10})); // Non-square world
        
        Entity<std::string, 2> entity;
        entity.entity = "test_entity";
        entity.coords = Array<unsigned long, 2>({14, 9}); // Test edges
        
        engine.spawn(entity);
        
        Entity<std::string, 2> match;
        match.entity = "test_entity";
        match.coords = Array<unsigned long, 2>({14, 9});
        
        engine.despawn(match);
    }

    // Test 3: Multiple entity management in 3D non-cubic world
    {
        Engine<int, 3> engine(Array<unsigned long, 3>({8, 5, 3})); // Non-cubic world

        // Spawn multiple entities
        for(int i = 0; i < 100; i++) {
            Entity<int, 3> entity;
            entity.entity = i % 3;
            entity.coords = Array<unsigned long, 3>({
                static_cast<unsigned long>(i % 8),
                static_cast<unsigned long>((i/8) % 5),
                static_cast<unsigned long>((i/40) % 3)
            });
            
            engine.spawn(entity);
        }

        // Despawn half the entities
        for(int i = 0; i < 50; i++) {
            Entity<int, 3> entity;
            entity.entity = i % 3;
            entity.coords = Array<unsigned long, 3>({
                static_cast<unsigned long>(i % 8),
                static_cast<unsigned long>((i/8) % 5),
                static_cast<unsigned long>((i/40) % 3)
            });
            engine.despawn(entity);
        }
    }

    // Test 4: Memory safety with nested scopes
    {
        auto engine_ptr = make_unique<Engine<std::string, 2>>(Array<unsigned long, 2>({12, 8}));
        
        {
            Entity<std::string, 2> entity;
            entity.entity = "scope_test";
            entity.coords = Array<unsigned long, 2>({11, 7});
            
            engine_ptr->spawn(entity);
        }
        
        engine_ptr.reset();
    }

    // Test 5: Concurrent entity types at same location (continued)
    {
        Engine<std::string, 2> engine(Array<unsigned long, 2>({5, 7}));
        
        Entity<std::string, 2> entity1{"type1", Array<unsigned long, 2>({4, 6})};
        Entity<std::string, 2> entity2{"type2", Array<unsigned long, 2>({4, 6})};
        Entity<std::string, 2> entity3{"type1", Array<unsigned long, 2>({4, 6})};

        engine.spawn(entity1);
        engine.spawn(entity2);
        engine.spawn(entity3);

        // Selective despawn
        engine.despawn(entity1);  // Should remove only first "type1"
        engine.despawn(entity2);  // Should remove "type2"
    }

    // Test 6: Edge cases in 2D world
    {
        Engine<int, 2> engine(Array<unsigned long, 2>({3, 3}));
        
        // Test corners
        Entity<int, 2> corner1{1, Array<unsigned long, 2>({0, 0})};
        Entity<int, 2> corner2{2, Array<unsigned long, 2>({0, 2})};
        Entity<int, 2> corner3{3, Array<unsigned long, 2>({2, 0})};
        Entity<int, 2> corner4{4, Array<unsigned long, 2>({2, 2})};

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
        Engine<int, 3> engine(Array<unsigned long, 3>({4, 4, 4}));

        std::vector<Entity<int, 3>> entities;
        
        // Create and store entities
        for(unsigned long x = 0; x < 4; x++) {
            for(unsigned long y = 0; y < 4; y++) {
                for(unsigned long z = 0; z < 4; z++) {
                    entities.push_back(Entity<int, 3>{
                        static_cast<int>(x + y + z),
                        Array<unsigned long, 3>({x, y, z})
                    });
                }
            }
        }

        // Rapid spawn/despawn cycles
        for(int cycle = 0; cycle < 3; cycle++) {
            for(const auto& entity : entities) {
                engine.spawn(entity);
            }
            for(const auto& entity : entities) {
                engine.despawn(entity);
            }
        }
    }

    std::cout << "All additional Engine tests passed!\n";
}

void test_discrete_grid_and_engine() {
    std::cout << "Testing DiscreteGrid and DiscreteEngine functionality...\n";

    // Test 1: Basic spawn/despawn operations in 2D
    {
        std::cout << "Testing basic 2D operations...\n";
        Array<unsigned long, 2> dims({10, 10});
        DiscreteEngine<std::string, 2> engine(dims);

        Entity<std::string, 2> entity;
        entity.entity = "test_entity";
        entity.coords = Array<unsigned long, 2>({5, 5});
        
        engine.spawn(entity);
        
        // Verify spawn
        auto entities_at = engine.getWeakEntitiesAt(Array<unsigned long, 2>({5, 5}));
        assert(entities_at.size() == 1);
        assert(entities_at[0].lock()->entity == "test_entity");
        
        // Test despawn
        engine.despawn(entity);
        auto strong_entities_at = engine.getEntitiesAt(Array<unsigned long, 2>({5, 5}));
        assert(strong_entities_at.empty());
        entities_at = engine.getWeakEntitiesAt(Array<unsigned long, 2>({5, 5}));
        assert(entities_at.empty());
    }

    // Test 2: Multiple entities at same location in 3D
    {
        std::cout << "Testing multiple entities at same location in 3D...\n";
        Array<unsigned long, 3> dims({5, 5, 5});
        DiscreteEngine<int, 3> engine(dims);

        Array<unsigned long, 3> location({2, 2, 2});
        Entity<int, 3> entity1;
        entity1.entity = 1;
        entity1.coords = location;

        Entity<int, 3> entity2;
        entity2.entity = 2;
        entity2.coords = location;

        engine.spawn(entity1);
        engine.spawn(entity2);

        // Verify both entities
        auto entities_at = engine.getEntitiesAt(location);
        assert(entities_at.size() == 2);
        bool found1 = false, found2 = false;
        for(const auto& e : entities_at) {
            if(e->entity == 1) found1 = true;
            if(e->entity == 2) found2 = true;
        }
        assert(found1 && found2);

        // Test despawn of one entity
        engine.despawn(entity1);
        entities_at = engine.getEntitiesAt(location);
        assert(entities_at.size() == 1);
        assert(entities_at[0]->entity == 2);
    }

    // Test 3: Edge cases with 1D world
    {
        std::cout << "Testing 1D world edge cases...\n";
        Array<unsigned long, 1> dims({100});
        DiscreteEngine<int, 1> engine(dims);

        // Test boundaries
        Entity<int, 1> start_entity{1, Array<unsigned long, 1>({0})};
        Entity<int, 1> end_entity{2, Array<unsigned long, 1>({99})};
        
        engine.spawn(start_entity);
        engine.spawn(end_entity);

        // Verify boundary entities
        auto start_entities = engine.getEntitiesAt(Array<unsigned long, 1>({0}));
        auto end_entities = engine.getEntitiesAt(Array<unsigned long, 1>({99}));
        assert(start_entities.size() == 1);
        assert(end_entities.size() == 1);
        assert(start_entities[0]->entity == 1);
        assert(end_entities[0]->entity == 2);

        engine.despawn(start_entity);
        engine.despawn(end_entity);
        
        // Verify removal
        assert(engine.getEntitiesAt(Array<unsigned long, 1>({0})).empty());
        assert(engine.getEntitiesAt(Array<unsigned long, 1>({99})).empty());
    }

    // Test 4: Grid coverage test
    {
        std::cout << "Testing grid coverage...\n";
        Array<unsigned long, 2> dims({3, 3});
        DiscreteEngine<int, 2> engine(dims);

        // Spawn entities in each cell
        for(unsigned long x = 0; x < 3; x++) {
            for(unsigned long y = 0; y < 3; y++) {
                Entity<int, 2> entity;
                entity.entity = x * 3 + y;
                entity.coords = Array<unsigned long, 2>({x, y});
                engine.spawn(entity);
            }
        }

        // Verify each cell
        for(unsigned long x = 0; x < 3; x++) {
            for(unsigned long y = 0; y < 3; y++) {
                auto entities = engine.getEntitiesAt(Array<unsigned long, 2>({x, y}));
                assert(entities.size() == 1);
                assert(entities[0]->entity == x * 3 + y);
            }
        }
    }

    std::cout << "All DiscreteGrid and DiscreteEngine tests passed!\n";
}

int main(int argc, char *argv[])
{
    test_array_operations();
    test_narray();
    test_world();
    test_ptr_world();
    test_ptr_world2();
    test_ptr_world2_scoping();
    test_engine1_private();
    test_engine1();
    test_engine2_private();
    test_engine2();
    test_discrete_grid_and_engine();
    // test_engine_mass();
    return 0;
}
