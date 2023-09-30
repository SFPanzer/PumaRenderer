#pragma once

#include "memory"
#include "string"

namespace PumaRenderer {

    class LogSystem;
    class WindowSystem;

    class RuntimeGlobalContext
    {
    public:
        void StartSystem();
        void ShutdownSystem();

        std::shared_ptr<LogSystem> m_LogSystem;
        std::shared_ptr<WindowSystem> m_WindowSystem;
    };

    extern RuntimeGlobalContext g_runtime_global_context;
} // PumaRenderer
