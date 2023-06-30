# SFUnpacker

A Standalone executable for extracting Setup Factory installers. Currently only supports V9.

Most of the code comes from [Observer](https://github.com/lazyhamster/Observer/)

## How to build from source ##
Project is developed under MS Visual Studio 2022.

Depends on zlib, The easiest way to install it is with [vcpkg](https://github.com/Microsoft/vcpkg) tool.

For x86 version run:
* vcpkg install zlib --triplet x86-windows

For x64 version run:
* vcpkg install zlib --triplet x64-windows

## License ##

SFUnpacker is [free](http://www.gnu.org/philosophy/free-sw.html) software: you can use it, redistribute it and/or modify it under the terms of the [GNU Lesser General Public License](http://www.gnu.org/licenses/lgpl.html) as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
