# Observer pattern
The observer pattern allows for a fan type of effect where there is one
so called "Subject" that allowes many observers to register with itself
and can then notify them of certain updates when appropriate. This updating
can also be called "broadcasting", since all registered objects are notified.

## Example
In the example, one LogAggregator can send logs to multiple Loggers, which are
first registered with the aggregator. Every time a log is send to the aggregator
they are also send to all registered loggers.
