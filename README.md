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

  ```
  
