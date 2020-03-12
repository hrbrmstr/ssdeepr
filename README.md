
[![Project Status: Active – The project has reached a stable, usable
state and is being actively
developed.](https://www.repostatus.org/badges/latest/active.svg)](https://www.repostatus.org/#active)
[![Signed
by](https://img.shields.io/badge/Keybase-Verified-brightgreen.svg)](https://keybase.io/hrbrmstr)
![Signed commit
%](https://img.shields.io/badge/Signed_Commits-85%25-lightgrey.svg)
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

You’ll need `libfuzzy` installed and available for linking. See
<https://ssdeep-project.github.io/ssdeep/index.html#platforms> for
platform support.

On Ubuntu/Debian you can do:

``` shell
sudo apt install libfuzzy-dev
```

On macOS you can do:

``` shell
brew install ssdeep
```

The library works on Windows, I just need to do some manual labor for
that.

Package installation:

``` r
install.packages("ssdeepr", repos = c("https://cinc.rud.is", "https://cloud.r-project.org/"))
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
## [1] "1536:IWaFR+jsCHr6UVyn1KSLnGURhAa0qYHaYF8tUdkWO9F+mTi9f0ruvSWnqd4:GWL6EOKsGMYJF8t99EBxznw4"

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
##  expr      min       lq     mean   median       uq       max neval
##   con 5.902252 6.004019 6.410288 6.130342 6.531428 16.202922   100
##   gzc 6.717070 6.821839 7.175860 7.037044 7.540798  8.369695   100
##   fil 5.129446 5.218194 5.559326 5.392933 5.692457  7.002297   100
```

## ssdeepr Metrics

| Lang         | \# Files |  (%) | LoC |  (%) | Blank lines |  (%) | \# Lines |  (%) |
| :----------- | -------: | ---: | --: | ---: | ----------: | ---: | -------: | ---: |
| C++          |        2 | 0.13 | 168 | 0.49 |          45 | 0.34 |       26 | 0.14 |
| R            |       10 | 0.67 |  92 | 0.27 |          39 | 0.30 |       96 | 0.51 |
| Bourne Shell |        2 | 0.13 |  53 | 0.16 |          10 | 0.08 |       14 | 0.07 |
| Rmd          |        1 | 0.07 |  28 | 0.08 |          37 | 0.28 |       53 | 0.28 |

## Code of Conduct

Please note that this project is released with a Contributor Code of
Conduct. By participating in this project you agree to abide by its
terms.
