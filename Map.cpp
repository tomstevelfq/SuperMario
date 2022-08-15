#include"Headers/Map.h"
#include"Headers/Global.h"
#include<fstream>
#include<algorithm>
Map::Map(RenderWindow& window):window(window){
    ifstream ifs("MapResource/level.txt");
    brick.loadFromFile("Resource/brick.png");
    sprite.setTexture(brick);
    vector<vector<int>> tem;
    int a,b,c,d;
    int siz=0;
    while(!ifs.eof()){
        siz=max(a,siz);
        ifs>>a>>b>>c>>d;
        tem.push_back({a,b,c,d});
    }
    ifs.close();
    m.resize(siz+1,vector<Point>(ScreenHeight/CellSize));
    //初始化地图
    for(auto &it:tem){
        m[it[0]][it[1]]=Point(it[2],it[3],Brick);
    }
}
void Map::draw(){
    for(int i=0;i<m.size();i++){
        for(int j=0;j<ScreenHeight/CellSize;j++){
            if(m[i][j].type!=Empty){
                sprite.setTextureRect(IntRect(m[i][j].x*CellSize,m[i][j].y*CellSize,CellSize,CellSize));
                sprite.setPosition(Vector2f(i*CellSize,j*CellSize));
                window.draw(sprite);
            }
        }
    }
}
void Map::update(){

}
