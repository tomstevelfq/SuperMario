#include"Headers/Geezer.h"
Geezer::Geezer(Mario& mario,Map& m,RenderWindow& wind):Entity(mario,m,wind){
    sprite.setTexture(GenTexture::getTexture("Geezer.png"));
    type=Geezer_;
}
void Geezer::update(){//老头的更新函数

}
void Geezer::setPos(int x,int y){
    px=x;
    py=y;
}
void Geezer::draw(){
    sprite.setPosition(Vector2f(px,py));
    window.draw(sprite);
}