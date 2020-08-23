#include "qmlimagefx_plugin.h"

#include "imagefx.h"

#include <qqml.h>

void QMLImageFxPlugin::registerTypes(const char *uri)
{
    //пришлось вписать руками. иначен дизайнер не видит
    qmlRegisterType<ImageFx>("QMLImageFx", 1, 0, "ImageFx");
}

