#include"Headers/Mario.h"
#include<math.h>
#include"Headers/Brick.h"
#include"Headers/Geezer.h"
#include"Headers/Bullet.h"

Mario::Mario(RenderWindow& wind,View& view):window(wind),view(view){
    loadResource();
    marioMap=new Map(window,*this);
    marioMap->init();
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
    dead_pic.loadFromFile("./Resource/dead.png");
}
void Mario::draw(){
    marioMap->draw();
    for(auto& it:bullets){
        it->draw();
    }
    window.draw(sprite);
}
void Mario::update(){
    dx=0;
    dy=0;
    timer2+=clock.getElapsedTime().asSeconds();
    clock.restart();
    pos=sprite.getPosition();
    //print("pos.y",{int(pos.y)});
    //print("ground",{ground});
    if(!ground){
        vspeed=min(vspeed+Gravity,MaxVSpeed);
    }

    switch(state){
        case ALIVE:{
            alive();
            break;
        }
        case DEAD:{
            dead();
            break;
        }
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
void Mario::startDead(){
    sprite.setTexture(dead_pic,true);
    sprite.setTextureRect(IntRect(0,0,16,16));
    ground=false;
    hspeed=0;
    vspeed=-JumpSpeed;//开始跳
    deadTimer=DeadTime;//死亡帧数计数器开始
    state=DEAD;
}
void Mario::dead(){
    if(deadTimer>0){
        deadTimer--;
        sprite.setPosition(Vector2f(sprite.getPosition().x,sprite.getPosition().y+vspeed));
    }else{
        cout<<"dead finish"<<endl;
        sleep(seconds(0.2));
        startAlive();
    }
}
void Mario::startAlive(){
    sprite.setTexture(person_pic,true);
    sprite.setTextureRect(IntRect(0,0,PersonWidth,PersonHeight));
    state=ALIVE;
    sprite.setPosition({10,10});
    vspeed=0;
    hspeed=0;
}
void Mario::fire(){//发射子弹
    cout<<"fire"<<endl;
    shared_ptr<Bullet> bullet(new Bullet());
    bullet->setProperty(this,marioMap,&window);
    if(hspeed<0){
        bullet->hspeed*=-1;
        bullet->setPos(pos.x,pos.y);
    }else{
        bullet->setPos(pos.x+CellSize,pos.y);
    }
    bullets.push_back(bullet);
}
void Mario::alive(){
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
            hspeed=max(hspeed-Acc,0.0f);
        }else if(hspeed<0){
            hspeed=min(hspeed+Acc,0.0f);
        }
        stand();
    }

    ground=false;
    marioMap->update();
    for(auto& it:bullets){
        it->update();
    }
    
    sprite.setPosition(Vector2f(pos.x+hspeed,pos.y+vspeed));
    if(sprite.getPosition().y>208){
        cout<<"hello"<<endl;
    }
    if(sprite.getPosition().x<0){//边缘检测
        sprite.move(Vector2f(-sprite.getPosition().x,0));
    }

    if(sprite.getPosition().x+hspeed>=0){//镜头移动
        sprite.setPosition(sprite.getPosition().x+hspeed,sprite.getPosition().y);
        if(sprite.getPosition().x>ScreenWidth/2){
            view.setCenter(sprite.getPosition().x,view.getCenter().y);
        }else{
            view.setCenter(ScreenWidth/2,view.getCenter().y);
        }
    }
    if(sprite.getPosition().y>=ScreenHeight){//高度死亡检测
        cout<<"death"<<endl;
        startDead();
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

    if(Keyboard::isKeyPressed(Keyboard::Enter)){
        if(fireDua--==0){
            fireDua=FireDuration;
            fire();
        }
    }else{
        fireDua=0;
    }
}
