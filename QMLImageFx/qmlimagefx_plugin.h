#ifndef QMLIMAGEFX_PLUGIN_H
#define QMLIMAGEFX_PLUGIN_H

#include <QQmlExtensionPlugin>

class QMLImageFxPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    void registerTypes(const char *uri) override;
};

#endif // QMLIMAGEFX_PLUGIN_H
