#include "nonpreservedtexture.h"

#include "context.h"
#include <private/qsgtexture_p.h>
#include <private/qquickwindow_p.h>

namespace CustomContext {

/*
    Typically a texture factory will keep a reference to the
    QImage so that it can be reused when QQuickWindow::setPersistentSceneGraph(false)
    is set and the window is hidden and then re-exposed.

    This texture factory does not keep a reference, and is
    intended to lower memory usage in the case of an embedded
    system with only a single window that is never hidden or re-exposed.
*/

NonPreservedTextureFactory::NonPreservedTextureFactory(const QImage &image, Context *context)
    : m_image(image), m_context(context)
{
    m_size = m_image.size();
    m_byteCount = m_image.byteCount();
}

QSGTexture *NonPreservedTextureFactory::createTexture(QQuickWindow *window) const
{
    Q_ASSERT(window);
    QSGRenderContext *renderContext = static_cast<QQuickWindowPrivate *>(QObjectPrivate::get(window))->context;
    Q_ASSERT(renderContext);
    QSGTexture *texture = renderContext->createTexture(m_image);
    m_image = QImage(); // remove the reference to the QImage
    return texture;
}

} // end of namespace
