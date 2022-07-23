#include <stdio.h>

int main()
{
    // review insertion, selection, bubble sort, for best case and worst case

    /* INSERTION SORT
    takes next item and inserts in sorted part left of it
    has 1 + 2 + ... n comparisons at worst case
    complexity is n^2
    best case is n? */

    /* SELECTION SORT
    finds the smallest item in list (select) and puts to the front
        repeats for rest of list, selecting smallest and adding to beginning
    has n + (n-1) + ... 1 comaprisons at worst case
    complextity is n^2 */

    /*BUBBLE SORT*/

    /* MERGE SORT
    splits list in half recursively, creates a tree with log(2) n  levels
    merging part assumes two sorted lists: uses 2 pointers, compares, appends, moves pointer
    worst case is n comparisons at each level
        can have less if one list is smaller than the other
    overall worst case is nlogn */

    /* QUICK SORT
    sets a pivot position, moves smaller items left of pivot and keeps greater on right
        repeats with new pivot as leftmost of subpartition
    has n + (n-1) + ... 1 comparisons at worst case
    complexity is n^2
    best case is nlogn, pivot in always median */

    // O(n) is best case for comparisons, need n comparisons to check
    // O(nlogn) best worst case for comparisons

    return 0;
}