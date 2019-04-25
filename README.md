# stateMachine

Under construction....

The goal of this repository is to save material for teaching how to implement a state machine (Arduino/C++ language). A simple calculator application is used as an example. The application can calculate simple equations given from Arduino serial monitor (like 12+5) and responds to serial monitor (like result=17). A finite state machine runs when there are events. In this application events are characters read from Arduino serial monitor (like NUMBER_GIVEN, NUMBER_GIVEN, OPERAND_GIVEN, NUMBER_GIVEN and NOT_A_NUMBER_GIVEN for simple 12+5 input).

The calculator example is implemented with 3 diffent ways according to [1]

[1] Rob Williams, Real-Time System Develoment 
