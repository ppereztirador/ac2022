#include <stdio.h>
#include <string.h>
#include "common.h"

int main() {
	char stack1[] = "abcdefghij\0";
	char stack2[] = "123\0      ";
	char** temp = allocStringArray(1);

	printf("Start\n%s\n%s\n%s\n\n", stack1, stack2, temp[0]);

	popChar(stack1, 4, temp[0]);
	printf("Pop\n%s\n%s\n%s\n\n", stack1, stack2, temp[0]);

	pushChar(stack2, temp[0]);
	printf("Push\n%s\n%s\n%s\n\n", stack1, stack2, temp[0]);

	freeStringArray(temp, 1);
	return 0;
}
