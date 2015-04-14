#include "gui.hpp"
#include <glibmm/ustring.h>
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm/builder.h>
#include <gtkmm/entry.h>

using namespace Gtk;

int search_gui(int argc, char **argv) {
    auto app = Application::create(argc, argv, "org.gtkmm.examples.base");
    auto builder = Builder::create_from_file("main.glade");
    Window* window = 0;
    Entry* entry = 0;
    builder->get_widget("main_window", window);
    builder->get_widget("query_entry", entry);
    entry->set_text(window->get_title());
    int running = app->run(*window);
    delete window;
    delete entry;
    return running;
}
