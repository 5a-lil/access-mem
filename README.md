# ACCESS_MEM

This library gives you the right to not free() mallocs and close() fds anymore.
To compile just type this command in the repository:
```
$ make lib
```

Now in the repository you have access to access_mem.a library that you can include wherever you want ⚒️ !

### Here are some lib functions:
- ```void *access_mem_ALLOC(size_t size)``` -> this function replaces malloc and also protects the malloc if it fails causing to program to exit cleanly.
- ```int access_mem_OPEN(const char *pathname, int flags, ...)``` -> this function replaces open function from top to bottom, no differences !
- ```void access_mem_NUKE()``` -> this function nukes your environment freeing and closing everything and then exiting cleanly (you use this one in case of fails or at the end of your program to end it cleanly).

Have fun with C Language GOD MODE 🔥 !