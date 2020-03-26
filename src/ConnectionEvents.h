//
// Created by 毛华伟 on 2020/3/26.
//

#ifndef RSOCKET_EXAMPLE_CONNECTIONEVENTS_H
#define RSOCKET_EXAMPLE_CONNECTIONEVENTS_H

#include <rsocket/RSocket.h>
#include <iostream>


// 连接回调

class ConnectionEvents : public rsocket::RSocketConnectionEvents{

public:
  ConnectionEvents(){
    std::cout<<"ConnectionEvents"<<std::endl;
  }
  ~ConnectionEvents(){}




   void onConnected() {


     std::cout<<  "onConnected" <<std::endl;
   }
   void onDisconnected(const folly::exception_wrapper&) {
     std::cout<<"onDisconnected"<<std::endl;
   }
   void onClosed(const folly::exception_wrapper&) {
     std::cout<<"onClosed"<<std::endl;
   }
   void onStreamsPaused() {
     std::cout<<"onStreamsPaused"<<std::endl;
   }
   void onStreamsResumed() {

     std::cout<<"onStreamsResumed"<<std::endl;

   }


};


#endif // RSOCKET_EXAMPLE_CONNECTIONEVENTS_H
