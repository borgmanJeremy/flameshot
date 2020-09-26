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

#include <QWidget>

class QVBoxLayout;
class QCheckBox;
class QPushButton;
class QLabel;
class QLineEdit;

class PluginConf : public QWidget
{
    Q_OBJECT
public:
    explicit PluginConf(QWidget* parent = nullptr);

public slots:
    void updateComponents();

private slots:
    void showHelpChanged(bool checked);
    void showSidePanelButtonChanged(bool checked);
    void showDesktopNotificationChanged(bool checked);
    void showTrayIconChanged(bool checked);
    void autostartChanged(bool checked);
    void closeAfterCaptureChanged(bool checked);
    void saveAfterCopyChanged(bool checked);
    void changeSavePath();
    void importConfiguration();
    void exportFileConfiguration();
    void resetConfiguration();

private:
    QVBoxLayout* m_layout;
    QLineEdit* m_savePath;
};
