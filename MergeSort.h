#include "Contact.h"
#include <stdbool.h>

/* function prototypes */
void MergeSort(struct Contact_Node** headRef, char compare_by);
struct Contact_Node* SortedMerge(struct Contact_Node* a, struct Contact_Node* b, bool (*cmp_func)(struct Contact* a, struct Contact* b));
void FrontBackSplit(struct Contact_Node* source,
    struct Contact_Node** frontRef, struct Contact_Node** backRef);
void printList(struct Contact_Node* node);
bool compare_by_fname(struct Contact* a, struct Contact* b);
bool compare_by_lname(struct Contact* a, struct Contact* b);
bool compare_by_phone(struct Contact* a, struct Contact* b);
bool compare_by_cphone(struct Contact* a, struct Contact* b);


/* sorts the linked list by changing next pointers (not data) */
void MergeSort(struct Contact_Node** headRef, char compare_by)
{
    struct Contact_Node* head = *headRef;
    struct Contact_Node* a;
    struct Contact_Node* b;

    /* Base case -- length 0 or 1 */
    if ((head == NULL) || (head->next == NULL)) {
        return;
    }

    /* Split head into 'a' and 'b' sublists */
    FrontBackSplit(head, &a, &b);

    /* Recursively sort the sublists */
    MergeSort(&a, compare_by);
    MergeSort(&b, compare_by);

    /* answer = merge the two sorted lists together */
    switch (compare_by)
    {
    case '1': *headRef = SortedMerge(a, b, compare_by_fname);
        break;
    case '2': *headRef = SortedMerge(a, b, compare_by_lname);
        break;
    case '3': *headRef = SortedMerge(a, b, compare_by_phone);
        break;
    case '4': *headRef = SortedMerge(a, b, compare_by_cphone);
        break;
    }
}

struct Contact_Node* SortedMerge(struct Contact_Node* a, struct Contact_Node* b, bool (*cmp_func)(struct Contact* a, struct Contact* b))
{
    struct Contact_Node* result = NULL;

    /* Base cases */
    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);

    /* Pick either a or b, and recur */
    if (cmp_func(a->data, b->data)) {
        result = a;
        result->next = SortedMerge(a->next, b, cmp_func);
    }
    else {
        result = b;
        result->next = SortedMerge(a, b->next, cmp_func);
    }
    return (result);
}

/* UTILITY FUNCTIONS */
/* Split the nodes of the given list into front and back halves,
    and return the two lists using the reference parameters.
    If the length is odd, the extra node should go in the front list.
    Uses the fast/slow pointer strategy. */
void FrontBackSplit(struct Contact_Node* source,
    struct Contact_Node** frontRef, struct Contact_Node** backRef)
{
    struct Contact_Node* fast;
    struct Contact_Node* slow;
    slow = source;
    fast = source->next;

    /* Advance 'fast' two nodes, and advance 'slow' one node */
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    /* 'slow' is before the midpoint in the list, so split it in two
    at that point. */
    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
}

/* Function to print nodes in a given linked list */
void printList(struct Contact_Node* node)
{
    while (node != NULL) {
        printf("%s\n ", node->data->fname);
        node = node->next;
    }
}

bool compare_by_fname(struct Contact* a, struct Contact* b)
{
    return strcmp(a->fname, b->fname) > 0;
}
bool compare_by_lname(struct Contact* a, struct Contact* b)
{
    return strcmp(a->fname, b->fname) > 0;
}
bool compare_by_phone(struct Contact* a, struct Contact* b)
{
    return strcmp(a->fname, b->fname) > 0;
}
bool compare_by_cphone(struct Contact* a, struct Contact* b)
{
    return strcmp(a->fname, b->fname) > 0;
}