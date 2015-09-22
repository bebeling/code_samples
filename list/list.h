#ifndef mylist_h
#define mylist_h

template <typename Object>
class mylist_arr {
    public:
        explicit mylist_arr();        // constructor
        bool empty() const;           // returns true if list is empty
        int size() const;             // returns number of elements in list
        void clear();                 // deletes all the elements of the list
        const Object* front() const;  // returns element at front of list
        const Object* back() const;   // returns last element in list
        void push_front(Object);      // adds element to beginning of list
        void push_back(Object);       // adds node to end of list
        Object* pop_front();          // returns node at beginning of list and  
                                      // removes it from list
        Object* pop_back();           // returns node at end of list and removes
                                      // it from list

    private:
        void enlarge();               // increases size of underlying array
        Object** list;                // pointer to underlying array
        static const int INIT_S = 5;  //starting size of array
        int array_s;                  // size of array
        int listsize;                 // number of elements in list
        int head;                     // index of first element
        int tail;                     // index of last element
};

#endif

