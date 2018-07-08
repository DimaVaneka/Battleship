#pragma once
#include "Player.h"

//����� �����-���������
class ComputerPlayer : public Player {
private:
	enum fireOnEnemy { defaultRand = 0, hitLastShot, thereAreWoundDeck };//defaultRand-���������, hitLastShot-����� ��������� �������, thereAreWoundDeck-���� �������� ������
	fireOnEnemy fireEnemy;//��������� ��������
public:
	ComputerPlayer()
	{
		playerMap.mapGenerate();//��������� �����
		setMapColor();//�������� �������
		maxNumberOfDecks = 20;//������������ ���-�� ����� - 20

		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				ShipsOnMap[i][j] = None;
				canPut[i][j] = true;
				canShotOnMap[i][j] = true;
				isItComp = true;
				fireEnemy = defaultRand;
			}
		}

		numOfEnemyShips = 1;
		numberOfTheDeck = 1;//���-�� ����� �� ��������� ����������� ������ �������
		deckNums = 0;//���-�� �� �������� �����
		deckWoundNums = 0;//���-�� �������� �����
	}
	virtual void addShipsOnMap();//����������� �������
	virtual void shotInEnemy(RenderWindow& win, Vector2i p, bool& canEnemyShot, Map& enemy);//�������� �� �����
	void randXY();//��������� ���������� ��� ��������
	int getEnemyX() { return enemyX; }
	int getEnemyY() { return enemyY; }
};