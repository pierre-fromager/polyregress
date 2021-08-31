# Polyregress

Polyregress is a c99 portage from initial [python polyregress solver](https://arachnoid.com/polysolve/).  
It provides polynomial equation from a cloud of points.  
Higher is the polynomial degree, higher is the accuracy for data fitting.  
Keep in mind one degree of polynome represents one inflexion.  

## Build

to build simply make

``` 
make
```

## Doc

to build doc

``` 
make doc
```

Then doc will be generated in the doc/html folder.

## Usage

The first number of the serie is the higher degree.  
The following numbers are XY points and should be paired.  
Degree can't be higner than the number of XY points.  

``` 
echo "4 1 0 2 2 3 1 4 4 5 2" | ./polyregress -
```

## Performance

It can perform from x3 upto x20 faster than the initial script, depending on **gcc** flags.  
Default setup is designed for x20.

``` 
time echo "4 1 0 2 2 3 1 4 4 5 2" | ./polyregress -
```

Removing the **#** line 13 in Makefile, will enforce security adding sanitizers but downperf to x3.  

Read [Security-related flags and options for C compilers](https://airbus-seclab.github.io/c-compiler-security/) to know more.

## Accuracy

Here we are dealing with double type.  
You can change the solution accuracy from the solution.h file.  

``` 
#define SOL_ACCURACY_FMT "16"
``` 

## Limitations

Input buffer is limited to 2048 bytes but you can change it in main.

## Tests

Wip.

## Todo

* Unit tests.
* Improve arguments flags.
* Populate data from file format (csv,..).

## Links

* [c++ polyreg](https://gogs.pier-infor.fr/pf.pier-infor.fr/polyreg) to reuse result and play with the gnuplot renderer.
* [Array Pointer](https://www.geeksforgeeks.org/pointer-array-array-pointer/) to understand how to use a 2D matrix with a 1D array and pointers.
* [Matrices and Linear Algebra](http://www.mymathlib.com/matrices/) to find most common practices on matrices.