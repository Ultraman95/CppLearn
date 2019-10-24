#include "hello_client_impl.h"

#include <iostream>

int main() {
  HelloClientImpl client(grpc::CreateChannel("localhost:50041", grpc::InsecureChannelCredentials()));
  std::string user("world");
  std::string reply = client.SayHello("YaniPapi");
  std::cout << "Client received: " << reply << std::endl;
  return 0;
}
