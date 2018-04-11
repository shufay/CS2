1. 
The philosophers pick up an available left fork then pick up an available 
right fork, eat, then set down the right fork before setting down the left 
fork. This is bound to cause a deadlock since we will run into the case 
where all philosophers have picked up a left fork and are stuck in a waiting 
process.

2. 
Since there are 5 forks, to prevent a deadlock, a maximum of 4 
philosophers can sit at the table at any one time. When all 
philosophers pick up a left fork, there will always be a right fork
available for one philosopher to eat.

3.
If the solution began from a state where all philosophers begin with
dirty, left forks, each would send a request to their right neighbour 
and recieve a request from their left neighbour asking for a fork. Since 
the forks are all dirty, they would all clean their forks and send it to 
their left neighbours. Now they all have clean forks and are unable to 
fulfill any requests while waiting for another fork. Hence they are in 
deadlock.  

