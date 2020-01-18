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
    //first two lines of map file are the number of size and size
    size = 0;
    file >> size;
    
    string* mapLines = new std::string[size];
    char** map2dChars = new char*[size];
    mapTiles = new mapTile[size*size];
    for(int i = 0; i < size; ++i) {
        map2dChars[i] = new char[size];
    }

    if(!file.is_open()){
        exit(1);
    }
    //read each line of file into mapLines[] as a string, then read each char of those strings into map2dChars
    for(int i=0; i<size; i++){
        file >> mapLines[i];
    }
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            map2dChars[j][i] = mapLines[i][j];
        }
    }
    file.close();

    //initialize map tiles
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            mapTiles[index(j,i)] = mapTile();
            if(map2dChars[j][i] == '2'){
                mapTiles[index(j, i)].empty = true;
            }
            else {
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
            }
        }
    }
    delete[] mapLines;
    for(int i=0; i<size; i++){
        delete[] map2dChars[i];
    }
    delete[] map2dChars;

    verticies = sf::VertexArray(sf::Quads, 0);
    floorVerticies = sf::VertexArray(sf::Quads, 0);
    spriteSheet = sheet;
    /*
     * Load verticies for floor tiles
     *
     * Floor tiles aren't entities because their place in the draw order never needs to be updated
     *
     */
    int y = 0;
    for (int i = 0; i < size; i++) {
        for (int x = 0; x <= i; x++) {
            y = i - x;
            if (!mapTiles[index(x, y)].empty) {
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
        }
    }
    for (int i = 0; i < size; i++) {
        y = size - 1;
        for (int x = i; x < size; x++) {

            if (!mapTiles[index(x, y)].empty) {
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



/*
 * Loop through every tile in the map in screen y order (loop through each diagonal of the square)
 *
 * For each tile, load all of its entities to a vertex array
 */
void gameMap::loadEntVerticies() {
    int y;
    for (int i = 0; i < size; i++) {
        for (int x = 0; x <= i; x++) {
            y = i - x;
            for (int k = mapTiles[index(x, y)].entities.size() - 1; k >= 0; k--) {
                    loadEntityToVertexArray(verticies, mapTiles[index(x, y)].entities.at(k));
            }
        }
    }
    for (int i = 0; i < size; i++) {
        y = size - 1;
        for (int x = i; x < size; x++) {
            for (int k = mapTiles[index(x, y)].entities.size() - 1; k >= 0; k--) {
                loadEntityToVertexArray(verticies, mapTiles[index(x, y)].entities.at(k));
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


