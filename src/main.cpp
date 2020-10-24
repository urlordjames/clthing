#include <CL/cl.hpp>
#include <iostream>
#include <fstream>
#include <vector>

int main() {
  // get platform
  std::vector<cl::Platform> platforms;
  cl::Platform::get(&platforms);
  auto platform = platforms.front();

  // print platform vendor
  std::string vendor;
  platform.getInfo(CL_PLATFORM_VENDOR, &vendor);
  std::cout << "platform vendor: " << vendor << '\n';

  // print platform name
  std::string platformname;
  platform.getInfo(CL_PLATFORM_NAME, &platformname);
  std::cout << "platform name: " << platformname << '\n';

  // get first device
  std::vector<cl::Device> devices;
  platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);
  auto device = devices.front();

  // print device name
  std::string devicename;
  device.getInfo(CL_DEVICE_NAME, &devicename);
  std::cout << "device name: " << devicename << '\n';

  // get kernel code string from file
  std::ifstream kernelcode;
  kernelcode.open("src/helloWorld.cl");
  std::string code((std::istreambuf_iterator<char>(kernelcode)), (std::istreambuf_iterator<char>()));
  kernelcode.close();

  // initialize and push code into sources
  cl::Program::Sources sources;
  sources.push_back({code.c_str(), code.length()});

  //create context
  cl::Context context({device});

  // initialize program
  cl::Program program(context, sources);
  
  // build program
  std::cout << "BUILDING...\n";
  auto build_error = program.build();

  // get build log if error
  if (build_error != 0) {
    std::cout << "BUILD ERROR: " << build_error << '\n';
    std::string log;
    program.getBuildInfo(device, CL_PROGRAM_BUILD_LOG, &log);
    std::cout << log << '\n';
  }

  // initialize input data
  std::vector<int> input(4096);
  std::fill(input.begin(), input.end(), 3);

  // initialize input buffer
  cl::Buffer inBuf(context, CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR | CL_MEM_HOST_NO_ACCESS, sizeof(int) * input.size(), input.data());

  // initialize kernel
  cl::Kernel kernel(program, "helloWorld");

  // set kernel args
  kernel.setArg(0, inBuf);

  // initialize command queue
  cl::CommandQueue queue(context, device);

  // queue the kernel and asynchronously put the data back in the vector
  queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(input.size()));
  queue.enqueueReadBuffer(inBuf, false, 0, sizeof(int) * input.size(), input.data());

  std::cout << "letting OpenCL do it's magic...\n";

  // await async buffer read
  cl::finish();

  // print the first value of the vector
  std::cout << input.front() << '\n';
}
