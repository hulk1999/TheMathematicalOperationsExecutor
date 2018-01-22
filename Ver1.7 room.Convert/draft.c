#include <stdio.h>

int main(){
	char ch = getch();
	printf("%u\n", ch);
	ch = getch();
	printf("%u", ch);
	return 0;
}
