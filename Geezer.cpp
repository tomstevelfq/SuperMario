#include"Headers/Geezer.h"
#include"Headers/Mario.h"
#include<math.h>
const float reduce=0.8;
const float reduce1=0.6;
const int dying_timer=3;
const int dead_timer=30;
Geezer::Geezer(){
    sprite.setTexture(GenTexture::getTexture("Geezer1.png"),true);
    sprite.setTextureRect(IntRect(0,0,CellSize,CellSize));
    type=Enemy;
    state=Alive;
    hspeed=GeezerHSpeed;
    height=CellSize;
    width=CellSize;
}
void Geezer::walkAnimation(){
    if(dua--==0){
        dua=GeezerAnimationDuration;
        sprite.setTextureRect(IntRect((anipos++%2)*CellSize,0,CellSize,CellSize));
    }
}
void Geezer::update(){//老头的更新函数
    if(state==Alive){
        Vector2f pos=mario->pos;
        if(mario->vspeed>0){
            if(checkCollision(pos.x,pos.y,DOWN)){
                startDead();
                enemyJumpFlag=true;
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
        if(hspeed!=0){
            walkAnimation();
        }
        if(hspeed>0){
            if(checkCollision(RIGHT,Brick_)){
                hspeed=-hspeed;
            }
        }else{
            if(checkCollision(LEFT,Brick_)){
                hspeed=-hspeed;
            }
        }
        //更新位置
        px+=hspeed;
        py+=vspeed;

    }else if(state==Dying){
        if(dyingTimer>0){
            dyingTimer--;
            sprite.setTextureRect(IntRect(0,0,CellSize,CellSize));
        }else if(dyingTimer>-dying_timer){
            if(enemyJumpFlag){
                enemyJumpFlag=false;
                mario->vspeed=EnemyJump;
            }
            dyingTimer--;
            sprite.setTextureRect(IntRect(2*CellSize,0,CellSize,CellSize));
        }else if(dyingTimer>-dying_timer-dead_timer){
            dyingTimer--;
            sprite.setTextureRect(IntRect(2*CellSize,0,CellSize,CellSize));
        }else{
            state=Dead;
        }
    }else if(state==DeadBounce){
        if(deadBounceTimer>0){
            deadBounceTimer--;
            vspeed=min(vspeed+Gravity,MaxVSpeed);
            if(vspeed<0){
                sprite.setTextureRect(IntRect(0,0,CellSize,CellSize));
            }else{
                sprite.setTextureRect(IntRect(0,CellSize,CellSize,-CellSize));  
            }
            py+=vspeed;
        }else{
            state=Dead;
        }
    }
}
void Geezer::setPos(int x,int y){
    px=x*CellSize;
    py=y*CellSize;
}
Vector2f Geezer::getPosition(){
    return Vector2f(px,py);
}
void Geezer::draw(){
    if(state!=Dead){
        sprite.setPosition(Vector2f(px,py));
        window->draw(sprite);
    }
}
bool Geezer::checkCollision(float x,float y,Direc direct){
    switch(direct){
        case UP:
            if(x-px>=-CellSize&&x-px<=CellSize&&y-py>=0&&y-py<=CellSize){
                return true;
            }
            break;
        case DOWN:
            if(x-px>=-CellSize&&x-px<=CellSize&&y-py<=0&&y-py>=-CellSize){
                return true;
            }
            break;
        case LEFT:
            if(x-px>0&&x-px<CellSize&&y-py>-CellSize&&y-py<CellSize){
                return true;
            }
            break;
        case RIGHT:
            if(x-px<0&&x-px>-CellSize&&y-py>-CellSize&&y-py<CellSize){
                return true;
            }
            break;
        case ALL:
            if(x-px>=-CellSize&&x-px<=CellSize&&y-py>=-CellSize&&y-py<=CellSize){
                return true;
            }
    }
    return false;
}
void Geezer::startDead(){
    if(state!=Dying&&state!=Dead&&state!=DeadBounce){
        state=Dying;
        dyingTimer=dying_timer;
        deadTimer=dead_timer;
    }
}
void Geezer::startDead2(){
    //反弹死亡
    if(state!=Dying&&state!=Dead&&state!=DeadBounce){
        state=DeadBounce;
        hspeed=0;
        vspeed=DeadJump;
        deadBounceTimer=DeadTime;
    }
}
bool Geezer::checkCollision(Direc direct,Type type){
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