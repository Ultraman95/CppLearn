#pragma once

#include "hello.grpc.pb.h"

#include <grpcpp/grpcpp.h>

#include <memory>
#include <string>

class HelloClientImpl {
 public:
  HelloClientImpl(std::shared_ptr<grpc::Channel> channel);
  std::string SayHello(const std::string &user);
 private:
  std::unique_ptr<Yano::Greeter::Stub> _stub;
};
