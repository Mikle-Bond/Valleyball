#include "textrender.h"
#include <iostream>

#ifdef DEBUG
#include "sam.h"
#include "dan.h"
#include "manager.h"
#include <stdexcept>
#include <string>
#endif // DEBUG


static const Ball * bll = nullptr;
static const Player * lplr = nullptr;
static const Player * rplr = nullptr;

void RenderInterface::draw() const
{

}

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
	mgr->addPlayer("left", "DanThePlayer").init(Vector2D(-1.0), Vector2D(), 0.2, 0.05, 0.5, 0.5);
	mgr->addPlayer("right", "SamThePlayer").init(Vector2D(), Vector2D(1.0), 0.2, 0.05, 0.5, 0.5);
	mgr->addBlock("leftPlate", "left") = Block(Vector2D(-1.0), Vector2D());
	mgr->addBlock("rightPlate", "right") = Block(Vector2D(), Vector2D(1.0));
	mgr->addNet("lwall") = Block(-1.0, 0.0, -1.0, 1.0);
	mgr->addNet("rwall") = Block( 1.0, 0.0,  1.0, 1.0);
	mgr->addNet("twall") = Block(-1.0, 1.0,  1.0, 1.0);
	mgr->addNet("net")   = Block( 0.0, 0.0,  0.0, 0.5);
	bll = 
		&(mgr->addBall("ball") = Ball(
				Vector2D(-1.0, 0.0), 
				Vector2D(1.0, 1.0), 
				Vector2D(-0.5, 0.5),
				Vector2D())
		); // TODO: Ball initialization
	// bll = &(mgr->addBall("ball") = Ball()); // TODO: Ball initialization
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
		<< "\tright: " << rplr->Movable::get_pos().x
		<< "\tball: ( " << bll->get_pos().x << ", " << bll->get_pos().y << " )"
		<< std::endl;
}

void TextRender::afterUpdate()
{
	typedef Manager::Status St;
	Manager::State const & st = Manager::getState();
	switch(st.currentStatus) {
	case St::OK:
		std::cout << "Stats is [ OK ]" << std::endl;
		break;
	case St::ATTACK:
		std::cout << *(st.playerName) << " player pushed ball" << std::endl;
		break;
	default:
		// Do nithing
		break;
	}
}

void TextRender::stop()
{
    Manager::State const & st = Manager::getState();
	std::cout << "Game Over. The " 
		<< (st.playerName ? *(st.playerName) : "[not defined]") 
		<< " wasn't able to prevent " 
		<< (st.ballName ? *(st.ballName) : "[not defined]")
		<< " to touch the "
		<< (st.blockName ? *(st.blockName) : "[not defined]")
		<< "." << std::endl;
}
/*
void Block::draw() const
{

}

void SamThePlayer::draw() const
{

}
*/
/*
void Ball::draw() const
{

}
*/
#ifdef DEBUG
int main ()
{
    try {
        TextRender tr;
        tr.init();
        tr.start();
    } catch(std::logic_error & e) {
        std::cerr << "Error occured: " << e.what() << std::endl;
    }

	return 0;
}
#endif

