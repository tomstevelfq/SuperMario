#include"Headers/Brick.h"
#include"Headers/Mario.h"
void Brick::setPos(int x,int y){
    px=x;
    py=y;
}
void Brick::update(){
    Vector2f pos=mario.sprite.getPosition();
    Vector2f tem=pos;
    float& vspeed=mario.vspeed;
    float& hspeed=mario.hspeed;
    float dy=0;
    float dx=0;
    bool& ground=mario.ground;
    int& jump=mario.jump;
    if(vspeed<0){
        pair<int,int>p1=getTopleft(pos.x,pos.y);
        pair<int,int>p2=getTopleft(pos.x+CellSize,pos.y);
        if(p1==pair<int,int>{px,py}||p2==pair<int,int>{px,py}){
            if(pos.x>px*CellSize){
                if(px*CellSize+CellSize-pos.x>=CollisionWidth){
                    vspeed=0;
                }
            }else{
                if(pos.x+CellSize-px*CellSize>=CollisionWidth){
                    vspeed=0;
                }
            }
            // if(px*CellSize+CellSize-pos.x>=CollisionWidth||pos.x+CellSize-px*CellSize>=CollisionWidth){
            //     vspeed=0;
            // }
            //dy=vspeed;
        }
        // Type t=checkCollision(FloatRect(pos.x,pos.y+vspeed,CellSize,CellSize),0);
        // if(t!=Empty){
        //     vspeed=0;
        // }
        // dy=vspeed;
    }
    else{
        pair<int,int>p1=getTopleft(pos.x,pos.y+CellSize);
        pair<int,int>p2=getTopleft(pos.x+CellSize,pos.y+CellSize);
        if(p1==pair<int,int>{px,py}||p2==pair<int,int>{px,py}){
            if(pos.x>px*CellSize){
                if(px*CellSize+CellSize-pos.x>=CollisionWidth){
                    dy=floor((pos.y+vspeed)/CellSize)*CellSize-pos.y;
                    if(dy!=0){
                        cout<<dy<<endl;
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
            // if(px*CellSize+CellSize-pos.x>=CollisionWidth||pos.x+CellSize-px*CellSize>=CollisionWidth){
            //     dy=floor((pos.y+vspeed)/CellSize)*CellSize-pos.y;
            //     vspeed=0;
            //     ground=true;
            //     if(jump!=2){  //取消连续跳
            //         jump=1;
            //     }
            // }else{
            //     //ground=false;//不在地上了
            //     dy=0;
            // }
        }
        // Type t=checkCollision(FloatRect(pos.x,pos.y+vspeed,CellSize,CellSize),1);
        // if(t!=Empty){
        //     dy=floor((pos.y+vspeed)/CellSize)*CellSize-pos.y;
        //     vspeed=0;
        //     ground=true;
        //     if(jump!=2){  //取消连续跳
        //         jump=1;
        //     }
        // }else{
        //     ground=false;//不在地上了
        //     dy=vspeed;
        // }
    }
    pos.y+=dy;
    if(hspeed>0){
        pair<int,int>p1=getTopleft(pos.x+CellSize,pos.y);
        pair<int,int>p2=getTopleft(pos.x+CellSize,pos.y+CellSize);
        if(p1==pair<int,int>{px,py}||p2==pair<int,int>{px,py}){
            if(pos.y>py*CellSize){
                if(py*CellSize+CellSize-pos.y>=CollisionHeight){
                dx=floor((pos.x+hspeed)/CellSize)*CellSize-pos.x;
                hspeed=0;
                if(dx>10||dx<-10){
                    cout<<dx<<endl;
                }
                }else{
                    dx=0; 
                }
            }else{
                if(pos.y+CellSize-py*CellSize>=CollisionHeight){
                dx=floor((pos.x+hspeed)/CellSize)*CellSize-pos.x;
                hspeed=0;
                if(dx>10||dx<-10){
                    cout<<dx<<endl;
                }
                }else{
                    dx=0; 
                }
            }
        }
        // Type t=checkCollision(FloatRect(pos.x+hspeed,pos.y-1,CellSize,CellSize),3);
        // if(t!=Empty){//碰到墙壁开始停止
        //     dx=floor((pos.x+hspeed)/CellSize)*CellSize-pos.x;
        //     hspeed=0;
        //     if(dx>10||dx<-10){
        //         cout<<dx<<endl;
        //     }
        // }else{
        //     dx=hspeed;
        // }
    }else if(hspeed<0){
        pair<int,int>p1=getTopleft(pos.x,pos.y);
        pair<int,int>p2=getTopleft(pos.x,pos.y+CellSize);
        if(p1==pair<int,int>{px,py}||p2==pair<int,int>{px,py}){
            if(p1==pair<int,int>{px,py}||p2==pair<int,int>{px,py}){
                if(pos.y>py*CellSize){
                    if(py*CellSize+CellSize-pos.y>=CollisionHeight){
                    dx=ceil((pos.x+hspeed)/CellSize)*CellSize-pos.x;
                    hspeed=0;
                    if(dx>10||dx<-10){
                        cout<<dx<<endl;
                    }
                    }else{
                        dx=0; 
                    }
                }else{
                    if(pos.y+CellSize-py*CellSize>=CollisionHeight){
                    dx=ceil((pos.x+hspeed)/CellSize)*CellSize-pos.x;
                    hspeed=0;
                    if(dx>10||dx<-10){
                        cout<<dx<<endl;
                    }
                    }else{
                        dx=0; 
                    }
                }
            }
        }
        // Type t=checkCollision(FloatRect(pos.x+hspeed,pos.y-1,CellSize,CellSize),2);
        // if(t!=Empty){
        //     dx=ceil((pos.x+hspeed)/CellSize)*CellSize-pos.x;
        //     hspeed=0;
        //     //cout<<dx<<endl;
        // }else{
        //     dx=hspeed;
        // }
    }else{
        dx=0;
    }
    //mario.setPosition(pos.x+dx,pos.y+dy);
    mario.dx=dx;
    mario.dy=dy;
    // if(checkCollision2(FloatRect(pos.x+hspeed,pos.y+vspeed,CellSize,CellSize))){
        
    // }
}
Type Brick::checkCollision(FloatRect rec,int direct){
    float i,j;
    pair<int,int> res;
    Type t;
    if(direct==0){//UP
        i=rec.left;
        j=rec.top;
        res=getTopleft(i,j);
        if(res.first*CellSize+CellSize-i>=CollisionWidth){
            t=marioMap.m[res.first][res.second].type;
            if(t!=Empty){//找到冲突 冲突宽度足够大的时候

                return t;
            }
        }
        i=rec.left+CellSize;
        j=rec.top;
        res=getTopleft(i,j);
        if(i-res.first*CellSize>=CollisionWidth){
            t=marioMap.m[res.first][res.second].type;
            if(t!=Empty){//找到冲突 冲突宽度足够大的时候

                return t;
            }
        }
    }else if(direct==1){//DOWN
        i=rec.left;
        j=rec.top+CellSize;
        res=getTopleft(i,j);
        if(res.first*CellSize+CellSize-i>=CollisionWidth){
            t=marioMap.m[res.first][res.second].type;
            if(t!=Empty){//找到冲突 冲突宽度足够大的时候

                return t;
            }
        }
        i=rec.left+CellSize;
        j=rec.top+CellSize;
        res=getTopleft(i,j);
        if(i-res.first*CellSize>=CollisionWidth){
            t=marioMap.m[res.first][res.second].type;
            if(t!=Empty){//找到冲突 冲突宽度足够大的时候

                return t;
            }
        }
    }else if(direct==2){//LEFT
        i=rec.left;
        j=rec.top;
        res=getTopleft(i,j);
        if(res.second*CellSize+CellSize-j>=CollisionHeight){
            t=marioMap.m[res.first][res.second].type;
            if(t!=Empty){//找到冲突 冲突宽度足够大的时候

                return t;
            }
        }
        i=rec.left;
        j=rec.top+CellSize;
        res=getTopleft(i,j);
        if(j-res.second*CellSize>=CollisionHeight){
            t=marioMap.m[res.first][res.second].type;
            if(t!=Empty){//找到冲突 冲突宽度足够大的时候

                return t;
            }
        }
    }else if(direct==3){//RIGHT
        i=rec.left+CellSize;
        j=rec.top;
        res=getTopleft(i,j);
        if(res.second*CellSize+CellSize-j>=CollisionHeight){
            t=marioMap.m[res.first][res.second].type;
            if(t!=Empty){//找到冲突 冲突宽度足够大的时候

                return t;
            }
        }
        i=rec.left+CellSize;
        j=rec.top+CellSize;
        res=getTopleft(i,j);
        if(j-res.second*CellSize>=CollisionHeight){
            t=marioMap.m[res.first][res.second].type;
            if(t!=Empty){//找到冲突 冲突宽度足够大的时候

                return t;
            }
        }
    }
    return Empty;
}
bool Brick::checkCollision2(FloatRect rec){
    pair<int,int> p={px,py};
    if(getTopleft(rec.left,rec.top)==p){//判断冲撞
        return true;
    }else if(getTopleft(rec.left+CellSize,rec.top)==p){
        return true;
    }else if(getTopleft(rec.left+CellSize,rec.top+CellSize)==p){
        return true;
    }else if(getTopleft(rec.left,rec.top+CellSize)==p){
        return true;
    }
    return false;
}
