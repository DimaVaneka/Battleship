#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

//����� �����
class Map {
public:
	void mapGenerate();// ��������� �����
	sf::RectangleShape map[10][10]; //�����, ������� ���������
};