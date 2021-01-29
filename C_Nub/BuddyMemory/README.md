The buddy memory allocation technique is a memory allocation algorithm that divides memory into partitions to try to satisfy 
a memory request as suitably as possible. This system makes use of splitting memory into halves to try to give a best fit.

Let's say in this system, the smallest possible block is 64 kilobytes in size, and the upper limit for the order is 4, 
which results in a largest possible allocatable block, 24 times 64 K = 1024 K in size. 

One version of the buddy allocation algorithm was described in detail by Donald Knuth in volume 1 of 'The Art of Computer Programming'.
