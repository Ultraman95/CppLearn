#include "hello_client_impl.h"

HelloClientImpl::HelloClientImpl(std::shared_ptr<grpc::Channel> channel)
: _stub(Yano::Greeter::NewStub(channel)) {}

std::string HelloClientImpl::SayHello(const std::string &user) {
  Yano::HelloRequest req;
  req.set_name(user);

  Yano::HelloReply res;

  grpc::ClientContext context;

  grpc::Status status = _stub->SayHello(&context, req, &res);

  if (status.ok()) {
    return res.message();
  } else {
    return "RPC failed";
  }
}
