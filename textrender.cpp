#include "textrender.h"
#include <iostream>

const Ball * bll = nullptr;
const Player * lplr = nullptr;
const Player * rplr = nullptr;

TextRender::TextRender()
{

}

TextRender::~TextRender()
{

}

void TextRender::init()
{
	mgr = &(Manager::getSingleton());
	mgr->setStep(1.0 / 60.0);
	mgr->addPlayer("SamThePlayer", "left").init(Vector2D(-1.0), Vector2D(), 0.2, 1.0, 1.0, 0.5);
	mgr->addPlayer("SamThePlayer", "right").init(Vector2D(), Vector2D(1.0), 0.2, 1.0, 1.0, 0.5);
	mgr->addBlock("leftPlate", "left") = Block(Vector2D(-1.0), Vector2D());
	mgr->addBlock("rightPlate", "right") = Block(Vector2D(), Vector2D(1.0));
	mgr->addNet("lwall") = Block(-1.0, 0.0, -1.0, 1.0);
	mgr->addNet("rwall") = Block( 1.0, 0.0,  1.0, 1.0);
	mgr->addNet("twall") = Block(-1.0, 1.0,  1.0, 1.0);
	mgr->addNet("net")   = Block( 0.0, 0.0,  0.0, 0.5);
	bll = &(mgr->addBall("ball") = Ball()); // TODO: Ball initialization
	lplr = &(mgr->getPlayer("left"));
	rplr = &(mgr->getPlayer("right"));
}

void TextRender::start()
{
	RenderMachine::start();
}

void TextRender::beforeUpdate()
{

}

void TextRender::update()
{
	mgr->nextFrame();
	std::cout 
		<< "left: " << lplr->get_pos().x
		<< " right: " << rplr->Movable::get_pos().x
		<< " ball: ( " << bll->get_x() << ", " << bll->get_y() << " )"
		<< std::endl;
}

void TextRender::afterUpdate()
{

}

void TextRender::stop()
{
	Manager::State st = Manager::getState();
	std::cout << "Game Over. The " 
		<< *(st.playerName) 
		<< " wasn't able to prevent " 
		<< *(st.ballName)
		<< " to touch the "
		<< *(st.blockName)
		<< "." << std::endl;
}

void Block::draw() const
{

}

void Ball::draw() const
{

}

#ifdef DEBUG
int main ()
{
	TextRender tr;
	tr.init();
	tr.start();
	return 0;
}
#endif

