#include "precompiler.h"


int main()
{
    
    bool gameOn = true;
    int screen;

    showMenu();

    while (gameOn != false)
    {

        std::cin >> screen;





        switch (screen)
        {

        case 1:

            std::cout << "Start";
            //openStart();

            break;

        case 2:

            std::cout << "Info";
            //openInfo();

            break;

        case 3:

            gameOn = false;

        }
    }

}
