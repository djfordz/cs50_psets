#include <stdio.h>

int main(void)
{
	// declare arrays.
	int len1 = 10, len2 = 20;
	int array1[len1], array2[len2];

	int i, j;

	//populate array1 and array2.
	for(i = 0; i < len1; i++) {
		array2[i] = i;
		array1[i] = i;
	}

	// append array1 to array2.
	for(i = len1, j = 0; i < len2; i++, j++)
		array2[i] = array1[j];

	//print array2.
	for(i = 0; i < 20; i++)
		printf("array2[%d] = %d\n", i, array2[i]);

	//print newline.
	printf("\n");
}