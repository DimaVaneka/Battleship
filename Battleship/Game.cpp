#include "Game.h"

using namespace std;
void Game::run()
{
	while (mWindow.isOpen())
	{
		if (gC == gameover)
			break;
		render();
		processEvents();

	}
}
void Game::render()
{
	mWindow.clear(Color::Yellow);//������� ����(������ ���)

	renderPlayer(p1, 1);//��������� ����� ������� ������
	if (menuSelection == twoPlayer)
		renderPlayer(p2, 2);//��������� ����� ������� ������
	else if (menuSelection == onePlayer)
		renderPlayer(pC, 3);
	mWindow.display();
}
void Game::processEvents()
{
	Event event;
	while (mWindow.pollEvent(event))
	{
		if (event.type == Event::Closed || menuSelection == exitGame)
			mWindow.close();//���� ������ �������, �����!

							//���� � ������ �� ������� �� �������� ��������� ��������
		if (p1.getNumOfEnemyShips() == 0 || p2.getNumOfEnemyShips() == 0 || pC.getNumOfEnemyShips() == 0)
		{
			gC = gameover;
			if (!p1.getNumOfEnemyShips())
			{
				renderFinish(1);
			}
			else if (!p2.getNumOfEnemyShips() && menuSelection == twoPlayer)
				renderFinish(2);
			else if (!pC.getNumOfEnemyShips())
				renderFinish(3);
			break;
		}
		//���� ������ ����� ��������� ���, �� ������� ������
		if (p1.maxNumberOfDecks == 0 && (p2.maxNumberOfDecks == 0 || pC.maxNumberOfDecks == 0) && gC == putShip)
		{
			shipsAreReady = true;
			gC = shot;

			for (int i = 0; i < 10; i++)
				for (int j = 0; j < 10; j++)
				{
					if (menuSelection == twoPlayer)
					{
						p1.enemysShipsOnMap[i][j] = p2.ShipsOnMap[i][j];
						p2.enemysShipsOnMap[i][j] = p1.ShipsOnMap[i][j];
					}
					else if (menuSelection == onePlayer)
					{
						p1.enemysShipsOnMap[i][j] = pC.ShipsOnMap[i][j];
						pC.enemysShipsOnMap[i][j] = p1.ShipsOnMap[i][j];
					}
				}
		}
		//���������� �������
		if ((event.type == Event::MouseButtonPressed) && (shipsAreReady == false))//������ ������� ����
			if (event.key.code == Mouse::Left)//� ������ - �����
			{
				if (p1.maxNumberOfDecks > 0)//���������� ������� ��� ������� ������, ���� ��� �� ��� ����������
					p1.addShipsOnMap(mWindow, pos, 0);
				else if (menuSelection == twoPlayer || p2.maxNumberOfDecks > 0) //��� �������.
					p2.addShipsOnMap(mWindow, pos, 400);
			}

		//�������� ������� ������
		if (event.type == Event::KeyPressed)
			if (event.key.code == Keyboard::R)
			{
				if (p1.maxNumberOfDecks == 0)
					p1.setMapColor();
				if (p2.maxNumberOfDecks == 0)
					p2.setMapColor();
			}

		//�������� ������
		if ((event.type == Event::MouseButtonPressed) && (shipsAreReady == true))
			if (event.key.code == Mouse::Left)//� ������ - �����
			{
				if (p1.canShot)
				{
					if (menuSelection == twoPlayer)
						p1.shotInEnemy(mWindow, pos, 400, p2.canShot, p2.playerMap);
					else if (menuSelection == onePlayer)
						p1.shotInEnemy(mWindow, pos, 400, pC.canShot, pC.playerMap);
				}
				else if (menuSelection == twoPlayer || p2.canShot)
					p2.shotInEnemy(mWindow, pos, 0, p1.canShot, p1.playerMap);
			}

		//�������� �����
		if (pC.canShot)
		{
			pC.shotInEnemy(mWindow, pos, p1.canShot, p1.playerMap);//��������
		}
	}
}
void Game::renderPlayer(Player &p, int numPlayer)
{
	mWindow.setView(p.view);

	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
		{
			mWindow.draw(p.playerMap.map[i][j]); //��������� ������ ����������
		}

	//������ ����� � ����������� �� ������
	if (numPlayer == 1)
		p.text.setString("Player 1");
	else if (numPlayer == 2)
		p.text.setString("Player 2");

	//���� �����-���������
	if (p.getIsItComp())
		p.text.setString("Computer");

	p.text.setPosition(p.view.getCenter().x - 25, 0);
	mWindow.draw(p.text);
}
void Game::renderFinish(short winner)
{
	RenderWindow win(VideoMode(250, 60), "Battleship winner");

	while (win.isOpen())
	{
		Event event;
		while (win.pollEvent(event))
		{
			if (event.type == Event::Closed || menuSelection == exitGame)
				win.close();//���� ������ �������, �����!
		}
		Font font;
		font.loadFromFile("arial.ttf");
		Text t;
		t.setFont(font);
		t.setFont(font);
		t.setFillColor(Color::Red);

		t.setCharacterSize(20);
		string str;

		switch (winner)
		{
		case 1: str = "Player 1";
			break;
		case 2:	str = "Player 2";
			break;
		case 3: str = "Computer";
			break;
		}
		str += " is winner!";
		t.setString(str);

		win.clear();
		win.draw(t);
		win.display();
	}

}