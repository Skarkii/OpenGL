#include "render.h"


#define GL_CHECK(x) \
    do { \
        x; \
        GLenum glErr; \
        while ((glErr = glGetError()) != GL_NO_ERROR) { \
            std::cerr << "OpenGL error in " << __FILE__ << ":" << __LINE__ << " - " << #x << "():" << std::endl; \
            std::cerr << glErr << std::endl; \
        } \
    } while (false)

Render::Render()
{

}

Render::~Render()
{
    
}


void Render::Loop()
{
    this->mtx->lock();
    glfwMakeContextCurrent(this->window);

    if(glfwGetCurrentContext() == NULL) { std::cout << "Failed to make context current!" << std::endl; }

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        system("pause");
        glfwSetWindowShouldClose(this->window, true);
        return;
    }
        GL_CHECK();

    float base = 0.5f;

    float vertices[] = {
        -base, -base, 0.0f,
        -base, base, 0.0f,
        base, -base, 0.0f,
        base, base, 0.0f
    };
    
    unsigned int indices[] = {  
    0, 1, 2,   // first triangle
    1, 2, 3    // second triangle
    };

    Shader* vertex = new Shader("shaders/default.vert", GL_VERTEX_SHADER);
    Shader* frag = new Shader("shaders/default.frag", GL_FRAGMENT_SHADER);

    ShaderProgram program = ShaderProgram();

    program.AttachShader(vertex);
    program.AttachShader(frag);

    program.Link();

    VBO vbo;
    VAO vao;
    EBO ebo;


    vbo.SetBufferData(vertices, sizeof(vertices));

    ebo.SetBufferData(indices, sizeof(indices));

    vao.LinkVBO(vbo);

    this->mtx->unlock();


    while(!glfwWindowShouldClose(this->window))
    {
        this->mtx->lock();
        glfwMakeContextCurrent(this->window);

        glClearColor(0.5f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        program.SetActive();

        vao.Bind();

        ebo.Bind();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
        //glDrawArrays(GL_TRIANGLES, 0, 3);

        vao.Unbind();

        glfwSwapBuffers(this->window);
        glfwMakeContextCurrent(NULL);
        this->mtx->unlock();
    }
}
       
void Render::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    std::cout << "Viewport changed to : [" << width << "][" << height << "]" << std::endl;

    this->mtx->lock();

    glfwMakeContextCurrent(this->window);

    glViewport(0,0,width, height);

    glfwMakeContextCurrent(NULL);

    this->mtx->unlock();
}

GLFWwindow* Render::GetWindowPtr()
{
    return this->window;
}

void Render::StaticFramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    Render* instance = reinterpret_cast<Render*>(glfwGetWindowUserPointer(window));
    instance->FramebufferSizeCallback(window, width, height);
}

void Render::test()
{
    std::cout << "Test" << std::endl;
}

void Render::SetWindowPtr(GLFWwindow* win)
{
    this->window = win;
}

void Render::Init(int width, int height, std::string title, std::mutex* _mtx)
{
    if(this->window != nullptr) 
    { 
        std::cout << "Window is already initialized!" << std::endl;
        return; 
    }
    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

    if(this->window == NULL)
    {
        std::cout << "Failed to initialize GLFW!" << std::endl;
        glfwTerminate();
        return;
    }
    
    this->mtx = _mtx;

    if(this->mtx == nullptr)
    {
        std::cout << "Failed to link to mtx" << std::endl;
        return;
    }

    glfwSetWindowUserPointer(this->window, this);
    glfwSetFramebufferSizeCallback(this->window, this->StaticFramebufferSizeCallback);

    return;
}

