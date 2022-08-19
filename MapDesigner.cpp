#include "Headers/MapDesigner.h"
#include "Headers/Global.h"
#include<fstream>

static vector<Type> EnemyList={Geezer_,Turtle_};
MapDesigner::MapDesigner(){
    cout<<"输入地图文件名字"<<endl;
    cin>>filename;
    loadFiles();
    edge.resize(4);
    rec.setFillColor(Color::Red);
}
void MapDesigner::start(){
    window.create(VideoMode({(ScreenWidth+PanelWidth)*ZoomSize,ScreenHeight*ZoomSize}),"MapDesigner");
    view.setCenter(Vector2f((ScreenWidth+PanelWidth)/2,ScreenHeight/2));
    view.setSize(Vector2f(ScreenWidth+PanelWidth,ScreenHeight));
    window.setView(view);
    Clock clock;
    float frameTimer=0;
    while(window.isOpen()){
        timer+=clock.getElapsedTime().asSeconds();
        frameTimer+=clock.getElapsedTime().asSeconds();
        if(timer>1.1){
            timer-=1.1;
            //cout<<view.getCenter().x<<" "<<view.getCenter().y<<endl;
            //cout<<"loop"<<endl;
        }
        clock.restart();
        Event e;
        while(window.pollEvent(e)){
            switch(e.type){
            case Event::Closed:
                close();
                break;
            }
        }
        if(frameTimer>0.0125){
            frameTimer-=0.0125;
            if(Mouse::isButtonPressed(Mouse::Left)){
                click();
            }
            window.clear(Color(108,67,58));
            draw();
            window.display();
        }
    }
}
void MapDesigner::draw(){
    window.setView(view);
    drawLines();
    drawTools();
    drawMap();
}
void MapDesigner::drawMap(){
    sprite.setTexture(brick_pic,true);
    // for(auto &it:m){
    //     sprite.setTextureRect(IntRect(it.second.first*CellSize,it.second.second*CellSize,CellSize,CellSize));
    //     sprite.setPosition(Vector2f(it.first.first*CellSize,it.first.second*CellSize));
    //     window.draw(sprite);
    // }
    for(auto &it:m){
        if(it.second.type==Brick_){
            sprite.setTexture(brick_pic,true);
            sprite.setTextureRect(IntRect(it.second.x*CellSize,it.second.y*CellSize,CellSize,CellSize));
            sprite.setPosition(Vector2f(it.first.first*CellSize,it.first.second*CellSize));
            window.draw(sprite);
        }else if(it.second.type==Geezer_){
            sprite.setTexture(enemy_pic,true);
            sprite.setTextureRect(IntRect(it.second.x*CellSize,it.second.y*CellSize,CellSize,CellSize));
            sprite.setPosition(Vector2f(it.first.first*CellSize,it.first.second*CellSize));
            window.draw(sprite);
        }else if(it.second.type==Turtle_){
            sprite.setTexture(GenTexture::getTexture("Turtle.png"),true);
            sprite.setTextureRect(IntRect(it.second.x*CellSize,it.second.y*CellSize,TurtleWidth,TurtleHeight));
            sprite.setPosition(Vector2f(it.first.first*CellSize,it.first.second*CellSize-TurtleHeight+CellSize));
            window.draw(sprite);
        }
    }
}
void MapDesigner::drawLines(){
    //int x=offset/CellSize;
    VertexArray line(LineStrip,2);
    line[0].color=Color(58,108,74);
    line[0].position={Vector2f(ScreenWidth+offset,0)};
    line[1].position={Vector2f(ScreenWidth+offset,ScreenHeight)};
    window.draw(line);
    line[0].color=Color(239,0,255);
    for(int i=0;i<ScreenHeight/CellSize+1;i++){
        line[0].position={Vector2f(offset,i*CellSize)};
        line[1].position={Vector2f(ScreenWidth+offset,i*CellSize)};
        window.draw(line);
    }
    int x=offset/CellSize;
    for(int i=x;i<x+ScreenWidth/CellSize+1;i++){
        line[0].position={Vector2f(i*CellSize,0)};
        line[1].position={Vector2f(i*CellSize,ScreenHeight)};
        window.draw(line);
    }
}
void MapDesigner::drawTools(){
    sprite.setTexture(brick_pic,true);
    for(int i=0;i<8;i++){
        for(int j=0;j<2;j++){
            int h=min((i*2+j)/3,4);
            int w=(i*2+j)%3;
            sprite.setTextureRect(IntRect(w*CellSize,h*CellSize,CellSize,CellSize));
            sprite.setPosition(Vector2f(325+j*(CellSize+gap)+offset,16+i*(CellSize+gap)));
            bricks.insert({pair<int,int>{325+j*(CellSize+gap),16+i*(CellSize+gap)},pair<int,int>{w,h}});
            window.draw(sprite);
        }
    }
    for(int i=0;i<EnemyList.size();i++){
        if(EnemyList[i]==Geezer_){
            sprite.setTexture(GenTexture::getTexture("Geezer.png"),true);
            sprite.setTextureRect(IntRect(0,0,CellSize,CellSize));
            sprite.setPosition(Vector2f(325+(CellSize+gap)*2+offset,16+i*(CellSize+gap)));
            enemys.insert({pair<int,int>{325+(CellSize+gap)*2,16+i*(CellSize+gap)},Cell(0,0,Geezer_)});
            window.draw(sprite);
        }else if(EnemyList[i]==Turtle_){
            sprite.setTexture(GenTexture::getTexture("Turtle.png"),true);
            sprite.setTextureRect(IntRect(0,0,TurtleWidth,TurtleHeight));
            sprite.setPosition(Vector2f(325+(CellSize+gap)*2+offset,16+i*(CellSize+gap)));
            enemys.insert({pair<int,int>{325+(CellSize+gap)*2,16+i*(CellSize+gap)},Cell(0,0,Turtle_)});
            window.draw(sprite);
        }
    }
    if(tool){
        for(int i=0;i<4;i++){
            rec.setPosition(Vector2f(edge[i][0]+offset,edge[i][1]));
            rec.setSize(Vector2f(edge[i][2],edge[i][3]));
            window.draw(rec);
        }
    }
    sprite.setTexture(arrow_pic,true);
    sprite.setPosition(Vector2f(325+offset,20+8*(CellSize+gap)));
    window.draw(sprite);
    sprite.setTextureRect(IntRect(16,0,-16,16));
    sprite.setPosition(Vector2f(325+CellSize+gap+offset,20+8*(CellSize+gap)));
    window.draw(sprite);
}
void MapDesigner::loadFiles(){
    if(!brick_pic.loadFromFile("Resource/brick.png")){
        cout<<"error"<<endl;
    }
    if(!arrow_pic.loadFromFile("Resource/arrow.png")){
        cout<<"error"<<endl;
    }
    if(!enemy_pic.loadFromFile("Resource/Geezer.png")){
        cout<<"error"<<endl;
    }
}
int MapDesigner::checkClick(int x,int y,Point& p){
    x-=offset;
    int left=x/CellSize;
    int top=y/CellSize;
    int res=5;
    if(left<20&&top<15){
        p={(x+offset)/CellSize,top};
        res=1;
    }
    for(auto& it:bricks){
        if(x>=it.first.first&&x<=it.first.first+CellSize&&y>=it.first.second&&y<=it.first.second+CellSize){
            edge[0]={it.first.first-2,it.first.second-2,2,CellSize+4};
            edge[1]={it.first.first-2,it.first.second-2,CellSize+4,2};
            edge[2]={it.first.first+CellSize,it.first.second-2,2,CellSize+4};
            edge[3]={it.first.first-2,it.first.second+CellSize,CellSize+4,2};
            p={it.second.first,it.second.second,Brick_};
            res=2;
        }
    }
    for(auto& it:enemys){
        if(x>=it.first.first&&x<=it.first.first+CellSize&&y>=it.first.second&&y<=it.first.second+CellSize){
            edge[0]={it.first.first-2,it.first.second-2,2,CellSize+4};
            edge[1]={it.first.first-2,it.first.second-2,CellSize+4,2};
            edge[2]={it.first.first+CellSize,it.first.second-2,2,CellSize+4};
            edge[3]={it.first.first-2,it.first.second+CellSize,CellSize+4,2};
            p={it.second.x,it.second.x,it.second.type};
            res=2;
        }
    }
    if(x>=325&&x<=325+CellSize&&y>=20+8*(CellSize+gap)&&y<=20+8*(CellSize+gap)+CellSize){
        res=3;
    }
    if(x>=325+CellSize+gap&&x<=325+2*CellSize+gap&&y>=20+8*(CellSize+gap)&&y<=20+8*(CellSize+gap)+CellSize){
        res=4;
    }
    return res;
}
void MapDesigner::click(){
    Vector2f pos=window.mapPixelToCoords(Vector2i(Mouse::getPosition(window).x,Mouse::getPosition(window).y));
    int x=pos.x;
    int y=pos.y;

    Point p;
    //auto pos=getTopLeft(x,y);
    int res=checkClick(x,y,p);
    if(res==1){
        if(tool){
            m[{p.x,p.y}]=toolPos;//向地图中加入各种材质
        }else{
            m.erase({p.x,p.y});
        }
    }else if(res==2){
        tool=true;
        toolPos=p;
    }else if(res==3){
        if(offset>0){
            offset-=1;
            view.move(Vector2f(-1,0));
        }
    }else if(res==4){
        offset+=1;
        view.move(Vector2f(1,0));
    }else{
        tool=false;
    }
}
pair<int,int> getTopLeft(int x,int y){
    return {x/CellSize,y/CellSize};
}
void MapDesigner::close(){
    ofstream ofs("MapResource/"+filename+".txt");
    // for(auto& it:m){
    //     ofs<<it.first.first<<" ";
    //     ofs<<it.first.second<<" ";
    //     ofs<<it.second.first<<" ";
    //     ofs<<it.second.second<<endl;
    // }
    for(auto& it:m){
        ofs<<it.first.first<<" ";
        ofs<<it.first.second<<" ";
        ofs<<it.second.x<<" ";
        ofs<<it.second.y<<" ";
        ofs<<it.second.type<<endl;
    }
    ofs.close();
    window.close();
}