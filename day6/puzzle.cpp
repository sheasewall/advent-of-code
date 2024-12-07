#include <exception>
#include <stdexcept>
#include <iostream>

#include "../headers/solver.h"
#include "../headers/utils.h"

enum Tile
{
    Unexplored,
    Explored,
    Obstacle,
    Offsite
};

enum Direction
{
    North,
    East,
    South,
    West
};

struct Turtle
{
    std::vector<std::vector<Tile>> map;
    int x;
    int y;
    Direction facing;
    int visited = 0;

    Tile *checkAhead()
    {
        switch (facing)
        {
        case North:
            return &map[y - 1][x];
        case East:
            return &map[y][x + 1];
        case South:
            return &map[y + 1][x];
        case West:
            return &map[y][x - 1];
        }
    }

    void rotate()
    {
        switch (facing)
        {
        case North:
            facing = East;
            return;
        case East:
            facing = South;
            return;
        case South:
            facing = West;
            return;
        case West:
            facing = North;
            return;
        }
    }

    void advance()
    {
        switch (facing)
        {
        case North:
            y--;
            break;
        case East:
            x++;
            break;
        case South:
            y++;
            break;
        case West:
            x--;
            break;
        }
    }

    bool move()
    {
        Tile *ahead = checkAhead();
        switch (*ahead)
        {
        case Offsite:
            return false;
        case Obstacle:
            rotate();
            break;
        case Unexplored:
            visited++;
            *ahead = Explored;
            advance();
            break;
        case Explored:
            advance();
            break;
        }
        return true;
    }

    int testObstruction()
    {   
        if (*checkAhead() != Tile::Offsite)
        {
            
        }
        return 0;
    }

    friend std::ostream &operator<<(std::ostream &os, const Turtle &turtle)
    {
        for (size_t y = 0; y < turtle.map.size(); y++)
        {
            for (size_t x = 0; x < turtle.map[y].size(); x++)
            {
                if (x == turtle.x && y == turtle.y)
                {
                    // Show turtle with its facing direction
                    switch (turtle.facing)
                    {
                    case North:
                        os << '^';
                        break;
                    case East:
                        os << '>';
                        break;
                    case South:
                        os << 'v';
                        break;
                    case West:
                        os << '<';
                        break;
                    }
                }
                else
                {
                    // Show map tiles
                    switch (turtle.map[y][x])
                    {
                    case Unexplored:
                        os << '.';
                        break;
                    case Explored:
                        os << 'X';
                        break;
                    case Obstacle:
                        os << '#';
                        break;
                    case Offsite:
                        os << ' ';
                        break;
                    }
                }
            }
            os << '\n';
        }
        return os;
    }
};

namespace day6
{
    class Day6Solver : public solve::Solver<Turtle, int>
    {
    public:
        Day6Solver(std::string name, int puzzle_index) : Solver(name, 6, puzzle_index) {}

        Turtle parseInputFile(std::string file_name) override
        {
            Turtle turtle = Turtle();
            // To be padded later
            turtle.map.push_back(std::vector<Tile>());
            int input_x = 1;
            int input_y = 1;

            std::ifstream file(file_name);
            std::string line;

            while (std::getline(file, line))
            {
                input_y++;
                input_x = 0;
                std::vector<Tile> row = {Tile::Offsite};
                for (char c : line)
                {
                    input_x++;
                    switch (c)
                    {
                    case '#':
                        row.push_back(Tile::Obstacle);
                        break;
                    case '.':
                        row.push_back(Tile::Unexplored);
                        break;
                    case '^':
                        turtle.x = input_x;
                        turtle.y = input_y;
                        turtle.facing = Direction::North;
                        row.push_back(Tile::Explored);
                        turtle.visited++;
                        break;
                    default:
                        std::throw_with_nested(std::runtime_error("Invalid char: " + std::to_string(c)));
                        break;
                    }
                }
                row.push_back(Tile::Offsite);
                turtle.map.push_back(row);
            }
            turtle.map.push_back(std::vector<Tile>(turtle.map[1].size(), Tile::Offsite));
            // Padding the first line now that we know how long a row should be
            turtle.map[0] = std::vector<Tile>(turtle.map[1].size(), Tile::Offsite);

            return turtle;
        }
    };

    class Puzzle1Solver : public Day6Solver
    {
    public:
        Puzzle1Solver() : Day6Solver("puzzle 1", 1) {}

        int computeSolution(Turtle turtle) override
        {
            while (turtle.move());
            return turtle.visited;
        }
    };

    class Puzzle2Solver : public Day6Solver
    {
    public:
        Puzzle2Solver() : Day6Solver("try to trap", 2) {}

        int computeSolution(Turtle turtle) override
        {
            int possible_obstructions = turtle.testObstruction();
            while (turtle.move())
            {
                turtle.testObstruction();
            }
            return int();
        }
    };
}