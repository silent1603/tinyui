
#include "sokol_app.h"
#include "sokol_gfx.h"
#include "sokol_log.h"
#include "sokol_glue.h"
#define IMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "imgui.h"
#include "util/sokol_imgui.h"


static struct {
	sg_pass_action pass_action;
} state;

static void init(void) {
	sg_desc desc = {};
	desc.environment = sglue_environment();
	desc.logger.func = slog_func;
	
	sg_setup(&desc);
	simgui_desc_t imgui_desc = { 0 };
	simgui_setup(&imgui_desc);

	// initial clear color
	sg_pass_action pass_action = {};
	pass_action.colors[0] = {};
	pass_action.colors[0].load_action = SG_LOADACTION_CLEAR;
	pass_action.colors[0].clear_value = { 0.0f, 0.5f, 1.0f, 1.0 };

	state.pass_action = pass_action;
}

static void frame(void) {
	simgui_frame_desc_t desc_t = {};
	desc_t.width = sapp_width();
	desc_t.height = sapp_height();
	desc_t.delta_time = sapp_frame_duration();
	desc_t.dpi_scale = sapp_dpi_scale();
	simgui_new_frame(&desc_t);

	/*=== UI CODE STARTS HERE ===*/

	ImGui::SetNextWindowPos({ 10, 10 }, ImGuiCond_Once, { 0, 0 });
	ImGui::SetNextWindowSize({ 400, 100 }, ImGuiCond_Once);
	ImGui::Begin("Hello Dear ImGui!", 0, ImGuiWindowFlags_None);
	ImGui::ColorEdit3("Background", &state.pass_action.colors[0].clear_value.r, ImGuiColorEditFlags_None);
	ImGui::End();
	/*=== UI CODE ENDS HERE ===*/
	sg_pass pass = {};
	pass.action = state.pass_action;
	pass.swapchain = sglue_swapchain();
	sg_begin_pass(&pass);
	simgui_render();
	sg_end_pass();
	sg_commit();
}

static void cleanup(void) {
	simgui_shutdown();
	sg_shutdown();
}

static void event(const sapp_event* ev) {
	simgui_handle_event(ev);
}

sapp_desc sokol_main(int argc, char* argv[]) {
	(void)argc;
	(void)argv;
	sapp_desc desc = {};
	desc.init_cb = init;
	desc.frame_cb = frame;
	desc.cleanup_cb = cleanup;
	desc.event_cb = event;
	desc.window_title = "Hello Sokol + Dear ImGui";
	desc.width = 800;
	desc.height = 600;
	desc.icon.sokol_default = true;
	desc.logger.func = slog_func;
	return desc;
}