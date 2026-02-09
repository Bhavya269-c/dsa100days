#include <stdio.h>
#include <string.h>

int main()
{
    char str[100];
    int start, end;
    char temp;

    // Input string
    printf("Enter code name: ");
    scanf("%s", str);

    // Find length
    end = strlen(str) - 1;
    start = 0;

    // Reverse string
    while (start < end)
    {
        temp = str[start];
        str[start] = str[end];
        str[end] = temp;

        start++;
        end--;
    }

    // Output reversed string
    printf("Transformed code name: %s", str);

    return 0;
}