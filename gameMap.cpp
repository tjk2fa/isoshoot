//
// Created by Tom on 12/25/19.
//

#include "gameMap.h"

gameMap::gameMap(std::string filename, sf::Texture textures[5]){
    std::ifstream file(filename);
    //first two lines of map file are the number of rows and cols
    rows = 0;
    cols = 0;
    file >> rows;
    file >> cols;


    auto* mapLines = new std::string[rows];
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
    delete[] mapLines;
    for(int i=0; i<cols; i++){
        delete[] map2dInts[i];
    }
    delete[] map2dInts;

    floorVerticies = sf::VertexArray(sf::Quads, 0);
    westWallVerticies = sf::VertexArray(sf::Quads, 0);
    southWallVerticies = sf::VertexArray(sf::Quads, 0);
    eastWallVerticies = sf::VertexArray(sf::Quads, 0);
    northWallVerticies = sf::VertexArray(sf::Quads, 0);

    floorText = textures[0];
}

void gameMap::loadVerticies() {
    sf::Vector2f currentTileRoot = sf::Vector2f(0,0);
    sf::Vertex* lastOne;
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            if(!mapTiles[index(j,i)].isEmpty){
                addElementToVertexArray(floorVerticies, sf::Vector2f(j*tileSize,i*tileSize), floorText);

            }
        }
    }
    std::cout << floorVerticies.getVertexCount() << std::endl;
}

void gameMap::renderMap(sf::RenderWindow *window) {
    window->draw(floorVerticies, &floorText);
}

void gameMap::addElementToVertexArray(sf::VertexArray &v, sf::Vector2f worldCoords, sf::Texture t) {
    sf::Vertex root = sf::Vertex(WorldToScreen(worldCoords));
    std::cout << "adding tile at: " << worldCoords.x << "," << worldCoords.y << std::endl;
    root.texCoords = sf::Vector2f(0,0);
    sf::Vertex two = adjustVec(t.getSize().x, 0, root.position);
    two.texCoords = sf::Vector2f(t.getSize().x, 0);
    sf::Vertex three = adjustVec(t.getSize().x, t.getSize().y, root.position);
    three.texCoords = sf::Vector2f(t.getSize().x, t.getSize().y);
    sf::Vertex four = adjustVec(0, t.getSize().y, root.position);
    four.texCoords = sf::Vector2f(0, t.getSize().y);
    v.append(root);
    v.append(two);
    v.append(three);
    v.append(four);
}

