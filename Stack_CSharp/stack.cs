// AUTHOR : Nub-T

using System; 
using System.Collections.Generic;
 
namespace Stack{
   public class Stack<t>{
        private List<t> _array;     
        private int _size;       
        private int _top;
        static List<t> _emptyArray = new List<t>(); 
        public Stack(){
            _array = _emptyArray;
            _size = 0; 
            _top = -1;
        }
        public void Push(t data){
            _array.Add(data);
            _size++;
            _top++;
        }
        public void Pop(){
            _array.RemoveAt(_top--);
        }
        public t Top(){
            return _array[_top];
        }
    }
}