#include "../tools/imgur/uploadplugin.h"
#include <boost/config.hpp>
#include <iostream>
#include <vector>


#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

#define IMGUR_CLIENT_ID 1234

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

    void upload();
};

void imgur_plugin::upload()
{
    QUrlQuery urlQuery;
    urlQuery.addQueryItem(QStringLiteral("title"),
                          QStringLiteral("flameshot_screenshot"));
    QString description = "test"; //FileNameHandler().parsedPattern();
    urlQuery.addQueryItem(QStringLiteral("description"), description);

    QUrl url(QStringLiteral("https://api.imgur.com/3/image"));
    url.setQuery(urlQuery);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      "application/application/x-www-form-urlencoded");
    request.setRawHeader(
      "Authorization",
      QStringLiteral("Client-ID %1").arg(IMGUR_CLIENT_ID).toUtf8());

    //m_NetworkAM->post(request, byteArray);
}

// Exporting `my_namespace::plugin` variable with alias name `plugin`
// (Has the same effect as `BOOST_DLL_ALIAS(my_namespace::plugin, plugin)`)
extern "C" BOOST_SYMBOL_EXPORT imgur_plugin plugin;
imgur_plugin plugin;
// BOOST_DLL_ALIAS(my_namespace::plugin, plugin)
} // namespace my_namespace