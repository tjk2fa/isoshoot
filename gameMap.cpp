//
// Created by Tom on 12/25/19.
//

#include "gameMap.h"

gameMap::gameMap(std::string filename){

    std::ifstream file(filename);
    int rows;
    int cols;
    file >> rows;
    file >> cols;
    std::cout << rows << "rows" << std::endl;
    std::string shit[] = {};
    int** ish = new int*[cols];
    tilez  = new mapTile*[cols];
    for(int i = 0; i < cols; ++i) {
        tilez[i] = new mapTile[rows];
        ish[i] = new int[rows];
    };
    if(file.is_open()){
        for(int i=0; i<rows; i++){
            file >> shit[i];
            for(int j=0; j<cols; j++){
                ish[j][i] = ((int)shit[i][j])-48;
            }
        }
    }
    file.close();


}

