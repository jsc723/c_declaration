# c_declaration
A parser that translate a subset of c declaration into English
compile:
  `gcc cdec.c -o cdec.exe`
run:
  `.\cdec.exe <c_declaration>`
example:
  `.\cdec.exe "int \t(*(*vtable)[])(int **, int (*)[])"`
  
