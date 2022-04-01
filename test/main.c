#include <stdio.h>

int main() {
	int i = 0;
	int k = 0;
	while (i < 6400) {
		printf("%d\n", k);
		i*=10; k++;
	}

	return 0;
}