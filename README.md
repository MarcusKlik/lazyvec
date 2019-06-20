
<!-- README.md is generated from README.Rmd. Please edit that file -->

<!-- <img src="logo.png" align="right" /> -->

[![Linux/OSX Build
Status](https://travis-ci.org/fstpackage/lazyvec.svg?branch=develop)](https://travis-ci.org/fstpackage/lazyvec)
[![WIndows Build
status](https://ci.appveyor.com/api/projects/status/bfm7amtkyjvc2rk9?svg=true)](https://ci.appveyor.com/project/fstpackage/lazyvec)
[![License: AGPL
v3](https://img.shields.io/badge/License-AGPL%20v3-blue.svg)](https://www.gnu.org/licenses/agpl-3.0)
[![Lifecycle:
experimental](https://img.shields.io/badge/lifecycle-maturing-blue.svg)](https://www.tidyverse.org/lifecycle/#maturing)
[![codecov](https://codecov.io/gh/fstpackage/lazyvec/branch/develop/graph/badge.svg)](https://codecov.io/gh/fstpackage/lazyvec)

> This repository is home to the `lazyvec` package. `lazyvec` depends
> heavily on the (complete) ALTREP framework that was rolled out with
> `R` 3.6.0. Therefore, you need at least this version of `R` to build
> or use the package.

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
devtools::install_github("fstpackage/lazyvec")
```

## Basic usage

From `R` version 3.5 onwards, several basic vectors are (internally)
implemented as ALTREP vectors:

``` r
library(lazyvec)

x <- 1:10  # this is an ordered sequence

# ordered sequences are implemented as ALTREP vectors
is_altrep(x)
#> [1] TRUE

# ALTREP class
altrep_class(x)
#> [1] "compact_intseq"

# package in which the ALTREP definition is stored
altrep_package(x)
#> [1] "base"

# internal (compact) representation
altrep_data(x)
#> [1] 10  1  1
```

To study the inner workings of this ALTREP vector, we can add listeners
to it:

``` r
# add listeners
y <- altrep_listener(x, "x")
```

We can already see `R` making calls to the ALTREP vector. Subsequent
operations will reveal more of these internal calls to `x`:

``` r
# single element
y[2]
#> x : ALTREP length : result = int[1] 10
#> x : ALTREP element : result = int[1] 2
#> [1] 2

# vector length
length(y)
#> x : ALTREP length : result = int[1] 10
#> x : ALTREP length : result = int[1] 10
#> [1] 10

# sum
sum(y)
#> ALTREP sum: na.rm = lgl[1] FALSE, result:  int[1] 55
#> [1] 55
```

As can be seen, no elements are actually retrieved to calculate the sum,
only the internal ALTREP method for calculating the sum is called.

``` r
# print vector
min(y)
#> x : ALTREP min: result = NA[0] 
#> x : ALTREP length : result = int[1] 10
#> x : ALTREP dataptr_or_null, null returned:  lgl[1] TRUE
#> x : ALTREP length : result = int[1] 10
#> x : ALTREP dataptr_or_null, null returned:  lgl[1] TRUE
#> x : ALTREP get_region : result = int[1] 10, start = int[1] 0, length = int[1] 10
#> [1] 1
```
