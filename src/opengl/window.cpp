#include <algorithm>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "window.h"
#include "resource_manager.h"

// Init Window Pointer for OpenGL callbacks
Window* Window::windowPointer = NULL;

Window::Window(char* title, const int width, const int height) : title(title)
{
    // Store Pointer for OpenGL callbacks
    windowPointer = this;
    ResourceManager::ViewportWidth = width;
    ResourceManager::ViewportHeight = height;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if(window == NULL)
    {
        glfwTerminate();
        throw "Failed to create GLFW window";
    }
    
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, 
        [](GLFWwindow *window, int width, int height) 
        { 
            glViewport(0, 0, width, height); 
            ResourceManager::ViewportWidth = width;
            ResourceManager::ViewportHeight = height;
            Window::windowPointer->resize();
        });
    glfwSetKeyCallback(window, 
        [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            Window::windowPointer->handleKeys(key, scancode, action, mods);
        });
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        throw "Failed to initialize OpenGL context";
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsLight();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");    
    io.Fonts->AddFontFromFileTTF("PixelType.ttf", 16.0f);
}

void Window::setClearColor(const GLfloat red, const GLfloat green, const GLfloat blue, const GLfloat alpha) const
{
    glClearColor(red, green, blue, alpha);
}

void Window::startLoop()
{
    bool show_demo_window = true;
    while(!glfwWindowShouldClose(window))
    {        
        glClear(GL_COLOR_BUFFER_BIT);  

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
      
        for(Screen* screen : screenVec)
        {
            screen->render();
        }

        ImGui::ShowDemoWindow(&show_demo_window);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();    
    }
    glfwTerminate();
}

bool Window::addRowDefinition(const GridDefinition rowDefinition)
{
    bool result = true;
    for(GridDefinition existingDef : rowDefinitionVec)
    {
        if(existingDef.index == rowDefinition.index)
        {
            result = false;
            std::cout << "WARN::WINDOW::ROWINDEX_ALREADY_DEFINED";   
            break;
        }
    }
    if(result) rowDefinitionVec.push_back(rowDefinition);
    std::sort(rowDefinitionVec.begin(), rowDefinitionVec.end());

    return result;
}

bool Window::addColumnDefinition(const GridDefinition columnDefinition)
{
    bool result = true;
    for(GridDefinition existingDef : columnDefinitionVec)
    {
        if(existingDef.index == columnDefinition.index)
        {
            result = false;
            std::cout << "WARN::WINDOW::COLUMNINDEX_ALREADY_DEFINED";   
            break;
        }
    }
    if(result) columnDefinitionVec.push_back(columnDefinition);
    std::sort(columnDefinitionVec.begin(), columnDefinitionVec.end());

    return result;
}

bool Window::addScreen(Screen* screen)
{
    bool result = true;
    
    for(Screen* registeredScreen : screenVec)
    {
        if(registeredScreen->row == screen->row
        && registeredScreen->column == screen->column)
        {
            result = false;
            std::cout << "WARN::WINDOW::ROW_COLUMN_TAKEN";    
            break;
        }

        if(screen->column >= (int) columnDefinitionVec.size()
        || screen->row >= (int) rowDefinitionVec.size())
        {
            result = false;
            std::cout << "WARN::WINDOW::ROW_OR_COLUMN_NOT_DEFINED";    
            break;
        }
    }
    screenVec.push_back(screen);        
    resize();

    return result;
}

void Window::resize() const
{   
    float onePercentageWidth = ResourceManager::ViewportWidth / 100.0f;
    float onePercentageHeight = ResourceManager::ViewportHeight / 100.0f;

    float rowStartY = 0;
    for(int rowIndex = 0; rowIndex < (int) rowDefinitionVec.size(); rowIndex++)
    {
        GridDefinition rowDefinition = rowDefinitionVec.at(rowIndex);
        float rowHeight = rowDefinition.sizePercentage * onePercentageHeight;

        float columnStartX = 0;
        std::vector<Screen*> rowScreenVec = getScreensInRow(rowIndex);
        for(int colIndex = 0; colIndex < (int) rowScreenVec.size(); colIndex++)
        {
            GridDefinition columnDefinition = columnDefinitionVec.at(colIndex);
            float columnWidth = columnDefinition.sizePercentage * onePercentageWidth;
            
            if(colIndex == (int) rowScreenVec.size() - 1 && columnWidth + columnStartX < ResourceManager::ViewportWidth)
            {
                columnWidth = ResourceManager::ViewportWidth - columnStartX;
            }

            rowScreenVec.at(colIndex)->setScreenCords(columnStartX, rowStartY, columnStartX + columnWidth, rowStartY + rowHeight);
            columnStartX += columnWidth;
        }        
        rowStartY += rowHeight;
    }
}

void Window::handleKeys(const int key, const int scancode, const int action, const int mods) const
{
    for(Screen* screen : screenVec)
    {
        screen->handleKeys(key, scancode, action, mods);
    }
}

std::vector<Screen*> Window::getScreensInRow(const int row) const
{
    std::vector<Screen*> screensInRow;
    for(Screen* registeredScreen : screenVec)
    {
        if(registeredScreen->row == row)
        {
            screensInRow.push_back(registeredScreen);
        }
    }

    auto columnCompare = [](Screen *s, Screen *s2) { return s->column < s2->column; };
    std::sort(screensInRow.begin(), screensInRow.end(), columnCompare);    

    return screensInRow;
}