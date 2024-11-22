#include <cstdint>

struct RoboPredictor {
    struct RoboMemory;
    RoboMemory* roboMemory_ptr;
    bool useGroupTags; // Flag to toggle Task 2 features

    bool predictTimeOfDayOnNextPlanet(std::uint64_t nextPlanetID,
                                      bool spaceshipComputerPrediction,
                                      int nextPlanetGroupTag);

    void observeAndRecordTimeofdayOnNextPlanet(std::uint64_t nextPlanetID,
                                               bool timeOfDayOnNextPlanet,
                                               int nextPlanetGroupTag);

    RoboPredictor(bool enableGroupTags);
    ~RoboPredictor();
};

static_assert(
    sizeof(RoboPredictor::RoboMemory) <= 65536,
    "Robo's memory exceeds 65536 bytes (64KiB) in your implementation. "
    "Prediction algorithms using so much "
    "memory are ineligible. Please reduce the size of your RoboMemory struct.");
