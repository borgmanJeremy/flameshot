//
// Created by jeremy on 9/24/20.
//

#ifndef FLAMESHOT_UPLOADPLUGIN_H
#define FLAMESHOT_UPLOADPLUGIN_H

#include <string>
#include <boost/config.hpp>

void test();

enum UploadStatus{
    UPLOAD_NOT_STARTED,
    UPLOAD_IN_PROCESS,
    UPLOAD_FINISHED,
    UPLOAD_FAILED,
};

class BOOST_SYMBOL_VISIBLE UploadPlugin
{
public:

    // Plugin should COPY data out of this buffer. It is not ref counted
    virtual void init(char* buffer, unsigned int size) = 0;

    virtual UploadStatus uploadStatus() = 0;

    virtual ~UploadPlugin() {}
};

#endif // FLAMESHOT_UPLOADPLUGIN_H
