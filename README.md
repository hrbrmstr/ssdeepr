
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
![License](https://img.shields.io/badge/License-AGPL-blue.svg)

# ssdeepr

Context Triggered Piecewise Hash Computation Using ‘ssdeep’

## Description

The ssdeep project provides an open source library
<https://github.com/ssdeep-project/ssdeep/> context triggered piecewise
hashing. Methods are provided to compute and compare hashes from
character/byte streams.

## What’s Inside The Tin

The following functions are implemented:

  - `hash_compare`: Compare two hashes
  - `hash_file`: Return CTP hash of one or more files
  - `hash_raw`: Return CTP hash of a raw vector

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
## [1] '0.1.0'
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

## ssdeepr Metrics

| Lang | \# Files | (%) | LoC |  (%) | Blank lines |  (%) | \# Lines |  (%) |
| :--- | -------: | --: | --: | ---: | ----------: | ---: | -------: | ---: |
| C++  |        2 | 0.2 |  67 | 0.52 |          21 | 0.30 |        8 | 0.07 |
| R    |        7 | 0.7 |  45 | 0.35 |          22 | 0.32 |       61 | 0.54 |
| Rmd  |        1 | 0.1 |  16 | 0.12 |          26 | 0.38 |       45 | 0.39 |

## Code of Conduct

Please note that this project is released with a Contributor Code of
Conduct. By participating in this project you agree to abide by its
terms.
