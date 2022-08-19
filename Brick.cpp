#include"Headers/Brick.h"
#include"Headers/Mario.h"
const float h1=1;
const float h2=1.5;
const float v1=-4;
const float v2=-3;
Brick::Brick(){
    sprite.setTexture(GenTexture::getTexture("brick.png"),true);
    type=Brick_;//类型为砖块
    state=Alive;
}
void Brick::draw(){
    if(state==Alive){
        sprite.setPosition(Vector2f(px*CellSize,py*CellSize));
        window->draw(sprite);
    }else if(state==Dying){ //绘制碎块
        for(auto& it:broke){
            window->draw(it.rec);
        }
    }
}
void Brick::setPos(int x,int y){
    px=x;
    py=y;
}
void Brick::startDead(){
    state=Dying;
    auto pos=sprite.getPosition();
    RectangleShape rec;
    rec.setTexture(&GenTexture::getTexture("brick.png"));
    rec.setTextureRect(IntRect(textureX*CellSize,textureY*CellSize,CellSize,CellSize));
    rec.setSize(Vector2f(CellSize/2.5,CellSize/2.5));
    rec.setPosition(pos);
    broke.push_back(Broke(-h1,v1,rec));//初始化碎块数组
    rec.setPosition(Vector2f(pos.x+CellSize/2.0,pos.y));
    broke.push_back(Broke(h1,v1,rec));
    rec.setPosition(Vector2f(pos.x,pos.y+CellSize/2.0));
    broke.push_back(Broke(-h2,v2,rec));
    rec.setPosition(Vector2f(pos.x+CellSize/2.0,pos.y+CellSize/2.0));
    broke.push_back(Broke(h2,v2,rec));
}
void Brick::update(){
    if(state==Alive){
        Vector2f pos=mario->pos;
        Vector2f tem=pos;
        float& vspeed=mario->vspeed;
        float& hspeed=mario->hspeed;
        float dy=0;
        float dx=0;
        bool& ground=mario->ground;
        int& jump=mario->jump;
        int& keepTimer=mario->keepTimer;
        if(vspeed<0){
            if(checkCollision(pos.x,pos.y,UP)){
                if(pos.x>px*CellSize){
                    if(px*CellSize+CellSize-pos.x>=CollisionWidth){
                        vspeed=0;
                        keepTimer=0;
                        startDead(); //撞到砖块
                    }
                }else{
                    if(pos.x+CellSize-px*CellSize>=CollisionWidth){
                        vspeed=0;
                        keepTimer=0;
                        startDead();
                    }
                }   
            }
        }
        else{
            if(checkCollision(pos.x,pos.y+vspeed,DOWN)){
                if(pos.x>px*CellSize){
                    if(px*CellSize+CellSize-pos.x>=CollisionWidth){
                        dy=floor((pos.y+vspeed)/CellSize)*CellSize-pos.y;
                        if(dy<0){
                            cout<<"dy"<<dy<<endl;
                        }
                        vspeed=0;
                        ground=true;
                        if(jump!=2){  //取消连续跳
                            jump=1;
                        }
                    }else{
                        dy=0;
                    }
                }else{
                    if(pos.x+CellSize-px*CellSize>=CollisionWidth){
                        dy=floor((pos.y+vspeed)/CellSize)*CellSize-pos.y;
                        if(dy<0){
                            cout<<"dy"<<dy<<endl;
                        }
                        vspeed=0;
                        ground=true;
                        if(jump!=2){  //取消连续跳
                            jump=1;
                        }
                    }else{
                        dy=0;
                    }
                }
            }

        }
        pos.y+=dy;
        if(hspeed>0){
            if(checkCollision(pos.x,pos.y,RIGHT)){
                if(pos.y>py*CellSize){
                    if(py*CellSize+CellSize-pos.y>=CollisionHeight){
                    dx=0;//floor((pos.x+hspeed)/CellSize)*CellSize-pos.x;
                    hspeed=0;
                    }else{
                        dx=0; 
                    }
                }else{
                    if(pos.y+CellSize-py*CellSize>=CollisionHeight){
                    dx=0;//floor((pos.x+hspeed)/CellSize)*CellSize-pos.x;
                    hspeed=0;
                    }else{
                        dx=0; 
                    }
                }
            }
        }else if(hspeed<0){
            if(checkCollision(pos.x,pos.y,LEFT)){
                if(pos.y>py*CellSize){
                    if(py*CellSize+CellSize-pos.y>=CollisionHeight){
                    dx=0;//ceil((pos.x+hspeed)/CellSize)*CellSize-pos.x;
                    hspeed=0;
                    }else{
                        dx=0; 
                    }
                }else{
                    if(pos.y+CellSize-py*CellSize>=CollisionHeight){
                    dx=0;//ceil((pos.x+hspeed)/CellSize)*CellSize-pos.x;
                    hspeed=0;
                    }else{
                        dx=0; 
                    }
                }
            }
        }else{
            dx=0;
        }
        mario->dx=dx;
        mario->dy=dy;
    }else if(state==Dying){
        if(broke.size()==0){
            state=Dead;
        }else{
            Vector2f pos;
            for(auto& it:broke){
                pos=it.rec.getPosition();
                it.v=min(it.v+Gravity,MaxVSpeed);
                pos.x=pos.x+it.h;
                pos.y=pos.y+it.v;
                it.rec.setPosition(pos);
            }
            for(auto iter=broke.begin();iter!=broke.end();){
                if(iter->rec.getPosition().y>ScreenHeight){//触底消失
                    iter=broke.erase(iter);   
                }else{
                    iter++;
                }
            }
        }
    }else if(state==Dead){
        ;
    }
}
bool Brick::checkCollision(float x,float y,Direc direct){
    float i,j;
    pair<int,int> res;
    if(direct==UP){//UP
        i=x;
        j=y;
        if(getTopleft(i,j)==pair<int,int>{px,py}){
            return true;
        }
        i=x+CellSize;
        j=y;
        if(getTopleft(i,j)==pair<int,int>{px,py}){
            return true;
        } 
    }else if(direct==DOWN){//DOWN
        i=x;
        j=y+CellSize;
        if(getTopleft(i,j)==pair<int,int>{px,py}){
            return true;
        }
        i=x+CellSize;
        j=y+CellSize;
        if(getTopleft(i,j)==pair<int,int>{px,py}){
            return true;
        }
    }else if(direct==LEFT){//LEFT
        i=x;
        j=y;
        if(getTopleft(i,j)==pair<int,int>{px,py}){
            return true;
        }
        i=x;
        j=y+CellSize;
        if(getTopleft(i,j)==pair<int,int>{px,py}){
            return true;
        }
    }else if(direct==RIGHT){//RIGHT
        i=x+CellSize;
        j=y;
        if(getTopleft(i,j)==pair<int,int>{px,py}){
            return true;
        }
        i=x+CellSize;
        j=y+CellSize;
        if(getTopleft(i,j)==pair<int,int>{px,py}){
            return true;
        }
    }
    return false;
}
