# Garbage_Collector

This library gives you the right to not **free() mallocs** and **close() fds** anymore.
To compile without debugging just type this command in the repository:
```
$ make lib
```
for debug mode:
```
$ make debug
```

Now in the repository you have access to access_mem.a library that you can include wherever you want ⚒️ !

### Here are all the lib macros that you can use:
- ```_AM_MALLOC(size)``` -> malloc and also protects the malloc if it fails causing to program to exit cleanly.
- ```_AM_FREE(alloc_to_free)``` -> frees an allocation (you use it instead of ```free()```).
- ```_AM_REGISTER_ALLOC(new_alloc)``` -> registers a malloc not coming from _AM_MALLOC to keep track of it with all other mallocs (ex: ```readline()```).
- ```_AM_OPEN(pathname, flags, ...)``` -> open function from top to bottom, no differences!
- ```_AM_CLOSE(fd_to_close)``` -> closes an fd (you use it instead of ```close()```).
- ```_AM_REGISTER_FD(new_fd)``` -> registers an open not coming from _AM_OPEN to keep track of it with all other opens (ex: ```socket()```).
- ```_AM_LOG_ALLOCS()``` -> logs all of your mallocs.
- ```_AM_LOG_FDS()``` -> logs all of your opens.
- ```_AM_NUKE_EXIT(opt_exit_code)``` -> nukes your environment freeing and closing everything and then exiting cleanly (you use this one in case of fails or at the end of your program to end it cleanly).
- ```_AM_NUKE_NO_EXIT()``` -> nukes your environment without exiting.

⚠️ Only use the macros, no other functions ⚠️

Have fun with C Language GOD MODE ! 🔥

