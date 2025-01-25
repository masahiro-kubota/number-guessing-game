#include "IoFactory.hpp"

std::shared_ptr<IIoHandler> generate_io(std::string io_type){
  if(io_type == "cli"){
    return std::make_shared<CliIo>();
  }else if(io_type == "ros"){
    return std::make_shared<RosIo>();
  }else{
    throw std::invalid_argument("invalid io type");
  }
}