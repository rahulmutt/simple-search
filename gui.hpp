#ifndef __GUI__HPP___
#define __GUI__HPP___
#include <string>
#include <glibmm/refptr.h>
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm/builder.h>
#include <gtkmm/entry.h>
using namespace Gtk;
using namespace Glib;

class GuiApp {
public:
    GuiApp(int argc, char** argv, std::string&& pGladeFile);
    ~GuiApp();
    int run();
    void click_add_dir();
private:
    void init_bindings();
    RefPtr<Application> mApp;
    RefPtr<Builder> mBuilder;
    Window* mWindow;
    Entry* mEntry;
};
#endif
