//
// Created by henry on 2021-12-07.
//

#ifndef FINAL_PROJECT_ENGINE_NCURSES_CURSESRENDERADAPTER_H_
#define FINAL_PROJECT_ENGINE_NCURSES_CURSESRENDERADAPTER_H_

#include "../renderer/RenderTarget.h"

namespace AGE::Renderer {

class CursesRenderAdapter : public RenderTarget {
  public:
    void render(ScreenBuffer &buffer) const override;
};

}

#endif //FINAL_PROJECT_ENGINE_NCURSES_CURSESRENDERADAPTER_H_
