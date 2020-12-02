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

#pragma once

#include <QObject>

enum class FileExtension{
    PNG,
    JPG,
    BMP
};

struct FileType{
    FileExtension ext;
    std::string ext_str;
    std::string description;
};

QString cleanDateSpecifier(const QString& input_date_string);
QString getDateString(const QString& date_string);

class FileNameHandler : public QObject
{
    Q_OBJECT
public:
    explicit FileNameHandler(QObject* parent = nullptr);

    QString parseFilename(const QString& name);
    QString generateAbsolutePath(const QString& path,
                                 const QString& filePattern);
    QString absoluteSavePath(QString directory, const QString& filename);

    static constexpr int MAX_CHARACTERS = 70;
    static constexpr char DEFAULT_FORMAT[] = "%F_%H-%M";

    QString fixPath(QString directory, QString filename);

private:
    std::vector<FileType> _supportedFiles;
};
