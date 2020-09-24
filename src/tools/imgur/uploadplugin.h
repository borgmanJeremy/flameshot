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
    virtual std::string name() const=0;
    virtual float calculate(float x, float y) =0;

    virtual ~UploadPlugin() {}
};

#endif // FLAMESHOT_UPLOADPLUGIN_H
