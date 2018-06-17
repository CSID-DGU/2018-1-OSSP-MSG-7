# Starwars

Space Shooting game (Developed by team "MSG")

## Description

* Simple space shooting game based on the "Dodge" game from "Awesome" team.
* Original Open Source : https://github.com/CSID-DGU/2017-2-OSSP-Awesome-1
* Written in C++

## How To Run

1. Install SDL library
```
sudo apt-get install libsdl1.2-dev
sudo apt-get install libsdl-image1.2-dev  
sudo apt-get install libsdl-ttf2.0-dev
```

2. Install g++
```
sudo apt-get install g++
```

2. Pull or clone our github
```
git clone https://github.com/CSID-DGU/2018-1-OSSP-MSG-7
```

3. Type the things in "make" file and compile
```
g++ -o main main.cpp helpers.h helpers.cpp AirPlane.cpp AirPlane.h define.h -lSDL -lSDL_ttf -lSDL_image -std=c++11
```

4. Run the "main"
```
./main
```

## Contributors
Seung Kyu Maeng / Tae Gyun Kim / Seung Woo Ryu / Soo Lyn Choi
