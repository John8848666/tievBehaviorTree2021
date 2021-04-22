#include "crossdoor_nodes.h"

// This function must be implemented in the .cpp file to create
// a plugin that can be loaded at run-time
BT_REGISTER_NODES(factory)
{
    CrossDoor::RegisterNodes(factory);
}

// For simplicity, in this example the status of the door is not shared
// using ports and blackboards
static bool _parking_slot = false;
static bool _available_parking_slot = false;

NodeStatus CrossDoor::FindParkingSlot()
{
    SleepMS(2000);
    if (_parking_slot)
    {
        return NodeStatus::SUCCESS;
    }
    else
    {
        _parking_slot = true;
        return NodeStatus::FAILURE;
    }
}

NodeStatus CrossDoor::ChangeToAnotherRoad()
{
    SleepMS(3000);
    return NodeStatus::SUCCESS;
}

NodeStatus CrossDoor::AreThereAvailableParkingSlots()
{
    SleepMS(2000);
    if (_available_parking_slot)
    {
        return NodeStatus::SUCCESS;
    }
    else
    {
        _available_parking_slot = true;
        return NodeStatus::FAILURE;
    }
}

NodeStatus CrossDoor::GetInTheParkingSlot()
{
    SleepMS(3000);
    return NodeStatus::SUCCESS;
}

NodeStatus CrossDoor::Park()
{
    SleepMS(3000);
    return NodeStatus::SUCCESS;
}

// Register at once all the Actions and Conditions in this file
void CrossDoor::RegisterNodes(BehaviorTreeFactory& factory)
{
    factory.registerSimpleAction("FindParkingSlot", std::bind(FindParkingSlot));
    factory.registerSimpleAction("ChangeToAnotherRoad", std::bind(ChangeToAnotherRoad));
    factory.registerSimpleCondition("AreThereAvailableParkingSlots", std::bind(AreThereAvailableParkingSlots));
    factory.registerSimpleAction("GetInTheParkingSlot", std::bind(GetInTheParkingSlot));
    factory.registerSimpleAction("Park", std::bind(Park));
}
