#include "rendmachine.h"

RenderInterface::~RenderInterface()
{

}

RenderMachine::~RenderMachine()
{

}

void RenderMachine::init()
{
	Manager::getSingleton();
}

void RenderMachine::start()
{
	while (Manager::getState().currentStatus != Manager::Status::GAME_OVER) {
		beforeUpdate();
		update();
		afterUpdate();
	}
	stop();
}

void RenderMachine::beforeUpdate()
{
	
}

void RenderMachine::update()
{
	Manager::getSingleton().nextFrame();
}

void RenderMachine::afterUpdate()
{
	
}

void RenderMachine::stop()
{
	Manager::resetSingleton();
}


