#ifndef RENDER_MACHINE_H
#define RENDER_MACHINE_H

#include "renderinterface.h"
#include "manager.h"

class RenderMachine
{
public:
	virtual ~RenderMachine() = 0;
	virtual void init();
	virtual void start();

protected:
	virtual void beforeUpdate();
	virtual void update();
	virtual void afterUpdate();
	virtual void stop();
};

#endif // RENDER_MACHINE_H

