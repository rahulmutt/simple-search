#ifndef __MODEL__HPP__
#define __MODEL__HPP__
#include<glibmm/ustring.h>
#include<gtkmm/treemodelcolumn.h>
using namespace Gtk;

class FileColumns : public TreeModelColumnRecord
{
public:
    FileColumns();
    TreeModelColumn<Glib::ustring> mFile;
};

extern FileColumns mFileColumns;

class ResultColumns : public TreeModelColumnRecord
{
public:
    ResultColumns();
    TreeModelColumn<Glib::ustring> mFile;
    TreeModelColumn<int> mHits;
};

extern ResultColumns mResultColumns;
#endif
