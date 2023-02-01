# Buffering-with-Memory
The goal of this program is to receive a value and process it correctly according to 6 predetermined operation IDs. First, the main.c program calls the buffer.c file to get a value from the io.c file and read it into an input buffer. The input buffer uses the "malloc" function to borrow only as much memory as it needs. Next, the value is transferred into a local buffer, which also allocates memory, and the input buffer's memory is freed. The local buffer's contents are then ssessed depending on the value of its first element: 
  
0 - MIN: the minimum value in the buffer is found.  
1 - MAX: the maximum value in the buffer is found.  
2 - ODD: the number of odd values in the buffer is found.  
3 - EVEN: the number of even values in the buffer is found.  
4 - MINMAX: the minimum and maximum values in the buffer are found.  
5 - ODDEVEN: the number of odd and even values in the buffer is found.  

The local buffer is then replaced by four elements: the ID, the number of results, the first result, and the second result (in that order). These results are transferred to the output buffer, which is allocated memory. After the local buffer's memory is released, the output buffer is then checked by the io.c file. The output buffer's memory is then freed, and the process begins again with a new value.
