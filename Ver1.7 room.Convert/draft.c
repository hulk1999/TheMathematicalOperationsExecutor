#include <stdio.h>
#include <math.h>

int main(){
	int a = 0;
	int b = a + ++a + a + a + ++a;
	printf("%d", b);
	return 0;
}

// 1 4 7 11 16 22

// x + y + z = 7
// x + y - z = 1
// x - y - z = -3

// x = 2
// y = 2
// z = 3
