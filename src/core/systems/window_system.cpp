#include "src/core/systems/window_system.h"

#include "src/core/base/macro.h"

namespace PumaRenderer {

    WindowSystem::~WindowSystem() {
        glfwDestroyWindow(m_window);
        glfwTerminate();
    }

    void WindowSystem::Initialize(WindowInfo windowInfo) {
        if (!glfwInit()) {
            LOG_FATAL(__FUNCTION__, "Failed to initialize GLFW.");
        }

        // Create window.
        m_width = windowInfo.width;
        m_height = windowInfo.height;
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        m_window = glfwCreateWindow(windowInfo.width, windowInfo.height, windowInfo.title, nullptr, nullptr);
        if (!m_window) {
            LOG_FATAL(__FUNCTION__, "Failed to create window.");
            glfwTerminate();
            return;
        }

        // Setup callbacks.
        glfwSetWindowUserPointer(m_window, this);
        glfwSetKeyCallback(m_window, OnKeyCallback);
        glfwSetWindowSizeCallback(m_window, OnWindowSizeCallBack);
        glfwSetWindowCloseCallback(m_window, windowCloseCallback);
    }

    bool WindowSystem::ShouldClose() const {
        return glfwWindowShouldClose(m_window);
    }

    void WindowSystem::SetTitle(const char *title) {
        glfwSetWindowTitle(m_window, title);
    }

    std::array<int, 2> WindowSystem::GetWindowSize() const {
        return std::array<int, 2>({m_width, m_height});
    }

    void WindowSystem::OnKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
        auto *app = static_cast<WindowSystem *>(glfwGetWindowUserPointer(window));
        if (app) {
            app->OnKey(key, scancode, action, mods);
        }
    }

    void WindowSystem::OnWindowSizeCallBack(GLFWwindow *window, int width, int height) {
        auto *app = static_cast<WindowSystem *>(glfwGetWindowUserPointer(window));
        if (app) {
            app->m_width = width;
            app->m_height = height;
            app->OnWindowSize(width, height);
        }
    }

    void WindowSystem::windowCloseCallback(GLFWwindow *window) {
        auto *app = static_cast<WindowSystem *>(glfwGetWindowUserPointer(window));
        if (app) {
            app->OnWindowClose();
            glfwSetWindowShouldClose(window, true);
        }
    }

    void WindowSystem::OnKey(int key, int scancode, int action, int mods) {
        for (auto &func: m_onKeyFunc)
            func(key, scancode, action, mods);
    }

    void WindowSystem::OnWindowSize(int width, int height) {
        for (auto &func: m_onWindowSizeFunc)
            func(width, height);
    }

    void WindowSystem::OnWindowClose() {
        for (auto &func: m_onWindowCloseFunc)
            func();
    }

}