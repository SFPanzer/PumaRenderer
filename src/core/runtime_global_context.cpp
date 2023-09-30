#include "runtime_global_context.h"

#include "src/core/systems/log_system.h"
#include "src/core/systems/window_system.h"

namespace PumaRenderer {

    void RuntimeGlobalContext::StartSystem()
    {
        m_LogSystem = std::make_shared<LogSystem>();
        m_WindowSystem = std::make_shared<WindowSystem>();

        WindowInfo windowInfo;
        m_WindowSystem->Initialize(windowInfo);
    }

    void RuntimeGlobalContext::ShutdownSystem()
    {
        m_LogSystem.reset();
        m_WindowSystem.reset();
    }

} // PumaRenderer