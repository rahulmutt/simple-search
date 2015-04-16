#include "gui.hpp"
#include "model.hpp"
#include <gtkmm/treeiter.h>
#include <string>

using namespace std;
using namespace Gtk;

GuiApp::GuiApp(int argc, char** argv, string&& pGladeFile) {
    mApp = Application::create(argc, argv, "org.gtkmm.examples.base");
    mBuilder = Builder::create_from_file(pGladeFile);
    init_bindings();
}

GuiApp::~GuiApp() {
    delete mWindow;
    delete mEntry;
    delete mTreeView;
    delete mDirButton;
    delete mStatusbar;
}

int GuiApp::run() {
    return mApp->run(*mWindow);
}

void GuiApp::init_bindings() {
    // Bind Window
    mBuilder->get_widget("main_window", mWindow);

    // Initialize TreeView
    mBuilder->get_widget("search_results", mTreeView);
    mTreeModel = TreeStore::create(mColumns);
    mTreeView->set_model(mTreeModel);

    TreeModel::Row row = *(mTreeModel->append());
    row[mColumns.mFile] = "No files added yet.";
    row[mColumns.mHits] = 0;
    mTreeView->append_column("Files", mColumns.mFile);
    mTreeView->append_column("Hits", mColumns.mHits);

    //Initialize Entry
    mBuilder->get_widget("query_entry", mEntry);

    //Initialize Dir Button
    mBuilder->get_widget("dir_button", mDirButton);
    mDirButton->signal_clicked().connect(sigc::mem_fun(*this, &GuiApp::on_click_dir)); 

    //Initialize Statusbar
    mBuilder->get_widget("main_status", mStatusbar);
    print_status(string("My love"));
}

void GuiApp::print_status(string&& status) {
    mStatusbar->push(status);
}

void GuiApp::on_click_dir() {
    FileChooserDialog dialog("Please choose a folder", FILE_CHOOSER_ACTION_SELECT_FOLDER);
    dialog.set_transient_for(*mWindow);
    dialog.add_button("Cancel", RESPONSE_CANCEL);
    dialog.add_button("Select", RESPONSE_OK);

    int result = dialog.run();

    switch (result) {
        case RESPONSE_OK:
            string dirname = dialog.get_filename();
            vector<string> files = engine.populate(dirname);
            // @TODO: Populate Data Model
            TreeModel::Row dir = *(mTreeModel->append());
            dir[mColumns.mFile] = dirname;
            dir[mColumns.mHits] = 0;

            for (auto& file : files) {
                TreeModel::Row file = *(mTreeModel->append(dir.children()));
                file[mColumns.mFile] = file;
                file[mColumns.mHits] = 0;
            }

            print_status(dirname);
            break;
        case RESPONSE_CANCEL:
            print_status("Canceled");
            break;
        default:
            print_status("Other Error");
            break;
    }
}
