#include"Headers/Mario.h"
#include<math.h>

Mario::Mario(RenderWindow& wind,View& view):window(wind),view(view){
    loadResource();
    marioMap=shared_ptr<Map>(new Map(window));
    sprite.setTexture(person_pic,true);
    sprite.setTextureRect(IntRect(0,0,PersonWidth,PersonHeight));
    sprite.setPosition({10,10});
}
void Mario::walkAnimation(){
    if(dua--==0){
        dua=AnimationDuration;
        sprite.setTexture(person_pic,true);
        sprite.setTextureRect(IntRect((anipos++%3)*PersonWidth,0,PersonWidth,PersonHeight));
    }
}
void Mario::rwalkAnimation(){
    if(rdua--==0){
        rdua=AnimationDuration;
        sprite.setTexture(person_pic,true);
        sprite.setTextureRect(IntRect((anipos++%3+1)*PersonWidth,0,-PersonWidth,PersonHeight));
    }
}
void Mario::stand(){
    //texture=&stand_pic;
    sprite.setTexture(person_pic,true);
    sprite.setTextureRect(IntRect(0,0,PersonWidth,PersonHeight));
}
void Mario::drawGround(){
    VertexArray line(LineStrip,2);
    line[0].color=Color(108,67,58);
    line[0].position={0,0};
    line[1].position={0,ScreenHeight};
    window.draw(line);
    line[1].position={ScreenWidth,0};
    window.draw(line);
    ground_sprite.setTexture(ground_pic);
    ground_sprite.setTextureRect(IntRect(0,3*CellSize,CellSize,CellSize));
    for(int i=0;i<10;i++){
        ground_sprite.setPosition(i*CellSize,Height+PersonHeight);
        window.draw(ground_sprite);
        ground_sprite.setPosition(i*CellSize,Height+PersonHeight+CellSize);
        window.draw(ground_sprite);
    }
}
void Mario::loadResource(){
    person_pic.loadFromFile("./Resource/mario.png");
    stand_pic.loadFromFile("./Resource/stand.png");
    ground_pic.loadFromFile("./Resource/brick.png");
}
void Mario::draw(){
    marioMap->draw();
    window.draw(sprite);
}
void Mario::update(){
    timer2+=clock.getElapsedTime().asSeconds();
    clock.restart();
    Vector2f pos=sprite.getPosition();
    print("pos.y",{int(pos.y),checkCollision(IntRect(pos.x,pos.y+vspeed,CellSize,CellSize)),checkCollision(IntRect(pos.x,pos.y+vspeed,CellSize,CellSize),false)});
    print("ground",{ground});
    if(!ground){
        vspeed=min(vspeed+Gravity,MaxVSpeed);
    }
    if(vspeed<0){
        //Type t=checkCollision(IntRect(pos.x,pos.y+vspeed,CellSize,CellSize));
        Type t=checkCollision2(FloatRect(pos.x,pos.y+vspeed,CellSize,CellSize),0);
        if(t!=Empty){
            vspeed=0;
        }
        dy=vspeed;
    }
    else{
        //Type t=checkCollision(IntRect(pos.x,pos.y+vspeed,CellSize,CellSize));
        Type t=checkCollision2(FloatRect(pos.x,pos.y+vspeed,CellSize,CellSize),1);
        if(t!=Empty){
            //dy=((int(pos.y)+int(vspeed))/CellSize)*CellSize-pos.y;
            dy=floor((pos.y+vspeed)/CellSize)*CellSize-pos.y;
            vspeed=0;
            ground=true;
            if(jump!=2){  //取消连续跳
                jump=1;
            }
        }else{
            ground=false;//不在地上了
            // cout<<"false"<<pos.y+vspeed<<endl;
            // if(pos.y+vspeed>=191.8){
            //     int a=0;
            //     cout<<"aa"<<endl;
            //     a++;
            // }
            // //dy=vspeed;
            // Type t=checkCollision(IntRect(pos.x,pos.y+vspeed-CollisionWidth,CellSize,CellSize));
            // if(t!=Empty){
            //     dx=round((pos.x+hspeed)/CellSize)*CellSize-pos.x;
            //     pos.x+=dx;
            // }
            dy=vspeed;
        }
    }
    pos.y+=dy;
    dy=0;
    //cout<<pos.y<<endl;
    if(Keyboard::isKeyPressed(Keyboard::D)){
        
        if(hspeed<0){
            hspeed=hspeed+Gravity;
        }else{
            hspeed=MaxHSpeed;//min(hspeed+0.1,10.0);
        }
        walkAnimation();
    
    }else if(Keyboard::isKeyPressed(Keyboard::A)){
        if(hspeed>0){
            hspeed=hspeed-Gravity;
        }else{
            hspeed=-MaxHSpeed;//max(hspeed-0.1,-10.0);
        }
        rwalkAnimation();
    }else{
        rdua=0;
        dua=0;
        if(hspeed>0){
            hspeed=max(hspeed-0.3,0.0);
        }else if(hspeed<0){
            hspeed=min(hspeed+0.3,0.0);
        }
        stand();
    }

    // if(checkCollision(IntRect(pos.x+hspeed,pos.y-1,CellSize,CellSize),false)!=Empty){//碰到墙壁立即停下
    //     Type t=checkBottomCollision(FloatRect(pos.x+hspeed,pos.y-1.6,CellSize,CellSize));
    //     if(t!=Empty){
    //         hspeed=0;
    //     }else{
    //         //dy=floor(pos.y/CellSize)*CellSize-pos.y;//升高
    //         dy=0;
    //         if(timer2>1){
    //             cout<<"haha"<<dy<<endl;
    //         }
    //     }
    //     dx=hspeed;
    //     // if(hspeed>0){
    //     //     dx=floor((pos.x+hspeed)/CellSize)*CellSize-pos.x;
    //     // }else{
    //     //     dx=ceil((pos.x+hspeed)/CellSize)*CellSize-pos.x;
    //     // }
    //     // hspeed=0;
    //     // if(timer2>1){
    //     //     cout<<"dx"<<dx<<" "<<pos.x<<endl;
    //     // }
    // }else{
    //     if(timer2>1){
    //         cout<<"dx_"<<dx<<" "<<pos.x<<endl;
    //     }
    //     dx=hspeed;
    // }
    if(hspeed>0){
        //if(checkCollision2(FloatRect(pos.x+hspeed,pos.y-1,CellSize,CellSize),3)!=Empty){//碰到墙壁立即停下
        Type t=checkCollision2(FloatRect(pos.x+hspeed,pos.y-1,CellSize,CellSize),3);
        if(t!=Empty){
            hspeed=0;
        }
        // }else{
        //     //dy=floor(pos.y/CellSize)*CellSize-pos.y;//升高
        //     dy=0;
        //     if(timer2>1){
        //         cout<<"haha"<<dy<<endl;
        //     }
        // }
        dx=hspeed;
        // if(hspeed>0){
        //     dx=floor((pos.x+hspeed)/CellSize)*CellSize-pos.x;
        // }else{
        //     dx=ceil((pos.x+hspeed)/CellSize)*CellSize-pos.x;
        // }
        // hspeed=0;
        // if(timer2>1){
        //     cout<<"dx"<<dx<<" "<<pos.x<<endl;
        // }
        // }else{
        //     if(timer2>1){
        //         cout<<"dx_"<<dx<<" "<<pos.x<<endl;
        //     }
        //     dx=hspeed;
        // }
    }else if(hspeed<0){
        Type t=checkCollision2(FloatRect(pos.x+hspeed,pos.y-1,CellSize,CellSize),2);
        if(t!=Empty){
            hspeed=0;
        }
        dx=hspeed;
    }else{
        dx=hspeed;
    }
    // if(checkCollision2(FloatRect(pos.x+hspeed,pos.y-1,CellSize,CellSize),false)!=Empty){//碰到墙壁立即停下
    //     Type t=checkBottomCollision(FloatRect(pos.x+hspeed,pos.y-1.6,CellSize,CellSize));
    //     if(t!=Empty){
    //         hspeed=0;
    //     }else{
    //         //dy=floor(pos.y/CellSize)*CellSize-pos.y;//升高
    //         dy=0;
    //         if(timer2>1){
    //             cout<<"haha"<<dy<<endl;
    //         }
    //     }
    //     dx=hspeed;
    //     // if(hspeed>0){
    //     //     dx=floor((pos.x+hspeed)/CellSize)*CellSize-pos.x;
    //     // }else{
    //     //     dx=ceil((pos.x+hspeed)/CellSize)*CellSize-pos.x;
    //     // }
    //     // hspeed=0;
    //     // if(timer2>1){
    //     //     cout<<"dx"<<dx<<" "<<pos.x<<endl;
    //     // }
    // }else{
    //     if(timer2>1){
    //         cout<<"dx_"<<dx<<" "<<pos.x<<endl;
    //     }
    //     dx=hspeed;
    // }
    sprite.setPosition(pos.x+dx,pos.y+dy);
    if(sprite.getPosition().x+hspeed>=0){
        sprite.setPosition(sprite.getPosition().x+hspeed,sprite.getPosition().y);
        if(sprite.getPosition().x>ScreenWidth/2){
            view.setCenter(sprite.getPosition().x,view.getCenter().y);
        }
    }

    if(Keyboard::isKeyPressed(Keyboard::W)){
        if(ground&&jump==1){  //在地上的时候可以小跳
            ground=false;
            keepTimer=13;
            vspeed=-JumpSpeed;
            jump=2;
        }else{
            if(jump==2){  //小跳接大跳 防止二段跳
                if(keepTimer>0){
                    ground=false;
                    keepTimer-=1;
                    vspeed=-JumpSpeed;
                }
            }
        }
    }else{
        jump=3;
    }
    if(timer2>1){
        timer2-=1;
    }
}
void Mario::move(int x){
    if(x==0){
        return;
    }
    cout<<x<<endl;
    if(x>0){
        offset+=x;
        if(x+offset>ScreenWidth/2){
            view.move(Vector2f(x,0));
        }
    }else{
        offset+=x;
        if(offset+x>ScreenHeight/2){//到边缘镜头不移动
            view.move(Vector2f(x,0));
        }
    }
}
Type Mario::checkCollision(IntRect rec,bool flag){
    // for(int i=rec.left;i<=rec.left+rec.width;i+=CellSize){
    //     for(int j=rec.top;j<=rec.top+rec.height;j+=CellSize){
    //         pair<int,int> res=getTopleft(i,j);
    //         Type t=marioMap->m[res.first][res.second].type;
    //         if(t!=Empty){//找到冲突 冲突宽度足够大的时候
    //             return t;
    //         }
    //     }
    // }
    int i,j;
    int collision=0;
    if(flag){
        collision=CollisionWidth;
    }
    i=rec.left+collision;
    j=rec.top;
    pair<int,int> res=getTopleft(i,j);
    Type t=marioMap->m[res.first][res.second].type;
    if(t!=Empty){//找到冲突 冲突宽度足够大的时候
        return t;
    }
    i=rec.left+CellSize-collision;
    j=rec.top;
    res=getTopleft(i,j);
    t=marioMap->m[res.first][res.second].type;
    if(t!=Empty){//找到冲突 冲突宽度足够大的时候
        return t;
    }
    i=rec.left+collision;
    j=rec.top+CellSize;
    res=getTopleft(i,j);
    t=marioMap->m[res.first][res.second].type;
    if(t!=Empty){//找到冲突 冲突宽度足够大的时候
        return t;
    }
    i=rec.left+CellSize-collision;
    j=rec.top+CellSize;
    res=getTopleft(i,j);
    t=marioMap->m[res.first][res.second].type;
    if(t!=Empty){//找到冲突 冲突宽度足够大的时候
        return t;
    }
    return Empty;
}
Type Mario::checkBottomCollision(FloatRect rec){
    // for(int i=rec.left;i<=rec.left+rec.width;i+=CellSize){
    //     for(int j=rec.top;j<=rec.top+rec.height;j+=CellSize){
    //         pair<int,int> res=getTopleft(i,j);
    //         Type t=marioMap->m[res.first][res.second].type;
    //         if(t!=Empty){//找到冲突 冲突宽度足够大的时候
    //             return t;
    //         }
    //     }
    // }
    pair<int,int> res;
    float i,j;
    i=rec.left;
    j=rec.top+CellSize;
    res=getTopleft(i,j);
    Type t=marioMap->m[res.first][res.second].type;
    if(t!=Empty){//找到冲突 冲突宽度足够大的时候
        return t;
    }
    i=rec.left+CellSize;
    j=rec.top+CellSize;
    res=getTopleft(i,j);
    t=marioMap->m[res.first][res.second].type;
    if(t!=Empty){//找到冲突 冲突宽度足够大的时候
        return t;
    }
    return Empty;
}
//碰撞检测函数
Type Mario::checkCollision2(FloatRect rec,int direct){
    float i,j;
    pair<int,int> res;
    Type t;
    if(direct==0){//UP
        i=rec.left;
        j=rec.top;
        res=getTopleft(i,j);
        if(res.first*CellSize+CellSize-i>=CollisionWidth){
            t=marioMap->m[res.first][res.second].type;
            if(t!=Empty){//找到冲突 冲突宽度足够大的时候

                return t;
            }
        }
        i=rec.left+CellSize;
        j=rec.top;
        res=getTopleft(i,j);
        if(i-res.first*CellSize>=CollisionWidth){
            t=marioMap->m[res.first][res.second].type;
            if(t!=Empty){//找到冲突 冲突宽度足够大的时候

                return t;
            }
        }
    }else if(direct==1){//DOWN
        i=rec.left;
        j=rec.top+CellSize;
        res=getTopleft(i,j);
        if(res.first*CellSize+CellSize-i>=CollisionWidth){
            t=marioMap->m[res.first][res.second].type;
            if(t!=Empty){//找到冲突 冲突宽度足够大的时候

                return t;
            }
        }
        i=rec.left+CellSize;
        j=rec.top+CellSize;
        res=getTopleft(i,j);
        if(i-res.first*CellSize>=CollisionWidth){
            t=marioMap->m[res.first][res.second].type;
            if(t!=Empty){//找到冲突 冲突宽度足够大的时候

                return t;
            }
        }
    }else if(direct==2){//LEFT
        i=rec.left;
        j=rec.top;
        res=getTopleft(i,j);
        if(res.second*CellSize+CellSize-j>=0.5){
            t=marioMap->m[res.first][res.second].type;
            if(t!=Empty){//找到冲突 冲突宽度足够大的时候

                return t;
            }
        }
        i=rec.left;
        j=rec.top+CellSize;
        res=getTopleft(i,j);
        if(j-res.second*CellSize>=0.5){
            t=marioMap->m[res.first][res.second].type;
            if(t!=Empty){//找到冲突 冲突宽度足够大的时候

                return t;
            }
        }
    }else if(direct==3){//RIGHT
        i=rec.left+CellSize;
        j=rec.top;
        res=getTopleft(i,j);
        if(res.second*CellSize+CellSize-j>=0.5){
            t=marioMap->m[res.first][res.second].type;
            if(t!=Empty){//找到冲突 冲突宽度足够大的时候

                return t;
            }
        }
        i=rec.left+CellSize;
        j=rec.top+CellSize;
        res=getTopleft(i,j);
        if(j-res.second*CellSize>=0.5){
            t=marioMap->m[res.first][res.second].type;
            if(t!=Empty){//找到冲突 冲突宽度足够大的时候

                return t;
            }
        }
    }
    return Empty;
}
void Mario::print(string str,vector<int> v){
    if(timer2>1){
        cout<<str<<"  ";
        for(auto it:v){
            cout<<it<<" ";
        }
        cout<<endl;
    }
}
