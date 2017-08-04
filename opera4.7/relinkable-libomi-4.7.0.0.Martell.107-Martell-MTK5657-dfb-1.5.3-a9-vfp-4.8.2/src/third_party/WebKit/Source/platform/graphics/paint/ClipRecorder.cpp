// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "config.h"
#include "platform/graphics/paint/ClipRecorder.h"

#include "platform/graphics/GraphicsContext.h"
#include "platform/graphics/paint/ClipDisplayItem.h"
#include "platform/graphics/paint/PaintController.h"

namespace blink {

ClipRecorder::ClipRecorder(GraphicsContext& context, const DisplayItemClientWrapper& client, DisplayItem::Type type, const LayoutRect& clipRect)
    : m_client(client)
    , m_context(context)
    , m_type(type)
{
    m_context.paintController().createAndAppend<ClipDisplayItem>(m_client, type, pixelSnappedIntRect(clipRect));
}

ClipRecorder::~ClipRecorder()
{
    m_context.paintController().endItem<EndClipDisplayItem>(m_client, DisplayItem::clipTypeToEndClipType(m_type));
}

} // namespace blink
