//
// Created by jeremy on 9/24/20.
//

#ifndef FLAMESHOT_UPLOADPLUGIN_H
#define FLAMESHOT_UPLOADPLUGIN_H

#include <string>
#include <boost/config.hpp>

void test();

class BOOST_SYMBOL_VISIBLE UploadPlugin
{
public:
    // Plugin should COPY data out of this buffer. It is not ref counted
    virtual std::string name(char* buffer, unsigned int size);

    virtual ~UploadPlugin() {}
};

#endif // FLAMESHOT_UPLOADPLUGIN_H
