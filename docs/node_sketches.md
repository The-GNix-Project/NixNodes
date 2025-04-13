# Nodes Sketches
These are some **Very** preliminary sketches to get an idea of the direction of this programming language

## Function Sketches
<img src="assets/functions_sketch_3.png" height=250px><br>
compiles to:
```nix
{ myInput, anotherInput }:
let myInt = 2;
in {
    myNum = myInput + anotherInput + myInt;
    myString = "Hello World!";
    myPath = ./nixos;
}
```
<img src="assets/functions_sketch_2.png" height=250px><br>
compiles to:
```nix
myInput:
let myInt = 2;
in {
    myNum = myInput + myInt;
    myString = "Hello World!";
    myPath = ./nixos;
}
```
<img src="assets/functions_sketch_1.png" height=250px><br>
compiles to:
```nix
myInput:
let myInt = 2;
in {
    myNum = myInput + myInt;
    myString = "Hello World!";
    myPath = ./nixos;
}
```

## Datatype Sketches
<img src="assets/basic_types_sketch.png" height=250px><br>
compiles to:
```nix
anotherPath = ./nixos;
anotherAttrSet = {
  myNum = 52;
  myString = "Hello World!";
  myList = [
    "Hello World!"
    52
  ];
};
myAttrSet = {
  myNum = 52;
  myString = "Hello World!";
  myPath = anotherPath;
  myList = anotherAttrSet.myList
};
```