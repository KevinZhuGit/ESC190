#include <stdio.h>
#include <stdlib.h>

struct ListNode
{
    int cargo;
    struct ListNode *next; // allocates space for a pointer, know how much memory is being allocated
};
ListNode;

void print_ll(ListNode *head)
{
    ListNode *curr = head;
    while (curr != NULL)
    {
        printf("%d" curr->cargo); // -> = (*curr).cargo
        curr = curr->next;
    }
}

ListNode *create_ll(int *arr, int n)
{
}

int main()
{
    // LINKED LIST
    // points to head of the list, each node contains value and address of next node
    // indexingtakes O(i) for accessing value at index i, have to go through everything before
    // can be fixed by keeping pointer to tail of the list
    // inserting/deleting takes O(i)

    // Array
    // indexing takes O(1), insert/delete are O(n-i)
    // however, can be O(n) because of realloc() if there is not enough space

    //

    ListNode;

    return 0;
}