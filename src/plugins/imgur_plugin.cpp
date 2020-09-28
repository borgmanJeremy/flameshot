#include "../tools/imgur/uploadplugin.h"
#include <boost/config.hpp>
#include <iostream>
#include <vector>

namespace my_namespace {

class imgur_plugin : public UploadPlugin
{
public:
    void init(char* buffer, unsigned int size) override
    {
        _buffer = std::vector<char>(buffer, buffer + size);
        _uploadStatus = UploadStatus::UPLOAD_NOT_STARTED;
    }

    UploadStatus uploadStatus() override { return _uploadStatus; }

    ~imgur_plugin() override = default;

private:
    std::vector<char> _buffer;
    UploadStatus _uploadStatus;
};

// Exporting `my_namespace::plugin` variable with alias name `plugin`
// (Has the same effect as `BOOST_DLL_ALIAS(my_namespace::plugin, plugin)`)
extern "C" BOOST_SYMBOL_EXPORT imgur_plugin plugin;
imgur_plugin plugin;
// BOOST_DLL_ALIAS(my_namespace::plugin, plugin)
} // namespace my_namespace