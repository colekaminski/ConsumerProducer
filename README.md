# ConsumerProducer

Operating Systems Fall 2023
Cole Kaminski
11/7/2023


//PURPOSE

The purpose of this project is to replicate a common consumer and producer problem.
The program solves the issue listed below:

"The producer generates items and puts items onto the table. The consumer will pick up items.
The table can only hold two items at the same time. When the table is complete, the producer
will wait. When there are no items, the consumer will wait. We use semaphores to synchronize
producer and consumer.  Mutual exclusion should be considered. We use threads in the 
producer program and consumer program. Shared memory is used for the “table”."

This is achieved by taking use of semaphores to synchronize the producer and consumer actions.

//USAGE

In order to run the code, consider using the below commands:

g++ -o consumerProducer consumerProducer.cpp -pthread
./consumerProducer

