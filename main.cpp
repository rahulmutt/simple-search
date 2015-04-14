#include "cli.hpp"
#include "gui.hpp"
#include<string>

int main(int argc, char **argv)
{
    if (argc > 1) {
        return search_cli(argc, argv);
    } else {
        return GuiApp(argc, argv, std::string("main.glade")).run();
    }
}
