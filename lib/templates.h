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

#include "getevents.h"
#include "wrapstar.h"

#if (NODE_MODULE_VERSION < 10)
#define RUNLOOP_SEMANTICS ev_run(ev_default_loop(), EVRUN_ONCE)
#else
#define RUNLOOP_SEMANTICS uv_run(uv_default_loop(), UV_RUN_ONCE)
#endif

NAN_METHOD(Socket) {
  NanScope();
  int64_t type = args[1].As<Number>()->IntegerValue();
  int ret = nn_socket(args[0].As<Number>()->IntegerValue(), type);
  if(type == NN_SUB)
    nn_setsockopt (ret, NN_SUB, NN_SUB_SUBSCRIBE, "", 0);
  NanReturnValue(NanNew<Number>(ret));
}

NAN_METHOD(Close){
  NanScope();
  int ret = nn_close(args[0].As<Number>()->IntegerValue());
  NanReturnValue(NanNew<Number>(ret));
}

NAN_METHOD(Bind) {
  int64_t s = args[0].As<Number>()->IntegerValue();
  String::Utf8Value addr(args[1]);
  NanReturnValue(NanNew<Number>(nn_bind(s, *addr)));
}

NAN_METHOD(Connect) {
  int64_t s = args[0].As<Number>()->IntegerValue();
  String::Utf8Value addr(args[1]);
  NanReturnValue(NanNew<Number>(nn_connect(s, *addr)));
}

NAN_METHOD(Send) {
  Local<Object> obj = args[1]->ToObject();
  nn_send (args[0].As<Number>()->IntegerValue(), node::Buffer::Data(obj),
  node::Buffer::Length(obj), args[2].As<Number>()->IntegerValue());
  NanReturnUndefined();
}

NAN_METHOD(SendString){
  int64_t s = args[0].As<Number>()->IntegerValue();
  String::Utf8Value str(args[1]);
  nn_send (s, *str, strlen(*str), args[2].As<Number>()->IntegerValue());
  NanReturnUndefined();
}

NAN_METHOD(Recv) {
  char *buf = NULL;
  nn_recv (args[0].As<Number>()->IntegerValue(), &buf, NN_MSG,
  args[1].As<Number>()->IntegerValue());

  nn_freemsg (buf);
  NanReturnValue(NanNew<String>(buf));
}

NAN_METHOD(RecvBuf) {
  void *buf = NULL;
  int r = nn_recv(args[0].As<Number>()->IntegerValue(), &buf, NN_MSG,
    args[1].As<Number>()->IntegerValue());

  nn_freemsg (buf);
  NanReturnValue(NanNewBufferHandle((char*) buf, r));
}

NAN_METHOD(GetEventIn){
  NanReturnValue(getevents(args[0].As<Number>()->IntegerValue(), NN_IN,
    args[1].As<Number>()->IntegerValue()));
}

NAN_METHOD(Stall) {
  NanScope();
  RUNLOOP_SEMANTICS;
  NanReturnUndefined();
}
