//
// Created by Tom on 12/25/19.
//

#include "gameMap.h"

gameMap::gameMap(std::string filename){
    std::ifstream file(filename);
    //first two lines of map file are the number of rows and cols
    rows = 0;
    cols = 0;
    file >> rows;
    file >> cols;


    std::string* mapLines = new std::string[rows];
    int** map2dInts = new int*[cols];
    mapTiles = new mapTile[cols*rows];
    for(int i = 0; i < cols; ++i) {
        map2dInts[i] = new int[rows];
    }

    if(!file.is_open()){
        exit(1);
    }
    //read each line of file into mapLines[] as a string, then read each char of those strings into map2dInts
    for(int i=0; i<rows; i++){
        file >> mapLines[i];

    }
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            map2dInts[j][i] = ((int)mapLines[i][j])-48;
        }
    }

    file.close();

    //initialize map tiles
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            if(map2dInts[j][i] == 1 || map2dInts[j][i] == 2){
                emptyTile(mapTiles[index(j,i)]);
                continue;
            }
            mapTiles[index(j,i)].isEmpty = false;
            mapTiles[index(j, i)].hasNorthWall = map2dInts[j - 1][i] == 1;
            mapTiles[index(j, i)].hasEastWall = map2dInts[j][i - 1] == 1;
            mapTiles[index(j, i)].hasSouthWall = map2dInts[j + 1][i] == 1;
            mapTiles[index(j, i)].hasWestWall = map2dInts[j][i + 1] == 1;
        }
    }


}



