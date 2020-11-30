// Copyright(c) 2017-2019 Alejandro Sirgo Rica & Contributors
//
// This file is part of Flameshot.
//
//     Flameshot is free software: you can redistribute it and/or modify
//     it under the terms of the GNU General Public License as published by
//     the Free Software Foundation, either version 3 of the License, or
//     (at your option) any later version.
//
//     Flameshot is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//     GNU General Public License for more details.
//
//     You should have received a copy of the GNU General Public License
//     along with Flameshot.  If not, see <http://www.gnu.org/licenses/>.

#include "filenamehandler.h"
#include <QDir>
#include <QStandardPaths>
#include <ctime>
#include <locale>

#include <QDebug>
constexpr char FileNameHandler::DEFAULT_FORMAT[];

FileNameHandler::FileNameHandler(QObject* parent)
  : QObject(parent)
{
    std::locale::global(std::locale(""));
}

QString cleanDateSpecifier(const QString& input_date_string)
{
    QString clean_date_string = input_date_string.isEmpty()
                                  ? FileNameHandler::DEFAULT_FORMAT
                                  : input_date_string;

    // remove trailing characters '%' in the pattern
    while (clean_date_string.endsWith('%')) {
        clean_date_string.chop(1);
    }
    return clean_date_string;
}

QString getDateString(const QString& date_string)
{
    std::time_t t = std::time(nullptr);
    char date_data[FileNameHandler::MAX_CHARACTERS] = { 0 };
    std::strftime(date_data,
                  FileNameHandler::MAX_CHARACTERS,
                  date_string.toStdString().data(),
                  std::localtime(&t));

    return QString::fromLocal8Bit(date_data, (int)strlen(date_data));
}

QString FileNameHandler::parseFilename(const QString& input_specifier)
{
    QString clean_specifier = cleanDateSpecifier(input_specifier);
    QString date_string = getDateString(clean_specifier);

    // add the parsed pattern in a correct format for the filesystem
    date_string = date_string.replace(QLatin1String(":"), QLatin1String("-"));
    return date_string;
}

QString FileNameHandler::generateAbsolutePath(const QString& path, const QString& filePattern)
{
    QString directory = path;
    QString filename = parseFilename(filePattern);
    fixPath(directory, filename);
    qDebug() << "absolute path: " << directory + filename;
    return directory + filename;
}

QString FileNameHandler::absoluteSavePath(QString directory, const QString& filename)
{
    qDebug() << "directory: " << directory;
    if (directory.isEmpty() || !QDir(directory).exists() ||
        !QFileInfo(directory).isWritable()) {
        directory =
          QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
        qDebug() << "not writable";
    }
    //filename = parseFilename(ConfigHandler().filenamePatternValue());
    auto final_path = fixPath(directory, filename);

    return final_path;
}

QString FileNameHandler::fixPath(QString directory, QString filename)
{
    // add '/' at the end of the directory
    if (!directory.endsWith(QLatin1String("/"))) {
        directory += QLatin1String("/");
    }
    // add numeration in case of repeated filename in the directory
    // find unused name adding _n where n is a number

    //TODO need to support all file extensions
    QFileInfo checkFile(directory + filename + ".png");
    if (checkFile.exists()) {
        filename += QLatin1String("_");
        int i = 1;
        while (true) {
            checkFile.setFile(directory + filename + QString::number(i) +
                              ".png");
            if (!checkFile.exists()) {
                filename += QString::number(i);
                break;
            }
            ++i;
        }
    }
    return directory + filename;
}
