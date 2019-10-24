#pragma once

#include <grpcpp/grpcpp.h>

//#include "hello.pb.h"
#include "hello.grpc.pb.h"

class HelloServerImpl final : public Yano::Greeter::Service {
public:
  HelloServerImpl() = default;
  grpc::Status SayHello(grpc::ServerContext *context, const Yano::HelloRequest *req, Yano::HelloReply *reply) override;
};

void RunServer();
