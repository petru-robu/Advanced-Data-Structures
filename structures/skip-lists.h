/*
Skip lists
Operations to support:
1.insert(value)
2.delete(value)
3.test if value in set
4.greatest number below a value
5.lowest number above a value
6.all numbers in range [x, y] in sorted order
*/

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <fstream>
struct SkipListNode
{
    int value;
    std::vector<SkipListNode *> forward;

    SkipListNode(int val, int level) : value(val), forward(level + 1, nullptr) {}
};

class SkipList
{
private:
    int maxLevel;
    float probability;
    SkipListNode *header;
    std::mt19937 rng;
    std::uniform_real_distribution<> dist;

    int randomLevel()
    {
        int level = 0;
        while (dist(rng) < probability && level < maxLevel)
        {
            level++;
        }
        return level;
    }

public:
    SkipList(int maxLvl = 16, float prob = 0.5) : maxLevel(maxLvl), probability(prob), rng(std::random_device{}()), dist(0.0, 1.0)
    {
        header = new SkipListNode(0, maxLevel);
    }

    ~SkipList()
    {
        SkipListNode *current = header;
        while (current)
        {
            SkipListNode *next = current->forward[0];
            delete current;
            current = next;
        }
    }

    void insert(int value)
    {
        std::vector<SkipListNode *> update(maxLevel + 1);
        SkipListNode *current = header;

        for (int i = maxLevel; i >= 0; --i)
        {
            while (current->forward[i] && current->forward[i]->value < value)
            {
                current = current->forward[i];
            }
            update[i] = current;
        }

        int level = randomLevel();
        SkipListNode *newNode = new SkipListNode(value, level);

        for (int i = 0; i <= level; ++i)
        {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
    }

    bool remove(int value)
    {
        std::vector<SkipListNode *> update(maxLevel + 1);
        SkipListNode *current = header;
        bool found = false;

        for (int i = maxLevel; i >= 0; --i)
        {
            while (current->forward[i] && current->forward[i]->value < value)
            {
                current = current->forward[i];
            }
            update[i] = current;
        }

        if (current->forward[0] && current->forward[0]->value == value)
        {
            found = true;
            SkipListNode *nodeToDelete = current->forward[0];
            for (int i = 0; i <= maxLevel && update[i]->forward[i] == nodeToDelete; ++i)
            {
                update[i]->forward[i] = nodeToDelete->forward[i];
            }
            delete nodeToDelete;
        }
        return found;
    }

    bool contains(int value)
    {
        SkipListNode *current = header;
        for (int i = maxLevel; i >= 0; --i)
        {
            while (current->forward[i] && current->forward[i]->value < value)
            {
                current = current->forward[i];
            }
        }
        return (current->forward[0] && current->forward[0]->value == value);
    }

    int findLargestLessThanOrEqual(int value)
    {
        SkipListNode *current = header;
        SkipListNode *candidate = nullptr;

        for (int i = maxLevel; i >= 0; --i)
        {
            while (current->forward[i] && current->forward[i]->value <= value)
            {
                current = current->forward[i];
                candidate = current;
            }
        }
        return candidate ? candidate->value : -1;
    }

    int findSmallestGreaterThanOrEqual(int value)
    {
        SkipListNode *current = header;

        for (int i = maxLevel; i >= 0; --i)
        {
            while (current->forward[i] && current->forward[i]->value < value)
            {
                current = current->forward[i];
            }
        }
        if (current->forward[0])
        {
            return current->forward[0]->value;
        }
        return -1;
    }

    std::vector<int> findRange(int lowerBound, int upperBound)
    {
        std::vector<int> result;
        SkipListNode *current = header;
        for (int i = maxLevel; i >= 0; --i)
        {
            while (current->forward[i] && current->forward[i]->value < lowerBound)
            {
                current = current->forward[i];
            }
        }

        current = current->forward[0];
        while (current && current->value <= upperBound)
        {
            result.push_back(current->value);
            current = current->forward[0];
        }
        std::sort(result.begin(), result.end());
        return result;
    }

    void printList() const
    {
        for (int i = 0; i <= maxLevel; ++i)
        {
            std::cout << "Level " << i << ": ";
            SkipListNode *current = header->forward[i];
            while (current)
            {
                std::cout << current->value << (current->forward[i] ? " -> " : "");
                current = current->forward[i];
            }
            std::cout << std::endl;
        }
    }
};
