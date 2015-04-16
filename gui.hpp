#ifndef __GUI__HPP___
#define __GUI__HPP___
#include "coreengine.hpp"

#include <string>
#include <sstream>
#include <glibmm/refptr.h>
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm/treeview.h>
#include <gtkmm/builder.h>
#include <gtkmm/entry.h>
#include <gtkmm/treemodel.h>
#include <gtkmm/treestore.h>
#include <gtkmm/liststore.h>
#include <gtkmm/filechooserdialog.h>
#include <gtkmm/statusbar.h>
using namespace std;
using namespace Gtk;
using namespace Glib;

class GuiApp {
public:
    GuiApp(int argc, char** argv, string const& pGladeFile);
    ~GuiApp();
    int run();
private:
    void init_bindings();
    void on_click_dir();
    void on_text_changed();
    void add_files(string const& dirname, vector<string> const& files);
    void print_status(string const& status);
    RefPtr<Application> mApp;
    RefPtr<Builder> mBuilder;
    Window* mWindow;
    Entry* mEntry;
    TreeView* mTreeView;
    RefPtr<ListStore> mResultModel;
    RefPtr<TreeStore> mFileModel;
    Button* mDirButton;
    Statusbar* mStatusbar;
    CoreEngine engine;
    ostringstream out;
};
#endif
