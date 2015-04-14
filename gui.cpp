#include "gui.hpp"
#include <glibmm/ustring.h>
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm/builder.h>
#include <gtkmm/entry.h>

using namespace Gtk;

GuiApp::GuiApp(int argc, char** argv, std::string&& pGladeFile) {
    mApp = Application::create(argc, argv, "org.gtkmm.examples.base");
    mBuilder = Builder::create_from_file(pGladeFile);
    init_bindings();
}

GuiApp::~GuiApp() {
    delete mWindow;
    delete mEntry;
}

int GuiApp::run() {
    return mApp->run(*mWindow);
}

void GuiApp::init_bindings() {
    mBuilder->get_widget("main_window", mWindow);
    mBuilder->get_widget("query_entry", mEntry);
    mEntry->set_text(mWindow->get_title());
}
