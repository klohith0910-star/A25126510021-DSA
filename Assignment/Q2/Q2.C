#include <stdio.h>

int main() {
    int n, key, j, c = 0;

    printf("Enter number of students: ");
    scanf("%d", &n);

    int a[n];

    printf("Enter student marks:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    for (int i = 1; i < n; i++) {
        key = a[i];
        j = i - 1;

        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            c++;
            j--;
        }

        a[j + 1] = key;

        printf("Pass %d: ", i);
        for (int k = 0; k < n; k++)
            printf("%d ", a[k]);

        printf("\n");
    }

    printf("Final sorted marks: ");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\nTotal element shifts: %d\n", c);

    return 0;
}
