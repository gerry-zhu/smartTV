/*
 * Copyright (C) 2011, 2012 Apple Inc.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef TextTrackList_h
#define TextTrackList_h

#include "core/CoreExport.h"
#include "core/events/EventListener.h"
#include "core/events/EventTarget.h"
#include "core/html/HTMLMediaElement.h"
#include "platform/Timer.h"
#include "platform/heap/Handle.h"
#include "wtf/PassRefPtr.h"
#include "wtf/RefCounted.h"
#include "wtf/Vector.h"

namespace blink {

class GenericEventQueue;
class TextTrack;

class CORE_EXPORT TextTrackList final : public RefCountedGarbageCollectedEventTargetWithInlineData<TextTrackList> {
    DEFINE_WRAPPERTYPEINFO();
    REFCOUNTED_GARBAGE_COLLECTED_EVENT_TARGET(TextTrackList);
public:
    static TextTrackList* create(HTMLMediaElement* owner)
    {
        return new TextTrackList(owner);
    }
    ~TextTrackList() override;

    unsigned length() const;
    int getTrackIndex(TextTrack*);
    int getTrackIndexRelativeToRenderedTracks(TextTrack*);
    bool contains(TextTrack*) const;

    TextTrack* anonymousIndexedGetter(unsigned index);
    TextTrack* getTrackById(const AtomicString& id);
    void append(TextTrack*);
    void remove(TextTrack*);

    // EventTarget
    const AtomicString& interfaceName() const override;
    ExecutionContext* executionContext() const override;

    DEFINE_ATTRIBUTE_EVENT_LISTENER(addtrack);
    DEFINE_ATTRIBUTE_EVENT_LISTENER(change);
    DEFINE_ATTRIBUTE_EVENT_LISTENER(removetrack);

#if !ENABLE(OILPAN)
    void clearOwner();
#endif
    HTMLMediaElement* owner() const;

    void scheduleChangeEvent();
    void removeAllInbandTracks();

    bool hasShowingTracks();

    DECLARE_VIRTUAL_TRACE();

private:
    explicit TextTrackList(HTMLMediaElement*);

    void scheduleTrackEvent(const AtomicString& eventName, TextTrack*);

    void scheduleAddTrackEvent(TextTrack*);
    void scheduleRemoveTrackEvent(TextTrack*);

    void invalidateTrackIndexesAfterTrack(TextTrack*);

    RawPtrWillBeMember<HTMLMediaElement> m_owner;

    OwnPtrWillBeMember<GenericEventQueue> m_asyncEventQueue;

    HeapVector<Member<TextTrack>> m_addTrackTracks;
    HeapVector<Member<TextTrack>> m_elementTracks;
    HeapVector<Member<TextTrack>> m_inbandTracks;
};

} // namespace blink

#endif // TextTrackList_h
