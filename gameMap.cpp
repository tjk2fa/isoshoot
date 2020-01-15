//
// Created by Tom on 12/25/19.
//

#include "gameMap.h"
using namespace std;
//north wall needs an adjustment of y:-90
//west wall needs to go y:-90 and then world space x:19/3 and y:19/3
//east needs y:-90 and world x:19/3 y:-19/3
//south needs y:-90 and world x:2*19/3

gameMap::gameMap(std::string filename, sf::Texture sheet){
    std::ifstream file(filename);
    //first two lines of map file are the number of rows and cols
    rows = 0;
    cols = 0;
    file >> rows;
    file >> cols;


    auto* mapLines = new std::string[rows];
    char** map2dChars = new char*[cols];
    mapTiles = new mapTile[cols*rows];
    for(int i = 0; i < cols; ++i) {
        map2dChars[i] = new char[rows];
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
            map2dChars[j][i] = mapLines[i][j];
            //std::cout << map2dInts[j][i];

        }
        //std::cout << std::endl;
    }

    file.close();

    //initialize map tiles

    for(int i=0; i<rows; i++){
        //std::cout << std::endl;
        for(int j=0; j<cols; j++){
            mapTiles[index(j,i)] = mapTile();

            //std::cout << map2dInts[j][i];
            if(map2dChars[j][i] == '2'){
                //cout << "tile was empty branch" << endl;
                mapTiles[index(j, i)].empty = true;
                //std::cout << "(x,y): " << j << ", " << i << "empty?: " << mapTiles[index(j, i)].empty << std::endl;
            }
            else {
                cout <<  map2dChars[j][i] << endl;

                if (map2dChars[j][i] == 'w') {
                    mapTiles[index(j, i)].entities.push_back(Wall(north, j * tileSize, i * tileSize));
                }
                else if (map2dChars[j][i] == 'e') {
                    mapTiles[index(j, i)].entities.push_back(
                            Wall(south, (j * tileSize) + 2.f * tileSize / 3.f, i * tileSize));
                }
                else if (map2dChars[j][i] == 'n') {
                    mapTiles[index(j, i)].entities.push_back(
                            Wall(east, (j * tileSize) + tileSize/3, (i * tileSize) - tileSize/3));
                }
                else if (map2dChars[j][i] == 's') {
                            mapTiles[index(j, i)].entities.push_back(Wall(west, (j * tileSize) + tileSize / 3.f,
                                                                          (i * tileSize) + tileSize / 3.f));
                }
                else if(map2dChars[j][i] == 'i'){
                    mapTiles[index(j, i)].entities.push_back(Wall(northwest, j * tileSize, i * tileSize));

                }
                else if(map2dChars[j][i] == 'j'){
                    mapTiles[index(j, i)].entities.push_back(Wall(southwest, j * tileSize, i * tileSize));

                }
                else if(map2dChars[j][i] == 'k'){
                    mapTiles[index(j, i)].entities.push_back(Wall(southeast, j * tileSize+tileSize/3.f, i * tileSize+tileSize/3.f));

                }
                else if(map2dChars[j][i] == 'l'){
                    mapTiles[index(j, i)].entities.push_back(Wall(northeast, j * tileSize+tileSize/3.f, i * tileSize-tileSize/3.f));

                }
                /*
                 * old system
                if (map2dInts[j - 1][i] == 1) {
                    mapTiles[index(j, i)].entities.push_back(Wall(north, j * tileSize, i * tileSize));
                }
                if (map2dInts[j][i + 1] == 1) {
                    mapTiles[index(j, i)].entities.push_back(Wall(west, (j * tileSize) + tileSize / 3.f,
                                                                  (i * tileSize) + tileSize / 3.f));
                }
                if (map2dInts[j + 1][i] == 1) {
                    mapTiles[index(j, i)].entities.push_back(
                            Wall(south, (j * tileSize) + 2.f * tileSize / 3.f, i * tileSize));
                }
                if (map2dInts[j][i - 1] == 1) {
                    mapTiles[index(j, i)].entities.push_back(
                            Wall(east, (j * tileSize) + tileSize / 3.f, (i * tileSize) - tileSize / 3.f));
                }
                 */

            }
            /*
            mapTiles[index(j,i)].isEmpty = false;
            mapTiles[index(j, i)].hasNorthWall = map2dInts[j-1][i] == 1;
            mapTiles[index(j, i)].hasWestWall = map2dInts[j][i+1] == 1;
            mapTiles[index(j, i)].hasSouthWall = map2dInts[j+1][i] == 1;
            mapTiles[index(j, i)].hasEastWall = map2dInts[j][i-1] == 1;
             */
            //std::cout << "tile: " << j << ", " << i << " nsew: " << mapTiles[index(j,i)].hasNorthWall << " " << mapTiles[index(j,i)].hasSouthWall << " " << mapTiles[index(j,i)].hasEastWall << " " << mapTiles[index(j,i)].hasWestWall << std::endl;
            //std::cout << "(x,y): " << j << ", " << i << "empty?: " << mapTiles[index(j, i)].empty << std::endl;

        }
    }
    delete[] mapLines;
    for(int i=0; i<cols; i++){
        delete[] map2dChars[i];
    }
    delete[] map2dChars;

    verticies = sf::VertexArray(sf::Quads, 0);
    floorVerticies = sf::VertexArray(sf::Quads, 0);
    spriteSheet = sheet;
    int y = 0;

    /*
    for (int i = 0; i < rows; i++) {
        for (int x = 0; x <= i; x++) {
            y = i - x;
            std::cout << "i: " << i << std::endl;
            std::cout << "(x,y): " << x << ", " << y << std::endl;
            //y--;
        }
    }
    */
    //exit(1);

    for (int i = 0; i < rows; i++) {
        for (int x = 0; x <= i; x++) {
            y = i - x;
            //std::cout << "x: " << x << " y: " << y << std::endl;
            if (!mapTiles[index(x, y)].empty) {

                //add floor
                sf::Vertex a = sf::Vertex(WorldToScreen(sf::Vector2f(x * tileSize, y * tileSize)));
                sf::Vertex b = sf::Vertex(adjustVec(0, 39, a.position));
                sf::Vertex c = sf::Vertex(adjustVec(75, 39, a.position));
                sf::Vertex d = sf::Vertex(adjustVec(75, 0, a.position));
                a.texCoords = sf::Vector2f(0,0);
                b.texCoords = adjustVec(0, 39, a.texCoords);
                c.texCoords = adjustVec(75, 39, a.texCoords);
                d.texCoords = adjustVec(75, 0, a.texCoords);
                floorVerticies.append(a);
                floorVerticies.append(b);
                floorVerticies.append(c);
                floorVerticies.append(d);
                std::cout << "i: " << i << std::endl;
                std::cout << "(x,y): " << x << ", " << y << std::endl;
            }
        }
    }

    for (int i = 0; i < cols; i++) {
        y = rows - 1;
        for (int x = i; x < cols; x++) {

            if (!mapTiles[index(x, y)].empty) {
                std::cout << "i: " << i << std::endl;
                std::cout << "(x,y): " << x << ", " << y << std::endl;
                //add floor
                sf::Vertex a = sf::Vertex(WorldToScreen(sf::Vector2f(x * tileSize, y * tileSize)));
                sf::Vertex b = sf::Vertex(adjustVec(0, 39, a.position));
                sf::Vertex c = sf::Vertex(adjustVec(75, 39, a.position));
                sf::Vertex d = sf::Vertex(adjustVec(75, 0, a.position));
                a.texCoords = sf::Vector2f(0,0);
                b.texCoords = adjustVec(0, 39, a.texCoords);
                c.texCoords = adjustVec(75, 39, a.texCoords);
                d.texCoords = adjustVec(75, 0, a.texCoords);
                floorVerticies.append(a);
                floorVerticies.append(b);
                floorVerticies.append(c);
                floorVerticies.append(d);

            }
            y--;
        }
    }


}

