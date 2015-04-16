#include "model.hpp"
#include <gtkmm/treemodelcolumn.h>

ModelColumns mColumns;

ModelColumns::ModelColumns() {
    add(mFile);
    add(mHits);
}
