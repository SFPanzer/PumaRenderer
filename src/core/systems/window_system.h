#pragma once

#include "GLFW/glfw3.h"

#include "array"
#include "functional"

namespace PumaRenderer{

    struct WindowInfo {
        int width {1280};
        int height {720};
        const char* title {"PumaEngine"};
        bool is_fullScreen {false};
    };

    class WindowSystem{
    public:
        WindowSystem() = default;
        ~WindowSystem();

        void Initialize(WindowInfo windowInfo);
        bool ShouldClose() const;
        void SetTitle(const char* title);
        GLFWwindow* GetWindow() const { return m_window; };
        std::array<int, 2>  GetWindowSize() const;

        typedef std::function<void(int, int, int, int)> OnKeyFunc;
        typedef std::function<void(int, int)> OnWindowSizeFunc;
        typedef std::function<void()> OnWindowCloseFunc;

        void RegisterOnKeyFunc(const OnKeyFunc& func) { m_onKeyFunc.push_back(func); }
        void RegisterOnWindowSizeFunc(const OnWindowSizeFunc& func) { m_onWindowSizeFunc.push_back(func); }
        void RegisterOnWindowCloseFunc(const OnWindowCloseFunc& func) { m_onWindowCloseFunc.push_back(func); }


    protected:
        static void OnKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void OnWindowSizeCallBack(GLFWwindow* window, int width, int height);
        static void windowCloseCallback(GLFWwindow* window);


        void OnKey(int key, int scancode, int action, int mods);
        void OnWindowSize(int width, int height);
        void OnWindowClose();

    private:
        GLFWwindow* m_window {nullptr};
        int m_width {0};
        int m_height {0};

        std::vector<OnKeyFunc> m_onKeyFunc;
        std::vector<OnWindowSizeFunc> m_onWindowSizeFunc;
        std::vector<OnWindowCloseFunc> m_onWindowCloseFunc;
    };

}