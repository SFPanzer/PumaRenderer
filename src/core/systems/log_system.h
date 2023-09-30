#pragma once

#include <spdlog/spdlog.h>

#include <cstdint>
#include <stdexcept>

namespace PumaRenderer {

    class LogSystem final {
    public:
        enum class LogLevel : uint8_t {
            debug,
            info,
            warn,
            error,
            fatal
        };

        LogSystem();
        ~LogSystem();

        template<typename... T_args>
        void log(LogLevel level, T_args&&... args) {
            switch (level) {
                case LogLevel::debug:
                    m_logger->debug(std::forward<T_args>(args)...);
                    break;
                case LogLevel::info:
                    m_logger->info(std::forward<T_args>(args)...);
                    break;
                case LogLevel::warn:
                    m_logger->warn(std::forward<T_args>(args)...);
                    break;
                case LogLevel::error:
                    m_logger->error(std::forward<T_args>(args)...);
                    break;
                case LogLevel::fatal:
                    m_logger->critical(std::forward<T_args>(args)...);
                    fatalCallback(std::forward<T_args>(args)...);
                    break;
                default:
                    break;
            }
        }

        template<typename... T_args>
        void fatalCallback(T_args&&... args) {
            const std::string format_str = fmt::format(std::forward<T_args>(args)...);
            throw std::runtime_error(format_str);
        }

    private:
        std::shared_ptr<spdlog::logger> m_logger;
    };

} // PumaRenderer
