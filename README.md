# nrr_enumerate
Python-like 'enumerate' for C++

Python and some other languages have a handy built-in function called [`enumerate()`](https://docs.python.org/3/library/functions.html?highlight=enumerate#enumerate), which lets you iterate over an object (e.g. a list) and have access to both the index and the item in each iteration. This header gives a C++17/20 implementation of the same idea. Use it like:

```cpp
std::vector<Thing> things;
...
for (auto [i, thing] : enumerate(things))
{
    // i gets the index and thing gets the Thing in each iteration
}
```

Iterating over `things` itself would give you `thing`, but not `i`, and there are plenty of situations where you want both. See the [accompanying blog post](http://reedbeta.com/blog/python-like-enumerate-in-cpp17/) for more info.

There's also a const version, `cenumerate()`, which iterates the given object as const. (Sadly, using `const auto [i, thing]` doesn't actually do the job, because of reasons.)
