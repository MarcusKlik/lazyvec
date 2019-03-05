
<!-- README.md is generated from README.Rmd. Please edit that file -->

<!-- <img src="logo.png" align="right" /> -->

[![Linux/OSX Build
Status](https://travis-ci.org/fstpackage/lazyvec.svg?branch=master)](https://travis-ci.org/fstpackage/lazyvec)
[![WIndows Build
status](https://ci.appveyor.com/api/projects/status/bfm7amtkyjvc2rk9?svg=true)](https://ci.appveyor.com/project/fstpackage/lazyvec)
[![License: AGPL
v3](https://img.shields.io/badge/License-AGPL%20v3-blue.svg)](https://www.gnu.org/licenses/agpl-3.0)

> This repository is home to the `lazyvec` package. `lazyvec` depends
> heavily on the ALTREP framework that will be rolled out with `R` 3.6.
> Therefore, at the moment, it can only be compiled from source when you
> are running the latest `dev` version of `R`. After the `R` 3.6
> release, `lazyvec` will be submitted to CRAN and more readily
> available to the user.

## Overview

The [*lazyvec* package](https://github.com/fstpackage/lazyvec) for `R`
provides an easy way to create custom `ALTREP` vectors without the need
to write any `C/C++` code. The package provides the necessary ALTREP
method overrides that are normally implemented in `C/C++` and allows the
user to write their much simpler `R` equivalents.

In addition to providing the tools to generate custom ALTREP’s,
`lazyvec` provides a diagnostic framework to observe the internal calls
made to existing or custom ALTREP vectors.

## Installation

You can install the package directly from GitHub:

``` r
# install.packages("devtools")
devtools::install_github("fstpackage/lazyvec")
```

## Basic usage

To observe the internal behaviour of ALTREP ranges, the object can be
wrapped:

``` r
library(lazyvec)

x <- 1:10  # a range

# ranges are implemented as ALTREP for R versions > 3.5.0
is_altrep(x)
#> [1] TRUE

# wrap ALTREP vector
y <- alt_wrap(x, "x")
```

We can already see `R` making calls to the ALTREP vector. Subsequent
operations will reveal more of these internal calls to `x`:

``` r
# single element
y[2]
#> x : ALTREP length : result = integer[1] 10
#> ALTREP element : result = integer[1] 2
#> [1] 2

# vector length
length(y)
#> x : ALTREP length : result = integer[1] 10
#> x : ALTREP length : result = integer[1] 10
#> [1] 10

# sum
sum(y)
#> ALTREP sum called, na.rm =  logical[1] FALSE, result:  integer[1] 55
#> [1] 55
```

As can be seen, no elements are actually retrieved to calculate the sum,
only the internal ALTREP method for calculating the sum is called.

``` r
# print vector
min(y)
#> x : ALTREP min : result = NULL[0] 
#> x : ALTREP length : result = integer[1] 10
#> x : ALTREP dataptr_or_null called, null returned:  logical[1] TRUE
#> x : ALTREP length : result = integer[1] 10
#> x : ALTREP dataptr_or_null called, null returned:  logical[1] TRUE
#> x : ALTREP get_region : result = integer[1] 10, start = integer[1] 0, length = integer[1] 10
#> [1] 1
```
