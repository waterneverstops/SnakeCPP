#include <SFML/Graphics.hpp>
#include <time.h>
#include "snake.cpp"
#include "fruct.cpp"

int mapWidth = 20;
int mapHeight = 20;
int size = 32;
int windowWidth = size * mapWidth;
int windowHeight = size * mapHeight;

std::string texturePath = "images/texture.jpg";

int dir = 0;
int num = 4;
Snake snake[100];
Fruct fruct;

void drawMap(sf::RenderWindow& window, sf::Sprite& sprite);

void drawSnake(sf::RenderWindow& window, sf::Sprite& sprite);

void drawFruct(sf::RenderWindow& window, sf::Sprite& sprite);

void randomFruct();

void Tick();

int main()
{
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SSSsssnake");

	sf::Texture texture;
	texture.loadFromFile(texturePath);

	sf::Sprite spriteMap(texture);
	sf::Sprite spriteSnake(texture);
	sf::Sprite spriteApple(texture);

	spriteMap.setTextureRect(sf::IntRect(0, 0, 32, 32));
	spriteSnake.setTextureRect(sf::IntRect(32, 0, 32, 32));
	spriteApple.setTextureRect(sf::IntRect(64, 0, 32, 32));

	sf::Clock clock;
	float timer = 0;
	float delay = 0.1;

	randomFruct();

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && dir != 0) { dir = 2; }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && dir != 2) { dir = 0; }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && dir != 3) { dir = 1; }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && dir != 1) { dir = 3; }

		if (timer > delay)
		{
			timer = 0;
			Tick();
		}

		window.clear();
		drawMap(window, spriteMap);
		drawSnake(window, spriteSnake);
		drawFruct(window, spriteApple);
		window.display();
	}

	return 0;
}

void drawMap(sf::RenderWindow& window, sf::Sprite& sprite)
{
	for (int i = 0; i < mapHeight; i++)
	{
		for (int k = 0; k < mapWidth; k++)
		{
			sprite.setPosition(i * size, k * size);
			window.draw(sprite);
		}
	}
}

void drawSnake(sf::RenderWindow& window, sf::Sprite& sprite)
{
	for (int i = 0; i < num; i++)
	{
		sprite.setPosition(snake[i].x * size, snake[i].y * size);
		window.draw(sprite);
	}
}

void drawFruct(sf::RenderWindow& window, sf::Sprite& sprite)
{
	sprite.setPosition(fruct.x * size, fruct.y * size);
	window.draw(sprite);
}

void randomFruct()
{
	fruct.x = rand() % mapWidth;
	fruct.y = rand() % mapHeight;
}

void Tick()
{
	for (int i = num; i > 0; --i)
	{
		snake[i].x = snake[i - 1].x;
		snake[i].y = snake[i - 1].y;
	}

	if (dir == 0) { snake[0].x += 1; }
	if (dir == 1) { snake[0].y -= 1; }
	if (dir == 2) { snake[0].x -= 1; }
	if (dir == 3) { snake[0].y += 1; }

	if ((snake[0].x == fruct.x) && (snake[0].y == fruct.y))
	{
		num++;
		randomFruct();
	}

	if (snake[0].x > mapWidth) { snake[0].x = 0; }
	if (snake[0].y > mapHeight) { snake[0].y = 0; }

	if (snake[0].x < 0) { snake[0].x = mapWidth; }
	if (snake[0].y < 0) { snake[0].y = mapHeight; }

	for (int i = 1; i < num; i++)
	{
		if ((snake[0].x == snake[i].x) && (snake[0].y == snake[i].y))
		{
			dir = 3;
			num = 4;
			snake[0].x = 0;
			snake[0].y = 0;
		}
	}
}