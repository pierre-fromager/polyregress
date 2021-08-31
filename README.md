# Polyregress

Polyregress is a portage from initial [python polyregress solver](https://arachnoid.com/polysolve/).  
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

It performs x20 faster than the intial script.

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