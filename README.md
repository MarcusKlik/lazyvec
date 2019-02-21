
<!-- README.md is generated from README.Rmd. Please edit that file -->

<!-- <img src="logo.png" align="right" /> -->

[![Linux/OSX Build
Status](https://travis-ci.org/MarcusKlik/lazyvec.svg?branch=master)](https://travis-ci.org/MarcusKlik/lazyvec)
[![WIndows Build
status](https://ci.appveyor.com/api/projects/status/bfm7amtkyjvc2rk9?svg=true)](https://ci.appveyor.com/project/MarcusKlik/lazyvec)
[![License: AGPL
v3](https://img.shields.io/badge/License-AGPL%20v3-blue.svg)](https://www.gnu.org/licenses/agpl-3.0)

## Overview

The [*lazyvec* package](https://github.com/MarcusKlik/lazyvec) for `R`
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
devtools::install_github("marcusklik/lazyvec")
```

## Basic usage

To observe the internal behaviour of ALTREP ranges, the object can be
wrapped:
