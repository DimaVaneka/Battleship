#include "ComputerPlayer.h"


void ComputerPlayer::addShipsOnMap()
{
	srand(time(NULL));

	while (maxNumberOfDecks > 0)
	{
		enemyX = rand() % 9;
		enemyY = rand() % 9;

		if (ShipsOnMap[enemyX][enemyY] == None && canPut[enemyX][enemyY] == true)
		{
			//����������� ������
			if (fourDeckShip != 0)
			{
				initShipOnMap(enemyX, enemyY, 4);//�������� ���-�� �����
			}
			else if (threeDeckShip != 0 && fourDeckShip == 0)
			{
				if (numberOfTheDeck == 4) numberOfTheDeck = 1;
				initShipOnMap(enemyX, enemyY, 3);//�������� ���-�� �����
			}
			else if (twoDeckShip != 0 && threeDeckShip == 0)
			{
				if (numberOfTheDeck == 3) numberOfTheDeck = 1;
				initShipOnMap(enemyX, enemyY, 2);//�������� ���-�� �����
			}
			else if (oneDeckShip != 0 && twoDeckShip == 0)
			{
				deckIsReady(enemyX, enemyY);
				ShipsOnMap[enemyX][enemyY] = Deck;
				//������ ������� ������� ������
				if ((enemyX - 1) >= 0) canPut[enemyX - 1][enemyY] = false;
				if ((enemyX + 1) <= 9) canPut[enemyX + 1][enemyY] = false;
				if ((enemyY - 1) >= 0) canPut[enemyX][enemyY - 1] = false;
				if ((enemyY + 1) <= 9) canPut[enemyX][enemyY + 1] = false;
			}
		}
	}
}
void ComputerPlayer::randXY()
{
	srand(time(NULL));
	enemyX = rand() % 9;
	enemyY = rand() % 9;
}
void ComputerPlayer::shotInEnemy(RenderWindow& win, Vector2i p, bool& canEnemyShot, Map& enemy)
{

	if (fireEnemy == defaultRand)// ���� �� ���������(��-���� ������� ������� - ������, � ��� �������� �����
	{
		do {
			randXY();
		} while (canShotOnMap[enemyX][enemyY] != true);

	}

	if (fireEnemy == thereAreWoundDeck || fireEnemy == hitLastShot)//���� ���� �������� ������
	{
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++)
			{
				if (enemysShipsOnMap[i][j] == Wound && (canShotOnMap[i - 1][j] || canShotOnMap[i + 1][j] || canShotOnMap[i][j - 1] || canShotOnMap[i][j + 1]))
				{

					if (enemysShipsOnMap[i - 1][j] != Wound && canShotOnMap[i - 1][j])
					{
						enemyX = i - 1;
						enemyY = j;
						break;
					}
					else if (enemysShipsOnMap[i + 1][j] != Wound && canShotOnMap[i + 1][j])
					{
						enemyX = i + 1;
						enemyY = j;
						break;
					}
					else if (enemysShipsOnMap[i][j - 1] != Wound && canShotOnMap[i][j - 1])
					{
						enemyY = j - 1;
						enemyX = i;
						break;
					}
					else if (enemysShipsOnMap[i][j + 1] != Wound && canShotOnMap[i][j + 1])
					{
						enemyY = j + 1;
						enemyX = i;
						break;
					}
				}
			}
	}

	if (enemysShipsOnMap[enemyX][enemyY] == Deck)//���� ������ � ������
	{
		canShotOnMap[enemyX][enemyY] = false;//������ ��������
											 //���� ����� ��� �����
		if ((((enemyX - 1) >= 0 && enemysShipsOnMap[enemyX - 1][enemyY] == None) || (enemyX - 1) < 0) && (((enemyX + 1) <= 9 && enemysShipsOnMap[enemyX + 1][enemyY] == None) || (enemyX + 1) > 9) && (((enemyY - 1) >= 0 && enemysShipsOnMap[enemyX][enemyY - 1] == None) || (enemyY - 1) < 0) && (((enemyY + 1) <= 9 && enemysShipsOnMap[enemyX][enemyY + 1] == None) || (enemyY + 1) > 9))
		{
			deckIsDestroyed(enemyX, enemyY, enemy);//���� ����� ���� ����� - ���������� �������
			oneDeckShip--;//����� ���� ������������ �������
			fireEnemy = defaultRand;//�� ���������
		}
		//���� ����� ������
		else if (((enemyX - 1) >= 0 && enemysShipsOnMap[enemyX - 1][enemyY] == Deck) || ((enemyX + 1) <= 9 && enemysShipsOnMap[enemyX + 1][enemyY] == Deck) || ((enemyY - 1) >= 0 && enemysShipsOnMap[enemyX][enemyY - 1] == Deck) || ((enemyY + 1) <= 9 && enemysShipsOnMap[enemyX][enemyY + 1] == Deck))
		{
			enemy.map[enemyX][enemyY].setFillColor(sf::Color::Green);//���� Green ���� �����
			fireEnemy = hitLastShot;//���������
			enemysShipsOnMap[enemyX][enemyY] = Wound;//�����, ���� ����� Deck 	
		}
		//���� ����� �������� ������
		else if (enemysShipsOnMap[enemyX][enemyY - 1] == Wound || enemysShipsOnMap[enemyX][enemyY + 1] == Wound)
		{
			deckNums = 0;//���-�� �� �������� �����
			deckWoundNums = 0;//���-�� �������� �����

							  //���� ������ ��� ����� ���� �� �������� ������
			if (enemysShipsOnMap[enemyX][enemyY - 1] == Wound)
			{
				for (int k = 1; k <= 3; k++)
					if ((enemyY - k) >= 0 && enemysShipsOnMap[enemyX][enemyY - k] != None)
					{
						if (enemysShipsOnMap[enemyX][enemyY - k] == Deck)
							deckNums++;
					}
					else break;
			}
			if (enemysShipsOnMap[enemyX][enemyY + 1] == Wound)
			{
				for (int k = 1; k <= 3; k++)
					if ((enemyY + k) <= 9 && enemysShipsOnMap[enemyX][enemyY + k] != None)
					{
						if (enemysShipsOnMap[enemyX][enemyY + k] == Deck)
							deckNums++;
					}
					else break;
			}

			//���� ���� �� �������� ������, �� ������ ����� ������
			if (deckNums != 0)
			{
				enemy.map[enemyX][enemyY].setFillColor(sf::Color::Green);
				fireEnemy = hitLastShot;//���������
				canShotOnMap[enemyX][enemyY] = false;//������ ��������
				enemysShipsOnMap[enemyX][enemyY] = Wound;
			}
			else if (deckNums == 0)//����� ���������� �������
			{
				deckIsDestroyed(enemyX, enemyY, enemy);
				deckWoundNums = 1;

				//������� �������� ����� �� ���������
				for (int a = 1; a <= 3; a++)
				{
					if ((enemyY - a) >= 0 && enemysShipsOnMap[enemyX][enemyY - a] != None)
					{
						if (enemysShipsOnMap[enemyX][enemyY - a] == Wound)
						{
							deckIsDestroyed(enemyX, enemyY - a, enemy);
							deckWoundNums++;
						}
					}
					else break;
				}
				for (int a = 1; a <= 3; a++)
				{
					if ((enemyY + a) >= 0 && enemysShipsOnMap[enemyX][enemyY + a] != None)
					{
						if (enemysShipsOnMap[enemyX][enemyY + a] == Wound)
						{
							deckIsDestroyed(enemyX, enemyY + a, enemy);
							deckWoundNums++;
						}
					}
					else break;
				}
			}

			//���� ������� ���������
			if (deckNums == 0)
				fireEnemy = defaultRand;
		}
		else if (enemysShipsOnMap[enemyX - 1][enemyY] == Wound || enemysShipsOnMap[enemyX + 1][enemyY] == Wound)
		{
			deckNums = 0;//���-�� �� �������� �����
			deckWoundNums = 0;//���-�� �������� �����

							  //���� ������ ��� ����� ���� �� �������� ������
			if (enemysShipsOnMap[enemyX - 1][enemyY] == Wound)
			{
				for (int k = 1; k <= 3; k++)
					if ((enemyX - k) >= 0 && enemysShipsOnMap[enemyX - k][enemyY] != None)
					{
						if (enemysShipsOnMap[enemyX - k][enemyY] == Deck)
							deckNums++;
					}
					else break;
			}
			if (enemysShipsOnMap[enemyX + 1][enemyY] == Wound)
			{
				for (int k = 1; k <= 3; k++)
					if ((enemyX + k) <= 9 && enemysShipsOnMap[enemyX + k][enemyY] != None)
					{
						if (enemysShipsOnMap[enemyX + k][enemyY] == Deck)
							deckNums++;
					}
					else break;
			}

			//���� ���� �� �������� ������, �� ������ ����� ������
			if (deckNums != 0)
			{
				enemy.map[enemyX][enemyY].setFillColor(sf::Color::Green);
				fireEnemy = hitLastShot;//���������
				canShotOnMap[enemyX][enemyY] = false;//������ ��������
				enemysShipsOnMap[enemyX][enemyY] = Wound;
			}
			else if (deckNums == 0)//����� ���������� �������
			{
				deckIsDestroyed(enemyX, enemyY, enemy);
				deckWoundNums = 1;

				//������� �������� ����� �� ���������
				for (int a = 1; a <= 3; a++)
				{
					if ((enemyX - a) >= 0 && enemysShipsOnMap[enemyX - a][enemyY] != None)
					{
						if (enemysShipsOnMap[enemyX - a][enemyY] == Wound)
						{
							deckIsDestroyed(enemyX - a, enemyY, enemy);
							deckWoundNums++;
						}
					}
					else break;
				}
				for (int a = 1; a <= 3; a++)
				{
					if ((enemyX + a) >= 0 && enemysShipsOnMap[enemyX + a][enemyY] != None)
					{
						if (enemysShipsOnMap[enemyX + a][enemyY] == Wound)
						{
							deckIsDestroyed(enemyX + a, enemyY, enemy);
							deckWoundNums++;
						}
					}
					else break;
				}
			}

			//���� ������� ���������
			if (deckNums == 0)
				fireEnemy = defaultRand;
		}
		numOfEnemyShips = 0;

		//��������� �������� �� ��� ������� � ����������
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++)
				if (enemysShipsOnMap[i][j] == Deck)
					numOfEnemyShips++;

	}
	else if (enemysShipsOnMap[enemyX][enemyY] == None)//���� ������
	{
		enemy.map[enemyX][enemyY].setFillColor(sf::Color::Magenta);//���� Magenta ���� ������
		canShotOnMap[enemyX][enemyY] = false;
		canShot = false;
		canEnemyShot = true;
		if (fireEnemy == hitLastShot)
			fireEnemy = thereAreWoundDeck;//���� �� �������� ������, � ���� ��� �������� �����
	}
}