# stateMachine

The goal of this repository is to save material for teaching how to implement a state machine (Arduino/C++ language). A simple calculator application is used as an example. The application can calculate simple equations given from Arduino serial monitor (like 12+5) and responds to serial monitor (like result=17). A finite state machine runs when there are events. In this application events are characters read from Arduino serial monitor (like NUMBER_GIVEN, NUMBER_GIVEN, OPERAND_GIVEN, NUMBER_GIVEN and NOT_A_NUMBER_GIVEN for simple 12+5 input).

There are at least 5 different ways to implementent finite state machine [1]. This repository implements 3 of those (sequential code, multiple switch-case and a table based method). A student is supposed to study all given 3 solutions to simple calculator application. And after that he/she should be able to add functionality which makes the calculator capable of calcating with rational numbers. I.e. equations like (12,3+5,1) would be valid.

Before starting to code you should first watch following youtube-videos:

1. Some background on FSMs and task definition, https://youtu.be/Hqu0n7in1Z8
2. Explaining the basic structure of my code, https://youtu.be/EWBk0fbOFTE 
3. A simple way of reading desimal part, https://youtu.be/8GFJF-fmMqs 

[1] Rob Williams, 2006, Real-Time System Develoment. 
