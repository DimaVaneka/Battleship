#include "Map.h"
#pragma once
#include "Map.h"

//����� ������
class Player {
protected:
	unsigned int fourDeckShip = 1;//���-�� 4-� �������� ��������
	unsigned int threeDeckShip = 2;//���-�� 3-� �������� ��������
	unsigned int twoDeckShip = 3;//���-�� 2-� �������� ��������
	unsigned int oneDeckShip = 4;//���-�� 1-� �������� ��������
	int numberOfTheDeck;//���-�� ����� �� ��������� ����������� ������ ������� (�� 1 �� 4)
	short numOfEnemyShips;//���-�� ���������� �������� ����������, ������������ ��� ��������� ����
	bool canPut[10][10];//����� ������� ������ ��� ���
	bool canShotOnMap[10][10];//����� �������� ��� ���
	enum decksConditions { Deck = 1, Wound, None, Kill };//��������� ������: deck - �����, wound - ������, none - ����(�����), kill - ���������� 
	bool isItComp;//����� - ����. ��� ���
	int enemyX, enemyY;//���������� ��������� ������, � ������� ������
	int deckNums;//���-�� �� �������� �����
	int deckWoundNums;//���-�� �������� �����
public:
	Font font;//�����
	Text text;//������� ������
	Text finishTextMessage;//��������� �� ��������� ����
	decksConditions ShipsOnMap[10][10];//������ ��������
	decksConditions enemysShipsOnMap[10][10];//������ �������� ����������
	int maxNumberOfDecks;//����. ���-�� �����
	bool canShot;//���������� �� ��������
	View view;//������
	Map playerMap;//����� �����������

	Player() {
		playerMap.mapGenerate();//��������� �����
		maxNumberOfDecks = 20;//������������ ���-�� ����� - 20
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				ShipsOnMap[i][j] = None;
				canPut[i][j] = true;
				canShotOnMap[i][j] = true;
				isItComp = false;
			}
		}

		numberOfTheDeck = 1;//���-�� ����� �� ��������� ����������� ������ �������
		numOfEnemyShips = 1;
		font.loadFromFile("arial.ttf");

		//�������� ������
		text.setFont(font);
		text.setFillColor(Color::Red);
		text.setCharacterSize(24);

		//��������� � ����� ����
		finishTextMessage.setFont(font);
		finishTextMessage.setFillColor(Color::Red);
		finishTextMessage.setCharacterSize(30);
	}

	void setMapColor();//���� �����
	void addShipsOnMap(RenderWindow& win, Vector2i p, int movePos);//�������������� � ������, �������� ���������� ��������
	virtual void shotInEnemy(RenderWindow& win, Vector2i p, int movePos, bool& canEnemyShot, Map& enemy);//�������� �� �����
	void initShipOnMap(int s, int f, int decs);
	void deckIsReady(int i, int j);//������ ������
	void deckIsDestroyed(int a, int b, Map& enemy);//���������� ������
	bool getIsItComp() { return isItComp; }
	short getNumOfEnemyShips() { return numOfEnemyShips; }
};