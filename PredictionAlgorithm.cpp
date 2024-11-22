#include "PredictionAlgorithm.hpp"

const int HASH_TABLE_SIZE = 64 * 1024 / (3 * 8); // Adjusted for group tags

struct RoboPredictor::RoboMemory {
    struct Entry {
        uint64_t planetID;
        bool timeOfDay;
        int groupTag; // Group tag for Task 2
    };

    Entry hashTable[HASH_TABLE_SIZE];
    bool isOccupied[HASH_TABLE_SIZE];

    RoboMemory() {
        for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
            isOccupied[i] = false;
        }
    }

    int hash(uint64_t planetID) {
        return planetID & (HASH_TABLE_SIZE - 1); // Use bitwise AND for faster hashing
    }

    Entry* find(uint64_t planetID) {
        int index = hash(planetID);
        int probe = 1;
        while (isOccupied[index]) {
            if (hashTable[index].planetID == planetID) {
                return &hashTable[index];
            }
            index = (index + probe * probe) % HASH_TABLE_SIZE; // Quadratic probing
            probe++;
        }
        return nullptr;
    }

    void insert(uint64_t planetID, bool timeOfDay, int groupTag) {
        int index = hash(planetID);
        int probe = 1;
        while (isOccupied[index]) {
            index = (index + probe * probe) % HASH_TABLE_SIZE; // Quadratic probing
            probe++;
        }
        hashTable[index].planetID = planetID;
        hashTable[index].timeOfDay = timeOfDay;
        hashTable[index].groupTag = groupTag; // Store group tag
        isOccupied[index] = true;
    }
};

bool RoboPredictor::predictTimeOfDayOnNextPlanet(
    std::uint64_t nextPlanetID, bool spaceshipComputerPrediction, int nextPlanetGroupTag) {
    Entry* entry = roboMemory_ptr->find(nextPlanetID);
    if (entry) {
        if (useGroupTags && entry->groupTag == nextPlanetGroupTag) {
            // Task 2: Use group tags for prediction
            return entry->timeOfDay;
        } else if (!useGroupTags) {
            // Task 1: Ignore group tags
            return entry->timeOfDay;
        }
    }
    return spaceshipComputerPrediction; // Default to spaceship's suggestion
}

void RoboPredictor::observeAndRecordTimeofdayOnNextPlanet(
    std::uint64_t nextPlanetID, bool timeOfDayOnNextPlanet, int nextPlanetGroupTag) {
    if (useGroupTags) {
        // Task 2: Use group tags in memory
        roboMemory_ptr->insert(nextPlanetID, timeOfDayOnNextPlanet, nextPlanetGroupTag);
    } else {
        // Task 1: Use a default group tag of 0
        roboMemory_ptr->insert(nextPlanetID, timeOfDayOnNextPlanet, 0);
    }
}

RoboPredictor::RoboPredictor(bool enableGroupTags) : useGroupTags(enableGroupTags) {
    roboMemory_ptr = new RoboMemory;
}

RoboPredictor::~RoboPredictor() {
    delete roboMemory_ptr;
}
