/**
@file
@author Ben Yuan
@date 2013
@copyright 2-clause BSD; see License section

@brief
A multi-user echo server to validate the network wrapper.

@section License

Copyright (c) 2012-2013 California Institute of Technology.
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies,
either expressed or implied, of the California Institute of Technology.

*/

#include "server1.hpp"

using namespace CS2Net;

int main(int argc, char ** argv)
{

    REQUIRE(argc == 2, "usage: %s port", argv[0]);

    /* TODO: write this code.
     *
     * Accept incoming connections as they arrive.
     * In the meantime, rebroadcast anything you recv to all users.
     *
     */
    CS2Net::Socket listener;
  
    uint16_t port = atoi(argv[1]); 
    
    int err = listener.Bind(port, 3);
    REQUIRE(err == 0, "Failed to bind");

    std::vector<CS2Net::PollFD> poll_vec(1);
    poll_vec[0].sock = &listener;
    poll_vec[0].SetRead(true);

    std::vector<CS2Net::PollFD> poll_vec2;

    while (true)
    {
      // poll listener
      int poll_err = CS2Net::Poll(&poll_vec, 10);
      REQUIRE(poll_err >= 0, "error on poll");

      if (poll_vec[0].HasHangup() || poll_vec[0].HasError())
      {
        ERROR("error on poll");
      }

      if (poll_vec[0].CanRead())
      { 
        CS2Net::Socket *incoming_conn = NULL;
        incoming_conn = listener.Accept();
        REQUIRE(incoming_conn != NULL, "Failed to accept!");

        CS2Net::PollFD poll1;
        poll1.sock = incoming_conn;
        poll1.SetRead(true);
        poll_vec2.push_back(poll1);
      }

      // poll connections
      int poll_err2 = CS2Net::Poll(&poll_vec2, 10);
      REQUIRE(poll_err2 >= 0, "error on poll");

        for (unsigned int i = 0; i < poll_vec2.size(); i++)
        {
          if (poll_vec2[i].HasHangup() || poll_vec2[i].HasError())
          {
            ERROR("error on poll");
          }

          if (poll_vec2[i].CanRead())
          {
            std::string *incoming = poll_vec2[i].sock->Recv(1024, false);

            if (incoming == NULL)
            {
              ERROR("recv error: %s", strerror(errno));
            }

            else
            {
              std::cout << "incoming: " << *incoming << std::endl;

              for (unsigned int i = 0; i < poll_vec2.size(); i++)
              {
                int ret = poll_vec2[i].sock->Send(incoming);

                if (ret < 0)
                {
                  if (ret == -1)                  
                  {
                    ERROR("send error: %s", strerror(errno));
                  }

                  else
                  {
                    ERROR("this error should never occur");
                  }
                }
              }
            } 
          }
        }
      }
    
    
    for (unsigned int i = 1; i < poll_vec.size(); i++)
    {
      delete poll_vec[i].sock;
    }
    

    return 0;

}
