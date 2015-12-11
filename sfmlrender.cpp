
#include <SFML/Graphics.hpp>

#include "sfmlrender.h"

sf::Vector2f convert(const Vector2D & rhs)
{
	return sf::Vector2f(rhs.x, rhs.y);
}

void SfmlRender::init()
{
	const int multiplier = 400;
	const int gameWidth = 2;
	const int gameHeight = 1;
	const double playerHeight = 0.2;
	sf::Vector2f playerSize { 5., float(playerHeight * multiplier) };
	const float ballRadius = 0.05;
	const double netHeight = 0.5;
	
	// Create the window of the application
	window = new sf::RenderWindow(sf::VideoMode(gameWidth, gameHeight, 32), "Valleyball",
		sf::Style::Titlebar | sf::Style::Close);
	window->setVerticalSyncEnabled(true);

	// Setting up Mamager
	mgr = &(Manager::getSingleton());
	mgr->setStep(1.0 / 60.0);
	
	// To begin with, we need Players
	mgr->addPlayer("SamThePlayer", "left").init(Vector2D(-1.0), Vector2D(), 0.2, 1.0, 1.0, 0.5);
	mgr->addPlayer("SamThePlayer", "right").init(Vector2D(), Vector2D(1.0), 0.2, 1.0, 1.0, 0.5);
	
	// Next, the environment is required
	mgr->addBlock("leftPlate", "left") = Block(Vector2D(-1.0), Vector2D());
	mgr->addBlock("rightPlate", "right") = Block(Vector2D(), Vector2D(1.0));
	mgr->addNet("lwall") = Block(-1.0, 0.0, -1.0, 1.0);
	mgr->addNet("rwall") = Block( 1.0, 0.0,  1.0, 1.0);
	mgr->addNet("twall") = Block(-1.0, 1.0,  1.0, 1.0);
	mgr->addNet("net")   = Block( 0.0, 0.0,  0.0, netHeight);

	// Lastly, the Ball is added
	bll = 
		&(mgr->addBall("ball") = Ball(
				Vector2D(-1.0, 0.0), 
				Vector2D(1.0, 1.0), 
				Vector2D(-0.5, 0.7), 
				Vector2D())
		); // TODO: Ball initialization

	// Symblinking players
	lplr = &(mgr->getPlayer("left"));
	rplr = &(mgr->getPlayer("right"));

	//================================= Render mirrors
	
	// Create the left paddle
	leftPlayer.setSize(playerSize);
	leftPlayer.setOutlineThickness(1);
	leftPlayer.setOutlineColor(sf::Color::Black);
	leftPlayer.setFillColor(sf::Color(100, 100, 200));
	leftPlayer.setOrigin(multiplier * playerHeight, playerSize.x / 2.f);

	// Create the right paddle
	rightPlayer.setSize(playerSize);
	rightPlayer.setOutlineThickness(1);
	rightPlayer.setOutlineColor(sf::Color::Black);
	rightPlayer.setFillColor(sf::Color(200, 100, 100));
	rightPlayer.setOrigin(multiplier * playerHeight, playerSize.x / 2.f);

	// Create the ball
	ballRenderable.setRadius(ballRadius);
	ballRenderable.setOutlineThickness(1);
	ballRenderable.setOutlineColor(sf::Color::Black);
	ballRenderable.setFillColor(sf::Color::White);
	ballRenderable.setOrigin(sf::Vector2f(ballRadius, ballRadius) * float(multiplier / 2));

	// Load the text font
	sf::Font font;
	if (!font.loadFromFile("resources/sansation.ttf")) // TODO: chose the correct font.
		exit(EXIT_FAILURE);
	pauseMessage.setFont(font);
	pauseMessage.setCharacterSize(40);
	pauseMessage.setPosition(170.f, 150.f);
	pauseMessage.setColor(sf::Color::White);
	pauseMessage.setString("PAUSED");

	// prepare the background.
	sf::RectangleShape net(sf::Vector2f(2, float(multiplier * netHeight)));
	net.setOrigin(1, net.getSize().y);
	net.setPosition(multiplier, 0);
	net.setFillColor(sf::Color::Yellow);
	sf::RenderTexture tempTexture;
	tempTexture.draw(net);
	tempTexture.display();
	bg.setTexture(tempTexture.getTexture());
}

void SfmlRender::start()
{
	// This is main loop enterance
	clock.restart();

	while (window->isOpen()) {
		beforeUpdate();
		update();
		afterUpdate();
	}
	stop();
}

void SfmlRender::beforeUpdate()
{
	// Handle events
	sf::Event event;
	while (window->pollEvent(event)) {
		// Window closed or escape key pressed: exit
		if (event.type == sf::Event::Closed) {
			window->close();
			break;
		}

		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Escape) {
				window->close();
				break;
			} else if (event.key.code == sf::Keyboard::Space) {
				if (isPaused) clock.restart();
				isPaused = !isPaused;
			}
		
		}
	}

        // Clear the window
        window->clear(sf::Color(50, 50, 50));
	window->draw(bg);
}

void SfmlRender::update()
{
	if (isPaused)
		return;
	sf::Time t = clock.restart();
	mgr->setStep(t.asSeconds());
	mgr->nextFrame();
	leftPlayer.setSize(convert(lplr->get_pos()));
	rightPlayer.setSize(convert(rplr->get_pos()));
	ballRenderable.setPosition(convert(bll->get_pos()));
}

void SfmlRender::afterUpdate()
{
        if (isPaused) {
        	window->draw(pauseMessage);
	} else {
		// Draw the paddles and the ball
		window->draw(leftPlayer);
		window->draw(rightPlayer);
		window->draw(ballRenderable);
        }

        // Display things on screen
	window->display();
}

void SfmlRender::stop()
{
	delete window;
	window = nullptr;
}

void Block::draw() const {}
// Ok. I'm starting to think, that we don't need this intrface.
// But for now, I will not throw it out. May be it will be useful 
// with something like OpenGL.

#ifdef DEBUG
int main()
{
	SfmlRender rndr;
	rndr.init();
	rndr.start();
	return EXIT_SUCCESS;
}
#endif

