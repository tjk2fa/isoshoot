//
// Created by Tom on 12/25/19.
//

#include "gameMap.h"
#include "mapTile.h"
#include "Entity.h"


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
                map<char, direction> say_map = {{'w', west}, {'n', north}, {'s', south}, {'e', east},
                                              {'i', northwest}, {'j', southwest}, {'k', southeast}, {'l', northeast}};
                auto mapCode = say_map.find(map2dChars[j][i]);
                if(map2dChars[j][i] == 'p'){
                    mapTiles[index(j, i)].entities.push_back((Entity*)(new activeEntity(player, j,i, tileSize)));
                }
                else if(!(mapCode == say_map.end())) {
                    mapTiles[index(j, i)].entities.push_back(new Wall(mapCode->second, j, i, tileSize));
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
    Entity* dummyFloorEnt = new Floor(0,0);

    int y = 0;
    for (int i = 0; i < size; i++) {
        for (int x = 0; x <= i; x++) {
            y = i - x;
            if (!mapTiles[index(x, y)].empty) {
                dummyFloorEnt->worldX = tileSize*x;
                dummyFloorEnt->worldY = tileSize*y;
                loadEntityToVertexArray(floorVerticies, dummyFloorEnt);
            }
        }
    }
    for (int i = 0; i < size; i++) {
        y = size - 1;
        for (int x = i; x < size; x++) {

            if (!mapTiles[index(x, y)].empty) {
                dummyFloorEnt->worldX = tileSize*x;
                dummyFloorEnt->worldY = tileSize*y;
                loadEntityToVertexArray(floorVerticies, dummyFloorEnt);
            }
            y--;
        }
    }


}

gameMap::~gameMap(){
    for(int x=0; x<(size*size); x++){
        for(int y=0; y<mapTiles[x].entities.size(); x++){
            delete mapTiles[x].entities[y];
        }
    }
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


void gameMap::loadEntityToVertexArray(sf::VertexArray &v, Entity* e) {
    sf::Vertex root = sf::Vertex(WorldToScreen(sf::Vector2f(e->worldX, e->worldY)));
    root.texCoords = sf::Vector2f(e->texCoords.left,e->texCoords.top);
    sf::Vertex two = adjustVec(0, e->texCoords.height, root.position);
    two.texCoords = adjustVec(0, e->texCoords.height, root.texCoords);
    sf::Vertex three = adjustVec(e->texCoords.width, e->texCoords.height, root.position);
    three.texCoords = adjustVec(e->texCoords.width, e->texCoords.height, root.texCoords);
    sf::Vertex four = adjustVec(e->texCoords.width, 0, root.position);
    four.texCoords = adjustVec(e->texCoords.width, 0, root.texCoords);

    root.position.y -= e->zHeight;
    two.position.y -= e->zHeight;
    three.position.y -= e->zHeight;
    four.position.y -= e->zHeight;

    v.append(root);
    v.append(two);
    v.append(three);
    v.append(four);
}


