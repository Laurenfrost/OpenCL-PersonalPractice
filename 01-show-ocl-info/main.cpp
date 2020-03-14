#include <iostream>
#include <string>
#include <CL/opencl.h>

using namespace std;

void printDeviceInfo(const cl_uint j, const cl_device_id did);
void printPlatformInfo(const cl_uint i, const cl_platform_id pid);

void printDeviceInfo(const cl_uint j, const cl_device_id did) {
    struct {
        size_t name_size;
        size_t vendor_size;
        size_t extensions_size;
        char* name;
        char* vendor;
        char* extensions;
        cl_ulong global_memory;
        cl_uint  address_bits;
        cl_bool  available;
        cl_bool  compiler_available;
    }device;   
    clGetDeviceInfo(did, CL_DEVICE_NAME, 0, NULL, &device.name_size);
    clGetDeviceInfo(did, CL_DEVICE_VENDOR, 0, NULL, &device.vendor_size);
    clGetDeviceInfo(did, CL_DEVICE_EXTENSIONS, 0, NULL, &device.extensions_size);
    device.name       = new char[device.name_size];
    device.vendor     = new char[device.vendor_size];
    device.extensions = new char[device.extensions_size];
    clGetDeviceInfo(did, CL_DEVICE_NAME, device.name_size, device.name, NULL);
    clGetDeviceInfo(did, CL_DEVICE_VENDOR, device.vendor_size, device.vendor, NULL);
    clGetDeviceInfo(did, CL_DEVICE_EXTENSIONS, device.extensions_size, device.extensions, NULL);
    clGetDeviceInfo(did, CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(cl_ulong), &device.global_memory, NULL);
    clGetDeviceInfo(did, CL_DEVICE_ADDRESS_BITS, sizeof(cl_uint), &device.address_bits, NULL);
    clGetDeviceInfo(did, CL_DEVICE_AVAILABLE, sizeof(cl_bool), &device.available, NULL);
    clGetDeviceInfo(did, CL_DEVICE_COMPILER_AVAILABLE, sizeof(cl_bool), &device.compiler_available, NULL);
    cout << "|   Device " << j << endl;
    cout << "|   |   " << "Device name        : " << device.name << endl;
    cout << "|   |   " << "       vendor      : " << device.vendor << endl;
    cout << "|   |   " << "       available   : " << (device.available ? "yes" : "no") << endl;
    cout << "|   |   " << "       compiler    : " << (device.compiler_available ? "yes" : "no") << endl;
    cout << "|   |   " << "       global mem  : " << device.global_memory << endl;
    cout << "|   |   " << "       address bits: " << device.address_bits << endl;
    cout << "|   -   " << "       extensions  : " << device.extensions << endl;

}
void printPlatformInfo(const cl_uint i, const cl_platform_id pid) {
    struct {
        size_t name_size;
        size_t vendor_size;
        size_t version_size;
        size_t profile_size;
        size_t extensions_size;
        char* name;
        char* vendor;
        char* version;
        char* profile;
        char* extensions;
    }platform;
    clGetPlatformInfo(pid, CL_PLATFORM_NAME, 0, NULL, &platform.name_size);
    clGetPlatformInfo(pid, CL_PLATFORM_VENDOR, 0, NULL, &platform.vendor_size);
    clGetPlatformInfo(pid, CL_PLATFORM_VERSION, 0, NULL, &platform.version_size);
    clGetPlatformInfo(pid, CL_PLATFORM_PROFILE, 0, NULL, &platform.profile_size);
    clGetPlatformInfo(pid, CL_PLATFORM_EXTENSIONS, 0, NULL, &platform.extensions_size);
    platform.name       = new char[platform.name_size];
    platform.vendor     = new char[platform.vendor_size];
    platform.version    = new char[platform.version_size];
    platform.profile    = new char[platform.profile_size];
    platform.extensions = new char[platform.extensions_size];
    clGetPlatformInfo(pid, CL_PLATFORM_NAME, platform.name_size, platform.name, NULL);
    clGetPlatformInfo(pid, CL_PLATFORM_VENDOR, platform.vendor_size, platform.vendor, NULL);
    clGetPlatformInfo(pid, CL_PLATFORM_VERSION, platform.version_size, platform.version, NULL);
    clGetPlatformInfo(pid, CL_PLATFORM_PROFILE, platform.profile_size, platform.profile, NULL);
    clGetPlatformInfo(pid, CL_PLATFORM_EXTENSIONS, platform.extensions_size, platform.extensions, NULL);
    cout << "Platform " << i << endl;
    cout << "|   " << "Platform name     : " << platform.name << endl;
    cout << "|   " << "         vendor   : " << platform.vendor << endl;
    cout << "|   " << "         version  : " << platform.version << endl;
    cout << "|   " << "         profile  : " << platform.profile << endl;
    cout << "|   " << "         extension: " << platform.extensions << endl;
}


int main() {
    cl_int err;
    cl_uint num_platforms;
    clGetPlatformIDs(0, NULL, &num_platforms);
    cl_platform_id* platforms = new cl_platform_id[num_platforms];
    clGetPlatformIDs(num_platforms, platforms, NULL);
    for (cl_uint i = 0; i < num_platforms; i++) {
        printPlatformInfo(i, platforms[i]);
        cl_uint num_devices;
        err = clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, 0, NULL, &num_devices);
        if (err < 0) {
            cout << "No devices found" << endl;
            exit(1);
        }
        cl_device_id* did = new cl_device_id[num_devices];
        clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, num_devices, did, NULL);
        for (cl_uint j = 0; j < num_devices; j++) {
            printDeviceInfo(j, did[i]);
        }
    }

//    system("pause");
    return 0;
}
