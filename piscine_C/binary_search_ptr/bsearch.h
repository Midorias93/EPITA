#ifndef BSEARCH_H_
#define BSEARCH_H_

/*
** Search `elt` in the memory range of [`begin` - `end`[.
** `begin` is a pointer to the first element.
** `end` is a pointer **AFTER** the last element.
** The elements in the range [`begin` - `end`[ are sorted in ascending order.
** If the range is empty, `begin` == `end`.
** `begin` and `end` can't be `NULL`.
** Returns a pointer to the element if found, or a pointer to the memory
** location where the element could be inserted to keep the array sorted.
*/
int *binary_search(int *begin, int *end, int elt);

#endif /* !BSEARCH_H_ */
