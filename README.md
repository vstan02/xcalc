# xCalc
> A fast and simple to use calculator

[![Version: v0.1.0](https://img.shields.io/badge/version-v0.1.0-blue)](https://vstan02.github.io/xcalc)
[![License: LGPL v3](https://img.shields.io/badge/License-LGPL%20v3-blue.svg)](http://www.gnu.org/licenses/lgpl-3.0)

## Contents
- [Building and Installation](#building-and-installation)
- [License](#license)
- [Contributing](#contributing)

## Building and Installation

### Dependencies
- C compiler
- cmake (>= 3.17)
- glib (for testing)

These packages can usually be installed through your distributions package manager.

Some libraries:
- [Conix v1.0.0](https://github.com/vstan02/conix)
- [Arithmo v1.0.0](https://github.com/vstan02/arithmo)

### Building the project
To build the project, we first need to create a separate build directory:
```
mkdir build
```

Now that we've created our build directory (assuming it's created in the project root), we can `cd` into it and run `cmake` and pass the parent directory path to it, which is where the `CMakeLists.txt` file is located:
```
cd build
cmake ..
```

Once `cmake` is done generating makefiles, we can build the app by running `make` inside our build directory:
```
make
```

### Running the program
If everything went well with the compilation we can run the executable:
```
./xcalc
```

### Installing
To install the app run:
```
sudo make install
```
By default the app will be installed in `/usr/local/bin/` directory.

## License
xCalc is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
For more details, see [LICENSE](https://github.com/vstan02/xcalc/blob/master/LICENSE) file.

## Contributing
Contributions are welcome.
If you have a feature request, or have found a bug, feel free to open a [new issue](https://github.com/vstan02/xcalc/issues/new).
If you wish to contribute code, see [CONTRIBUTING.md](https://github.com/vstan02/xcalc/blob/master/CONTRIBUTING.md) for more details.
