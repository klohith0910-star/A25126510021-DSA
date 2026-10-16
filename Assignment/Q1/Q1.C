#include <stdio.h>

int main() {
    int n, key, low, high, mid, c = 0, found = 0;

    printf("Enter number of employees: ");
    scanf("%d", &n);

    int a[n];

    printf("Enter employee IDs in ascending order:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("Enter ID to search: ");
    scanf("%d", &key);

    low = 0;
    high = n - 1;

    while (low <= high) {
        c++;
        mid = low + (high - low) / 2;

        if (a[mid] == key) {
            printf("Employee ID found at position: %d\n", mid + 1);
            found = 1;
            break;
        } else if (a[mid] < key) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    if (!found)
        printf("Employee ID %d is absent from the records.\n", key);

    printf("Total comparisons: %d\n", c);

    return 0;
}
