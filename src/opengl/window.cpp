#include <algorithm>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "window.hpp"
#include "resource_manager.hpp"

namespace OpenGL
{
    Window* WindowPointer = NULL;

    Window::Window(std::string title, const int width, const int height)
    {
        // Store Pointer for OpenGL callbacks
        OpenGL::WindowPointer = this;
        OpenGL::ViewportWidth = width;
        OpenGL::ViewportHeight = height;

        glfwInit();
        #if __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        #endif
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        glfwWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
        if(glfwWindow == NULL)
        {
            glfwTerminate();
            throw "Failed to create GLFW window";
        }
        
        glfwMakeContextCurrent(glfwWindow);
        glfwSetFramebufferSizeCallback(glfwWindow, 
            [](GLFWwindow *window, int width, int height) 
            { 
                glViewport(0, 0, width, height); 
                OpenGL::ViewportWidth = width;
                OpenGL::ViewportHeight = height;
            });
        glfwSetKeyCallback(glfwWindow, 
            [](GLFWwindow* window, int key, int scancode, int action, int mods)
            {
                OpenGL::WindowPointer->handleKeys(key, scancode, action, mods);
            });
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
        {
            throw "Failed to initialize OpenGL context";
        }

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        ImGui::StyleColorsLight();
        ImGui_ImplGlfw_InitForOpenGL(glfwWindow, true);
        ImGui_ImplOpenGL3_Init("#version 330");    
        io.Fonts->AddFontFromFileTTF("FiraMono-Regular.ttf", 16.0f);
        
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(0.96f, 0.96f, 0.96f, 255.00f));
        ImGui::PushStyleColor(ImGuiCol_MenuBarBg, ImVec4(0.94f, 0.94f, 0.94f, 1.00f));
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.19f, 0.19f, 0.19f, 1.00f));
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.96f, 0.96f, 0.96f, 255.00f));
        ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.90f, 0.90f, 0.90f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0.78f, 0.78f, 0.78f, 0.40f));
        ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(0.78f, 0.78f, 0.78f, 1.00f));
        ImGui::PushStyleColor(ImGuiCol_CheckMark, ImVec4(0.19f, 0.19f, 0.19f, 1.00f));
        ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(0.43f, 0.43f, 0.43f, 0.78f));
        ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(0.19f, 0.19f, 0.19f, 0.60f));
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.78f, 0.78f, 0.78f, 0.40f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.86f, 0.86f, 0.86f, 1.00f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.78f, 0.78f, 0.78f, 1.00f));
        ImGui::PushStyleColor(ImGuiCol_ResizeGripHovered, ImVec4(0.86f, 0.86f, 0.86f, 1.00f));
        ImGui::PushStyleColor(ImGuiCol_ResizeGripActive, ImVec4(0.78f, 0.78f, 0.78f, 1.00f));
        ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.78f, 0.78f, 0.78f, 0.40f));
        ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(0.74f, 0.74f, 0.74f, 1.00f));
        ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0.86f, 0.86f, 0.86f, 1.00f));
        ImGui::PushStyleColor(ImGuiCol_Separator, ImVec4(0.86f, 0.86f, 0.86f, 0.62f));
        ImGui::PushStyleColor(ImGuiCol_SeparatorHovered, ImVec4(0.00f, 0.45f, 1.00f, 0.78f));
        ImGui::PushStyleColor(ImGuiCol_Tab, ImVec4(0.78f, 0.78f, 0.78f, 0.40f));
        ImGui::PushStyleColor(ImGuiCol_TabHovered, ImVec4(0.86f, 0.86f, 0.86f, 1.00f));
        ImGui::PushStyleColor(ImGuiCol_TabActive, ImVec4(0.78f, 0.78f, 0.78f, 1.00f));
        ImGui::PushStyleColor(ImGuiCol_TabUnfocusedActive, ImVec4(0.92f, 0.93f, 0.93f, 0.98f));
    }

    void Window::startLoop()
    {
        bool show_demo_window = true;
        while(!glfwWindowShouldClose(glfwWindow))
        {        
            glClear(GL_COLOR_BUFFER_BIT);  

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
        
            for(Screen* screen : screenVec)
            {
                screen->update();
            }
            
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            ImGuiIO& io = ImGui::GetIO(); (void)io;
            if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
            {
                GLFWwindow* backup_current_context = glfwGetCurrentContext();
                ImGui::UpdatePlatformWindows();
                ImGui::RenderPlatformWindowsDefault();
                glfwMakeContextCurrent(backup_current_context);
            }

            glfwSwapBuffers(glfwWindow);
            glfwPollEvents();    
        }
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        glfwDestroyWindow(glfwWindow);
        glfwTerminate();
    }

    void Window::addScreen(Screen* screen)
    {
        screenVec.push_back(screen);     
    }

    void Window::setClearColor(const GLfloat red, const GLfloat green, const GLfloat blue, const GLfloat alpha) const
    {
        glClearColor(red/255, green/255, blue/255, alpha/255);
    }

    void Window::handleKeys(const int key, const int scancode, const int action, const int mods) const
    {
        for(Screen* screen : screenVec)
        {
            screen->handleKeys(key, scancode, action, mods);
        }
    }
}