#include <stdio.h>
#include <stdlib.h>
void input(int* data, int count, int* flag);
void output(int* data, int count);
void sort(int* data, int n);
int main() {
	int n;
	int flag = 0;
	char c;
	scanf("%d%c", &n, &c);
	if (c != '\n') flag = 1;
	if (flag != 0) {
		printf("n/a");
	}
	else {
		int* data = (int*)malloc(n * sizeof(int));
		input(data, n, &flag);
		if (flag != 0) {
			printf("n/a");

		}
		else {
			sort(data, n);
			output(data, n);
		}
		free(data);
	}

	return 0;
}

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void sort(int* data, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {
			if (data[j] < data[i]) {
				swap(&data[j], &data[i]);
			}
		}
	}
}

void input(int* data, int count, int* flag) {
	char c;
	for (int i = 0; i < count; i++) {
		if (scanf("%d", data + i) != 1) *flag = 1;
	}
	scanf("%c", &c);
	if (c != '\n') *flag = 1;
}

void output(int* data, int count) {
	for (int i = 0; i < count - 1; i++) {
		printf("%d ", *(data + i));
	} 
	printf("%d", data[count - 1]);
}
