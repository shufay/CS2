Some threads might finish tracing all rays assigned to it and remain idle 
while others are taxed with tracing the computationally demanding rays.
An approach similar to the producer-consumer queue would assign a ray 
to a thread whenever it finishes tracing one so it never goes idle. Thus
the workload would be distributed across the threads more equally.  
