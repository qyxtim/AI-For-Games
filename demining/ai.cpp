#include "ai.h"
#include <random>

AI::AI(int s) : b(s), knownSafetyPlace({}), knowledges({})
{
    for (int i = 0; i < b.size; i++)
    {
        for (int j = 0; j < b.size; j++)
        {
            availableActions.insert({i, j});
        }
    }
}

void AI::makeRandomMove()
{
    std::set<GridLocation> relativelySate;
    for (auto iter = availableActions.begin(); iter != availableActions.end(); iter++)
        if (dangerousPlace.find(*iter) == dangerousPlace.end())
            relativelySate.insert(*iter);

    int randIndex = rand() % relativelySate.size();

    GridLocation g;
    for (auto iter = relativelySate.begin(); iter != relativelySate.end(); iter++, randIndex--)
        if (randIndex == 0)
            g = *iter;

    availableActions.erase(g);
    b.click(g);

    if (!b.isEnd())
    {
        knownSafetyPlace.insert(g);

        // Insert something into knowledge
        std::set<GridLocation> locations;
        if (g.x > 0)
            locations.insert({g.x - 1, g.y});
        if (g.x > 0 && g.y > 0)
            locations.insert({g.x - 1, g.y - 1});
        if (g.x > 0 && g.y < b.size - 1)
            locations.insert({g.x - 1, g.y + 1});
        if (g.y > 0)
            locations.insert({g.x, g.y - 1});
        if (g.y < b.size - 1)
            locations.insert({g.x, g.y + 1});
        if (g.x < b.size - 1)
            locations.insert({g.x + 1, g.y});
        if (g.x < b.size - 1 && g.y > 0)
            locations.insert({g.x + 1, g.y - 1});
        if (g.x < b.size - 1 && g.y < b.size - 1)
            locations.insert({g.x + 1, g.y + 1});

        knowledges.insert({locations, b.getMines(g)});
    }
}

void AI::updateKnowledge()
{
    std::set<Knowledge> newKnowledges;
    bool hasUpdate = false;

    do
    {
        newKnowledges.clear();
        hasUpdate = false;

        for (auto iter = knowledges.begin(); iter != knowledges.end(); iter++)
        {
            // Update information about safety places and danger places
            if (iter->numberOfMines == 0)
            {
                for (auto iter2 = iter->locations.begin(); iter2 != iter->locations.end(); iter2++)
                    knownSafetyPlace.insert(*iter2);
                hasUpdate = true;
                continue;
            }
            else if (iter->numberOfMines == iter->locations.size())
            {
                for (auto iter2 = iter->locations.begin(); iter2 != iter->locations.end(); iter2++)
                    dangerousPlace.insert(*iter2);
                hasUpdate = true;
                continue;
            }

            // Based on existing information about safety places and danger places, update knowledge
            std::set<GridLocation> tmp;
            int mines = iter->numberOfMines;
            for (auto iter2 = iter->locations.begin(); iter2 != iter->locations.end(); iter2++)
            {
                if (dangerousPlace.find(*iter2) != dangerousPlace.end())
                {
                    mines--;
                    hasUpdate = true;
                    continue;
                }
                else if (knownSafetyPlace.find(*iter2) != knownSafetyPlace.end())
                {
                    hasUpdate = true;
                    continue;
                }
                tmp.insert(*iter2);
            }
            if (tmp.size() != 0)
                newKnowledges.insert({tmp, mines});
        }

        knowledges = newKnowledges;
    } while (hasUpdate);
}

bool AI::isSubset(const Knowledge &a, const Knowledge &b) const
{
    const Knowledge &small = a.locations.size() <= b.locations.size() ? a : b;
    const Knowledge &big = a.locations.size() > b.locations.size() ? a : b;

    for (auto iter = small.locations.begin(); iter != small.locations.end(); iter++)
    {
        if (big.locations.find(*iter) == big.locations.end())
            return false;
    }
    return true;
}

void AI::makeInduction()
{
    std::set<Knowledge> newKnowledges;
    bool hasUpdate = false;

    do
    {
        hasUpdate = false;
        newKnowledges.clear();
        updateKnowledge();

        for (auto iter = knowledges.begin(); iter != knowledges.end(); iter++)
        {
            for (auto iter2 = iter; iter2 != knowledges.end(); iter2++)
            {
                if (iter == iter2)
                    continue;

                if (isSubset(*iter, *iter2))
                {
                    const Knowledge &small = iter->locations.size() <= iter2->locations.size() ? *iter : *iter2;
                    const Knowledge &big = iter->locations.size() > iter2->locations.size() ? *iter : *iter2;

                    std::set<GridLocation> newlocations;

                    for (auto iterBig = big.locations.begin(); iterBig != big.locations.end(); iterBig++)
                        if (small.locations.find(*iterBig) == small.locations.end())
                            newlocations.insert(*iterBig);

                    newKnowledges.insert(small);
                    newKnowledges.insert({newlocations, big.numberOfMines - small.numberOfMines});

                    hasUpdate = true;
                }
            }
        }
        knowledges = newKnowledges;
    } while (hasUpdate);
}

void AI::move()
{
    GridLocation availableSafetyPlace = {-1, -1};
    for (auto iter = knownSafetyPlace.begin(); iter != knownSafetyPlace.end(); iter++)
    {
        if (availableActions.find(*iter) != availableActions.end())
        {
            availableSafetyPlace = *iter;
            break;
        }
    }

    if (availableSafetyPlace.x != -1 && availableSafetyPlace.y != -1)
    {
        b.click(availableSafetyPlace);

        // Insert something into knowledge
        const GridLocation &g = availableSafetyPlace;
        std::set<GridLocation> locations;
        if (g.x > 0)
            locations.insert({g.x - 1, g.y});
        if (g.x > 0 && g.y > 0)
            locations.insert({g.x - 1, g.y - 1});
        if (g.x > 0 && g.y < b.size - 1)
            locations.insert({g.x - 1, g.y + 1});
        if (g.y > 0)
            locations.insert({g.x, g.y - 1});
        if (g.y < b.size - 1)
            locations.insert({g.x, g.y + 1});
        if (g.x < b.size - 1)
            locations.insert({g.x + 1, g.y});
        if (g.x < b.size - 1 && g.y > 0)
            locations.insert({g.x + 1, g.y - 1});
        if (g.x < b.size - 1 && g.y < b.size - 1)
            locations.insert({g.x + 1, g.y + 1});

        knowledges.insert({locations, b.getMines(g)});

        availableActions.erase(availableSafetyPlace);
    }
    else
        makeRandomMove();

    makeInduction();
}