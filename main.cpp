#include<iostream>
#include"Headers/Mario.h"
#include"Headers/Global.h"
#include"Headers/MapDesigner.h"
using namespace std;
using namespace sf;

int main(){
    cout<<"1: start"<<endl;
    cout<<"2: map designer"<<endl;
    int opt;
    cin>>opt;
    if(opt==1){
        RenderWindow window(VideoMode(ScreenWidth*ZoomSize,ScreenHeight*ZoomSize),"SuperMario");
        View view;
        Mario mario(window,view);
        view.setCenter(ScreenWidth/2,ScreenHeight/2);
        view.setSize(ScreenWidth,ScreenHeight);
        view.move(0,-10);
        Clock clock;
        float timer=0;
        Clock c;
        float t=0;
        while(window.isOpen()){
            timer+=clock.getElapsedTime().asSeconds();
            clock.restart();
            Event e;
            while(window.pollEvent(e)){
                switch(e.type){
                    case Event::Closed:
                        window.close();
                        break;
                }
            }

            if(timer>=0.015){
                timer=0;
                mario.update();
                window.clear(Color::Blue);
                mario.draw();
                window.setView(view);
                window.display();
            }
        }
    }else if(opt==2){
        MapDesigner md;
        md.start();
    }
    return 0;
}