gameMap::~gameMap(){
    delete[] mapTiles;

}




void gameMap::loadEntVerticies() {
    int y;
    for (int i = 0; i < rows; i++) {
        for (int x = 0; x <= i; x++) {
            y = i - x;
            for (int k = mapTiles[index(x, y)].entities.size() - 1; k >= 0; k--) {
                    loadEntityToVertexArray(verticies, mapTiles[index(x, y)].entities.at(k));

            }
        }
    }
    for (int i = 0; i < cols; i++) {
        y = rows - 1;
        for (int x = i; x < cols; x++) {
            for (int k = mapTiles[index(x, y)].entities.size() - 1; k >= 0; k--) {
                loadEntityToVertexArray(verticies, mapTiles[index(x, y)].entities.at(k));
                    //north wall needs an adjustment of y:-90
                    //west wall needs to go y:-90 and then world space x:19/3 and y:19/3
                    //east needs y:-90 and world x:19/3 y:-19/3
                    //south needs y:-90 and world x:2*19/3
                }
                y--;
        }
    }
}

void gameMap::renderMap(sf::RenderWindow *window) {
    window->draw(floorVerticies, &spriteSheet);
    window->draw(verticies, &spriteSheet);

}

void gameMap::loadEntityToVertexArray(sf::VertexArray &v, Entity e) {
    sf::Vertex root = sf::Vertex(WorldToScreen(sf::Vector2f(e.worldX, e.worldY)));
    //std::cout << "adding tile at: " << worldCoords.x << "," << worldCoords.y << std::endl;
    root.texCoords = sf::Vector2f(e.texCoords.left,e.texCoords.top);

    sf::Vertex two = adjustVec(0, e.texCoords.height, root.position);
    two.texCoords = adjustVec(0, e.texCoords.height, root.texCoords);

    sf::Vertex three = adjustVec(e.texCoords.width, e.texCoords.height, root.position);
    three.texCoords = adjustVec(e.texCoords.width, e.texCoords.height, root.texCoords);

    sf::Vertex four = adjustVec(e.texCoords.width, 0, root.position);
    four.texCoords = adjustVec(e.texCoords.width, 0, root.texCoords);

    root.position.y -= e.zHeight;
    two.position.y -= e.zHeight;
    three.position.y -= e.zHeight;
    four.position.y -= e.zHeight;

    v.append(root);
    v.append(two);
    v.append(three);
    v.append(four);
}


