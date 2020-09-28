#include <boost/config.hpp>
#include <iostream>
#include <vector>
#include "../tools/imgur/uploadplugin.h"


namespace my_namespace {

class my_plugin_sum : public UploadPlugin {
public:
    my_plugin_sum(char* buffer, unsigned int size) {
        _buffer = std::vector<char>(buffer, buffer + size);
    }

    std::string name() const {
        return "sum";
    }

    ~my_plugin_sum() override = default;
private:
    std::vector<char> _buffer;
};

// Exporting `my_namespace::plugin` variable with alias name `plugin`
// (Has the same effect as `BOOST_DLL_ALIAS(my_namespace::plugin, plugin)`)
extern "C" BOOST_SYMBOL_EXPORT my_plugin_sum plugin;
my_plugin_sum plugin;

} // namespace my_namespace