# HSharp
## Copyright (c) 2023 HusseinSharp(H#)
The H# Programming language

### usage of imports
#### fileone.hslib
```
Library{
Var PI = 3.14;
}; 
```
#### test.hussein
```
Import "fileone.hslib"
Void Main(){
Var radius = 30;
Var areal = (radius*radius)*PI;
Call areal;
Call radius;
};
```

### if statements
```
Void Main(){

Var s = 20;
Var d = 40;
Var svar ="";
    if(s<d){
    svar ="s er mindre";
    }
    else{
    svar ="d er mindre";
    };
Call svar;
};
```
