//
// Created by Tom on 12/25/19.
//

#include "gameMap.h"

gameMap::gameMap(std::string filename, sf::Texture sheet){
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
            //std::cout << map2dInts[j][i];

        }
        //std::cout << std::endl;
    }

    file.close();

    //initialize map tiles
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            if(map2dInts[j][i] == 1 || map2dInts[j][i] == 2){
                emptyTile(mapTiles[index(j,i)]);
                //std::cout << "tile: " << j << ", " << i << " nsew: " << mapTiles[index(j,i)].hasNorthWall << " " << mapTiles[index(j,i)].hasSouthWall << " " << mapTiles[index(j,i)].hasEastWall << " " << mapTiles[index(j,i)].hasWestWall << std::endl;
                continue;
            }
            mapTiles[index(j,i)].entities.push_back(Wall())
            mapTiles[index(j,i)].isEmpty = false;
            mapTiles[index(j, i)].hasNorthWall = map2dInts[j-1][i] == 1;
            mapTiles[index(j, i)].hasWestWall = map2dInts[j][i+1] == 1;
            mapTiles[index(j, i)].hasSouthWall = map2dInts[j+1][i] == 1;
            mapTiles[index(j, i)].hasEastWall = map2dInts[j][i-1] == 1;
            //std::cout << "tile: " << j << ", " << i << " nsew: " << mapTiles[index(j,i)].hasNorthWall << " " << mapTiles[index(j,i)].hasSouthWall << " " << mapTiles[index(j,i)].hasEastWall << " " << mapTiles[index(j,i)].hasWestWall << std::endl;

        }
    }

    delete[] mapLines;
    for(int i=0; i<cols; i++){
        delete[] map2dInts[i];
    }
    delete[] map2dInts;

    floorVerticies = sf::VertexArray(sf::Quads, 0);
    otherVerticies = sf::VertexArray(sf::Quads, 0);
    spriteSheet = sheet;
}

