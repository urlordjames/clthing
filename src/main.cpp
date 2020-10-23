#include <CL/cl.hpp>
#include <iostream>

int main() {
  std::vector<cl::Platform> platforms;
  cl::Platform::get(&platforms);
  std::cout << "number of platforms detected: " << platforms.size() << '\n';
  
  auto platform = platforms.front();

  std::string vendor;
  platform.getInfo(CL_PLATFORM_VENDOR, &vendor);
  std::cout << "platform vendor: " << vendor << '\n';

  std::string platformname;
  platform.getInfo(CL_PLATFORM_NAME, &platformname);
  std::cout << "platform name: " << platformname << '\n';

  std::vector<cl::Device> devices;
  platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);
  
  auto device = devices.front();

  std::string devicename;
  device.getInfo(CL_DEVICE_NAME, &devicename);

  std::cout << "device name: " << devicename << '\n';
}
