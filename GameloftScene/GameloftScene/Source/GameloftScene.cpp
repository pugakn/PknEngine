#include "pkn_prerequiites.h"
#include "pkn_application.h"
using namespace pugaknSDK;
int main(Int32 argc, char** argv)
{
  Application::StartUp();
  Application::Instance().Init(argc,argv);
  return 0;
}
