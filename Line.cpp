#include "Line.h"

Line::Line()
{}

Line::Line(const sf::Vector2f& point1, const sf::Vector2f& point2)
{
	m_vertices[0] = sf::Vertex(point1);
	m_vertices[1] = sf::Vertex(point2);
}

void Line::setPosition(const sf::Vector2f& point1, const sf::Vector2f& point2)
{
	m_vertices[0] = sf::Vertex(point1);
	m_vertices[1] = sf::Vertex(point2);
}

void Line::setColor(const sf::Color& color)
{
	m_vertices[0].color = color;
	m_vertices[1].color = color;
}

void Line::clear()
{
	m_vertices[0] = sf::Vector2f(0.f, 0.f);
	m_vertices[1] = sf::Vector2f(0.f, 0.f);
}

void Line::draw(sf::RenderWindow& window) const
{
	window.draw(m_vertices, 2, sf::Lines);
}