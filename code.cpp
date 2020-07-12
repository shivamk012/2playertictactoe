#include<SFML/Graphics.hpp>
#include<iostream>
#include<math.h>

class Game {

private:
	sf::RenderWindow window;
	sf::RectangleShape line1, line2, line3, line4,end;
	sf::Event evnt; int player = 1, done=0;
	sf::Vector2i pos;
	sf::Texture t1, t2;
	sf::Sprite X, O;
	int intarr[3][3];
	sf::Sprite spritearr[3][3];bool flagend = false;
private:
	void processevent();
	void update();
	void render();
	void check();
public:
	
	Game() {
		window.create(sf::VideoMode(800, 800), "Tic Tac Toe", sf::Style::Close);

		line1.setSize(sf::Vector2f(1.5, 600));
		line1.setPosition(sf::Vector2f(300, 100));
		line1.setFillColor(sf::Color::Black);

		line2.setSize(sf::Vector2f(600, 1.5));
		line2.setPosition(sf::Vector2f(100, 300));
		line2.setFillColor(sf::Color::Black);


		line3.setSize(sf::Vector2f(1.5, 600));
		line3.setPosition(sf::Vector2f(500, 100));
		line3.setFillColor(sf::Color::Black);


		line4.setSize(sf::Vector2f(600, 1.5));
		line4.setPosition(sf::Vector2f(100, 500));
		line4.setFillColor(sf::Color::Black);

		t1.loadFromFile("C:/Users/Hp/Desktop/My Folder/X.png");
		t2.loadFromFile("C:/Users/Hp/Desktop/My Folder/O.png");
		O.setTexture(t2);
		X.setTexture(t1);

		for (int i = 0; i < 3;++i) {
			for (int j = 0; j < 3; ++j) {
				intarr[i][j] = 100*(i+1)+j;
			}
		}
	}

	void run() {
		while (window.isOpen()) {
			processevent();
			update();
			render();
		}
	}

};

void Game::processevent() {
	//sf::Event evnt;
	if (window.pollEvent(evnt)) {
		if (evnt.type == sf::Event::Closed)
			window.close();
		else if ((evnt.type == sf::Event::MouseButtonPressed) && (evnt.key.code == sf::Mouse::Left)) {
			pos = sf::Mouse::getPosition(window);
			done = 1;
		}
	}
}

void Game::update() {
	if (done == 1) {
		if ((pos.x >= 100 && pos.x <= 700) && (pos.y >= 100 && pos.y <= 700)) {
			int x = pos.x / 100, y = pos.y / 100;
			if (x % 2 != 0)
				x = (x - 1) / 2;
			else
				x = (x - 2) / 2;
			if (y % 2 != 0)
				y = (y - 1) / 2;
			else
				y = (y - 2) / 2;
			if (player == 1) {
				if ((intarr[x][y]!=0) && (intarr[x][y]!=1)) {
					X.setPosition(sf::Vector2f(150.0 + 200.0 * x, 150.0 + 200.0 * y));
					intarr[x][y] = 1;spritearr[x][y] = X;
					player = 0;
				}
			}
			else {
				if ((intarr[x][y] != 0) && (intarr[x][y] != 1)) {
					O.setPosition(sf::Vector2f(150.0 + 200.0 * x, 150.0 + 200.0 * y));
					intarr[x][y] = 0;spritearr[x][y] = O;
					player = 1;
				}
			}
			check();
		}
	}
	done = 0;
}

void Game::render() {
	window.clear(sf::Color::White);
	window.draw(line1);window.draw(line2);window.draw(line3);window.draw(line4);
	for (int i = 0; i < 3;++i) {
		for (int j = 0; j < 3; ++j) {
			window.draw(spritearr[i][j]);
		}
	}
	if (flagend)
		window.draw(end);
	window.display();
}

void Game::check() {
	bool flag = false;
	for (int i = 0; i < 3; ++i) {
		flag = false;
		for (int j = 0; j < 2;++j) {
			if (intarr[i][j] == intarr[i][j + 1])
				flag = true;
			else {
				flag = false;
				break;
			}
		}
		if (flag) {
			flagend = true;
			end.setSize(sf::Vector2f(1, 600));
			//std::cout << spritearr[i][0].getPosition().x << " " << spritearr[i][0].getPosition().y << " " << i << std::endl;
			end.setPosition(sf::Vector2f(spritearr[i][0].getPosition().x + 50, spritearr[i][0].getPosition().y - 50));
			end.setFillColor(sf::Color::Black);
			break;
		}
	}

	for (int i = 0; i < 3;++i) {
		flag = false;
		for (int j = 0; j < 2;++j) {
			if (intarr[j][i] == intarr[j + 1][i])
				flag = true;
			else {
				flag = false;
				break;
			}
		}
		if (flag) {
			flagend = true;
			end.setSize(sf::Vector2f(600, 1));
			//std::cout << spritearr[i][0].getPosition().x << " " << spritearr[i][0].getPosition().y <<" "<<i<< std::endl;
			end.setPosition( sf::Vector2f ( spritearr[0][i].getPosition().x - 50 , spritearr[0][i].getPosition().y+50 ) );
			end.setFillColor(sf::Color::Black);
			break;
		}
	}

	if (((intarr[0][0] == intarr[1][1]) &&( intarr[0][0]==intarr[2][2]))||((intarr[0][2] == intarr[1][1]) && (intarr[0][2] == intarr[2][0]))) {
		if (((intarr[0][0] == intarr[1][1]) && (intarr[0][0] == intarr[2][2]))) {
			flagend = true;
			end.setSize(sf::Vector2f(600*pow(2,0.5) , 1));
			end.setRotation(45);
			end.setPosition(100, 100);
			end.setFillColor(sf::Color::Black);
		}
		else {
			flagend = true;
			end.setSize(sf::Vector2f(600 * pow(2, 0.5), 1));
			end.setRotation(135);
			end.setPosition(700, 100);
			end.setFillColor(sf::Color::Black);
		}
	}
}

int main() {

	Game game;
	game.run();
	return 0;
}
