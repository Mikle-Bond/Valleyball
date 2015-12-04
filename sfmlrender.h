#ifndef SFML_RENDER_H
#define SFML_RENDER_H

#include "rendmachine.h"
#include <SFML/Graphics.hpp>

class SfmlRender : public RenderMachine
{
public:
	SfmlRender();
	virtual ~SfmlRender();

	virtual void init();
	virtual void start();

protected:
	virtual void beforeUpdate();
	virtual void update();
	virtual void afterUpdate();
	virtual void stop();

private:
	sf::RenderWindow * window = nullptr;
	const Player * lplr = nullptr;
	const Player * rplr = nullptr;
	const Ball * bll = nullptr;
	Manager * mgr = nullptr;

	bool isPaused = true;

	sf::Sprite bg;
	sf::Clock clock;
	sf::Text pauseMessage;
	sf::RectangleShape leftPlayer;
	sf::RectangleShape rightPlayer;
	sf::CircleShape ballRenderable;

};

#endif // SFML_RENDER_H

