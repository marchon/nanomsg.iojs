/*
 * This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means.
 *
 * In jurisdictions that recognize copyright laws, the author or authors
 * of this software dedicate any and all copyright interest in the
 * software to the public domain. We make this dedication for the benefit
 * of the public at large and to the detriment of our heirs and
 * successors. We intend this dedication to be an overt act of
 * relinquishment in perpetuity of all present and future rights to this
 * software under copyright law.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * For more information, please refer to <http://www.wtfpl.net/>
 */

extern "C" {
  #include <nanomsg/nn.h>
  #include <nanomsg/pubsub.h>
  #include <nanomsg/pipeline.h>
  #include <nanomsg/bus.h>
  #include <nanomsg/pair.h>
  #include <nanomsg/reqrep.h>
  #include <nanomsg/survey.h>
  #include <nanomsg/ipc.h>
  #include <nanomsg/tcp.h>
  #include <nanomsg/inproc.h>
}

#include "node.h"
#include "node_buffer.h"
#include "nan.h"

#define EXPORT_METHOD(C, S) C->Set(NanNew(# S), NanNew<FunctionTemplate>(S)->GetFunction());

//using v8::Array;
using v8::Function;
using v8::FunctionTemplate;
using v8::Handle;
using v8::Local;
using v8::Number;
using v8::Object;
using v8::String;
using v8::StringObject;
using v8::Value;

#include "templates.h"

void module(Handle<Object> exports) {

  // Functions
  EXPORT_METHOD(exports, Socket);
  EXPORT_METHOD(exports, Close);
  EXPORT_METHOD(exports, Connect);
  EXPORT_METHOD(exports, Bind);
  EXPORT_METHOD(exports, Send);
  EXPORT_METHOD(exports, SendString);
  EXPORT_METHOD(exports, Recv);
  EXPORT_METHOD(exports, RecvBuf);
  EXPORT_METHOD(exports, GetEventIn);

  // SP address families
  NODE_DEFINE_CONSTANT(exports, AF_SP);
  NODE_DEFINE_CONSTANT(exports, AF_SP_RAW);

  // Max size of an SP address
  NODE_DEFINE_CONSTANT(exports, NN_SOCKADDR_MAX);

  // Socket option levels
  NODE_DEFINE_CONSTANT(exports, NN_SOL_SOCKET);

  // Generic socket options (NN_SOL_SOCKET level)
  NODE_DEFINE_CONSTANT(exports, NN_LINGER);
  NODE_DEFINE_CONSTANT(exports, NN_SNDBUF);
  NODE_DEFINE_CONSTANT(exports, NN_RCVBUF);
  NODE_DEFINE_CONSTANT(exports, NN_SNDTIMEO);
  NODE_DEFINE_CONSTANT(exports, NN_RCVTIMEO);
  NODE_DEFINE_CONSTANT(exports, NN_RECONNECT_IVL);
  NODE_DEFINE_CONSTANT(exports, NN_RECONNECT_IVL_MAX);
  NODE_DEFINE_CONSTANT(exports, NN_SNDPRIO);
  NODE_DEFINE_CONSTANT(exports, NN_RCVPRIO);
  NODE_DEFINE_CONSTANT(exports, NN_SNDFD);
  NODE_DEFINE_CONSTANT(exports, NN_RCVFD);
  NODE_DEFINE_CONSTANT(exports, NN_DOMAIN);
  NODE_DEFINE_CONSTANT(exports, NN_PROTOCOL);
  NODE_DEFINE_CONSTANT(exports, NN_IPV4ONLY);
  NODE_DEFINE_CONSTANT(exports, NN_SOCKET_NAME);

  // Send/recv options
  NODE_DEFINE_CONSTANT(exports, NN_DONTWAIT);

  // Ancillary data.
  NODE_DEFINE_CONSTANT(exports, PROTO_SP);
  NODE_DEFINE_CONSTANT(exports, SP_HDR);

  // Mutliplexing support
  NODE_DEFINE_CONSTANT(exports, NN_POLLIN);
  NODE_DEFINE_CONSTANT(exports, NN_POLLOUT);

  // Socket types
  NODE_DEFINE_CONSTANT(exports, NN_SURVEYOR);
  NODE_DEFINE_CONSTANT(exports, NN_RESPONDENT);
  NODE_DEFINE_CONSTANT(exports, NN_REQ);
  NODE_DEFINE_CONSTANT(exports, NN_REP);
  NODE_DEFINE_CONSTANT(exports, NN_PAIR);
  NODE_DEFINE_CONSTANT(exports, NN_PUSH);
  NODE_DEFINE_CONSTANT(exports, NN_PULL);
  NODE_DEFINE_CONSTANT(exports, NN_PUB);
  NODE_DEFINE_CONSTANT(exports, NN_SUB);
  NODE_DEFINE_CONSTANT(exports, NN_BUS);
}

NODE_MODULE(nanomsg, module)
