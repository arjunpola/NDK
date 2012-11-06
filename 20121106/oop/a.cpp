
// a.c

#include <stdio.h>

class stack
{
	private:
		int buff[10];
		int idx;
	public:
		void init() { idx = 0; }
		void push(int a) { buff[idx++] = a; }
		int pop() { return buff[--idx]; }
}; 


int main()
{
	stack s;
	s.init();

	s.push(1);
	s.push(2);
	s.push(3);
	s.push(4);

	printf("%d \n", s.pop());
	printf("%d \n", s.pop());
	printf("%d \n", s.pop());
	printf("%d \n", s.pop());
}
