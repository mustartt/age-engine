
#ifndef FINAL_PROJECT__CURSESCONTEXTMANAGER_H_
#define FINAL_PROJECT__CURSESCONTEXTMANAGER_H_

#include <memory>
#include "CursesRenderer.h"
#include "CursesKeyboard.h"

namespace AGE {

class CursesContextManager final {
    std::unique_ptr<CursesRenderer> renderer;
    std::unique_ptr<CursesKeyboard> keyboard;
  public:
    explicit CursesContextManager(int width = 80, int height = 25);
    ~CursesContextManager();

    CursesKeyboard *getKeyboardInstance() { return keyboard.get(); }
    CursesRenderer *getRendererInstance() { return renderer.get(); }
};

}

#endif //FINAL_PROJECT__CURSESCONTEXTMANAGER_H_
