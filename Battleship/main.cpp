#include <iostream>
#include "Class.h"
#include "Player.h"
#include "Map.h"
#include "ComputerPlayer.h"
#include "Game.h"
using namespace std;
int main()
{
	setlocale(LC_ALL, "rus");

	short chooseMenu;//����� ����

	cout << "----------------------------- ������� -----------------------------\n";
	cout << "������� ������������� � ����� �������:\n";
	cout << "- ���� 4-� ��������\n";
	cout << "- ��� 3-� ��������\n";
	cout << "- ��� 2-� ��������\n";
	cout << "- ������ 1-� ��������\n";
	cout << "R - ������ �������, ����� ����������.\n";
	cout << "������� ��������� - ������� ������\n";
	cout << "������� ��������� - ������� ���������\n";
	cout << "���������� ��������� - ������\n";

	do {
		cout << "\n----------------------------- ���� --------------------------------\n";
		cout << "1. ���� �����\n";
		cout << "2. ��� ������\n";
		cout << "3. �����\n";
		cout << "������� ��� �����:";
		try {
			if (!(cin >> chooseMenu) || cin.fail() || chooseMenu < 1 || chooseMenu > 3)
				throw 1;

			if (chooseMenu == 3)//�����
				return 0;

			Game game(chooseMenu);
			game.run();
		}
		catch (int)
		{
			cout << "������ �����! ���������� �����.\n";
			exit(1);
		}
	} while (chooseMenu != 3);

	return 0;
}
