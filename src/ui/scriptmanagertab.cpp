/*
** scriptmanagertab.cpp
**
** Copyright � Beyond Skyrim Development Team, 2017.
** This file is part of OPENCK (https://github.com/Beyond-Skyrim/openck)
**
** OpenCK is free software; this file may be used under the terms of the GNU
** General Public License version 3.0 or later as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.
**
** OpenCK is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
**
** Please review the following information to ensure the GNU General Public
** License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** You should have received a copy of the GNU General Public License version
** 3.0 along with OpenCK; if not, write to the Free Software Foundation,
** Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
**
** Created Date: 04-Jul-2017
*/

#include <ui/scriptmanagertab.h>
#include "ui_scriptmanagertab.h"

#include <models/scriptmanagermodel.h>
#include <models/scriptcompilermodel.h>

#include <QDebug>
#include <QSortFilterProxyModel>
#include <QFileSystemWatcher>

ScriptManagerTab::ScriptManagerTab(QWidget* parent)
    : QWidget(parent), ui(new Ui::ScriptManagerTab)
{
    ui->setupUi(this);

    // Setup manager model and the filter proxy.
    managerProxyModel = new QSortFilterProxyModel(this);
    auto managerModel = new models::ScriptManagerModel(managerProxyModel);
    managerProxyModel->setSourceModel(managerModel);

    auto* managerTree = ui->treeViewScripts;
    managerTree->setModel(managerProxyModel);
    managerTree->hideColumn(2);
    managerTree->hideColumn(3);

    // Setup compiler model.
    compilerModel = new models::ScriptCompilerModel(this);
    compilerModel->setSourceModel(managerModel);

    auto* compilerTree = ui->treeViewScriptsCompile;
    compilerTree->setModel(compilerModel);
    compilerTree->hideColumn(2);
    compilerTree->hideColumn(3);

    //TODO: Remove temp.
    connect(ui->treeViewScripts, SIGNAL(scriptIndexChanged(int)), ui->plainTextEditScriptEditor, SLOT(on_scriptIndexChanged(int)));
}

void ScriptManagerTab::on_lineEditScriptFilter_returnPressed()
{
    if (managerProxyModel) {
        managerProxyModel->setFilterFixedString(ui->lineEditScriptFilter->text());
    }
}

void ScriptManagerTab::on_lineEditScriptFilter_clearButtonClicked()
{
    if (managerProxyModel) {
        managerProxyModel->setFilterFixedString("");
    }
}