//librarie
#include <SFML/Graphics.hpp>
#include <stdlib.h>

//tabla de joc
int table[30][20];

int main()
{
	//ceva variabile
	int i, j, dir = 1, ok, lung = 3, bumbisor = 0, game_over=0, anterior;

	//dimensiunea ferestrei
	sf::RenderWindow window(sf::VideoMode(960, 640), "Snake"/*, sf::Style::Fullscreen*/);
	
	//"viteza jocului"
	window.setFramerateLimit(10);

	//texturile
	sf::Texture texture1;
	if (!texture1.loadFromFile("sprites/red.png"))
	{
		// error...
	}
	
	sf::Texture texture2;
	if (!texture2.loadFromFile("sprites/green.png"))
	{
		// error...
	}
	sf::Texture texture0;
	if (!texture0.loadFromFile("sprites/white.png"))
	{
		//error...
	}
	sf::Texture texture3;
	if (!texture3.loadFromFile("sprites/game_over.png"))
	{
		//error...
	}
	
	//sprite-urile
	sf::Sprite sprite1, sprite2, sprite0, sprite3;
	sprite1.setTexture(texture1);
	sprite2.setTexture(texture2);
	sprite0.setTexture(texture0);
	sprite3.setTexture(texture3);

	//pozitia de start
	table[8][10] = 3;
	table[9][10] = 2;
	table[10][10] = 1;

	//jocul in sine
	while (window.isOpen())
	{
		//bla bla
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//culoarea tablei
		window.clear(sf::Color::White);


		if (game_over == 0)
		{
			//marim fiecare numar din matrice pt stii tu ce
			for (i = 0; i < 30; i++)
				for (j = 0; j < 20; j++)
					if (table[i][j] != 0 && table[i][j] != -1 && table[i][j] != lung)
						table[i][j]++;
					else if (table[i][j] == lung)
						table[i][j] = 0;

			//verifica daca exista bumbisor
			if (bumbisor == 0)
			{
				bumbisor = 1;
				i = rand() % 30;
				j = rand() % 20;
				while (table[i][j] != 0)
				{
					i = rand() % 30;
					j = rand() % 20;
				}
				table[i][j] = -1;
			}

			//aflarea directiei
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && dir != 3)
				dir = 1;
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && dir != 4)
				dir = 2;
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && dir != 1)
				dir = 3;
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && dir != 2)
				dir = 4;


			//directia
			i = 0; ok = 1;
			while (i < 30 && ok == 1)
			{
				j = 0;
				while (j < 20 && ok == 1)
				{
					if (table[i][j] == 2)
					{
						ok = 0;
						switch (dir)
						{
						case 1:
							//mers stanga
							if (i != 29)
							{
								anterior = table[i + 1][j];
								table[i + 1][j] = 1;
							}
							else
							{
								anterior = table[0][j];
								table[0][j] = 1;
							}
							break;
						case 2:
							//mers sus
							if (j != 0)
							{
								anterior = table[i][j - 1];
								table[i][j - 1] = 1;
							}
							else
							{
								anterior = table[i][19];
								table[i][19] = 1;
							}
							break;
						case 3:
							//mers dreapta
							if (i != 0)
							{
								anterior = table[i - 1][j];
								table[i - 1][j] = 1;
							}
							else
							{
								anterior = table[29][j];
								table[29][j] = 1;
							}
							break;
						case 4:
							//mers jos
							if (j != 19)
							{
								anterior = table[i][j + 1];
								table[i][j + 1] = 1;
							}
							else
							{
								anterior = table[i][0];
								table[i][0] = 1;
							}
							break;
						}
					}
					j++;
				}
				i++;
			}

			//verifica ce a fost inainte
			if (anterior == -1)	//verif bumbisor
			{
				lung++;
				bumbisor = 0;
			}
			else if (anterior > 0)	//verif game_over
				game_over = 1;
		}
		else	//game over
		{
			game_over++;
		}
		//afisarea pozitilor sarpelui, bumbisorului si game over
		for (i = 0; i<30; i++)
			for (j = 0; j < 20; j++)
			{
				//afis alb
				if (table[i][j] == 0)
				{
					sprite0.setPosition(sf::Vector2f((i * 32), (j * 32)));
					window.draw(sprite0);
				}
				//afis rosu
				else if (table[i][j] > 0)
				{
					sprite1.setPosition(sf::Vector2f((i * 32), (j * 32)));
					window.draw(sprite1);
				}
				//afis verde
				else if (table[i][j] == -1)
				{
					sprite2.setPosition(sf::Vector2f((i * 32), (j * 32)));
					window.draw(sprite2);

				}
			}
		if (game_over != 0)
		{
			sprite3.setPosition(sf::Vector2f(320, 160));
			window.draw(sprite3);
		}

		//afisarea
		window.display();
		if (game_over == 40)
			window.close();
	}

	return 0;
}