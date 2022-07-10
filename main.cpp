#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}

// // Cpp
// #include <iostream>
// #include <ctime>
// #include <cstdlib>

// // SFML libarary
// #include <SFML/Graphics.hpp>
// #include <SFML/Window.hpp>

// using namespace std;
// using namespace sf;

// int main()
// {
//     cout << "Hej" << endl;
//     return 0;
// };

// class Human
// {
// public:
//     string name = "Dominik";

//     void displayName()
//     {
//         cout << name << endl;
//     }
// };

// // main::main(/* args */)
// // {
// // }

// // main::~main()
// // {
// // }

// int main()
// {

//     Human HumanObj;

//     HumanObj.displayName();
//     // cout << HumanObj.displayName() << endl;

//     const int target = (rand() % 10) + 1;
//     int answer;

//     do
//     {
//         cout << "Enter the number (0 - 10)";
//         cin >> answer;
//     } while (target != answer);

//     cout << "Game over" << endl;

//     return 0;
// }
