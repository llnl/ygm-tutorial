# YGM Tutorial

* Tutorial Repostiory for [YGM](https://github.com/LLNL/ygm)
* [YGM ReadTheDocs](https://ygm.readthedocs.io/en/v0.10-dev/)  

## Run YGM's Tutorial on docker
```
docker run -it ghcr.io/llnl/ygm-tutorial/tutorial:latest /bin/bash
# wait until it downloads and starts, then switch to the tutorial user
su tutorial
# Run examples and tutorial material
mpirun build/examples/howdy_world
```

## Build YGM's Tutorial on your own system
Requires GCC11 (or newer) and MPI
```
git clone https://github.com/llnl/ygm-tutorial.git
cd ygm-tutorial
mkdir build
cd build
cmake ../
make

# Run examples and tutorial material
mpirun build/examples/howdy_world
```

## NOTICE and Release

[NOTICE](NOTICE)

LLNL-CODE-789122
