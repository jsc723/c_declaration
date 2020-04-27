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
<div>
  <h2>Compile:</h2>
  <code>
    gcc cdec.c -o cdec.exe
  </code>
</div>
<div>
  <h2>Run:</h2>
  <code>
    .\cdec.exe &lt;c_declaration&gt;
  </code>
</div>
<div>
  <h2>Example:</h2>
  <code>
    .\cdec.exe "int (*(*vtable)[])(int **, int (*)[12])"
  </code>
</div>

  
