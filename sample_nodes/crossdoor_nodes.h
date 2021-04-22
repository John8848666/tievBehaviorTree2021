#pragma once

#include "behaviortree_cpp_v3/bt_factory.h"

using namespace BT;

namespace CrossDoor
{
inline void SleepMS(int ms)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

BT::NodeStatus FindParkingSlot();

BT::NodeStatus ChangeToAnotherRoad();

BT::NodeStatus AreThereAvailableParkingSlots();

BT::NodeStatus GetInTheParkingSlot();

BT::NodeStatus Park();

void RegisterNodes(BT::BehaviorTreeFactory& factory);
}
