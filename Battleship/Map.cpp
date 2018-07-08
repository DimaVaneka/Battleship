#include "Map.h"

void Map::mapGenerate()
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
		{
			map[i][j].setSize(sf::Vector2f(30, 30)); //������ ����������
			map[i][j].setFillColor(sf::Color(16, 16, 68));//����
			map[i][j].setOutlineThickness(2);//������� �������
			map[i][j].setOutlineColor(sf::Color(92, 94, 154));//����� �������
			map[i][j].setPosition((i + 2) * 30, (j + 2) * 30);//������� ���������� ������������ ������ View ������
		}
}