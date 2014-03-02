#ifndef OBJ2TRIANGLESOUP_H
#define OBJ2TRIANGLESOUP_H

#include <QString>
#include "Drawables/trianglesoup.h"
#include "Utils/abstractlog.h"

namespace IO
{
    class TriangleSoupImporters
    {
    public:
        static void readObj(const QString& filename, TriangleSoup& triSoup, float scale = 1.f, AbstractLog* log = nullptr);

    };
}
#endif // OBJ2TRIANGLESOUP_H
