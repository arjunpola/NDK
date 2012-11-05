
#include <stdio.h>

int add(int,int);
int sub(int, int);

int main()
{
	printf("%d + %d = %d\n", 4, 3, add(4,3));
	printf("%d - %d = %d\n", 4, 3, sub(4,3));
	return 0;
}
