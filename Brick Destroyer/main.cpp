#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <SFML/Audio.hpp>
#include <time.h>

using namespace std;

int main()
{
	srand(time(0));

	sf::RenderWindow Window(sf::VideoMode(1200, 900), "BRICK BREAKER");

	Window.setFramerateLimit(60);

	Window.setKeyRepeatEnabled(false);

	bool play = true;

	sf::Event event;

	//Variables
	int xVelocityPlayerBar = 0;
	int xVelocityBall = -8;
	int yVelocityBall = 8;

	int PlayerScore = 0, AIScore = 0;

	int PlayerWon = -1;

	int EnemyBlocks = 16;

	int xCacheBallPosition = 0, yCacheBallPosition = 0;

	//Font
	sf::Font Micross;
	if (Micross.loadFromFile("Data/micross.ttf") == 0)
	{
		return 2;
	}

	//Text
	sf::Text Score;
	Score.setFont(Micross);
	Score.setCharacterSize(30);
	Score.setPosition(400, 0);
	Score.setString(PlayerScore + " : " + AIScore);

	sf::Text MatchEnd;
	MatchEnd.setFont(Micross);
	MatchEnd.setCharacterSize(50);
	MatchEnd.setPosition(400, 0);

	sf::Text MenuText;
	MenuText.setFont(Micross);
	MenuText.setCharacterSize(45);
	MenuText.setString("Brick Destroyer\nPress P Key to Start\nPress Q Key to exit anytime");
	MenuText.setPosition(50, 600);

	//Images
	sf::Texture PlayerBar_Col;
	sf::Texture Background_Tex;
	sf::Texture Ball_Tex;

	sf::Texture BrickColor1;
	sf::Texture BrickColor2;
	sf::Texture BrickColor3;

	if (PlayerBar_Col.loadFromFile("Data/PlayingBar.png") == 0)
		return 1;

	if (Background_Tex.loadFromFile("Data/Background.jfif") == 0)
		return 1;

	if (Ball_Tex.loadFromFile("Data/Ball.png") == 0)
		return 1;

	if (BrickColor1.loadFromFile("Data/Brick1.png") == 0)
		return 1;
	if (BrickColor2.loadFromFile("Data/Brick2.png") == 0)
		return 1;
	if (BrickColor3.loadFromFile("Data/Brick3.png") == 0)
		return 1;

	//Sounds
	sf::SoundBuffer Buff_Hit;
	if(Buff_Hit.loadFromFile("Data/Hit.wav") == 0)
		return 2;

	sf::Sound Hit;
	Hit.setBuffer(Buff_Hit);

	//States
	bool Menu = true;
	bool Left = false;
	bool Right = false;

	bool Quit = false;

	bool RoundStart = true;
	bool RoundAfter = false;

	bool ResetBall = false;

	//Shapes
	sf::RectangleShape Background;
	Background.setSize(sf::Vector2f(1200, 900));
	Background.setPosition(0, 0);
	Background.setTexture(&Background_Tex);

	sf::RectangleShape PlayingBar;
	PlayingBar.setSize(sf::Vector2f(300, 75));
	PlayingBar.setPosition(450, 800);
	PlayingBar.setTexture(&PlayerBar_Col);

	sf::RectangleShape Ball;
	Ball.setSize(sf::Vector2f(50, 50));
	Ball.setPosition(575, 350);
	Ball.setTexture(&Ball_Tex);

	sf::RectangleShape Brick1;
	Brick1.setSize(sf::Vector2f(200, 100));
	Brick1.setPosition(0, 0);
	Brick1.setTexture(&BrickColor1);
	sf::RectangleShape Brick2;
	Brick2.setSize(sf::Vector2f(200, 100));
	Brick2.setPosition(250, 0);
	Brick2.setTexture(&BrickColor2);
	sf::RectangleShape Brick3;
	Brick3.setSize(sf::Vector2f(200, 100));
	Brick3.setPosition(500, 0);
	Brick3.setTexture(&BrickColor3);
	sf::RectangleShape Brick4;
	Brick4.setSize(sf::Vector2f(200, 100));
	Brick4.setPosition(750, 0);
	Brick4.setTexture(&BrickColor1);
	sf::RectangleShape Brick5;
	Brick5.setSize(sf::Vector2f(200, 100));
	Brick5.setPosition(1000, 0);
	Brick5.setTexture(&BrickColor2);
	sf::RectangleShape Brick6;
	Brick6.setSize(sf::Vector2f(200, 100));
	Brick6.setPosition(125, 100);
	Brick6.setTexture(&BrickColor3);
	sf::RectangleShape Brick7;
	Brick7.setSize(sf::Vector2f(200, 100));
	Brick7.setPosition(375, 100);
	Brick7.setTexture(&BrickColor1);
	sf::RectangleShape Brick8;
	Brick8.setSize(sf::Vector2f(200, 100));
	Brick8.setPosition(625, 100);
	Brick8.setTexture(&BrickColor2);
	sf::RectangleShape Brick9;
	Brick9.setSize(sf::Vector2f(200, 100));
	Brick9.setPosition(875, 100);
	Brick9.setTexture(&BrickColor3);
	sf::RectangleShape Brick10;
	Brick10.setSize(sf::Vector2f(200, 100));
	Brick10.setPosition(0, 200);
	Brick10.setTexture(&BrickColor1);
	sf::RectangleShape Brick11;
	Brick11.setSize(sf::Vector2f(200, 100));
	Brick11.setPosition(250, 200);
	Brick11.setTexture(&BrickColor2);
	sf::RectangleShape Brick12;
	Brick12.setSize(sf::Vector2f(200, 100));
	Brick12.setPosition(500, 200);
	Brick12.setTexture(&BrickColor3);
	sf::RectangleShape Brick13;
	Brick13.setSize(sf::Vector2f(200, 100));
	Brick13.setPosition(750, 200);
	Brick13.setTexture(&BrickColor1);
	sf::RectangleShape Brick14;
	Brick14.setSize(sf::Vector2f(200, 100));
	Brick14.setPosition(1000, 200);
	Brick14.setTexture(&BrickColor2);
	sf::RectangleShape Brick15;
	Brick15.setSize(sf::Vector2f(200, 100));
	Brick15.setPosition(125, 300);
	Brick15.setTexture(&BrickColor3);
	sf::RectangleShape Brick16;
	Brick16.setSize(sf::Vector2f(200, 100));
	Brick16.setPosition(875, 300);
	Brick16.setTexture(&BrickColor1);

	while (play)
	{
		//Event
		if (RoundStart == true)
		{
			switch (rand() % 2)
			{
			case 0: xVelocityBall = -7;
					yVelocityBall = 7;
					RoundStart = false;
					break;
			case 1: xVelocityBall = 7;
					yVelocityBall = 7;
					RoundStart = false;
					break;
			}
		}
			
		while (Window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || Quit == true)
			{
				play = false;
				return 9;
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::A) Left = true;
				if (event.key.code == sf::Keyboard::D) Right = true;
				if (event.key.code == sf::Keyboard::Q) Quit = true;
				if (event.key.code == sf::Keyboard::P && Menu == true) Menu = false;
			}
			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::A) Left = false;
				if (event.key.code == sf::Keyboard::D) Right = false;
			}		
		}
		
		//Logic
		if (RoundAfter == false && Menu == false)
		{
			//Player Movement//
			/////////////////////////////////////////////////////////////////////
			if (Left == true)
			{
				xVelocityPlayerBar = -7;
			}
			if (Right == true)
			{
				xVelocityPlayerBar = 7;
			}
			if (Left == true && Right == true)
			{
				xVelocityPlayerBar = 0;
			}
			if (Left == false && Right == false)
			{
				xVelocityPlayerBar = 0;
			}
			//Out of Bounds checking For Player
			if (PlayingBar.getPosition().x < 0)
				PlayingBar.setPosition(0, PlayingBar.getPosition().y);
		
			if (PlayingBar.getPosition().x > 900)
				PlayingBar.setPosition(900, PlayingBar.getPosition().y);
			/////////////////////////////////////////////////////////////////////

			//Move
			PlayingBar.move(xVelocityPlayerBar, 0);//Player

			//Ball Movement//
			/////////////////////////////////////////////////////////////////////

			//Move
			Ball.move(xVelocityBall, yVelocityBall);

			//Out of Bounds checking
			if (Ball.getPosition().y < 0)
			{
				yVelocityBall = -yVelocityBall;
			}
			if (Ball.getPosition().x < 0 || Ball.getPosition().x > 1150)
			{
				xVelocityBall = -xVelocityBall;
			}
			/////////////////////////////////////////////////////////////////////

			//Ball Colission//
			/////////////////////////////////////////////////////////////////////
			if (Ball.getGlobalBounds().intersects(PlayingBar.getGlobalBounds()) == true)
			{
				Hit.play();
				yVelocityBall = -yVelocityBall;
				ResetBall = true;
			}

			if (Ball.getGlobalBounds().intersects(Brick1.getGlobalBounds()) == true)
			{
				Brick1.setPosition(2000, 2000);
				EnemyBlocks--;
				if (ResetBall == false)
				{
					xVelocityBall = -xVelocityBall;
				}
				else
				{
					yVelocityBall = -yVelocityBall;
				}
				ResetBall = false;

			}
			if (Ball.getGlobalBounds().intersects(Brick2.getGlobalBounds()) == true)
			{
				Brick2.setPosition(2000, 2000);
				EnemyBlocks--;
				if (ResetBall == false)
				{
					xVelocityBall = -xVelocityBall;
				}
				else
				{
					yVelocityBall = -yVelocityBall;
				}
				ResetBall = false;
			}
			if (Ball.getGlobalBounds().intersects(Brick3.getGlobalBounds()) == true)
			{
				Brick3.setPosition(2000, 2000);
				EnemyBlocks--;
				if (ResetBall == false)
				{
					xVelocityBall = -xVelocityBall;
				}
				else
				{
					yVelocityBall = -yVelocityBall;
				}
				ResetBall = false;
			}
			if (Ball.getGlobalBounds().intersects(Brick4.getGlobalBounds()) == true)
			{
				Brick4.setPosition(2000, 2000);
				EnemyBlocks--;
				if (ResetBall == false)
				{
					xVelocityBall = -xVelocityBall;
				}
				else
				{
					yVelocityBall = -yVelocityBall;
				}
				ResetBall = false;
			}
			if (Ball.getGlobalBounds().intersects(Brick5.getGlobalBounds()) == true)
			{
				Brick5.setPosition(2000, 2000);
				EnemyBlocks--;
				if (ResetBall == false)
				{
					xVelocityBall = -xVelocityBall;
				}
				else
				{
					yVelocityBall = -yVelocityBall;
				}
				ResetBall = false;
			}
			if (Ball.getGlobalBounds().intersects(Brick6.getGlobalBounds()) == true)
			{
				Brick6.setPosition(2000, 2000);
				EnemyBlocks--;
				if (ResetBall == false)
				{
					xVelocityBall = -xVelocityBall;
				}
				else
				{
					yVelocityBall = -yVelocityBall;
				}
				ResetBall = false;
			}
			if (Ball.getGlobalBounds().intersects(Brick7.getGlobalBounds()) == true)
			{
				Brick7.setPosition(2000, 2000);
				EnemyBlocks--;
				if (ResetBall == false)
				{
					xVelocityBall = -xVelocityBall;
				}
				else
				{
					yVelocityBall = -yVelocityBall;
				}
				ResetBall = false;
			}
			if (Ball.getGlobalBounds().intersects(Brick8.getGlobalBounds()) == true)
			{
				Brick8.setPosition(2000, 2000);
				EnemyBlocks--;
				if (ResetBall == false)
				{
					xVelocityBall = -xVelocityBall;
				}
				else
				{
					yVelocityBall = -yVelocityBall;
				}
				ResetBall = false;
			}
			if (Ball.getGlobalBounds().intersects(Brick9.getGlobalBounds()) == true)
			{
				Brick9.setPosition(2000, 2000);
				EnemyBlocks--;
				if (ResetBall == false)
				{
					xVelocityBall = -xVelocityBall;
				}
				else
				{
					yVelocityBall = -yVelocityBall;
				}
				ResetBall = false;
			}
			if (Ball.getGlobalBounds().intersects(Brick10.getGlobalBounds()) == true)
			{
				Brick10.setPosition(2000, 2000);
				EnemyBlocks--;
				if (ResetBall == false)
				{
					xVelocityBall = -xVelocityBall;
				}
				else
				{
					yVelocityBall = -yVelocityBall;
				}
				ResetBall = false;
			}
			if (Ball.getGlobalBounds().intersects(Brick11.getGlobalBounds()) == true)
			{
				Brick11.setPosition(2000, 2000);
				EnemyBlocks--;
				if (ResetBall == false)
				{
					xVelocityBall = -xVelocityBall;
				}
				else
				{
					yVelocityBall = -yVelocityBall;
				}
				ResetBall = false;
			}
			if (Ball.getGlobalBounds().intersects(Brick12.getGlobalBounds()) == true)
			{
				Brick12.setPosition(2000, 2000);
				EnemyBlocks--;
				if (ResetBall == false)
				{
					xVelocityBall = -xVelocityBall;
				}
				else
				{
					yVelocityBall = -yVelocityBall;
				}
				ResetBall = false;
			}
			if (Ball.getGlobalBounds().intersects(Brick13.getGlobalBounds()) == true)
			{
				Brick13.setPosition(2000, 2000);
				EnemyBlocks--;
				if (ResetBall == false)
				{
					xVelocityBall = -xVelocityBall;
				}
				else
				{
					yVelocityBall = -yVelocityBall;
				}
				ResetBall = false;
			}
			if (Ball.getGlobalBounds().intersects(Brick14.getGlobalBounds()) == true)
			{
				Brick14.setPosition(2000, 2000);
				EnemyBlocks--;
				if (ResetBall == false)
				{
					xVelocityBall = -xVelocityBall;
				}
				else
				{
					yVelocityBall = -yVelocityBall;
				}
				ResetBall = false;
			}
			if (Ball.getGlobalBounds().intersects(Brick15.getGlobalBounds()) == true)
			{
				Brick15.setPosition(2000, 2000);
				EnemyBlocks--;
				if (ResetBall == false)
				{
					xVelocityBall = -xVelocityBall;
				}
				else
				{
					yVelocityBall = -yVelocityBall;
				}
				ResetBall = false;
			}
			if (Ball.getGlobalBounds().intersects(Brick16.getGlobalBounds()) == true)
			{
				Brick16.setPosition(2000, 2000);
				EnemyBlocks--;
				if (ResetBall == false)
				{
					xVelocityBall = -xVelocityBall;
				}
				else
				{
					yVelocityBall = -yVelocityBall;
				}
				ResetBall = false;
			}
			/////////////////////////////////////////////////////////////////////

			//Ball Side Wining//
			/////////////////////////////////////////////////////////////////////
			if (RoundAfter == false)
			{
				if (Ball.getPosition().y >= 850)
				{
					RoundStart = false;
					Ball.setPosition(575, 350);
					RoundAfter = true;
					PlayingBar.setPosition(450, 800);
					PlayerWon = 2;
				}
			}
			if (EnemyBlocks == 0)
			{
				PlayerWon = 1;
				RoundAfter = true;
			}
			/////////////////////////////////////////////////////////////////////
		}

		//Rendering
		Window.clear();

		Window.draw(Background);
		if (Menu == false)
		{
			Window.draw(PlayingBar);
			Window.draw(Ball);
		}

		if (Menu == true)
		{
			Window.draw(MenuText);
		}
			
		if (RoundAfter == true)
		{
			if (PlayerWon == 1)
			{
				MatchEnd.setPosition(525, 450);
				MatchEnd.setString("You Won!!");
			}
			else if (PlayerWon == 2)
			{
				MatchEnd.setPosition(500, 450);
				MatchEnd.setString("You Lose..");
			}
			Window.draw(MatchEnd);
		}

		if (Menu == false)
		{
			Window.draw(Brick1);
			Window.draw(Brick2);
			Window.draw(Brick3);
			Window.draw(Brick4);
			Window.draw(Brick5);
			Window.draw(Brick6);
			Window.draw(Brick7);
			Window.draw(Brick8);
			Window.draw(Brick9);
			Window.draw(Brick10);
			Window.draw(Brick11);
			Window.draw(Brick12);
			Window.draw(Brick13);
			Window.draw(Brick14);
			Window.draw(Brick15);
			Window.draw(Brick16);
		}
		Window.display();
	}
	//Clean up
	Window.close();

	return 0;
}