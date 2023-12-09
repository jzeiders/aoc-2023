#ifndef SOLVER_H
#define SOLVER_H

#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <sstream>

#include "grid.hpp"

class Solver
{
public:
    Solver(){};
    virtual ~Solver(){};
    virtual std::string getDay() = 0;

    virtual long solution(std::ifstream *file) = 0;
    virtual long solution2(std::ifstream *file) = 0;

    long solve()
    {
        std::cout << "Small" << std::endl;
        std::ifstream *smallFile = this->loadFile("/Users/jzeiders/Documents/Code/Mars/AOC/data/day" + getDay() + "_small.txt");
        long smallSolution = this->solution(smallFile);
        std::cout << smallSolution << std::endl;

        std::cout << "Full" << std::endl;
        long fullSolution = this->solution(this->loadMainFile());
        return fullSolution;
    }

    long solve2()
    {
        std::cout << "Day " << getDay() << " small" << std::endl;
        std::ifstream *smallFile = this->loadFile("/Users/jzeiders/Documents/Code/Mars/AOC/data/day" + getDay() + "_small2.txt");
        long smallSolution = this->solution2(smallFile);
        std::cout << smallSolution << std::endl;

        std::cout << "Day " << getDay() << " full" << std::endl;
        long fullSolution = this->solution2(this->loadMainFile());
        return fullSolution;
    }

private:
    std::ifstream *loadMainFile()
    {
        return loadFile("/Users/jzeiders/Documents/Code/Mars/AOC/data/day" + getDay() + ".txt");
    }

    std::ifstream *loadFile(std::string filePath)
    {
        std::ifstream *file = new std::ifstream(filePath);
        if (!file->is_open())
        {
            std::cout << "Unable to open file " << filePath << std::endl;
            exit(1);
        }
        return file;
    }
};

template <typename T, typename S = long>
class LineSolver : public Solver
{
public:
    LineSolver() : Solver(){};
    ~LineSolver(){};

    virtual T parse(std::string line) = 0;
    virtual S solveItem(T item) = 0;
    virtual S solveItem2(T item) = 0;
    virtual long combine(std::vector<S> results) = 0;

    long solution(std::ifstream *file) override
    {
        return solver(file, 1);
    }

    long solution2(std::ifstream *file) override
    {
        return solver(file, 2);
    }

private:
    long solver(std::ifstream *file, int part)
    {

        std::vector<T> parses = std::vector<T>();
        if (file->is_open())
        {
            std::string line;

            while (getline(*file, line))
            {
                T parse = this->parse(line);
                parses.push_back(parse);
            }
            file->close();
        }

        std::vector<S> results;
        auto solver = [this, part](const T &item)
        { return part == 1 ? this->solveItem(item) : this->solveItem2(item); };

        std::transform(parses.begin(), parses.end(), std::back_inserter(results), solver);

        return combine(results);
    }
};

class GridSolver : public Solver
{
public:
    GridSolver() : Solver(){};

    virtual long solveGrid(Grid<char> &grid) = 0;
    virtual long solveGrid2(Grid<char> &grid) = 0;

    long solution(std::ifstream *file)
    {
        auto grid = parseGrid(file);
        return solveGrid(grid);
    }

    long solution2(std::ifstream *file)
    {
        auto grid = parseGrid(file);
        return solveGrid2(grid);
    }

private:
    Grid<char> parseGrid(std::ifstream *file)
    {
        std::vector<std::vector<char>> rows;
        if (file->is_open())
        {
            std::string line;

            while (getline(*file, line))
            {
                std::vector<char> row(line.begin(), line.end());
                rows.push_back(row);
            }
            file->close();
        }

        return Grid<char>(rows);
    }
};

#endif // SOLVER_H