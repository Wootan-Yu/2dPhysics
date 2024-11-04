#include <SFML/Graphics.hpp>
#include "Application.h"
#include "Constants.h"



int main()
{
    Application app("config.txt");
    app.run();
    

    return 0;
}