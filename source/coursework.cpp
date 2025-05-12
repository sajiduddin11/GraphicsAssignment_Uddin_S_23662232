#include <iostream>
#include <cmath>


#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/maths.hpp>
#include <common/camera.hpp>
#include <common/model.hpp>
#include <common/light.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// Function prototypes
void keyboardInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos); // Add this line
float cubeVertices[] = {
    // positions           // normals
    -0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,   0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,   0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,   0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,   0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,   0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,   0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f,  -1.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  -1.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  -1.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  -1.0f,  0.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  -1.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  -1.0f,  0.0f, 0.0f,

     0.5f,  0.5f,  0.5f,   1.0f,  0.0f, 0.0f,
     0.5f,  0.5f, -0.5f,   1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,   1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,   1.0f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,   1.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,   1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,   0.0f, -1.0f, 0.0f,
     0.5f, -0.5f, -0.5f,   0.0f, -1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,   0.0f, -1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,   0.0f, -1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,   0.0f, -1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,   0.0f, -1.0f, 0.0f,

    -0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f
};


// Function prototypes
void keyboardInput(GLFWwindow *window);
void mouseInput(GLFWwindow* window);

// Define lastFrame globally 
float lastFrame = 0.0f;

Camera camera(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);

int main( void )
{
    // =========================================================================
    // Window creation - you shouldn't need to change this code
    // -------------------------------------------------------------------------
    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        getchar();
        return -1;
    }




    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    GLFWwindow* window;
    window = glfwCreateWindow(1024, 768, "Computer Graphics Coursework", NULL, NULL);
    
    if( window == NULL ){
        fprintf(stderr, "Failed to open GLFW window.\n");
        getchar();
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);



    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return -1;
    }

    unsigned int shaderProgram = LoadShaders("vertexShader.glsl", "fragmentShader.glsl");

    // Lighting uniform locations
    unsigned int lightDirLoc = glGetUniformLocation(shaderProgram, "lightDir");
    unsigned int lightColorLoc = glGetUniformLocation(shaderProgram, "lightColor");
    unsigned int objectColorLoc = glGetUniformLocation(shaderProgram, "objectColor");


    unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");

    unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
    unsigned int projLoc = glGetUniformLocation(shaderProgram, "projection");

    // View and Projection matrices (set once here, they don't change every frame)
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f)); // move back to see objects
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1024.0f / 768.0f, 0.1f, 100.0f);

    // Send them to the shader (only needs to be done once if static)
    glUseProgram(shaderProgram);

    // Light direction and colors
    glUniform3f(lightDirLoc, -0.2f, -1.0f, -0.3f);  // example direction
    glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);   // white light
    glUniform3f(objectColorLoc, 1.0f, 0.0f, 0.0f);  // red cube


    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));



    // Enable depth testing
    glEnable(GL_DEPTH_TEST);


    // Create Vertex Array Object (VAO) and Vertex Buffer Object (VBO)
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);



   

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    // -------------------------------------------------------------------------
    // End of window creation
    // =========================================================================
    
    // Ensure we can capture keyboard inputs
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);


    // Render loop
    while (!glfwWindowShouldClose(window))
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true); //end the program if escape is pressed

        // Get inputs
		keyboardInput(window);// Call keyboard input function to update camera position
		mouseInput(window); // Call mouse input function to update camera angles
		camera.updateCameraVectors();// Update camera vectors based on yaw and pitch angles


        // Clear the window
        glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //Proper clearing

        // Update camera view matrix
        glm::mat4 view = camera.getViewMatrix();  // Get the updated view matrix
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));  // Send the updated view matrix to the shader


        
        
        //draws the cube
		glUseProgram(shaderProgram); // Use our custom shader and draw the cube every frame, This keeps the object on screen and updates it if anything changes

		glBindVertexArray(VAO);

        // rotating cube
        glm::mat4 model1 = glm::mat4(1.0f);
        model1 = glm::rotate(model1, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model1));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // translated cube
        glm::mat4 model2 = glm::mat4(1.0f);
        model2 = glm::translate(model2, glm::vec3(1.5f, 0.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // scaled cube
        glm::mat4 model3 = glm::mat4(1.0f);
        model3 = glm::translate(model3, glm::vec3(-1.5f, 0.0f, 0.0f)); // move it to the left
        model3 = glm::scale(model3, glm::vec3(0.5f, 0.5f, 0.5f));      // scale it to half size
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model3));
        glDrawArrays(GL_TRIANGLES, 0, 36);


        glBindVertexArray(0);

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    //Re-enable mouse cursor before closing
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    // Close OpenGL window and terminate GLFW
    glfwTerminate();
    return 0;
}

void keyboardInput(GLFWwindow* window) {
    float currentFrame = glfwGetTime();
    float deltaTime = currentFrame - lastFrame;  // Calculate time between frames
    lastFrame = currentFrame;
    camera.processKeyboard(window, deltaTime);  // Update camera movement based on deltaTime

}


void mouseInput(GLFWwindow* window)
{
    static bool firstMouse = true;
    static double lastX = 1024.0 / 2.0;
    static double lastY = 768.0 / 2.0;

    double xPos, yPos;
    glfwGetCursorPos(window, &xPos, &yPos);

    if (firstMouse)
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
        return; // Skip the first frame to avoid jump
    }

    float xOffset = static_cast<float>(xPos - lastX);
    float yOffset = static_cast<float>(lastY - yPos); // y reversed

    lastX = xPos;
    lastY = yPos;

    float sensitivity = 0.1f; // adjust to control speed
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    camera.processMouseMovement(xOffset, yOffset);
}
