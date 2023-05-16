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

void Render::UpdateCameraPosition(glm::vec3 add)
{
    this->cameraPosition = this->cameraPosition + (this->cameraSpeed * add);
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
    
    float base = 0.5f;

    float vertices[] = {
    //    X       Y      Z       R       G       B       IX      IY
          base,   base,  base,   0.0f,   1.0f,   0.0f,   0.0f,   0.5f,      // Right Top  Back
          -base,   base,  base,   1.0f,   0.0f,   0.0f,   0.0f,   0.0f,     // Left Top  Back
          -base,   base,  -base,   1.0f,   0.0f,   0.0f,   0.5f,   1.0f,     // Left  Top  Front
          base,   base,  -base,   0.0f,   1.0f,   0.0f,   1.0f,   0.5f,    // Right  Top  Front

          base,   -base,  base,   0.0f,   1.0f,   0.0f,   1.0f,   0.5f,     // Right Bot Back
          -base,   -base,  base,   1.0f,   0.0f,   0.0f,   1.0f,   1.0f,    // Left Bot Back
        -base,   -base,  -base,   0.0f,   1.0f,   0.0f,   0.5f,   0.5f,    // Left Bot Front
          base,   -base,  -base,   1.0f,   0.0f,   0.0f,   0.5f,   0.5f  //  Right Bot Front

    };
    
    unsigned int indices[] = {  
        0, 1, 3, 3, 2, 1,   //Top
        4, 5, 7, 7, 6, 5,   //Bottom
        0, 1, 5, 5, 4, 0,   //Back 
        0, 3, 4, 4, 7, 3,   //Right
        1, 2, 5, 5, 6, 2,   //Left
        2, 3, 6, 6, 7, 3    //Front
    };

    Shader* vertex = new Shader("shaders/default.vert", GL_VERTEX_SHADER);
    Shader* frag = new Shader("shaders/default.frag", GL_FRAGMENT_SHADER);

    ShaderProgram program = ShaderProgram();

    program.AttachShader(vertex);
    program.AttachShader(frag);

    program.Link();

    Texture face;
    face.GenerateTexture("images/face.png");

    Texture lucas;
    lucas.GenerateTexture("images/lucas.png");

    Texture sinan;
    sinan.GenerateTexture("images/sinan.png");

    program.SetActive();

    //program.SetInt("backTexture", lucas.GetId());
    program.SetInt("backTexture", 0);
    program.SetInt("frontTexture", 1);

    VBO vbo(vertices, sizeof(vertices));
    EBO ebo(indices, sizeof(indices));
    VAO vao;

    vao.LinkVBO(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    vao.LinkVBO(vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(GL_FLOAT)));
    vao.LinkVBO(vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(GL_FLOAT)));

    float rotation = 0.0f;

    this->mtx->unlock();
    double lastFrameTime, currentFrameTime = glfwGetTime();
    double deltaTime, fps;
    std::string title = "";

    glEnable(GL_DEPTH_TEST);


    glm::mat4 proj = glm::mat4(1.0f);

    float fov = 60.0f;
    proj = glm::perspective(glm::radians(fov), 16.0f/9.0f, 0.1f, 100.0f);

    while(!glfwWindowShouldClose(this->window))
    {
        //std::cout << this->cameraPosition.x << " | " << this->cameraPosition.y << " | " << this->cameraPosition.z << std::endl;
        currentFrameTime = glfwGetTime();
        deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;
        fps = 1.0 / deltaTime;
        
        title = "Game - " + std::to_string((int)fps) + 
        " | " + std::to_string(this->cameraPosition.x) + 
        " | " + std::to_string(this->cameraPosition.y) +
         " | " + std::to_string(this->cameraPosition.z);

        glfwSetWindowTitle(this->window, title.c_str());

        this->mtx->lock();
        glfwMakeContextCurrent(this->window);

        glClearColor(0.5f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        program.SetActive();
        //program.SetFloat("scale", 1 * fabs(sin(glfwGetTime())));   


        if(deltaTime >= 1 / 60)
        {
            rotation += 0.5f;
        }

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);


        //model = glm::rotate(model, glm::radians(rotation), glm::vec3(1.0f, 1.0f, 1.0f));
        // DET DU LÄGGER I DEN ÄR DET SOM HÄNDER MED OBJEKTET

        //view = view * this->cameraPosition;
        //view = glm::translate(view, this->cameraPosition);
        view = glm::lookAt(this->cameraPosition, this->cameraPosition + glm::vec3(0.0f,0.0f,1.0f), glm::vec3(0.0f,1.0f,0.0f));
        // view = glm::rotate(view, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        // view = glm::rotate(view, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 1.0f));
        //view = glm::translate(view, glm::vec3(0,0,-10));
        //view = glm::translate(view, glm::vec3(1 * cos(glfwGetTime()), 1 * sin(glfwGetTime()), -5.0f));
        // TYP KAMERANS VIEWSPACE EN MATRIS SOM VART IFRÅN DU TITTAR IFRÅN


        model = glm::rotate(model, glm::radians(360.0f * (float)sin(glfwGetTime())), glm::vec3(0.5f, 0.5f, 0.5f));
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

        program.SetVec4("view", view);
        program.SetVec4("proj", proj);
        program.SetVec4("model", model);




        vao.Bind();

        ebo.Bind();

        glActiveTexture(GL_TEXTURE0);

        if(sin(glfwGetTime()) > 0)
        {
            sinan.Bind();
        }
        else
        {
            lucas.Bind();
        }

        glActiveTexture(GL_TEXTURE0 + 1);
        face.Bind();

       // glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
        glActiveTexture(GL_TEXTURE0);
        model = glm::mat4(1.0f);
        lucas.Bind();
        

        program.SetVec4("view", view);
        program.SetVec4("proj", proj);
        program.SetVec4("model", model);
        for (int i = 0; i < 20; i++)
        {
            for (int j = 0; j < 20; j++)
            {
                for (int k = 0; k < 20; k++)
                {
                    model = glm::mat4(1.0f);
                    model = glm::translate(model, glm::vec3(i, k, j));
                    program.SetVec4("model", model);
                    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
                }
                
            }
        }
        


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



