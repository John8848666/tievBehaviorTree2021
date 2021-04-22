# tievBehaviorTree2021
Self-driving project based on behavior tree in TiEV
# What is Behavior Tree
[Behavior tree](https://en.wikipedia.org/wiki/Behavior_tree) is a formal, graphical modelling language used primarily in systems and software engineering. We are trying to use behavior tree as the decision system of autonomous driving. This repository is inspired by [BehaviorTree.cpp](https://github.com/BehaviorTree/BehaviorTree.CPP) and can be visualized by [Groot, which is officially recommended GUI](https://github.com/BehaviorTree/Groot).
# How to run this repo
 1  Prepare a ubuntu environment
 
 2  Clone this repo
 
 3  Install dependency with:

     sudo apt-get install libzmq3-dev libboost-dev
     
And other dependencies are already in 3rdparty

 4  Compile the BehaviorTree Library with(you can refer to [BehaviorTree.cpp](https://github.com/BehaviorTree/BehaviorTree.CPP) )
 
     mkdir build; cd build
     cmake ..
     make
     sudo make install
     
  5  Install [Groot](https://github.com/BehaviorTree/Groot)
  
  6   Compile source codes in ./example, and run them in the CLI. Use the MONITOR in Groot when run the demo, and you can see the visualization of how behavior tree works.
  
  
  # demo src
  ```
  #include "crossdoor_nodes.h"

#include "behaviortree_cpp_v3/loggers/bt_cout_logger.h"
#include "behaviortree_cpp_v3/loggers/bt_minitrace_logger.h"
#include "behaviortree_cpp_v3/loggers/bt_file_logger.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#ifdef ZMQ_FOUND
#include "behaviortree_cpp_v3/loggers/bt_zmq_publisher.h"
#endif

/** This is a more complex example that uses Fallback,
 * Decorators and Subtrees
 *
 * For the sake of simplicity, we aren't focusing on ports remapping to the time being.
 *
 * Furthermore, we introduce Loggers, which are a mechanism to
 * trace the state transitions in the tree for debugging purposes.
 */


// clang-format off

static const char* xml_text = R"(
<root main_tree_to_execute="BehaviorTree">
    <!-- ////////// -->
    <BehaviorTree ID="BehaviorTree">
        <ReactiveSequence>
            <Fallback>
                <Action ID="FindParkingSlot"/>
                <Inverter>
                    <Action ID="ChangeToAnotherRoad"/>
                </Inverter>
            </Fallback>
            <Sequence>
                <Fallback>
                    <Condition ID="AreThereAvailableParkingSlots"/>
                    <Inverter>
                        <Action ID="ChangeToAnotherRoad"/>
                    </Inverter>
                </Fallback>
                <Action ID="GetInTheParkingSlot"/>
                <Action ID="Park"/>
            </Sequence>
        </ReactiveSequence>
    </BehaviorTree>
    <!-- ////////// -->
    <TreeNodesModel>
        <Condition ID="AreThereAvailableParkingSlots"/>
        <Action ID="ChangeToAnotherRoad"/>
        <Action ID="FindParkingSlot"/>
        <Action ID="GetInTheParkingSlot"/>
        <Action ID="Park"/>
    </TreeNodesModel>
    <!-- ////////// -->
</root>
 )";

// <root main_tree_to_execute = "MainTree">
// 	<!--------------------------------------->
//     <BehaviorTree ID="DoorClosed">
//         <Sequence name="door_closed_sequence">
//             <Inverter>
//                 <Condition ID="IsDoorOpen"/>
//             </Inverter>
//             <RetryUntilSuccesful num_attempts="4">
//                 <OpenDoor/>
//             </RetryUntilSuccesful>
//             <PassThroughDoor/>
//         </Sequence>
//     </BehaviorTree>
//     <!--------------------------------------->
//     <BehaviorTree ID="MainTree">
//         <Sequence>
//             <Fallback name="root_Fallback">
//                 <Sequence name="door_open_sequence">
//                     <IsDoorOpen/>
//                     <PassThroughDoor/>
//                 </Sequence>
//                 <SubTree ID="DoorClosed"/>
//                 <PassThroughWindow/>
//             </Fallback>
//             <CloseDoor/>
//         </Sequence>
//     </BehaviorTree>
//     <!---------------------------------------> 
// </root>

// clang-format on

using namespace BT;

int main(int argc, char** argv)
{
    BT::BehaviorTreeFactory factory;

    // register all the actions into the factory
    CrossDoor::RegisterNodes(factory);

    // Important: when the object tree goes out of scope, all the TreeNodes are destroyed
    auto tree = factory.createTreeFromText(xml_text);

    // This logger prints state changes on console
    StdCoutLogger logger_cout(tree);

    // This logger saves state changes on file
    FileLogger logger_file(tree, "bt_trace.fbl");

    // This logger stores the execution time of each node
    MinitraceLogger logger_minitrace(tree, "bt_trace.json");

#ifdef ZMQ_FOUND
    // This logger publish status changes using ZeroMQ. Used by Groot
    PublisherZMQ publisher_zmq(tree);
#endif

    printTreeRecursively(tree.rootNode());

    const bool LOOP = ( argc == 2 && strcmp( argv[1], "loop") == 0);

    do
    {
        NodeStatus status = NodeStatus::RUNNING;
        // Keep on ticking until you get either a SUCCESS or FAILURE state
        while( status == NodeStatus::RUNNING || status == NodeStatus::FAILURE)
        {
            status = tree.tickRoot();
            CrossDoor::SleepMS(1);   // optional sleep to avoid "busy loops"
        }
        CrossDoor::SleepMS(1000);
    }
    while(LOOP);

    return 0;
}

  ```
  
