// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file has been auto-generated by code_generator_v8.py. DO NOT MODIFY!

#include "config.h"
#include "V8TestCallbackInterface.h"

#include "bindings/core/v8/ScriptController.h"
#include "bindings/core/v8/V8Binding.h"
#include "bindings/core/v8/V8TestInterfaceEmpty.h"
#include "bindings/core/v8/V8TestInterfaceWillBeGarbageCollected.h"
#include "core/dom/ExecutionContext.h"
#include "wtf/Assertions.h"
#include "wtf/GetPtr.h"
#include "wtf/RefPtr.h"

namespace blink {

V8TestCallbackInterface::V8TestCallbackInterface(v8::Local<v8::Function> callback, ScriptState* scriptState)
    : ActiveDOMCallback(scriptState->executionContext())
    , m_scriptState(scriptState)
{
    m_callback.set(scriptState->isolate(), callback);
}

V8TestCallbackInterface::~V8TestCallbackInterface()
{
}

DEFINE_TRACE(V8TestCallbackInterface)
{
    TestCallbackInterface::trace(visitor);
    ActiveDOMCallback::trace(visitor);
}

void V8TestCallbackInterface::voidMethod()
{
    if (!canInvokeCallback())
        return;

    if (!m_scriptState->contextIsValid())
        return;

    ScriptState::Scope scope(m_scriptState.get());
    v8::Local<v8::Value> *argv = 0;

    ScriptController::callFunction(m_scriptState->executionContext(), m_callback.newLocal(m_scriptState->isolate()), v8::Undefined(m_scriptState->isolate()), 0, argv, m_scriptState->isolate());
}

bool V8TestCallbackInterface::booleanMethod()
{
    if (!canInvokeCallback())
        return true;

    if (!m_scriptState->contextIsValid())
        return true;

    ScriptState::Scope scope(m_scriptState.get());
    v8::Local<v8::Value> *argv = 0;

    v8::TryCatch exceptionCatcher;
    exceptionCatcher.SetVerbose(true);
    ScriptController::callFunction(m_scriptState->executionContext(), m_callback.newLocal(m_scriptState->isolate()), v8::Undefined(m_scriptState->isolate()), 0, argv, m_scriptState->isolate());
    return !exceptionCatcher.HasCaught();
}

void V8TestCallbackInterface::voidMethodBooleanArg(bool boolArg)
{
    if (!canInvokeCallback())
        return;

    if (!m_scriptState->contextIsValid())
        return;

    ScriptState::Scope scope(m_scriptState.get());
    v8::Local<v8::Value> boolArgHandle = v8Boolean(boolArg, m_scriptState->isolate());
    if (boolArgHandle.IsEmpty()) {
        if (!isScriptControllerTerminating())
            CRASH();
        return;
    }
    v8::Local<v8::Value> argv[] = { boolArgHandle };

    ScriptController::callFunction(m_scriptState->executionContext(), m_callback.newLocal(m_scriptState->isolate()), v8::Undefined(m_scriptState->isolate()), 1, argv, m_scriptState->isolate());
}

void V8TestCallbackInterface::voidMethodSequenceArg(const Vector<RefPtr<TestInterfaceEmpty>>& sequenceArg)
{
    if (!canInvokeCallback())
        return;

    if (!m_scriptState->contextIsValid())
        return;

    ScriptState::Scope scope(m_scriptState.get());
    v8::Local<v8::Value> sequenceArgHandle = toV8(sequenceArg, m_scriptState->context()->Global(), m_scriptState->isolate());
    if (sequenceArgHandle.IsEmpty()) {
        if (!isScriptControllerTerminating())
            CRASH();
        return;
    }
    v8::Local<v8::Value> argv[] = { sequenceArgHandle };

    ScriptController::callFunction(m_scriptState->executionContext(), m_callback.newLocal(m_scriptState->isolate()), v8::Undefined(m_scriptState->isolate()), 1, argv, m_scriptState->isolate());
}

void V8TestCallbackInterface::voidMethodFloatArg(float floatArg)
{
    if (!canInvokeCallback())
        return;

    if (!m_scriptState->contextIsValid())
        return;

    ScriptState::Scope scope(m_scriptState.get());
    v8::Local<v8::Value> floatArgHandle = v8::Number::New(m_scriptState->isolate(), floatArg);
    if (floatArgHandle.IsEmpty()) {
        if (!isScriptControllerTerminating())
            CRASH();
        return;
    }
    v8::Local<v8::Value> argv[] = { floatArgHandle };

    ScriptController::callFunction(m_scriptState->executionContext(), m_callback.newLocal(m_scriptState->isolate()), v8::Undefined(m_scriptState->isolate()), 1, argv, m_scriptState->isolate());
}

void V8TestCallbackInterface::voidMethodTestInterfaceEmptyArg(TestInterfaceEmpty* testInterfaceEmptyArg)
{
    if (!canInvokeCallback())
        return;

    if (!m_scriptState->contextIsValid())
        return;

    ScriptState::Scope scope(m_scriptState.get());
    v8::Local<v8::Value> testInterfaceEmptyArgHandle = toV8(testInterfaceEmptyArg, m_scriptState->context()->Global(), m_scriptState->isolate());
    if (testInterfaceEmptyArgHandle.IsEmpty()) {
        if (!isScriptControllerTerminating())
            CRASH();
        return;
    }
    v8::Local<v8::Value> argv[] = { testInterfaceEmptyArgHandle };

    ScriptController::callFunction(m_scriptState->executionContext(), m_callback.newLocal(m_scriptState->isolate()), v8::Undefined(m_scriptState->isolate()), 1, argv, m_scriptState->isolate());
}

void V8TestCallbackInterface::voidMethodTestInterfaceEmptyStringArg(TestInterfaceEmpty* testInterfaceEmptyArg, const String& stringArg)
{
    if (!canInvokeCallback())
        return;

    if (!m_scriptState->contextIsValid())
        return;

    ScriptState::Scope scope(m_scriptState.get());
    v8::Local<v8::Value> testInterfaceEmptyArgHandle = toV8(testInterfaceEmptyArg, m_scriptState->context()->Global(), m_scriptState->isolate());
    if (testInterfaceEmptyArgHandle.IsEmpty()) {
        if (!isScriptControllerTerminating())
            CRASH();
        return;
    }
    v8::Local<v8::Value> stringArgHandle = v8String(m_scriptState->isolate(), stringArg);
    if (stringArgHandle.IsEmpty()) {
        if (!isScriptControllerTerminating())
            CRASH();
        return;
    }
    v8::Local<v8::Value> argv[] = { testInterfaceEmptyArgHandle, stringArgHandle };

    ScriptController::callFunction(m_scriptState->executionContext(), m_callback.newLocal(m_scriptState->isolate()), v8::Undefined(m_scriptState->isolate()), 2, argv, m_scriptState->isolate());
}

void V8TestCallbackInterface::callbackWithThisValueVoidMethodStringArg(ScriptValue thisValue, const String& stringArg)
{
    if (!canInvokeCallback())
        return;

    if (!m_scriptState->contextIsValid())
        return;

    ScriptState::Scope scope(m_scriptState.get());
    v8::Local<v8::Value> thisHandle = thisValue.v8Value();
    if (thisHandle.IsEmpty()) {
        if (!isScriptControllerTerminating())
            CRASH();
        return;
    }
    v8::Local<v8::Value> stringArgHandle = v8String(m_scriptState->isolate(), stringArg);
    if (stringArgHandle.IsEmpty()) {
        if (!isScriptControllerTerminating())
            CRASH();
        return;
    }
    v8::Local<v8::Value> argv[] = { stringArgHandle };

    ScriptController::callFunction(m_scriptState->executionContext(), m_callback.newLocal(m_scriptState->isolate()), thisHandle, 1, argv, m_scriptState->isolate());
}

void V8TestCallbackInterface::voidMethodWillBeGarbageCollectedSequenceArg(const WillBeHeapVector<RefPtrWillBeMember<TestInterfaceWillBeGarbageCollected>>& sequenceArg)
{
    if (!canInvokeCallback())
        return;

    if (!m_scriptState->contextIsValid())
        return;

    ScriptState::Scope scope(m_scriptState.get());
    v8::Local<v8::Value> sequenceArgHandle = toV8(sequenceArg, m_scriptState->context()->Global(), m_scriptState->isolate());
    if (sequenceArgHandle.IsEmpty()) {
        if (!isScriptControllerTerminating())
            CRASH();
        return;
    }
    v8::Local<v8::Value> argv[] = { sequenceArgHandle };

    ScriptController::callFunction(m_scriptState->executionContext(), m_callback.newLocal(m_scriptState->isolate()), v8::Undefined(m_scriptState->isolate()), 1, argv, m_scriptState->isolate());
}

void V8TestCallbackInterface::voidMethodWillBeGarbageCollectedArrayArg(const WillBeHeapVector<RefPtrWillBeMember<TestInterfaceWillBeGarbageCollected>>& arrayArg)
{
    if (!canInvokeCallback())
        return;

    if (!m_scriptState->contextIsValid())
        return;

    ScriptState::Scope scope(m_scriptState.get());
    v8::Local<v8::Value> arrayArgHandle = toV8(arrayArg, m_scriptState->context()->Global(), m_scriptState->isolate());
    if (arrayArgHandle.IsEmpty()) {
        if (!isScriptControllerTerminating())
            CRASH();
        return;
    }
    v8::Local<v8::Value> argv[] = { arrayArgHandle };

    ScriptController::callFunction(m_scriptState->executionContext(), m_callback.newLocal(m_scriptState->isolate()), v8::Undefined(m_scriptState->isolate()), 1, argv, m_scriptState->isolate());
}

} // namespace blink
