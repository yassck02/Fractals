#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <cmath>

int windowWidth = 1500;
int windowHeight = 1000;
sf::Color backgroundColor = sf::Color(220,220,200);


template <class T>
sf::Color randomColor(T t){
	int x = int(t);
	srand(x);
	int r = rand() % 255;
	int g = rand() % 5;
	int b = rand() % 255;
	return sf::Color(r,g,b);
}

void Circles(sf::RenderWindow* W, float posX, float posY, float radius, int count, int max){
	count++;
	if(count >= max){
		return;
	}
	sf::CircleShape temp;
	temp.setOrigin(radius, radius);
	temp.setOutlineColor(sf::Color::Black);
	temp.setOutlineColor(randomColor(count));
	temp.setOutlineThickness((count * 100) / max);
	temp.setFillColor(sf::Color::Transparent);
	temp.setRadius(radius);
	temp.setPosition(posX, posY);
	W->draw(temp);
	
	Circles(W, posX-radius, posY, radius/2, count, max);
	Circles(W, posX+radius, posY, radius/2, count, max);
	Circles(W, posX, posY-radius, radius/2, count, max);
	Circles(W, posX, posY+radius, radius/2, count, max);
}

void lines(sf::RenderWindow* W, float posX, float posY, float length, int count, int max){
	count++;
	if(count >= max){
		return;
	}
	
	sf::RectangleShape temp;
	temp.setSize(sf::Vector2f(length,3));
	temp.setOrigin(length/2, 1.5);
	temp.setPosition(posX, posY);
	
	//temp.setFillColor(sf::Color::Black);
	temp.setFillColor(randomColor(count));
	
	temp.setOutlineThickness(0);
	W->draw(temp);
	
	lines(W, posX - length/3, posY+15, length/3, count, max);
	lines(W, posX + length/3, posY+15, length/3, count, max);

}

void tree(sf::RenderWindow* W, float posX, float posY, float length, float angle, int count, int max){
	count++;
	if(count >= max){
		return;
	}
	
	int lineThickness = 3;
	
	sf::RectangleShape temp;
	temp.setSize(sf::Vector2f(length,lineThickness));
	temp.setOrigin(0, lineThickness/2);
	temp.setRotation(angle);
	temp.setPosition(posX, posY);
	
	//temp.setFillColor(sf::Color::Black);
	temp.setFillColor(randomColor(count));
	
	temp.setOutlineThickness(0);
	W->draw(temp);
	
	posX = posX + cos(angle * M_PI / 180) * length;
	posY = posY + sin(angle * M_PI / 180) * length;
	
	float dif = sf::Mouse::getPosition(*W).y / float(W->getSize().y) * 90.0;
	
	tree(W, posX, posY, length*0.66, angle-dif, count, max);
	tree(W, posX, posY, length*0.66, angle+dif, count, max);
	
}

int main(int argc, char const** argv)
{
	int X = 4;			// itterations
	int Y = 100;			// size
	int num = 1;
	
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML window");
	window.setFramerateLimit(10);
	
	
	while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
			switch(event.type){
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
					switch(event.key.code){
						case sf::Keyboard::Num1:
							num = 1;
							break;
						case sf::Keyboard::Num2:
							num = 2;
							break;
						case sf::Keyboard::Num3:
							num = 3;
							break;
						case sf::Keyboard::Up:
							X++;
							break;
						case sf::Keyboard::Down:
							X--;
							break;
						case sf::Keyboard::Left:
							Y -= 3;
							break;
						case sf::Keyboard::Right:
							Y += 3;
							break;
						default:
							break;
					}
					break;
				case sf::Event::Resized:
					window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
					windowWidth = event.size.width;
					windowHeight = event.size.height;
					break;
				default:
					break;
			}
        }

        // Clear screen
        window.clear(backgroundColor);
		
		switch(num){
			case 1:
				Circles(&window, windowWidth/2, windowHeight/2, Y, 0, X);
				break;
			case 2:
				//void lines(sf::RenderWindow* W, float posX, float posY, float length, int count, int max){
				lines(&window, windowWidth/2, 25, Y, 0, X);
				break;
			case 3:
				tree(&window, windowWidth/2, windowHeight-25, Y, -90, 0, X);
				break;
		}

		
        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
