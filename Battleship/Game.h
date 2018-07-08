#pragma once
#include "Player.h"
#include "ComputerPlayer.h"

//����� ����
class Game {
private:
	bool shipsAreReady;//������� �����������
	RenderWindow mWindow; //����
	Player p1;//����� ����
	Player p2;//����� ���
	ComputerPlayer pC;//�����-���������
	Vector2i pos;//���������� ������� ����
	enum gameConditions { putShip = 0, shot, gameover };//��������� ����: putShip- ������������� �������; shot - ���� ��������
	gameConditions gC;
	enum chooseGameMenu { onePlayer = 1, twoPlayer, exitGame };//����� ������ ����
	chooseGameMenu menuSelection;
public:
	Game(short choiceMenu) : mWindow(sf::VideoMode(800, 400), "Battleship")
	{
		switch (choiceMenu)
		{
		case 1: menuSelection = onePlayer;
			break;
		case 2: menuSelection = twoPlayer;
			break;
		case 3: menuSelection = exitGame;
			break;
		}
		p1.view.setViewport(FloatRect(0, 0, 0.5f, 1));//����� ����� ����
		p1.view.reset(FloatRect(0, 0, 400, 400));//������ ������
		p1.canShot = true;//������ ����� ����� ��������,����� �������� �������

		if (menuSelection == twoPlayer)
		{
			p2.view.setViewport(FloatRect(0.5f, 0, 0.5f, 1));//������ ����� ����
			p2.view.reset(FloatRect(0, 0, 400, 400));//������ ������
			p2.canShot = false;//������ ����� �� ����� ��������
		}
		else if (menuSelection == onePlayer)//���� �� ������ ������, �� ��������� ������������� ����������� �������
		{
			pC.view.setViewport(FloatRect(0.5f, 0, 0.5f, 1));//������ ����� ����
			pC.view.reset(FloatRect(0, 0, 400, 400));//������ ������
			pC.canShot = false;//������ ����� �� ����� ��������
			pC.addShipsOnMap();//����������� �������
			pC.setMapColor();//�������� �������
		}

		gC = putShip; //��������� ���� ����������� ��������
		shipsAreReady = false;
	}
	void run();//������ ����
	void processEvents(); //��������� ��������
	void render(); //��������� ALL
	void renderPlayer(Player &p, int numPlayer);//��������� ���� �������
	void renderFinish(short winner);//����� ��������� � ����������
};