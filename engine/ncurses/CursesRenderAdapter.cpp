//
// Created by henry on 2021-12-07.
//

#include "CursesRenderAdapter.h"

namespace AGE::Renderer {

CursesRenderAdapter::CursesRenderAdapter(CursesRenderer *cursesRenderer) :
    cursesRenderer{cursesRenderer} {}

void CursesRenderAdapter::render(ScreenBuffer &buffer) const {
    cursesRenderer->drawBuffer(buffer);
    cursesRenderer->update();
}

}
