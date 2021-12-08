#include <SFML/Graphics.hpp>

int table[30][20];

int main()
{
	int i, j, k;

	sf::RenderWindow window(sf::VideoMode(960, 640), "Snake");
	
	window.setFramerateLimit(60);

	sf::Texture texture1;
	if (!texture1.loadFromFile("sprites/red.png", sf::IntRect(0, 0, 32, 32)))
	{
		// error...
	}
	
	sf::Texture texture2;
	if (!texture2.loadFromFile("sprites/green.png", sf::IntRect(0, 0, 32, 32)))
	{
		// error...
	}
	
	sf::Sprite sprite1, sprite2;
	sprite1.setTexture(texture1);
	sprite2.setTexture(texture2);

	k = 1;

	while (window.isOpen())
	{
		table[29][19] = 2;
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::White);
		table[k][6] = 1;
		table[k- 1][6] = 0;
		if (k == 29)
			k = 1;
		k++;

		for (i=0; i<30; i++)
			for (j = 0; j < 20; j++)
			{
				if (table[i][j] == 1)
				{
					sprite1.setPosition(sf::Vector2f((i * 32), (j * 32)));
					window.draw(sprite1);
				}
				else if (table[i][j] == 2)
				{
					sprite2.setPosition(sf::Vector2f((i * 32), (j * 32)));
					window.draw(sprite2);

				}
			}

		window.display();
	}

	return 0;
}