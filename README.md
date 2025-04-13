# NixNodes
Node based configuration editor for Nix<br>
<img src="docs/assets/functions_sketch_3.png" style="height:200;float:left">  Compiles to: 
```nix 
myInput:
let myInt = 2;
in {
    myNum = myInput + myInt;
    myString = "Hello World!";
    myPath = ./nixos;
}
```