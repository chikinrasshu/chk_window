#include "window.hpp"

#include <GLFW/glfw3.h>

namespace chk
{
    namespace impl {
        static s32 count = 0;

        bool push() { 
            if (count == 0) if (!glfwInit()) return false;
            ++count;
            return true; 
        }

        bool pop() {
            if (count <= 0) return false;
            if (count == 1) glfwTerminate();
            --count;
            return true; 
        }
    }

    Window::Window(s32 w, s32 h, String caption) {
        impl::push();
        
        GLFWwindow* handle = glfwCreateWindow(w, h, caption.c_str(), nullptr, nullptr);
        _internal = handle;

        glfwSetWindowUserPointer(handle, this);

        glfwSetWindowRefreshCallback(handle, [](GLFWwindow* handle){ 
            auto win = reinterpret_cast<Window*>(glfwGetWindowUserPointer(handle));
            if (win) {
                if (win->_frame_fn) win->_frame_fn();
            }
        });

        glfwSetWindowCloseCallback(handle, [](GLFWwindow* handle){ 
            auto win = reinterpret_cast<Window*>(glfwGetWindowUserPointer(handle));
            if (win) {
                win->_running = false;
            }
        });

        glfwSetWindowPosCallback(handle, [](GLFWwindow* handle, s32 x, s32 y){ 
            auto win = reinterpret_cast<Window*>(glfwGetWindowUserPointer(handle));
            if (win) {
                win->_x = x;
                win->_y = y;
            }
        });

        glfwSetWindowSizeCallback(handle, [](GLFWwindow* handle, s32 w, s32 h){ 
            auto win = reinterpret_cast<Window*>(glfwGetWindowUserPointer(handle));
            if (win) {
                win->_w = w;
                win->_h = h;
            }
        });

        _running = true;
    }

    Window::~Window() {
        auto handle = reinterpret_cast<GLFWwindow*>(_internal);
        if (_running) { 
            glfwDestroyWindow(handle); 
            _running = false; 
        }

        impl::pop();
    }


    s32 Window::run(const Callback &frame_fn) {
        _frame_fn = frame_fn;

        auto handle = reinterpret_cast<GLFWwindow*>(_internal); 
        while(_running && !glfwWindowShouldClose(handle)) {
            glfwPollEvents();
            if (!_running) break;
            if (_frame_fn) _frame_fn();
        }

        return 0;
    }

}