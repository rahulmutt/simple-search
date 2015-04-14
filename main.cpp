#include "cli.hpp"
#include "gui.hpp"

int main(int argc, char **argv)
{
    if (argc > 1) {
        return search_cli(argc, argv);
    } else {
        return search_gui(argc, argv);
    }
}
