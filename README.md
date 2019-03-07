# udacity-robond-p1

This repository contains my submission of the project "Build My World" to
Udacity Robotics Software Engineer Nanodegree.

## Contents

This project consists on a world (world/arena.world) involving:
 - A building (model/slash)
 - Two instances of a model created with the model editor (model/spheric_horse)
 - Two instances of a model from gazebo's online model database ("cafe_table")
 - A sphere

and the following interactions via plugins:
 - Welcome (console output)
 - Movement of the sphere

## Instructions

Clone the repository and open a terminal in the root directory.

### Building the plugins

```sh
> mkdir build && cd build
> cmake ../
> make
```

### Loading the world

If terminal is not in the root folder, substitute `$PWD` by its path in all commands below.

1. Advise gazebo where to look for the plugins included in the world or model description files:
```sh
> export GAZEBO_PLUGIN_PATH=$PWD/script:$GAZEBO_PLUGIN_PATH
```

2. Do the same for the models we added:
```sh
> export GAZEBO_MODEL_PATH=$PWD/model:~/.gazebo/models:$GAZEBO_MODEL_PATH
```
Notice that in the case of the models, one needs to add `~/.gazebo/models` along with the path where models created as part of this project are stored. The reason for this is that models included from gazebo's online model database will be downloaded into that folder, so it is necessary to let gazebo know that it should also check that directory when loading modules.

3. Load the world with gazebo:
```sh
> gazebo world/arena.world --verbose
```

It is possible that the first time the world is loaded the following error shows repeatedly:
```
[Err] [Node.cc:105] No namespace found
````
This is due to the download of the models from gazebo's online model database not being finished when gazebo is already trying to find the models. If gazebo takes too long in loading after the last time the error is outputted, close it and run the last command again.


## License
Original version of the license of this repository can be found here:
https://gist.github.com/laramartin/7796d730bba8cf689f628d9b011e91d8
