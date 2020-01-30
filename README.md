# ISTravel

This repository contains a practical application of the Dijkstra algorithm targetted in C language. Detailed documentation about this project scope and implementation choices is presented in [the project proposal](doc/enunciado.pdf) and [the report](doc/relatorio/relatorio.pdf). Note that both these documents are written in Portuguese because this project was performed in the context of my BSc degree, which is entirely taught in Portuguese.

## Summary

Given a network of public transports between cities and requests of clients to get from one city to another, this project aims at providing a solver that finds the optimal sequence of public transports. The cities on the map are the vertexes of a weighted graph and the public transports are the edges of that graph. Each edge has multiple weights corresponding to the type, cost, and duration of the public transport. Clients might impose restrictions regarding one or two of these features. Using the Dijkstra algorithm the optimal path that connects both cities having into account the client's constraints is found. If no path can satisfy all the client's requirements, the client is informed that such a request is unfulfillable.

As a secondary goal, the proposed solution also aims at providing optimal performance and dynamic memory allocation management.

## Requirements

* C compiler
* CMake >= 3.15

## Build

```
git clone https://github.com/joaomiguelvieira/ISTravel.git
mkdir ISTravel/build
cd ISTravel/build
cmake ..
make -j
```

## Verification

To run the software, just type `./ISTravel <map_file> <client_file>`, where `<map_file>` is the text file that contains the map and `<client_file>` contains the clients' requests. The syntax and purpose of both these files are explained in the [the project proposal](doc/enunciado.pdf).

To verify that all the dynamicaly allocated structures are correctly managed, `valgrind` can be used: `valgrind ./ISTravel <map_file> <client_file>`.
