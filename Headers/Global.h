#ifndef GLOBAL_H
#define GLOBAL_H
#include"SFML/Graphics.hpp"
#include<map>
using namespace sf;
using namespace std;
const int Height=192;
const int PersonHeight=16;
const int PersonWidth=16;
const int ScreenHeight=240;
const int ScreenWidth=320;
const int PanelWidth=50;
const int CellSize=16;
const int ZoomSize=4;
const float MaxHSpeed=1.5;
const float OriginHSpeed=0.5;
const float MaxVSpeed=4;
const float Gravity=0.25;
const float Acc=0.05;
const float JumpSpeed=3.6;
const int AnimationDuration=6;
const int CollisionWidth=4;
const int DeadTime=50;
const float CollisionHeight=0.5;
enum Type{
    Brick_,Bground,Empty
};
inline pair<int,int> getTopleft(int x,int y){
    return {x/CellSize,y/CellSize};
}
inline pair<int,int> getTopleft(float x,float y){
    return {x/CellSize,y/CellSize};
} 
class GenTexture{
    public:
        static Texture& getTexture(const string& file){
            auto it=m.find(file);
            if(it==m.end()){
                auto& text=m[file];
                text.loadFromFile("Resource/"+file);
                return text;
            }else{
                return it->second;
            }
        }
        static map<string,Texture> m;
};
#endif