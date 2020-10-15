find_package(
        Qt5
        CONFIG
        REQUIRED
        Core
        Network
)

add_library(imgur_plugin SHARED)
target_sources(imgur_plugin
        PRIVATE
        imgur_plugin.cpp)

target_link_libraries(imgur_plugin
  Qt5::Network
  Qt5::Widgets
)