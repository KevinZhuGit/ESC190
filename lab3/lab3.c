#include "lab3.h"

char *convert_string(char *str)
{
    int size = strlen(str);

    char *temp = (char *)malloc(sizeof(char) * (size + 1));

    for (int i = 0; i < (size); i++)
    {
        temp[i] = str[i];
    }

    *(temp + size) = '\0';

    return temp;
}

// Add TA party item request to the list
int add_request(struct party_node **head, char *item, double price, char *ta)
{

    if (strcmp(item, "IDE") != 0) // do we look at other cases of IDE??
    {

        struct party_node *top;
        top = (struct party_node *)malloc(sizeof(struct party_node));

        top->item = convert_string(item); // malloc(len(item+1))), USE STRCPY
        top->price = price;
        top->ta = convert_string(ta); // = ta
        top->next = *head;

        *head = top;

        // free(top)???????, NOPE TOP IS JUST A POINTER TO ADDRESS OF STRUCT, WE STILL NEED STRUCT TO BE IN THE LIST
        return 0;
    }

    return -1;
}

// Remove the last item added
void remove_request(struct party_node **head)
{
    // change address in head to previous node
    // free the node

    if (*head == NULL)
    {
        return;
    }

    struct party_node *temp = *head;
    *head = (*head)->next;

    // free(temp->next); // does everything in temp get freed?
    free(temp->item);
    free(temp->ta);
    free(temp);
}

void swap(struct party_node *a, struct party_node *b)
{
    double temp_price = a->price;
    char *temp_item = a->item;
    char *temp_ta = a->ta;

    a->price = b->price;
    a->item = b->item;
    a->ta = b->ta;

    b->price = temp_price;
    b->item = temp_item;
    b->ta = temp_ta;
}

// Sort party item requests
void make_sorted(struct party_node **head)
{
    int swapped;                    // checks for last case, everything has swapped
    struct party_node *ptr;         // ptr to first node of list
    struct party_node *lptr = NULL; // sets up where to last check/swap

    // checks for empty list
    if (*head == NULL)
    {
        return;
    }

    // swapping function
    do
    {
        swapped = 0; // resets to false case
        ptr = *head;

        while (ptr->next != lptr) // checks if it has reached second last node
        {
            if (ptr->price < ptr->next->price) // pushing smallest price to the end
            {
                swap(ptr, ptr->next); // copies data over between node, node positions dont change
                swapped = 1;          // sets to true
            }

            ptr = ptr->next; // goes through list making sure smallest is at bac
        }

        lptr = ptr; // after finished, moves lptr forward
    } while (swapped);
}

// Trim list to fit the budget
double finalize_list(struct party_node **head, double budget)
{
    // is list already sorted before calling this function?
    double remaining = budget;
    struct party_node *curr = *head;
    struct party_node *prev = NULL;

    while (curr->next != NULL) // go until last one
    {
        if ((remaining - curr->price) > 0)
        {
            remaining = remaining - curr->price;
            prev = curr;
            curr = curr->next;
        }
        else if (curr == *head)
        {
            remove_request(head);
            curr = *head;
        }
        else //? use temp?
        {
            prev->next = curr->next;
            free(curr);
            curr = prev->next;
        }
    }

    if ((remaining - curr->price) > 0)
    {
        remaining = remaining - curr->price;
    }
    else if (curr == *head)
    {
        *head = NULL;
        free(curr);
    }
    else
    {
        prev->next = NULL;
        free(curr);
    }

    return remaining;
}

// Print the current list - hope this is helpful!
void print_list(struct party_node *head)
{
    int count = 1;
    printf("The current list contains:\n");
    while (head != NULL)
    {
        printf("Item %d: %s, %.2lf, requested by %s\n",
               count, head->item, head->price, head->ta);
        count++;
        head = head->next;
    }
    printf("\n\n");
    return;
}
