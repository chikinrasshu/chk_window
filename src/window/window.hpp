#pragma once

#include <common/common.hpp>
#include <common/function.hpp>

namespace chk {

    class Window {
        public:
            Window(s32 w, s32 h, String caption);
            ~Window();

            s32 run(const Callback& frame_fn = nullptr);

        private:
            bool _running = false;
            bool _fullscreen = false;
            
            s32 _x = 0, _y = 0;
            s32 _w = 0, _h = 0;

            Callback _frame_fn = nullptr;
            void* _internal = nullptr;
    };

}