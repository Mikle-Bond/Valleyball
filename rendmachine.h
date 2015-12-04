#ifndef RENDER_MACHINE_H
#define RENDER_MACHINE_H

#include "renderinterface.h"
#include "manager.h"

class RenderMachine
{
public:
	virtual void init();
	virtual void start();
	virtual void beforeUpdate();
	virtual void update();
	virtual void afterUpdate();
	virtual void stop();
	virtual ~RenderMachine() = 0;
};

#endif // RENDER_MACHINE_H

