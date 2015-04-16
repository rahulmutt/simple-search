#ifndef __MODEL__HPP__
#define __MODEL__HPP__
#include<glibmm/ustring.h>
#include<gtkmm/treemodelcolumn.h>
using namespace Gtk;

class ModelColumns : public TreeModelColumnRecord
{
public:
    ModelColumns();
    TreeModelColumn<Glib::ustring> mFile;
    TreeModelColumn<int> mHits;
};

extern ModelColumns mColumns;
#endif
