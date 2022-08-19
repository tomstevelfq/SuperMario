#include"Headers/Map.h"
#include"Headers/Global.h"
#include"Headers/Mario.h"
#include"Headers/Geezer.h"
#include"Headers/Turtle.h"
#include<fstream>
#include<algorithm>
Map::Map(RenderWindow& window,Mario& mario):window(window),mario(mario){
    ifstream ifs("MapResource/l4.txt");
    brick.loadFromFile("Resource/brick.png");
    sprite.setTexture(brick);
    vector<vector<int>> tem;
    int a,b,c,d,e;
    int siz=0;
    while(!ifs.eof()){
        siz=max(a,siz);
        ifs>>a>>b>>c>>d>>e;
        tem.push_back({a,b,c,d,e});
    }
    ifs.close();
    m.resize(siz+1,vector<Point>(ScreenHeight/CellSize));
    //初始化地图
    for(auto &it:tem){
        if((Type)it[4]==Brick_){
            m[it[0]][it[1]]=Point(it[2],it[3],Brick_);
        }else if((Type)it[4]==Geezer_){
            shared_ptr<Geezer> ptr(new Geezer());
            ptr->setTexturePos(it[2],it[3]);
            ptr->setPos(it[0],it[1]);
            ptr->type=Geezer_;
            enemies.push_back(ptr);
        }else if((Type)it[4]==Turtle_){
            shared_ptr<Turtle> ptr(new Turtle());
            ptr->setTexturePos(it[2],it[3]);
            ptr->setPos(it[0],it[1]);
            ptr->type=Turtle_;
            enemies.push_back(ptr);
        }
    }
}
void Map::init(){
    for(int i=0;i<m.size();i++){
        for(int j=0;j<ScreenHeight/CellSize;j++){
            if(m[i][j].type!=Empty){//每个砖块都是一个对象
                m[i][j].entity=shared_ptr<Entity>(EntityFactory::getEntity(m[i][j].type,&mario,this,&window));
                m[i][j].entity->setPos(i,j);
                m[i][j].entity->setTexturePos(m[i][j].x,m[i][j].y);
            }//初始化地图里面的对象
        }
    }
    for(auto& it:enemies){
        it->setProperty(&mario,this,&window);
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
    for(auto& it:enemies){
        it->draw();
    }
}
void Map::update(){
    for(int i=0;i<m.size();i++){
        for(int j=0;j<ScreenHeight/CellSize;j++){
            if(m[i][j].type!=Empty){
                m[i][j].entity->update();
                if(mario.dx!=0||mario.dy!=0){
                    mario.pos.x+=mario.dx;
                    mario.pos.y+=mario.dy;
                }
            }
        }
    }
    for(auto& it:enemies){
        it->update();
    }
    //移除死掉的敌人
    for(auto iter=enemies.begin();iter!=enemies.end();){
        if((*iter)->state==Dead){
            iter=enemies.erase(iter);
        }else{
            iter++;
        }
    }
}
