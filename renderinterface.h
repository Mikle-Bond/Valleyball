#ifndef RENDER_INTERFACE_H
#define RENDER_INTERFACE_H

// Intrfaces for drawing are used in RenderMachine.
// Their realization is recommended to keep in the separated file.

class RenderInterface
{
public:
	virtual void draw() const = 0;
	virtual ~RenderInterface() = 0;
};

#endif // RENDER_INTERFACE_H

