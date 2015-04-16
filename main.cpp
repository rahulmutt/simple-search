#include "cli.hpp"
#include "gui.hpp"
#include<string>

using namespace std;

int main(int argc, char **argv)
{
    if (argc > 1) {
        return CliApp(argc, argv).run();
    } else {
        return GuiApp(argc, argv, string("main.glade")).run();
    }
}
