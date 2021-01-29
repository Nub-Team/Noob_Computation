// Author : Nub-T

using System; 
using System.Collections.Generic;

namespace Stack{
        public class main{
            static void Main(){
                Stack<int> stack = new Stack<int>();
                stack.Push(1);
                stack.Push(2);
		stack.Push(3);
		stack.Push(4);
		stack.Push(5);
		stack.Push(6);
		stack.Push(7);
                Console.WriteLine(stack.Top());
                stack.Pop(); //7 would be popped out
                Console.WriteLine(stack.Top());
                
            }
        }
}