void gameMap::loadVerticies() {
    /*for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            if(!mapTiles[index(j,i)].isEmpty){
                addElementToVertexArray(floorVerticies, sf::Vector2f(j*tileSize,i*tileSize), floorText, 0.f);
                //north wall needs an adjustment of y:-90
                //west wall needs to go y:-90 and then world space x:19/3 and y:19/3
                //east needs y:-90 and world x:19/3 y:-19/3
                //south needs y:-90 and world x:2*19/3
                if(mapTiles[index(j,i)].hasNorthWall){
                    addElementToVertexArray(northWallVerticies, sf::Vector2f(j*tileSize, i*tileSize), northWallText, 90.f);
                }
                if(mapTiles[index(j,i)].hasSouthWall){
                    addElementToVertexArray(southWallVerticies, sf::Vector2f((j*tileSize)+2.f*tileSize/3.f, i*tileSize), southWallText, 90.f);
                }
                if(mapTiles[index(j,i)].hasEastWall){
                    addElementToVertexArray(eastWallVerticies, sf::Vector2f((j*tileSize)+tileSize/3.f, (i*tileSize)-tileSize/3.f), eastWallText, 90.f);
                }
                if(mapTiles[index(j,i)].hasWestWall){
                    addElementToVertexArray(westWallVerticies, sf::Vector2f((j*tileSize)+tileSize/3.f, i*tileSize+tileSize/3.f), westWallText, 90.f);
                }
            }
        }
    }*/
    int y;
    for (int i = 0; i < rows; i++) {
        for (int x = 0; x < i; x++) {
            y = i - x;
            std::cout << "x: " << x << " y: " << y << std::endl;
            if (!mapTiles[index(x, y)].isEmpty) {
                addElementToVertexArray(floorVerticies, sf::Vector2f(x * tileSize, y * tileSize), floorText, 0.f);
                //north wall needs an adjustment of y:-90
                //west wall needs to go y:-90 and then world space x:19/3 and y:19/3
                //east needs y:-90 and world x:19/3 y:-19/3
                //south needs y:-90 and world x:2*19/3
                if (mapTiles[index(x, y)].hasNorthWall) {
                    addElementToVertexArray(northWallVerticies, sf::Vector2f(x * tileSize, y * tileSize), northWallText,90.f);
                }
                if (mapTiles[index(x, y)].hasSouthWall) {
                    addElementToVertexArray(southWallVerticies,sf::Vector2f((x * tileSize) + 2.f * tileSize / 3.f, y * tileSize),southWallText, 90.f);
                }
                if (mapTiles[index(x, y)].hasEastWall) {
                    addElementToVertexArray(eastWallVerticies, sf::Vector2f((x * tileSize) + tileSize / 3.f,(y * tileSize) - tileSize / 3.f),eastWallText, 90.f);
                }
                if (mapTiles[index(x, y)].hasWestWall) {
                    addElementToVertexArray(westWallVerticies, sf::Vector2f((x * tileSize) + tileSize / 3.f,y * tileSize + tileSize / 3.f),westWallText, 90.f);
                }
            }
        }
    }
    for (int i = 0; i < cols; i++) {
        y=rows-1;
        for (int x = i; x < cols; x++) {
            if (!mapTiles[index(x, y)].isEmpty) {
                addElementToVertexArray(floorVerticies, sf::Vector2f(x * tileSize, y * tileSize), floorText, 0.f);
                //north wall needs an adjustment of y:-90
                //west wall needs to go y:-90 and then world space x:19/3 and y:19/3
                //east needs y:-90 and world x:19/3 y:-19/3
                //south needs y:-90 and world x:2*19/3
                if (mapTiles[index(x, y)].hasNorthWall) {
                    addElementToVertexArray(northWallVerticies, sf::Vector2f(x * tileSize, y * tileSize), northWallText,90.f);
                }
                if (mapTiles[index(x, y)].hasSouthWall) {
                    addElementToVertexArray(southWallVerticies,sf::Vector2f((x * tileSize) + 2.f * tileSize / 3.f, y * tileSize),southWallText, 90.f);
                }
                if (mapTiles[index(x, y)].hasEastWall) {
                    addElementToVertexArray(eastWallVerticies, sf::Vector2f((x * tileSize) + tileSize / 3.f,(y * tileSize) - tileSize / 3.f),eastWallText, 90.f);
                }
                if (mapTiles[index(x, y)].hasWestWall) {
                    addElementToVertexArray(westWallVerticies, sf::Vector2f((x * tileSize) + tileSize / 3.f,y * tileSize + tileSize / 3.f),westWallText, 90.f);
                }
            }
            y--;
        }
    }
}

void gameMap::renderMap(sf::RenderWindow *window) {
    window->draw(floorVerticies, &floorText);
    window->draw(southWallVerticies, &southWallText);
    window->draw(westWallVerticies, &westWallText);
    window->draw(northWallVerticies, &northWallText);
    window->draw(eastWallVerticies, &eastWallText);

}

void gameMap::addElementToVertexArray(sf::VertexArray &v, sf::Vector2f worldCoords, sf::Texture t, float zHeight) {
    sf::Vertex root = sf::Vertex(WorldToScreen(worldCoords));
    //std::cout << "adding tile at: " << worldCoords.x << "," << worldCoords.y << std::endl;
    root.texCoords = sf::Vector2f(0,0);
    sf::Vertex two = adjustVec(t.getSize().x, 0, root.position);
    two.texCoords = sf::Vector2f(t.getSize().x, 0);
    sf::Vertex three = adjustVec(t.getSize().x, t.getSize().y, root.position);
    three.texCoords = sf::Vector2f(t.getSize().x, t.getSize().y);
    sf::Vertex four = adjustVec(0, t.getSize().y, root.position);
    four.texCoords = sf::Vector2f(0, t.getSize().y);

    root.position.y -= zHeight;
    two.position.y -= zHeight;
    three.position.y -= zHeight;
    four.position.y -= zHeight;

    v.append(root);
    v.append(two);
    v.append(three);
    v.append(four);
}


