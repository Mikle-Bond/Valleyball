#ifndef TEXT_RENDER_H
#define TEXT_RENDER_H

#include "rendmachine.h"

class TextRender : public RenderMachine
{
public:
	TextRender();
	virtual ~TextRender();

	virtual void init();
	virtual void start();
	virtual void beforeUpdate();
	virtual void update();
	virtual void afterUpdate();
	virtual void stop();

private:
	Manager * mgr;

};

#endif // TEXT_RENDER_H

