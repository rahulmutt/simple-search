#ifndef __GUI__HPP___
#define __GUI__HPP___
#include <string>
#include <glibmm/refptr.h>
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm/treeview.h>
#include <gtkmm/builder.h>
#include <gtkmm/entry.h>
#include <gtkmm/treemodel.h>
#include <gtkmm/treestore.h>
#include <gtkmm/filechooserdialog.h>
#include <gtkmm/statusbar.h>
using namespace Gtk;
using namespace Glib;

class GuiApp {
public:
    GuiApp(int argc, char** argv, std::string&& pGladeFile);
    ~GuiApp();
    int run();
private:
    void init_bindings();
    void on_click_dir();
    void print_status(std::string&& status);
    RefPtr<Application> mApp;
    RefPtr<Builder> mBuilder;
    Window* mWindow;
    Entry* mEntry;
    TreeView* mTreeView;
    RefPtr<TreeStore> mTreeModel;
    Button* mDirButton;
    Statusbar* mStatusbar;

    CoreEngine engine;
};
#endif
