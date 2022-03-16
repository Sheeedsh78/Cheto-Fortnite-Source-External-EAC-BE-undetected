#pragma once
#include <Windows.h>
#include <cstdint>
#include <TlHelp32.h>
#include <map>
#include <iostream>
#include <string>
#include <iomanip>
#include <chrono>
#include <thread>

class process_handler {
public:
	virtual ~process_handler() { };
	//P2C SRC BY PASTEPOLICE
	virtual bool is_attached() = 0;

	virtual bool attach(const char* proc_name) = 0;

	virtual	uint64_t get_module_base(const std::string& module_name) = 0;

	virtual void read_memory(uintptr_t src, uintptr_t dst, size_t size) = 0;
	//P2C SRC BY PASTEPOLICE
	//P2C SRC BY PASTEPOLICE
	virtual uint32_t virtual_protect(uint64_t address, size_t size, uint32_t protect) = 0;

	virtual uint64_t virtual_alloc(size_t size, uint32_t allocation_type, uint32_t protect, uint64_t address = NULL) = 0;
};
