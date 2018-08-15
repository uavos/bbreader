#include "bbreaderplugin.h"

#include <QSettings>

#include "mainwindow.h"

void BbReaderPlugin::init(void)
{
}

BbReaderPlugin::BbReaderPlugin()
{
    obj = new MainWindow();

    name = "bbreaderplugin";

    if(!QSettings().contains("plugins/bbreaderplugin"))
        QSettings().setValue("plugins/bbreaderplugin", "dock");

}

BbReaderPlugin::~BbReaderPlugin()
{

}
