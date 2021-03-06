#include "core/imgui/ImGuiLayer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "core/Application.h"
#include "core/events/Event.h"
#include "core/imgui/ImGuiBuild.h"

namespace engine {
namespace imgui {

bool ImGuiLayer::show_demo_window_ = true;

ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {}
ImGuiLayer::~ImGuiLayer() {}

/**
 * The default OnAttach creates a context, activates dark mode, and register
 * inputs with GLFW keys. This implementation currently only supports OpenGL and
 * will be modified in the future to use engine specified key codes.
 */
void ImGuiLayer::OnAttach() {
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();

  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

  ImGui::StyleColorsDark();

  ImGuiStyle& style = ImGui::GetStyle();
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    style.WindowRounding = 0.0f;
    style.Colors[ImGuiCol_WindowBg].w = 1.0f;
  }

  const Application& app = Application::GetApplication();
  GLFWwindow* window = static_cast<GLFWwindow*>(
      app.GetWindow().GetNativeWindow());

  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 410");
}

/**
 * Currently also only supports OpenGL.
 */
void ImGuiLayer::OnDetach() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

void ImGuiLayer::Begin() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}

void ImGuiLayer::End() {
  ImGuiIO& io = ImGui::GetIO();
  const Application& app = Application::GetApplication();
  io.DisplaySize = ImVec2(
      app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    GLFWwindow* current_context_backup = glfwGetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    glfwMakeContextCurrent(current_context_backup);
  }
}

void ImGuiLayer::OnImGuiRender() {
  ImGui::ShowDemoWindow(&show_demo_window_);
}

}  // namespace imgui
}  // namespace engine
