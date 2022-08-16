#include"Headers/Brick.h"
#include"Headers/Mario.h"
Brick::Brick(Mario& mario,Map& m,sf::RenderWindow& wind):Entity(mario,m,wind){
    sprite.setTexture(GenTexture::getTexture("brick.png"),true);
    type=Brick_;//类型为砖块
}
void Brick::draw(){
    sprite.setPosition(Vector2f(px*CellSize,py*CellSize));
    window.draw(sprite);
}
void Brick::setPos(int x,int y){
    px=x;
    py=y;
}
void Brick::update(){
    Vector2f pos=mario.pos;
    Vector2f tem=pos;
    float& vspeed=mario.vspeed;
    float& hspeed=mario.hspeed;
    float dy=0;
    float dx=0;
    bool& ground=mario.ground;
    int& jump=mario.jump;
    if(vspeed<0){
        if(checkCollision(pos.x,pos.y,UP)){
            if(pos.x>px*CellSize){
                if(px*CellSize+CellSize-pos.x>=CollisionWidth){
                    vspeed=0;
                }
            }else{
                if(pos.x+CellSize-px*CellSize>=CollisionWidth){
                    vspeed=0;
                }
            }   
        }
    }
    else{
        if(checkCollision(pos.x,pos.y,DOWN)){
            if(pos.x>px*CellSize){
                if(px*CellSize+CellSize-pos.x>=CollisionWidth){
                    dy=floor((pos.y+vspeed)/CellSize)*CellSize-pos.y;
                    if(dy!=0){
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
    mario.dx=dx;
    mario.dy=dy;
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
