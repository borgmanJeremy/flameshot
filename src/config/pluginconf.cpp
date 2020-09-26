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

#include "geneneralconf.h"
#include "src/core/controller.h"
#include "src/utils/confighandler.h"
#include "src/utils/filenamehandler.h"
#include <QCheckBox>
#include <QFile>
#include <QFileDialog>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QStandardPaths>
#include <QTextCodec>
#include <QVBoxLayout>
GeneneralConf::GeneneralConf(QWidget* parent)
  : QWidget(parent)
{
    m_layout = new QVBoxLayout(this);
    m_layout->setAlignment(Qt::AlignTop);
    initShowHelp();
    initShowSidePanelButton();
    initShowDesktopNotification();
    initShowTrayIcon();
    initAutostart();
    initCloseAfterCapture();
    initCopyAndCloseAfterUpload();
    initSaveAfterCopy();

    // this has to be at the end
    initConfingButtons();
    updateComponents();
}

void GeneneralConf::updateComponents()
{
    ConfigHandler config;


        ConfigHandler().setSaveAfterCopyPath(
          QStandardPaths::writableLocation(QStandardPaths::PicturesLocation));


}

void GeneneralConf::changeSavePath()
{
    QString path = QFileDialog::getExistingDirectory(
      this,
      tr("Choose a Folder"),
      QStandardPaths::writableLocation(QStandardPaths::PicturesLocation),
      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (path.isEmpty()) {
        return;
    }
    if (!QFileInfo(path).isWritable()) {
        QMessageBox::about(
          this, tr("Error"), tr("Unable to write to directory."));
        return;
    }
    m_savePath->setText(path);
    ConfigHandler().setSaveAfterCopyPath(path);
}
