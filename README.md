# Zeta
Zeta is a helper tool built for C/C++ developers built by a C/C++ developer.

## Why zeta?
I like to write a lot of C/C++ programs. Setting up a new workspace for each project becomes a hassle once you start doing many projects. That's the sole reason why Zeta exists. It tries to eliminate the preparation part of your C/C++ program by setting up a workspace with all the necessary files and folder.

## Installation
Zeta is in its early stages and there might be a few bugs.
It is still very usable and can be used in general development.

One line installation
```
curl -L https://bit.ly/3CTBfOk > install.sh && bash install.sh && rm install.sh
```
Zeta is also [GitMan](https://github/acidicneko/gitman) compatible.
Append the following block to `packages` array in `~/.config/gitman/packages.conf` to install Zeta
```json
    {
      "name": "zeta",
      "repo": "acidicneko/zeta",
      "branch": "main",
      "type": "commit"
    }
```
