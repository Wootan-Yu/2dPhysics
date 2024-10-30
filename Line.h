#pragma once
#include <SFML/Graphics.hpp>

class Line
{
	sf::Vertex m_vertices[2];
public:
	Line();
	Line(const sf::Vector2f& point1, const sf::Vector2f& point2);

	void setPosition(const sf::Vector2f& point1, const sf::Vector2f& point2);
	void setColor(const sf::Color& color);
	void draw(sf::RenderWindow& window) const;
	void clear();
};