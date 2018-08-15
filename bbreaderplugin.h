#ifndef HENPLUGIN_H
#define HENPLUGIN_H

#include "plugin_interface.h"

class BbReaderPlugin : public PluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.uavos.gcu.PluginInterface/1.0")
    Q_INTERFACES(PluginInterface)
public:
    void init(void);
    BbReaderPlugin();
    ~BbReaderPlugin();
};


#endif // HENPLUGIN_H
