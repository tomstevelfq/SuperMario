#include"Headers/Map.h"
#include"Headers/Global.h"
#include"Headers/Mario.h"
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
        m[it[0]][it[1]]=Point(it[2],it[3],Brick_);
    }
}
void Map::draw(){
    for(int i=0;i<m.size();i++){
        for(int j=0;j<ScreenHeight/CellSize;j++){
            if(m[i][j].type!=Empty){
                m[i][j].entity->draw();//把绘图写到entity中
            }
        }
    }
}
void Map::update(Mario& mario){
    for(int i=0;i<m.size();i++){
        for(int j=0;j<ScreenHeight/CellSize;j++){
            if(m[i][j].type!=Empty){
                m[i][j].entity->update();
                if(mario.dx!=0||mario.dy!=0){
                    //sprite.setPosition(Vector2f(pos.x+dx,pos.y+dy));
                    mario.pos.x+=mario.dx;
                    mario.pos.y+=mario.dy;
                }
            }
        }
    }
}
