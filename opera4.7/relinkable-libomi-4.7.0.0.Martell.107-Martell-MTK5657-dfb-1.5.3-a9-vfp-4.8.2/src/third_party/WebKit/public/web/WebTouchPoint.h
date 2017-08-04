/*
 * Copyright (C) 2010 Google Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *     * Neither the name of Google Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef WebTouchPoint_h
#define WebTouchPoint_h

#include "../platform/WebCommon.h"
#include "../platform/WebFloatPoint.h"
#include "../platform/WebPointerProperties.h"

namespace blink {

// TODO(e_hakkinen): Replace WebTouchEvent with WebPointerEvent and remove
// WebTouchEvent and this.
class WebTouchPoint : public WebPointerProperties {
public:
    WebTouchPoint()
        : WebPointerProperties()
        , state(StateUndefined)
        , radiusX(0)
        , radiusY(0)
        , rotationAngle(0)
    {
    }

    enum State {
        StateUndefined,
        StateReleased,
        StatePressed,
        StateMoved,
        StateStationary,
        StateCancelled,
    };

    State state;

    // TODO(e_hakkinen): Move position fields to WebPointerProperties.
    WebFloatPoint screenPosition;
    WebFloatPoint position;

    float radiusX;
    float radiusY;
    float rotationAngle;
};

} // namespace blink

#endif
