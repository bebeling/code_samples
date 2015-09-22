#ifndef mylist_c
#define mylist_c

#include "list.h"
#include <stdexcept>    // for out_of_range exception
#include <algorithm>    // for swap function


/* Constructor
 * -----------
 */

template <typename Object>
mylist_arr<Object>::mylist_arr()
{
    array_s = INIT_S;
    list = new Object*[array_s];
    head = 0;      // list is empty so head and tail are both 0
    tail = 0;
    listsize = 0;  // start with an empty list
}


/* empty()
 * -------
 *  Arguments: none
 *  Returns: true if the list is empty, false otherwise
 */

template <typename Object>
bool mylist_arr<Object>::empty() const
{
    if (listsize == 0) {
        return true;
    }
    else {
        return false;
    }
}


/* size()
 * ------
 * Arguments: none
 * Returns: the number of elements in the list
 */

template <typename Object>
int mylist_arr<Object>::size() const
{
    return listsize;
}


/* clear()
 * -------
 * Arguments: none
 * Returns: none
 * Purpose: deletes all elements in the list, leaving an empty list
 */

template <typename Object>
void mylist_arr<Object>::clear()
{
    while (listsize > 0 ) {
        Object* temp = pop_back();  //let pop_back do the work for deletion
        delete temp;       //still have to delete the returned data item, though
    }
}


/* front()
 * -------
 * Arguments: none
 * Returns: a const pointer to the first element in the list
 * Throws: std::out_of_range when the list is empty
 * Purpose: use to peek at the first element without modifying it
 */

template <typename Object>
const Object* mylist_arr<Object>::front() const
{
    if (listsize == 0) {  // list is empty - nothing to return
        throw std::out_of_range("List is empty");
    }

    return list[head];
}


/* back()
 * ------
 * Arguments: none
 * Returns: a const pointer to the last element in the list
 * Throws: std::out_of_range when the list is empty
 * Purpose: use to peek at the last element without modifying it
 */

template <typename Object>
const Object* mylist_arr<Object>::back() const
{
    if (listsize == 0) {  // list is empty - nothing to return
        throw std::out_of_range("List is empty");
    }

    return list[tail];
}


/* push_front()
 * ------------
 * Arguments: the object to add to the list
 * Returns: none
 * Purpose: adds an element to the beginning of the list;
 *          the element is passed by value
 */

template <typename Object>
void mylist_arr<Object>::push_front(Object item)
{
    Object* heapitem = new Object;
    std::swap(*heapitem, item);  //swap item from parameter list onto the heap

    if (listsize == 0) {  // special case where the list is empty
        head = 0;  // head and tail both point to the same item
        tail = 0;
    }
    else if (listsize < array_s) {  // check if we have room for another element
        head = (head + array_s - 1) % array_s;
    }
    else {
        enlarge();
        head = (head + array_s - 1) % array_s;  
    }

    list[head] = heapitem;  // add the new element to the head of the list
    listsize++;
}


/* push_back()
 * ------------
 * Arguments: the object to add to the list
 * Returns: none
 * Purpose: adds an element to the end of the list;
 *          the element is passed by value
 */

template <typename Object>
void mylist_arr<Object>::push_back(Object item)
{
    Object* heapitem = new Object;
    std::swap(*heapitem, item);  // swap item from parameter list onto the heap

    if (listsize == 0) {  // special case where the list is empty
        head = 0; // head and tail both point to the same item
        tail = 0;
    }
    else if (listsize <  array_s) { // check if we have room for another element
        tail = (tail+1) % array_s;
    }
    else {
        enlarge();
        tail = (tail+1) % array_s;
    }

    list[tail] = heapitem;  // add the new item to the tail of the list
    listsize++;
}


/* pop_front()
 * -----------
 * Arguments: none
 * Returns: a pointer to the element removed from the beginning of the list
 * Throws: std::out_of_range when the list is empty
 * Purpose: remove the first element from the list
 */

template <typename Object>
Object* mylist_arr<Object>::pop_front()
{
    if (listsize == 0) {  // list is empty - nothing to return
        throw std::out_of_range("List is empty");
    }

    Object* temp = list[head];  // save a pointer to the data item
    list[head] = nullptr;
    head = (head+1) % array_s;
    listsize--;
    return temp;
}


/* pop_back()
 * -----------
 * Arguments: none
 * Returns: a pointer to the element removed from the end of the list
 * Throws: std::out_of_range when the list is empty
 * Purpose: remove the last element from the list
 */

template <typename Object>
Object* mylist_arr<Object>::pop_back()
{
    if (listsize == 0) {  // list is empty - nothing to return
        throw std::out_of_range("List is empty");
    }

    Object* temp = list[tail];  // save a pointer to the data item
    list[tail] = nullptr;
    tail = (tail + array_s - 1) % array_s;
    listsize--;
    return temp;
}


/* enlarge()
 * ---------
 * Arguments: none
 * Returns: none
 * Purpose: private utility method, called when the existing underlying array is 
 *          full, to increase the space allotted for the list;
 *          creates a new array of double the size of the existing array (to 
 *          achieve amortized O(1) time insertions) and copies each element 
 *          from the old array to the new; 
 */

template <typename Object>
void mylist_arr<Object>::enlarge()
{
    array_s *= 2;  //  double the size of old array
    Object** temp = new Object*[array_s];
    int current = head;  // start copying elements at head element
    int index = 0;

    // copy each element from the old array to the new
    while (current != tail) {
        temp[index] = list[current];
        index++;
        current = (current+1) % listsize;  //circular array - modular arithmetic
    }

    // while loop stops one short, so have to copy over the tail item
    temp[index] = list[current];

    head = 0;  // head is at index 0 of new array
    tail = index;  // tail is last item copied
    std::swap(temp, list);  // swap new array with old
    delete [] temp;  // delete old array
}

#endif

