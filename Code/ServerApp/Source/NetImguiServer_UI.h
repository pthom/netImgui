#pragma once
#include <functional>

namespace NetImguiServer { namespace App { struct ServerTexture; } } // Forward Declare

namespace NetImguiServer { namespace UI
{
	constexpr uint32_t			kWindowDPIDefault	= 96;
	bool						Startup();
	void						Shutdown();
	ImVec4						DrawImguiContent();
	void						DrawCenteredBackground( const App::ServerTexture& Texture, const ImVec4& tint=ImVec4(1.f,1.f,1.f,1.f));
	float						GetDisplayFPS();
	const App::ServerTexture&	GetBackgroundTexture();

	// DPI handling options (to be set at server startup)
	// =================================================
	// You have two options to handle DPI scaling:
    // 1. Either set the window DPI:
    //     it will be used to scale the Fonts, either by calling the fontCreateFunction given at connection
    //     or by setting ImGui::GetIO().FontGlobalScale for the client
    // This simple version will work correctly on windows
	void						SetWindowDPI(uint32_t dpi);
	// 2. Or let the server transmit all its DPI settings to the clients:
	//    - DisplayFramebufferScale
	//      The server's ImGui::GetIO().DisplayFramebufferScale will be applied to the buffer in which the client will render
	//    - FontGlobalScale (from ImGui::GetIO().FontGlobalScale)
	//      The server's value for ImGui::GetIO().FontGlobalScale will be transmitted to clients
	//    - FontSizeLoadingRatio (which you need to set here): this is the ratio by which clients should multiply their font size at loading time
	// Warning, in this second case, clients need to actively call GetFontSizeLoadingRatio() to get this value
	void						SetUseServerDPISettings(float fontSizeLoadingRatio);

	// Provide a callback that will be called if the client want to change the window size
	// It is up to the server to check if that size fits on the screen, and to
	// adjust that size so that it correspond to a size on a 96PPI screen.
	// (the server may decide to apply a smaller size if needed)
	void 						SetCallbackWindowSize96PPI(std::function<void(uint16_t, uint16_t)> callbackWindowSize96PPI);

    // Internal API
	// ------------------------------------------------
    float						Internal_GetFontDPIScale(); // Returns a DPI Scale calculated from the window DPI, or ImGui::GetIO().FontGlobalScale if SetUseServerDPISettings() was called
	ImVec2						Internal_GetDisplayFramebufferScale(); // Returns (1,1) or ImGui::GetIO().DisplayFramebufferScale if SetUseServerDPISettings() was called
	float 						Internal_GetFontSizeLoadingRatio(); // Returns 1 or the value set by SetUseServerDPISettings()
	void						Internal_OnWindowSize96PPI(uint16_t width, uint16_t height);
}} //namespace NetImguiServer { namespace UI