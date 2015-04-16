#include "gui.hpp"
#include "model.hpp"
#include "utility.hpp"
#include <glibmm/ustring.h>
#include <gtkmm/treeiter.h>
#include<iostream>

GuiApp::GuiApp(int argc, char** argv, string const& pGladeFile) {
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
    mResultModel = ListStore::create(mResultColumns);
    mFileModel = TreeStore::create(mFileColumns);
    mTreeView->set_model(mFileModel);

    TreeModel::Row row = *(mFileModel->append());
    row[mFileColumns.mFile] = "No files added yet.";

    mTreeView->append_column("Files", mFileColumns.mFile);
    //mTreeView->append_column("Hits", mColumns.mHits);

    //Initialize Entry
    mBuilder->get_widget("query_entry", mEntry);
    mEntry->signal_changed().connect(sigc::mem_fun(*this, &GuiApp::on_text_changed));

    //Initialize Dir Button
    mBuilder->get_widget("dir_button", mDirButton);
    mDirButton->signal_clicked().connect(sigc::mem_fun(*this, &GuiApp::on_click_dir));

    //Initialize Statusbar
    mBuilder->get_widget("main_status", mStatusbar);
}

void GuiApp::print_status(string const& status) {
    mStatusbar->push(status);
}

void GuiApp::on_text_changed() {
    Glib::ustring text = mEntry->get_chars(0,-1);
    if (text.size() > 0) {
        cout << "OnTextChanged: " << text.raw() << endl;
        search_result results;
        double time = profile([this, &text, &results] () {
            results = this->engine.search(text.raw());
        });
        out.str("");
        out << "Search time " << time << "us.";
        print_status(out.str());
        cout << "SEARCHED" << endl;
        mResultModel->clear();
        mTreeView->remove_all_columns();
        mTreeView->set_model(mResultModel);
        mTreeView->append_column("File", mResultColumns.mFile);
        if (results.size() > 0) {
            for (auto& result : results) {
                cout << "Result: " << (*(result.second)) << endl;
                TreeModel::Row file = *(mResultModel->append());
                file[mResultColumns.mFile] = ustring(*(result.second));
                file[mResultColumns.mHits] = result.first;
            }
            mTreeView->append_column("Hits", mResultColumns.mHits);
        } else {
            TreeModel::Row file = *(mResultModel->append());
            file[mResultColumns.mFile] = "No results found for '" + text + "'";
        }
    } else {
        mTreeView->remove_all_columns();
        mTreeView->set_model(mFileModel);
        mTreeView->append_column("Directory", mFileColumns.mFile);
    }
}

void GuiApp::on_click_dir() {
    FileChooserDialog dialog("Please choose a folder", FILE_CHOOSER_ACTION_SELECT_FOLDER);
    dialog.set_transient_for(*mWindow);
    dialog.add_button("Cancel", RESPONSE_CANCEL);
    dialog.add_button("Select", RESPONSE_OK);

    int result = dialog.run();

    cout << "Result: " << result << endl; //DEBUG
    switch (result) {
        case RESPONSE_OK:
            {
                string dirname = dialog.get_filename();
                int num_files = engine.num_files();
                vector<string> files;
                double time = profile([this, &files, &dirname] () {
                    files = this->engine.populate(dirname);
                });
                out.str("");
                out << "Added " << files.size() << " files to index in " << time << "us.";
                print_status(out.str());
                if (files.size() <= 0) {
                    print_status("Error: Empty directory. Not added.");
                } else {
                    if (num_files <= 0) mFileModel->clear();
                    add_files(dirname, files);
                }
            }
            break;
        case RESPONSE_CANCEL:
            print_status("File dialog canceled.");
            break;
        default:
            print_status("Error: File dialog failed.");
            break;
    }
}

void GuiApp::add_files(string const& dirname, vector<string> const& files) {
    cout << "Populated" << endl; //DEBUG

    TreeModel::Row dir = *(mFileModel->append());
    dir[mFileColumns.mFile] = dirname;

    for (auto& filename : files) {
        cout << "Filename: " << filename << endl; //DEBUG
        TreeModel::Row file = *(mFileModel->append(dir.children()));
        file[mFileColumns.mFile] = ustring(filename);
    }
    mTreeView->remove_all_columns();
    mTreeView->set_model(mFileModel);
    mTreeView->append_column("Directory", mFileColumns.mFile);
}
