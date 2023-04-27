# listPractice

A reasonably simple templated linked list class written in C++, which utilises some slightly unusual but cool methods of optimisation to achieve incredibly fast sequential operations on the list.

The optimisation being used to greatly speed up sequential operations is a method in which the last node accessed is saved in a "cache" variable.

```
/*
    The cached node is used to improve the speed of sequential iterations through the list (but does also improve the speed of random selection from list),
    this is done by figuring out if the last node accessed by getNode() is closer to the current target node than either the head or tail node.

    This allows for speedy sequential access to the list without the end user of this class having to worry about using an iterator
*/
cachedNode<T> cached;
```

# Functions

* append (+ push_front)
* prepend (+ push_back)
* insert
* pop_front
* pop_back
* get
* getPointer (to allow for modifying a value in the list)
* remove
* len
