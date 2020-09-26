//
// Created by jeremy on 9/24/20.
//

#include <boost/dll/import.hpp>
#include <iostream>
#include "uploadplugin.h"

namespace dll=boost::dll;

void test()
{
    boost::dll::fs::path lib_path("/home/jeremy/github/borgman_flameshot/cmake-build-default/src/plugins");
    boost::shared_ptr<UploadPlugin> plugin;
    std::cout << "Loading the plugin" << std::endl;

    plugin = dll::import<UploadPlugin>(  // type of imported symbol is located between `<` and `>`
      lib_path / "libadder_plugin",        // path to the library and library name
      "plugin",                          // name of the symbol to import
      dll::load_mode::append_decorations // makes `libmy_plugin_sum.so` or `my_plugin_sum.dll` from `my_plugin_sum`
    );

    std::cout << "plugin->calculate(1.5, 1.5) call:  "
              << plugin->calculate(1.5, 1.5) << std::endl;
}