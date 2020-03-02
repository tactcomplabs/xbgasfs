# xBGAS-FS: xBGAS File System Infrastructure

## Getting Started

## Prerequisites
* C++14 Compiler (LLVM/Clang and GCC are tested)
* CMake 3.4.3+
* gRPC [https://grpc.io/]

## Building

The majority of the library and tool dependencies are contained 
within the xBGAS-FS source tree.  The only outside library 
dependencies are met with libstdc++ (from GCC or LLVM) and 
the Google RPC library infrastructure (gRPC).  Generally speaking, 
the xBGAS-FS Is built using the following steps: 

1. Clone the xBGAS-FS repository.  The are currently no git submodules dependencies.
```
git clone https://github.com/tactcomplabs/xbgasfs.git
cd xbgasfs
```
2. Create a ``build`` directory within the xBGAS-FS source tree.
```
mkdir build
cd build
```
3. Execute cmake to generate the target-specific makefiles
```
cmake ../
```
4. Execute the build
```
make
```

### Building with Clang/LLVM

Building xBGAS-FS with Clang/LLVM can be done by setting the CC and CXX environment variables.

1. Override default compiler
```
export CC=clang
export CXX=clang++
```


## CMake Build Options

### Standard Build Options
* -DCMAKE\_BUILD\_TYPE=Release : Builds a release build with optimization (Default)
* -DCMAKE\_BUILD\_TYPE=Debug : Builds with debugging options (-O0 -g, etc)
* -DCMAKE\_INSTALL\_PREFIX=/path/to/install : Forces alternate install locations
* -DGRPC\_INSTALL\_PATH=/path/to/grpc/install : Sets an alternate gRPC installation location (default=/usr/local)

### Documentation Options
* -DBUILD\_DOCUMENTATION=ON  : Enables Doxygenized documentaition.  ``make doc`` will build the documentation (requires Doxygen to be installed)

### Test Options
* -DBUILD\_ALL\_TESTING=ON : Enable ALL unit tests for CoreGen


## Contributing
We welcome outside contributions from corporate, acaddemic and individual developers.  However,
there are a number of fundamental ground rules that you must adhere to in order to participate.  These
rules are outlined as follows:

* All code must adhere to the existing C++ coding style.  While we are somewhat flexible in basic style, you will
adhere to what is currently in place.  This includes camel case C++ methods and inline comments.  Uncommented,
complicated algorithmic constructs will be rejected.
* We support compilaton and adherence to C++11 methods.  We do not currently accept C++14 and beyond.
* All new methods and variables contained within public, private and protected class methods must be commented
using the existing Doxygen-style formatting.  All new classes must also include Doxygen blocks in the new header
files.  Any pull requests that lack these features will be rejected.
* All changes to functionality and/or the API infrastructure must be accompanied by complementary tests
* All external pull requests **must** target the *devel* branch.  No external pull requests will be accepted
to the master branch.
* All external pull requests must contain sufficient documentation in the pull request comments in order to
be accepted.
* All external pull requests that update the CoreGen IR specification or the StoneCutter language specification
(et al. syntax) must contain complementary pull requests for the CoreGen IR spec or the
StoneCutter language spec.
* All pull requests will be reviewed by the core development staff.  Any necessary changes will be marked
in the respective pull request comments.  All pull requests will be tested against in the Tactical
Computing Laboratories development infrastructure.  This includes tests against all supported platforms.
Any failures in the test infrastructure will be noted in the pull request comments.

## Testing
All tests must be formatted using standard CMake directives.  See the existing CMakeLists for
examples on how these tests are to be formatted.  Any updates to the test infrastructure (new test
directory structure) must include complementary, unique directives as outlined in the Test Options
section above.  Any new directives must be documented in this Readme file within the respective pull
request.

## License
CoreGen is licensed under an Apache-style license - see the [LICENSE](LICENSE) file for details

## Authors
* *John Leidel* - *Chief Scientist* - [Tactical Computing Labs](http://www.tactcomplabs.com)
* *Brody Williams* - *PhD Student* - [Texas Tech University](https://discl.cs.ttu.edu/doku.php)
* *Xi Wang* - *PhD Student* - [Texas Tech University](https://discl.cs.ttu.edu/doku.php)

## Acknowledgements
* None at this time
