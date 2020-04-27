# c_declaration
Parse a subset of c declaration defined by the follwing language into English. 
```
    S   -> int E
    E   -> (E)
        -> E(S,...)
        -> E[N]
        -> *E
        -> literal
    N   -> [0-9]*
```
## Compile:
```
gcc cdec.c -o cdec.exe
```


## Run:
```
.\cdec.exe <c_declaration>
```

## Example:
```
.\cdec.exe "int (*(*vtable)[])(int **, int (*)[12])"
input: int (*(*vtable)[])(int **, int (*)[12])
vtable is a pointer to an array of a pointer to a function taking (a pointer to a pointer to int, a pointer to an array of 12 int) and returning int
```

  
