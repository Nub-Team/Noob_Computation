# Vector Operations
<h3>Created by : Dani Johanes</h3><br>

To understand vector operation on the GPU, we will start by writing a vector addition program on the CPU and then modify it to utilize the parallel structure of GPU. OpenCL is very "generic" in the sense that it supports many different vector type/size combos, but real-world hardware usually only implements some vector type/size combinations. You can query OpenCL devices for "preferred vector size" which should tell you what's the most efficient for that hardware.
