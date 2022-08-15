#include"Headers/Mario.h"
#include<math.h>
#include"Headers/Brick.h"

Mario::Mario(RenderWindow& wind,View& view):window(wind),view(view){
    loadResource();
    marioMap=shared_ptr<Map>(new Map(window));
    for(int i=0;i<marioMap->m.size();i++){
        for(int j=0;j<ScreenHeight/CellSize;j++){
            if(marioMap->m[i][j].type!=Empty){//每个砖块都是一个对象
                marioMap->m[i][j].brick=shared_ptr<Brick>(new Brick(*this,*marioMap));
                marioMap->m[i][j].brick->setPos(i,j);
            }//初始化地图里面的对象
        }
    }
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
    ground_pic.loadFromFile("./Resource/brick.png");
}
void Mario::draw(){
    marioMap->draw();
    window.draw(sprite);
}
void Mario::update(){
    dx=0;
    dy=0;
    timer2+=clock.getElapsedTime().asSeconds();
    clock.restart();
    Vector2f pos=sprite.getPosition();
    print("pos.y",{int(pos.y),checkCollision(IntRect(pos.x,pos.y+vspeed,CellSize,CellSize)),checkCollision(IntRect(pos.x,pos.y+vspeed,CellSize,CellSize),false)});
    print("ground",{ground});
    if(!ground){
        vspeed=min(vspeed+Gravity,MaxVSpeed);
    }

    if(Keyboard::isKeyPressed(Keyboard::D)){
        if(hspeed<0){
            hspeed=hspeed+Acc;
        }else{
            hspeed=min(hspeed+Acc,MaxHSpeed);
        }
        walkAnimation();
    
    }else if(Keyboard::isKeyPressed(Keyboard::A)){
        if(hspeed>0){
            hspeed=hspeed-Acc;
        }else{
            hspeed=max(hspeed-Acc,-MaxHSpeed);
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

    bool flag=false;
    ground=false;
    for(int i=0;i<marioMap->m.size();i++){
        for(int j=0;j<ScreenHeight/CellSize;j++){
            if(marioMap->m[i][j].type!=Empty){
                marioMap->m[i][j].brick->update();
                if(dx!=0||dy!=0){
                    sprite.setPosition(Vector2f(pos.x+dx,pos.y+dy));
                    pos.x+=dx;
                    pos.y+=dy;
                }
            }
        }
    }
    sprite.setPosition(Vector2f(pos.x+hspeed,pos.y+vspeed));

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
        if(res.second*CellSize+CellSize-j>=CollisionHeight){
            t=marioMap->m[res.first][res.second].type;
            if(t!=Empty){//找到冲突 冲突宽度足够大的时候

                return t;
            }
        }
        i=rec.left;
        j=rec.top+CellSize;
        res=getTopleft(i,j);
        if(j-res.second*CellSize>=CollisionHeight){
            t=marioMap->m[res.first][res.second].type;
            if(t!=Empty){//找到冲突 冲突宽度足够大的时候

                return t;
            }
        }
    }else if(direct==3){//RIGHT
        i=rec.left+CellSize;
        j=rec.top;
        res=getTopleft(i,j);
        if(res.second*CellSize+CellSize-j>=CollisionHeight){
            t=marioMap->m[res.first][res.second].type;
            if(t!=Empty){//找到冲突 冲突宽度足够大的时候

                return t;
            }
        }
        i=rec.left+CellSize;
        j=rec.top+CellSize;
        res=getTopleft(i,j);
        if(j-res.second*CellSize>=CollisionHeight){
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
void Mario::setPosition(float x,float y){
    sprite.setPosition(Vector2f(x,y));
}