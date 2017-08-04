/*
 * Copyright (C) 2009 Google Inc. All rights reserved.
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

#ifndef WebMediaPlayer_h
#define WebMediaPlayer_h

#include "WebCallbacks.h"
#include "WebCanvas.h"
#include "WebContentDecryptionModule.h"
#include "WebInbandTextTrack.h"
#include "WebMediaSource.h"
#include "WebMimeRegistry.h"
#include "WebSetSinkIdCallbacks.h"
#include "WebString.h"
#include "WebTimeRange.h"
#include "third_party/skia/include/core/SkXfermode.h"

#include <limits>

namespace blink {

class WebAudioSourceProvider;
class WebContentDecryptionModule;
class WebSecurityOrigin;
class WebString;
class WebURL;
struct WebRect;
struct WebSize;
class WebGraphicsContext3D;

class WebMediaPlayer {
public:
    enum NetworkState {
        NetworkStateEmpty,
        NetworkStateIdle,
        NetworkStateLoading,
        NetworkStateLoaded,
        NetworkStateFormatError,
        NetworkStateNetworkError,
        NetworkStateDecodeError,
    };

    enum ReadyState {
        ReadyStateHaveNothing,
        ReadyStateHaveMetadata,
        ReadyStateHaveCurrentData,
        ReadyStateHaveFutureData,
        ReadyStateHaveEnoughData,
    };

    enum Preload {
        PreloadNone,
        PreloadMetaData,
        PreloadAuto,
    };

    // Represents synchronous exceptions that can be thrown from the Encrypted
    // Media methods. This is different from the asynchronous MediaKeyError.
    enum MediaKeyException {
        MediaKeyExceptionNoError,
        MediaKeyExceptionInvalidPlayerState,
        MediaKeyExceptionKeySystemNotSupported,
        MediaKeyExceptionInvalidAccess,
    };

    enum CORSMode {
        CORSModeUnspecified,
        CORSModeAnonymous,
        CORSModeUseCredentials,
    };

    // Reported to UMA. Do not change existing values.
    enum LoadType {
        LoadTypeURL = 0,
        LoadTypeMediaSource = 1,
        LoadTypeMediaStream = 2,
        LoadTypeMax = LoadTypeMediaStream,
    };

    struct ContentDescription {
        WebString type;
        WebString codecs;
        WebString keySystem;
        WebString width;
        WebString height;
        WebString framerate;
        WebString bitrate;
        WebString channels;
    };

    typedef unsigned TrackId;

    virtual ~WebMediaPlayer() { }

    virtual void load(LoadType, const WebURL&, CORSMode, const WebString&) = 0;

    // Playback controls.
    virtual void play() = 0;
    virtual void prepareToPlay() {};
    virtual void pause() = 0;
    virtual bool supportsSave() const = 0;
    virtual void seek(double seconds) = 0;
    virtual void setRate(double) = 0;
    virtual void setVolume(double) = 0;

    virtual void requestRemotePlayback() { }
    virtual void requestRemotePlaybackControl() { }
    virtual void setPreload(Preload) { }
    virtual WebTimeRanges buffered() const = 0;
    virtual WebTimeRanges seekable() const = 0;

    // Attempts to switch the audio output device.
    // Implementations of setSinkId take ownership of the WebSetSinkCallbacks
    // object.
    // Note also that setSinkId implementations must make sure that all
    // methods of the WebSetSinkCallbacks object, including constructors and
    // destructors, run in the same thread where the object is created
    // (i.e., the blink thread).
    virtual void setSinkId(const WebString& sinkId, const WebSecurityOrigin&, WebSetSinkIdCallbacks*) = 0;

    // True if the loaded media has a playable video/audio track.
    virtual bool hasVideo() const = 0;
    virtual bool hasAudio() const = 0;

    // True if the media is being played on a remote device.
    virtual bool isRemote() const { return false; }

    // Dimension of the video.
    virtual WebSize naturalSize() const = 0;

    // Getters of playback state.
    virtual bool paused() const = 0;
    virtual bool seeking() const = 0;
    virtual double duration() const = 0;

    // Returns the 'timeline offset' as defined in the HTML5 spec
    // (http://www.w3.org/html/wg/drafts/html/master/embedded-content.html#timeline-offset).
    // The function should return the number of milliseconds between the
    // 'timeline offset' and January 1, 1970 UTC. Use base::Time::ToJsTime() for
    // generate this value from Chromium code. If the content does not have a
    // 'timeline offset' then std::numeric_limits<double>::quiet_NaN() should be returned.
    virtual double timelineOffset() const { return std::numeric_limits<double>::quiet_NaN(); }

    virtual double currentTime() const = 0;

    // Internal states of loading and network.
    virtual NetworkState networkState() const = 0;
    virtual ReadyState readyState() const = 0;

    virtual bool didLoadingProgress() = 0;

    virtual bool hasSingleSecurityOrigin() const = 0;
    virtual bool didPassCORSAccessCheck() const = 0;

    virtual double mediaTimeForTimeValue(double timeValue) const = 0;

    virtual unsigned decodedFrameCount() const = 0;
    virtual unsigned droppedFrameCount() const = 0;
    virtual unsigned corruptedFrameCount() const { return 0; }
    virtual unsigned audioDecodedByteCount() const = 0;
    virtual unsigned videoDecodedByteCount() const = 0;

    virtual void paint(WebCanvas*, const WebRect&, unsigned char alpha, SkXfermode::Mode) = 0;

    // TODO(dshwang): remove non-|target| version. crbug.com/349871
    virtual bool copyVideoTextureToPlatformTexture(WebGraphicsContext3D*, unsigned texture, unsigned internalFormat, unsigned type, bool premultiplyAlpha, bool flipY) { return false; }

    // Do a GPU-GPU textures copy. If the copy is impossible or fails, it returns false.
    virtual bool copyVideoTextureToPlatformTexture(WebGraphicsContext3D*, unsigned target,
        unsigned texture, unsigned internalFormat, unsigned type, int level,
        bool premultiplyAlpha, bool flipY) { return false; }
    // Copy sub video frame texture to |texture|. If the copy is impossible or fails, it returns false.
    virtual bool copyVideoSubTextureToPlatformTexture(WebGraphicsContext3D*, unsigned target,
        unsigned texture, int level, int xoffset, int yoffset, bool premultiplyAlpha,
        bool flipY) { return false; }

    virtual WebAudioSourceProvider* audioSourceProvider() { return nullptr; }

    // Returns whether keySystem is supported. If true, the result will be
    // reported by an event.
    virtual MediaKeyException generateKeyRequest(const WebString& keySystem, const unsigned char* initData, unsigned initDataLength) { return MediaKeyExceptionKeySystemNotSupported; }
    virtual MediaKeyException addKey(const WebString& keySystem, const unsigned char* key, unsigned keyLength, const unsigned char* initData, unsigned initDataLength, const WebString& sessionId) { return MediaKeyExceptionKeySystemNotSupported; }
    virtual MediaKeyException cancelKeyRequest(const WebString& keySystem, const WebString& sessionId) { return MediaKeyExceptionKeySystemNotSupported; }
    virtual void passDataAttributes(const WebVector<std::pair<WebString, WebString> >& attrs) { }
    virtual void setContentDecryptionModule(WebContentDecryptionModule* cdm, WebContentDecryptionModuleResult result) { result.completeWithError(WebContentDecryptionModuleExceptionNotSupportedError, 0, "ERROR"); }

    virtual void textTrackModeChanged(WebInbandTextTrack* textTrack, bool showing) { }

    // Sets the poster image URL.
    virtual void setPoster(const WebURL& poster) { }

    // Whether the WebMediaPlayer supports overlay fullscreen video mode. When
    // this is true, the video layer will be removed from the layer tree when
    // entering fullscreen, and the WebMediaPlayer is responsible for displaying
    // the video in enterFullscreen().
    virtual bool supportsOverlayFullscreenVideo() { return false; }
    // Instruct WebMediaPlayer to enter/exit fullscreen.
    virtual void enterFullscreen() { }

    virtual void addUnsupportedTextTrack(WebInbandTextTrack::Kind, const WebURL& url, const WebString& language, const WebString& label) { }

    virtual void enabledAudioTracksChanged(const WebVector<TrackId>& enabledTrackIds) { }
    // |selectedTrackId| is null if no track is selected.
    virtual void selectedVideoTrackChanged(TrackId* selectedTrackId) { }

    // Check if the mime type, codec and keySystem is supported by the
    // media player.
    static WebMimeRegistry::SupportsType supportsType(const ContentDescription& desc);
};

} // namespace blink

#endif
