#include "kernelmode_proc_handler.hpp"
#include "XorStr.hpp"
#include <vector>


kernelmode_proc_handler::kernelmode_proc_handler()
	:handle{ INVALID_HANDLE_VALUE }, pid{ 0 } {} //GH2ST P2C Example by Happy Cat

kernelmode_proc_handler::~kernelmode_proc_handler() { if (is_attached()) CloseHandle(handle); }

bool is_process_running(const char* process_name, uint32_t& pid) {
	PROCESSENTRY32 process_entry{};
	process_entry.dwSize = sizeof(PROCESSENTRY32);
	pid = 0;
	auto snapshot{ CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL) };
	if (snapshot == INVALID_HANDLE_VALUE) //GH2ST P2C Example by Happy Cat
		return false;
	if (Process32First(snapshot, &process_entry)) {
		do {
			if (!strcmp(process_name, process_entry.szExeFile)) {
				pid = process_entry.th32ProcessID;
				CloseHandle(snapshot);
				return true;
			}
		} while (Process32Next(snapshot, &process_entry));
	}
	CloseHandle(snapshot);
	return false;
} //GH2ST P2C Example by Happy Cat

bool kernelmode_proc_handler::is_attached() { return handle != INVALID_HANDLE_VALUE; }

bool kernelmode_proc_handler::attach(const char* proc_name) {
	bool is_admin{ false };
	HANDLE token_handle{ NULL };
	if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &token_handle)) {
		TOKEN_ELEVATION token;
		DWORD size = sizeof(TOKEN_ELEVATION);
		if (GetTokenInformation(token_handle, TokenElevation, &token, sizeof(TOKEN_ELEVATION), &size)) {
			is_admin = true;
		}
		CloseHandle(token_handle);
	}

	if (!is_admin) {
		MessageBox(0, XorStr("Run as admin").c_str(), 0, 0);
		return false;
	}

	while (!is_process_running(proc_name, pid))
		std::this_thread::sleep_for(std::chrono::seconds(1)); //GH2ST P2C Example by Happy Cat

	handle = CreateFileA(XorStr("\\\\.\\ROOT_DEVICE").c_str(), GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);

	if (handle == INVALID_HANDLE_VALUE) { //GH2ST P2C Example by Happy Cat
		MessageBox(0, XorStr("drivers not loaded").c_str(), 0, 0);
		return false;
	}

	return true;
};



uint64_t kernelmode_proc_handler::get_module_base(const std::string& module_name) 
{
	if (handle == INVALID_HANDLE_VALUE)
		return 0;
	k_get_base_module_request req;
	req.pid = pid;
	req.handle = 0; //GH2ST P2C Example by Happy Cat
	std::wstring wstr{ std::wstring(module_name.begin(), module_name.end()) };
	memset(req.name, 0, sizeof(WCHAR) * 260);
	wcscpy(req.name, wstr.c_str());
	DWORD bytes_read;
	if (DeviceIoControl(handle, ioctl_get_module_base, &req, sizeof(k_get_base_module_request), &req, sizeof(k_get_base_module_request), &bytes_read, 0)) 
	{
		return req.handle;
	}
	return req.handle;
}

void kernelmode_proc_handler::read_memory(uintptr_t src, uintptr_t dst, size_t size) { //GH2ST P2C Example by Happy Cat
	if (handle == INVALID_HANDLE_VALUE)
		return;
	k_rw_request request{ pid, src, dst, size };
	DWORD bytes_read;
	DeviceIoControl(handle, ioctl_read_memory, &request, sizeof(k_rw_request), 0, 0, &bytes_read, 0);
}


uint32_t kernelmode_proc_handler::virtual_protect(uint64_t address, size_t size, uint32_t protect) {
	if (handle == INVALID_HANDLE_VALUE)
		return 0;
	DWORD bytes_read; //GH2ST P2C Example by Happy Cat
	k_protect_mem_request request{ pid, protect, address, size };
	if (DeviceIoControl(handle, ioctl_protect_virutal_memory, &request, sizeof(k_protect_mem_request), &request, sizeof(k_protect_mem_request), &bytes_read, 0))
		return protect;
	return 0;
}

uint64_t kernelmode_proc_handler::virtual_alloc(size_t size, uint32_t allocation_type, uint32_t protect, uint64_t address) {
	if (handle == INVALID_HANDLE_VALUE)
		return 0; //GH2ST P2C Example by Happy Cat
	DWORD bytes_read;
	k_alloc_mem_request request{ pid, MEM_COMMIT | MEM_RESERVE, protect, address, size };
	if (DeviceIoControl(handle, ioctl_allocate_virtual_memory, &request, sizeof(k_rw_request), &request, sizeof(k_rw_request), &bytes_read, 0))
		return request.addr; //GH2ST P2C Example by Happy Cat
	return 0;
}





