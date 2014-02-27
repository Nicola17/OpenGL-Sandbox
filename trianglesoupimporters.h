#ifndef OBJ2TRIANGLESOUP_H
#define OBJ2TRIANGLESOUP_H

#include <QString>
#include "Drawables/trianglesoup.h"

namespace IO
{
    class TriangleSoupImporters
    {
    public:
        static void read(const QString& filename, TriangleSoup& triSoup);

    };
}
#endif // OBJ2TRIANGLESOUP_H
