
#include <stdio.h>

int add(int,int);
int sub(int, int);
int getsum(int);

int main()
{
	printf("%d + %d = %d\n", 4, 3, add(4,3));
	printf("%d - %d = %d\n", 4, 3, sub(4,3));
	printf("sum 1 to %d = %d\n",100, getsum(100));
	return 0;
}
