#include <array>
#include <chrono>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <vector>

#include <fmt/chrono.h>
#include <fmt/color.h>

#include "petri/logging.hpp"

namespace {
constexpr fmt::text_style GetStyle(pt::log::Level level) noexcept {
    switch (level) {
        case pt::log::Level::eFatal:
            return fmt::fg(fmt::color::dark_red);
        case pt::log::Level::eError:
            return fmt::fg(fmt::rgb(204, 0, 0));
        case pt::log::Level::eWarning:
            return fmt::fg(fmt::rgb(196, 160, 0));
        case pt::log::Level::eInfo:
            return fmt::fg(fmt::rgb(114, 159, 207));
        case pt::log::Level::eDebug:
            return fmt::fg(fmt::rgb(168, 228, 160));
        case pt::log::Level::eVerbose:
            return fmt::fg(fmt::color::dark_gray);
        case pt::log::Level::eTrace:
            return fmt::fg(fmt::color::blue);
        default:
            return { };
    }
}

constexpr fmt::text_style GetStyle(pt::log::Category level) noexcept {
    switch (level) {
        case pt::log::Category::eGeneral:
            return fmt::fg(fmt::color::white_smoke);
        case pt::log::Category::eVulkan:
            return fmt::fg(fmt::color::indian_red);
        default:
            return { };
    }
}

struct LocalTime {
    std::tm tm { };
    std::array<char, 6> tzOffset { };
};

LocalTime GetLocalTime(const std::chrono::system_clock::time_point tp) noexcept {
    const std::time_t t = std::chrono::system_clock::to_time_t(tp);
    LocalTime result { };

#ifdef PLATFORM_WINDOWS
    localtime_s(&result.tm, &t);
#else
    localtime_r(&t, &result.tm);
#endif

    char tempBuf[6] { };
    std::strftime(tempBuf, sizeof(tempBuf), "%z", &result.tm);
    std::memcpy(result.tzOffset.data(), tempBuf, 6);

    return result;
}

std::string FormatTzOffset(const std::array<char, 6>& tz) {
    if (tz[0] == '\0') {
        return { };
    }

    return fmt::format(" {:.3}:{}", tz.data(), tz.data() + 3);
}
}

namespace pt::log {
void SubmitLog(const Category category, const Level level, const std::string& message) {
    const auto now = std::chrono::system_clock::now();
    const auto ms =
        std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count() % 1000;
    const auto [tm, tzOffset] = GetLocalTime(now);

    fmt::println("{} {} {}: {}",
                 fmt::styled(fmt::format("[{:%H:%M:%S}.{:03d}{}]", tm, ms, FormatTzOffset(tzOffset)),
                             fmt::fg(fmt::color::gray)),
                 fmt::styled(fmt::format("[{}]", utils::ToString(category)), GetStyle(category)),
                 fmt::styled(fmt::format("[{}]", utils::ToString(level)), GetStyle(level)), message);

    std::fflush(stdout);
}
}

namespace pt::utils {
std::string_view ToString(const log::Level level) {
    switch (level) {
        case log::Level::eFatal:
            return "Fatal";
        case log::Level::eError:
            return "Error";
        case log::Level::eWarning:
            return "Warning";
        case log::Level::eInfo:
            return "Info";
        case log::Level::eDebug:
            return "Debug";
        case log::Level::eVerbose:
            return "Verbose";
        case log::Level::eTrace:
            return "Trace";
        default:
            return { };
    }
}

std::string_view ToString(const log::Category category) {
    switch (category) {
        case log::Category::eGeneral:
            return "General";
        case log::Category::eVulkan:
            return "Vulkan";
        default:
            return { };
    }
}
}
