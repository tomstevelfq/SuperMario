#include"Headers/Turtle.h"
#include"Headers/Map.h"
#include"Headers/Mario.h"
using namespace std;
using namespace sf;

const int dead_timer=20;
Turtle::Turtle(){
    sprite.setTexture(GenTexture::getTexture("Turtle.png"),true);
    sprite.setTextureRect(IntRect(0,0,TurtleWidth,TurtleHeight));
    type=Enemy;
    state=Alive;
    hspeed=TurtleHSpeed;
}
void Turtle::walkAnimation(){
    if(dua--==0){
        dua=TurtleAnimationDuration;
        sprite.setTextureRect(IntRect((anipos++%2)*TurtleWidth,0,TurtleWidth,TurtleHeight));
    }
}
void Turtle::rwalkAnimation(){
    if(dua--==0){
        dua=TurtleAnimationDuration;
        sprite.setTextureRect(IntRect((anipos++%2+1)*TurtleWidth,0,-TurtleWidth,TurtleHeight));
    }
}
void Turtle::draw(){
    sprite.setPosition(Vector2f(px,py));
    window->draw(sprite);
}
void Turtle::update(){
    switch(state){
        case Alive:{
            Vector2f pos=mario->pos;
            if(mario->vspeed>0){
                if(checkCollision(pos.x,pos.y,DOWN)){
                    startDead();
                    mario->vspeed=EnemyJump;
                }
            }else{
                if(checkCollision(pos.x,pos.y,ALL)){
                    mario->startDead();
                }
            }
            //更新位置
            vspeed=min(vspeed+Gravity,MaxVSpeed);
            if(vspeed>0){
                if(checkCollision(DOWN,Brick_)){
                    vspeed=0;
                }
            }
            if(hspeed>0){
                rwalkAnimation();
                if(checkCollision(RIGHT,Brick_)){
                    dua=0;
                    hspeed=-hspeed;
                }
            }else if(hspeed<0){
                walkAnimation();
                if(checkCollision(LEFT,Brick_)){
                    dua=0;
                    hspeed=-hspeed;
                }
            }
            //更新位置
            px+=hspeed;
            py+=vspeed;
            break;
        }
        case Shrink:{
            Vector2f pos=mario->pos;
            if(checkCollision(pos.x,pos.y,ALL)){
                if(pos.x<px){
                    hspeed=TurtleSlideSpeed;
                }else{
                    hspeed=-TurtleSlideSpeed;
                }
                state=Dying;
                deadTimer=dead_timer;
            }
            sprite.setTextureRect(IntRect(TurtleWidth*3,TurtleHeight-CellSize,TurtleWidth,CellSize));
            break;
        }
        case Dying:{
            Vector2f pos=mario->pos;
            vspeed=min(vspeed+Gravity,MaxVSpeed);
            sprite.setTextureRect(IntRect(TurtleWidth*3,TurtleHeight-CellSize,TurtleWidth,CellSize));
            if(vspeed>0){
                if(checkCollision(DOWN,Brick_)){
                    vspeed=0;
                }
            }
            if(deadTimer>0){
                deadTimer--;
            }else{
                if(checkCollision(pos.x,pos.y,ALL)){
                    mario->startDead();
                }
                Vector2f pos;
                for(auto& it:marioMap->enemies){
                    pos=it->getPosition();
                    if(it->type==Geezer_){
                        if(checkCollision(pos.x,pos.y,ALL)){
                            it->startDead2();
                        }
                    }else if(it->type==Turtle_){
                        if(checkCollision(pos.x,pos.y,ALL,TurtleWidth,TurtleHeight)){
                            it->startDead2();
                        }
                    }
                }
            }
            if(hspeed>0){
                if(checkCollision(RIGHT,Brick_)){
                    dua=0;
                    hspeed=-hspeed;
                }
            }else if(hspeed<0){
                if(checkCollision(LEFT,Brick_)){
                    dua=0;
                    hspeed=-hspeed;
                }
            }
            px+=hspeed;
            py+=vspeed;
            break;
        }
        case DeadBounce:{
            if(deadBounceTimer){
                deadBounceTimer--;
                vspeed=min(vspeed+Gravity,MaxVSpeed);
                if(vspeed<0){
                    sprite.setTextureRect(IntRect(0,0,CellSize,TurtleHeight));
                }else{
                    sprite.setTextureRect(IntRect(0,TurtleHeight,CellSize,-TurtleHeight));  
                }
                py+=vspeed;
            }else{
                state=Dead;
            }
            break;
        }
        case Dead:
            break;
    }
}
void Turtle::startDead(){
    if(state!=Dying&&state!=Dead&&state!=DeadBounce){
        state=Shrink;
        hspeed=0;
        py+=TurtleHeight-CellSize;
    }
}
void Turtle::startDead2(){
    if(state!=Dying&&state!=Dead&&state!=DeadBounce){
        deadBounceTimer=DeadTime;
        state=DeadBounce;
        hspeed=0;
        py+=TurtleHeight-CellSize;
        vspeed=DeadJump;
    }
}
void Turtle::setPos(int x,int y){
    px=x*CellSize;
    py=y*CellSize+CellSize-TurtleHeight;
}
Vector2f Turtle::getPosition(){
    return Vector2f(px,py);
}
bool Turtle::checkCollision(float x,float y,Direc direct,int objWidth,int objHeight){
    int height=TurtleHeight;
    if(state==Alive){
        height=TurtleHeight;
    }else{
        height=CellSize;
    }
    switch(direct){
        case UP:
            if(x-px>=-objWidth&&x-px<=TurtleWidth&&y-py>=0&&y-py<=height){
                return true;
            }
            break;
        case DOWN:
            if(x-px>=-objWidth&&x-px<=TurtleWidth&&y-py<=0&&y-py>=-objHeight){
                return true;
            }
            break;
        case LEFT:
            if(x-px>0&&x-px<TurtleWidth&&y-py>-objHeight&&y-py<height){
                return true;
            }
            break;
        case RIGHT:
            if(x-px<0&&x-px>-objWidth&&y-py>-objHeight&&y-py<height){
                return true;
            }
            break;
        case ALL:
            if(x-px>=-objWidth&&x-px<=TurtleWidth&&y-py>=-objHeight&&y-py<=height){
                return true;
            }
            break;
    }
    return false;
}
bool Turtle::checkCollision(Direc direct,Type type){
    if(direct==DOWN){
        if(type==Brick_){
           for(auto& v:marioMap->m){
            for(auto& it:v){
                if(it.type==Brick_){//砖块检测方向正好相反
                    if(checkCollision(it.entity->px*CellSize,it.entity->py*CellSize,UP)){
                        return true;
                    }
                }
            }
           } 
        }
    }else if(direct==LEFT){
        if(type==Brick_){
           for(auto& v:marioMap->m){
            for(auto& it:v){
                if(it.type==Brick_){
                    if(checkCollision(it.entity->px*CellSize,it.entity->py*CellSize,RIGHT)){
                        return true;
                    }
                }
            }
           } 
        }
    }else if(direct==RIGHT){
        if(type==Brick_){
           for(auto& v:marioMap->m){
            for(auto& it:v){
                if(it.type==Brick_){
                    if(checkCollision(it.entity->px*CellSize,it.entity->py*CellSize,LEFT)){
                        return true;
                    }
                }
            }
           } 
        }
    }
    return false;
}