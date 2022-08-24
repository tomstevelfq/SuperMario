#include"Headers/Bullet.h"
#include"Headers/Map.h"
using namespace std;
using namespace sf;

Bullet::Bullet(){
    sprite.setTexture(GenTexture::getTexture("Bullet.png"));
    sprite.setTextureRect(IntRect(0,0,BulletSize,BulletSize));
    hspeed=BulletHSpeed;
    vspeed=BulletVSpeed;
    state=Alive;
}
void Bullet::flyAnimation(){
    if(dua--==0){
        dua=BulletAnimationDuration;
        anipos=(anipos++)%4;
        sprite.setTextureRect(IntRect(anipos*(BulletSize+4),0,BulletSize,BulletSize));
    }
}
void Bullet::DeadAnimation(){
    if(dua--==0){
        dua=AnimationDuration/2;
        anipos++;
        if(anipos==1){
           sprite.setTextureRect(IntRect(8,0,12,12)); 
        }else if(anipos==2){
            sprite.setTextureRect(IntRect(20,0,16,16));
        }else if(anipos==3){
            state=Dead;
        }
    }
}
void Bullet::startDead(){
    state=Dying;
    dua=AnimationDuration/2;
    anipos=0;
    sprite.setTexture(GenTexture::getTexture("BulletDead.png"),true);
    sprite.setTextureRect(IntRect(0,0,8,8)); 
}
void Bullet::draw(){
    if(state!=Dead){
        sprite.setPosition(Vector2f(px,py));
        window->draw(sprite);
    }
}
void Bullet::update(){
    if(state==Alive){
        Vector2f pos;
        for(auto it:marioMap->enemies){
            pos=it->getPosition();
            if(checkCollision(pos.x,pos.y,it->width,it->height)){
                it->startDead2();
                startDead();
                break;
            }
        }
        flyAnimation();
        vspeed=min(vspeed+Gravity,MaxVSpeed);
        py+=vspeed;
        px+=hspeed;
        int res=checkCollision();
        if(res==1){
            if(vspeed>0){
                vspeed=-BulletJumpSpeed;
            }else{
                vspeed=BulletJumpSpeed;
            }
        }else if(res==2){
            startDead();
        }
    }else if(state==Dying){
        DeadAnimation();
    }
}
void Bullet::setPos(int x,int y){
    px=x;
    py=y;
}
Vector2f Bullet::getPosition(){
    return Vector2f(px,py);
}
bool Bullet::checkCollision(float x,float y,int objWidth,int objHeight){
    if(x-px>-objWidth&&x-px<BulletSize&&y-py>-objHeight&&y-py<BulletSize){
        return true;
    }
    return false;
}
int Bullet::checkCollision(){
    int x,y;
    float centerx=(px*2+BulletSize)/2.0;
    float centery=(py*2+BulletSize)/2.0;
    Vector2f pos;
    for(auto& v:marioMap->m){
        for(auto& it:v){
            if(it.type==Brick_){
                x=it.entity->px;
                y=it.entity->py;
                pos=Vector2f(x*CellSize,y*CellSize);
                if(checkCollision(pos.x,pos.y)){
                    if(vspeed>0){
                        if(getTopleft(px+BulletSize,py+BulletSize)==pair<int,int>{x,y}||
                        getTopleft(px,py+BulletSize)==pair<int,int>{x,y}){
                            if(py+BulletSize-pos.y>0&&py+BulletSize-pos.y<=6){
                                if(centerx-pos.x>=centery-pos.y){
                                    py=pos.y-BulletSize;
                                    return 1;//碰撞到顶部或者底部反弹
                                }else if(marioMap->m[x][y-1].type==Empty){
                                    py=pos.y-BulletSize;
                                    return 1;
                                }else{
                                    return 2;
                                }
                            }else{
                                return 2;//碰撞到侧面消失
                            }
                        }
                    }else{
                        if(getTopleft(px,py)==pair<int,int>{x,y}||getTopleft(px+BulletSize,py)==pair<int,int>{x,y}){
                            if(pos.y+CellSize-py>0&&pos.y+CellSize-py<=6){
                                if(centerx-pos.x>=centery-pos.y){
                                    py=pos.y+BulletSize;
                                    return 1;
                                }else if(marioMap->m[x][y+1].type==Empty){
                                    py=pos.y+BulletSize;
                                    return 1;
                                }else{
                                    return 2;
                                }
                            }else{
                                return 2;
                            }
                        }
                    }
                }
            }
        }
    } 
    return 3;//既不碰撞也不消失
}