#include "model.hpp"
#include <gtkmm/treemodelcolumn.h>

FileColumns mFileColumns;
ResultColumns mResultColumns;

FileColumns::FileColumns() {
    add(mFile);
}

ResultColumns::ResultColumns() {
    add(mFile);
    add(mHits);
}
