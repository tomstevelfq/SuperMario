#include"Headers/Treasure.h"
#include"Headers/Mario.h"
using namespace std;
using namespace sf;

Treasure::Treasure(){
    sprite.setTexture(GenTexture::getTexture("treasure.png"),true);
    coinSprite.setTexture(GenTexture::getTexture("coin.png"),true);
    type=Coin;//类型为砖块
    state=Alive;
}
void Treasure::coinAnimation(){
    if(dua--==0){
        dua=CoinDuration/2;
        coinSprite.setTextureRect(IntRect(anipos++%4*8,0,8,14));
    }
}
void Treasure::draw(){
    if(state==Alive){
        sprite.setTextureRect(IntRect(0,0,CellSize,CellSize));
        sprite.setPosition(Vector2f(px*CellSize,py*CellSize));
        window->draw(sprite);
    }else if(state==Wobble){
        sprite.setTextureRect(IntRect(0,0,CellSize,CellSize));
        sprite.setPosition(Vector2f(px*CellSize,nowdpy));
        window->draw(sprite);
        drawCoin();
    }else if(state==TreaEmpty){
        sprite.setTextureRect(IntRect(CellSize,0,CellSize,CellSize));
        sprite.setPosition(Vector2f(px*CellSize,py*CellSize));
        window->draw(sprite);
    }
}
void Treasure::drawCoin(){
    coinAnimation();
    coinSprite.setPosition(Vector2f(coinx+4,coiny));
    window->draw(coinSprite);
}
void Treasure::setPos(int x,int y){
    px=x;
    py=y;
    dpy=y*CellSize;
    nowdpy=dpy;
    coinx=x*CellSize;
    coiny=y*CellSize-CellSize;
}
Vector2f Treasure::getPosition(){
    return Vector2f(px*CellSize,py*CellSize);
}
void Treasure::startDead(){
    if(state==Alive){
        state=Wobble;
        vspeed=BrickWobbleSpeed;
        coiny=py*CellSize-CellSize;
    }
}
void Treasure::update(){
    if(state==Alive||state==TreaEmpty){
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
    }else if(state==Wobble){
        vspeed=min(vspeed+Gravity,MaxVSpeed);
        nowdpy+=vspeed;
        if(nowdpy>=dpy){
            nowdpy=dpy;
            state=TreaEmpty;
        }
        coiny=coiny+coinvspeed;
    }
}
bool Treasure::checkCollision(float x,float y,Direc direct){
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
