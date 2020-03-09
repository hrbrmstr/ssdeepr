
[![Project Status: Active – The project has reached a stable, usable
state and is being actively
developed.](https://www.repostatus.org/badges/latest/active.svg)](https://www.repostatus.org/#active)
[![Signed
by](https://img.shields.io/badge/Keybase-Verified-brightgreen.svg)](https://keybase.io/hrbrmstr)
![Signed commit
%](https://img.shields.io/badge/Signed_Commits-100%25-lightgrey.svg)
[![Linux build
Status](https://travis-ci.org/hrbrmstr/ssdeepr.svg?branch=master)](https://travis-ci.org/hrbrmstr/ssdeepr)  
![Minimal R
Version](https://img.shields.io/badge/R%3E%3D-3.2.0-blue.svg)
![License](https://img.shields.io/badge/License-MIT-blue.svg)

# ssdeepr

Context Triggered Piecewise Hash Computation Using ‘ssdeep’

## Description

The ssdeep project provides an open source library
<https://github.com/ssdeep-project/ssdeep/> context triggered piecewise
hashing. Methods are provided to compute and compare hashes from
character/byte streams.

## What’s Inside The Tin

The following functions are implemented:

  - `check_is_xptr`: Test whether an object is an external pointer
  - `hash_compare`: Compare two hashes
  - `hash_con`: Return CTP hash of one data collected from a connection
  - `hash_file`: Return CTP hash of one or more files
  - `hash_raw`: Return CTP hash of a raw vector
  - `is_null_xptr_`: Test whether an external pointer is null
  - `split_hash`: Splits an ssdeep hash string into component parts

## Installation

The ssdeep library is bundled with the package source.

The library works on Windows, I just need to do some manual labor for
that, still.

Package installation:

``` r
install.packages("ssdeepr", repos = "https://cinc.rud.is")
# or
remotes::install_git("https://git.rud.is/hrbrmstr/ssdeepr.git")
# or
remotes::install_git("https://git.sr.ht/~hrbrmstr/ssdeepr")
# or
remotes::install_gitlab("hrbrmstr/ssdeepr")
# or
remotes::install_bitbucket("hrbrmstr/ssdeepr")
# or
remotes::install_github("hrbrmstr/ssdeepr")
```

NOTE: To use the ‘remotes’ install options you will need to have the
[{remotes} package](https://github.com/r-lib/remotes) installed.

## Usage

``` r
library(ssdeepr)

# current version
packageVersion("ssdeepr")
## [1] '0.2.0'
```

  - `index.html` is a static copy of a blog main page with a bunch of
    `<div>`s with article snippets
  - `index1.html` is the same file as `index.htmnl` with a changed cache
    timestamp at the end
  - `index2.html` is the same file as `index.html` with one article
    snippet removed
  - `RMacOSX-FAQ.html` is the CRAN ‘R for Mac OS X FAQ’

<!-- end list -->

``` r
system.file("extdat", package="ssdeepr") %>% 
  list.files(full.names = TRUE, pattern = "html$", include.dirs = FALSE) %>% 
  hash_file() -> hashes

hashes
##                                                                                             path
## 1       /Library/Frameworks/R.framework/Versions/3.6/Resources/library/ssdeepr/extdat/index.html
## 2      /Library/Frameworks/R.framework/Versions/3.6/Resources/library/ssdeepr/extdat/index1.html
## 3      /Library/Frameworks/R.framework/Versions/3.6/Resources/library/ssdeepr/extdat/index2.html
## 4 /Library/Frameworks/R.framework/Versions/3.6/Resources/library/ssdeepr/extdat/RMacOSX-FAQ.html
##                                                                                                     hash
## 1 1536:rwjgwyHuuoH3yHgHJBH5H3YHwHuXiOXd6uEk9SWLIL7ERKvc4wHc+sius234Y4NY:rZvb7HHc+sius234Y4N4pqwrCihwnUui
## 2 1536:twjgwyHuuoH3yHgHJBH5H3YHwHuXiCe6uEk9SWLIL7ERKvc4wbc+sius234Y4N4j:tZvbPobc+sius234Y4N4pqwrCihwnUua
## 3 1536:twjgwyHuuoH3yHgHJBH5H3YHwHuXiCJEk9SWLIL7ERKvc4wbc+sius234Y4N4pqs:tZvbPHbc+sius234Y4N4pqwrCihwnUum
## 4                                1536:3ExSauOOiqyq5tfAJqE3+OmEvqVtEYsSWiWB/H5ZJ:0x9fqyqtfAJqEu8vOWYsLd5r

hash_compare(hashes$hash[1], hashes$hash[1])
## [1] 100
hash_compare(hashes$hash[1], hashes$hash[2])
## [1] 91
hash_compare(hashes$hash[1], hashes$hash[3])
## [1] 88
hash_compare(hashes$hash[1], hashes$hash[4])
## [1] 0
```

Works with Connections, too. All three should be the same if the
Wikipedia page hasn’t changed since making local copies in the package.

Using `hash_con()` has the advantage of not requiring the entire
contents of the target blob to be read into memory in exchange for a
tiny cost to speed for most files (see Benchmarks).

NOTE that retrieving the URL contents with different user-agent strings
and/or with javascript-enabled may/will likely generate different
content and, thus, a different hash.

``` r
(k1 <- hash_con(url("https://en.wikipedia.org/wiki/Donald_Knuth", 
                    header = setNames(splashr::ua_ios_safari, "User-Agent"))))
## [1] "1536:LWaFR+jsCHr6UVyn1KSLnGURhAa0qYHaYF8tUdkWO9F+mTi9f0ruvSWJqdI:JWL6EOKsGMYJF8t99EBxzJwI"

(k2 <- hash_con(file(system.file("knuth", "local.html", package = "ssdeepr"))))
## [1] "3072:u2dfqECHC6NPsWzqFg2qDKgNYsVeJb19pEDTlfrd5czRsZNqqelzPFKsuXs6X9pU:PQli6NPsWzcg2/EYsVUY6sI"

(k3 <- hash_con(gzfile(system.file("knuth", "local.gz", package = "ssdeepr"))))
## [1] "3072:u2dfqECHC6NPsWzqFg2qDKgNYsVeJb19pEDTlfrd5czRsZNqqelzPFKsuXs6X9pU:PQli6NPsWzcg2/EYsVUY6sI"

hash_compare(k1, k2)
## [1] 0

hash_compare(k1, k3)
## [1] 0

hash_compare(k2, k3)
## [1] 100
```

Benchmarks

``` r
microbenchmark::microbenchmark(
  con = hash_con(file(system.file("knuth", "local.html", package = "ssdeepr"))),
  gzc = hash_con(gzfile(system.file("knuth", "local.gz", package = "ssdeepr"))),
  fil = hash_file(system.file("knuth", "local.html", package = "ssdeepr"))
)
## Unit: milliseconds
##  expr      min       lq     mean   median       uq       max neval cld
##   con 6.050446 6.207712 6.357149 6.335506 6.489715  6.948830   100  b 
##   gzc 6.817468 7.082380 7.296807 7.172750 7.291186 19.176480   100   c
##   fil 5.269110 5.431974 5.544224 5.508470 5.652608  6.087048   100 a
```

## ssdeepr Metrics

| Lang         | \# Files |  (%) |   LoC |  (%) | Blank lines |  (%) | \# Lines |  (%) |
| :----------- | -------: | ---: | ----: | ---: | ----------: | ---: | -------: | ---: |
| Bourne Shell |       11 | 0.20 | 35855 | 0.72 |        5973 | 0.74 |     7791 | 0.86 |
| m4           |        7 | 0.13 |  9219 | 0.19 |         991 | 0.12 |      100 | 0.01 |
| C++          |       10 | 0.19 |  1649 | 0.03 |         536 | 0.07 |      404 | 0.04 |
| C            |        4 | 0.07 |  1027 | 0.02 |         178 | 0.02 |      223 | 0.02 |
| make         |        2 | 0.04 |  1019 | 0.02 |         131 | 0.02 |       51 | 0.01 |
| C/C++ Header |        9 | 0.17 |   732 | 0.01 |         212 | 0.03 |      360 | 0.04 |
| R            |       10 | 0.19 |    92 | 0.00 |          39 | 0.00 |       96 | 0.01 |
| Rmd          |        1 | 0.02 |    28 | 0.00 |          33 | 0.00 |       45 | 0.00 |

## Code of Conduct

Please note that this project is released with a Contributor Code of
Conduct. By participating in this project you agree to abide by its
terms.
