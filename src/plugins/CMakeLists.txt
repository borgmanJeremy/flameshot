
add_library(adder_plugin SHARED)
target_sources(adder_plugin
        PRIVATE
        my_plugin_sum.cpp)
