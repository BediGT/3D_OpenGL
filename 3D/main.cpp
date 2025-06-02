#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "shaderClass.h" // Klasa do zarz�dzania shaderami
#include "Texture.h"     // Klasa do zarz�dzania teksturami
#include "VAO.h"         // Klasa do zarz�dzania Vertex Array Objects

// Window dimensions
const unsigned int width = 1920;
const unsigned int height = 1080;

// Vertices for a cube (will be used for all objects)
// Ka�dy wierzcho�ek zawiera pozycj� (x, y, z), wektor normalny (nx, ny, nz) i wsp�rz�dne tekstury (u, v).
GLfloat vertices[] = {
    // Pozycje            // Normals           // Wsp�rz�dne tekstury
    // Tylna �ciana
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    // Przednia �ciana
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,

    // Lewa �ciana
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    // Prawa �ciana
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     // Dolna �ciana
     -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
      0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
      0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
      0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
     -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

     // G�rna �ciana
     -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
      0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
      0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
      0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
     -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

// Wierzcho�ki dla SkyBoxa z odpowiednimi wsp�rz�dnymi tekstury,
// dostosowanymi do atlasu tekstur, aby symulowa� sfer�.
GLfloat skyBoxVertices[] = {
    // Tylna �ciana (kolumna 3, wiersz 1) � odwr�cone U
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  4.0f * 0.25f, 1.0f * 0.333333f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  3.0f * 0.25f, 1.0f * 0.333333f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  3.0f * 0.25f, 2.0f * 0.333333f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  3.0f * 0.25f, 2.0f * 0.333333f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  4.0f * 0.25f, 2.0f * 0.333333f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  4.0f * 0.25f, 1.0f * 0.333333f,

    // Przednia �ciana (kolumna 1, wiersz 1)
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f * 0.25f, 1.0f * 0.333333f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  2.0f * 0.25f, 1.0f * 0.333333f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  2.0f * 0.25f, 2.0f * 0.333333f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  2.0f * 0.25f, 2.0f * 0.333333f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f * 0.25f, 2.0f * 0.333333f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f * 0.25f, 1.0f * 0.333333f,

    // Lewa �ciana (kolumna 0, wiersz 1)
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f * 0.25f, 2.0f * 0.333333f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f * 0.25f, 2.0f * 0.333333f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f * 0.25f, 1.0f * 0.333333f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f * 0.25f, 1.0f * 0.333333f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f * 0.25f, 1.0f * 0.333333f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f * 0.25f, 2.0f * 0.333333f,

    // Prawa �ciana (kolumna 2, wiersz 1) � odwr�cone U
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  2.0f * 0.25f, 2.0f * 0.333333f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  3.0f * 0.25f, 2.0f * 0.333333f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  3.0f * 0.25f, 1.0f * 0.333333f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  3.0f * 0.25f, 1.0f * 0.333333f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  2.0f * 0.25f, 1.0f * 0.333333f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  2.0f * 0.25f, 2.0f * 0.333333f,

     // Dolna �ciana (kolumna 1, wiersz 2) � poprawione V
     -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f * 0.25f, 0.0f * 0.333333f,
      0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  2.0f * 0.25f, 0.0f * 0.333333f,
      0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  2.0f * 0.25f, 1.0f * 0.333333f,
      0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  2.0f * 0.25f, 1.0f * 0.333333f,
     -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f * 0.25f, 1.0f * 0.333333f,
     -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f * 0.25f, 0.0f * 0.333333f,

     // G�rna �ciana (kolumna 1, wiersz 0)
     -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f * 0.25f, 3.0f * 0.333333f,
     -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f * 0.25f, 2.0f * 0.333333f,
      0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  2.0f * 0.25f, 2.0f * 0.333333f,
      0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  2.0f * 0.25f, 2.0f * 0.333333f,
      0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  2.0f * 0.25f, 3.0f * 0.333333f,
     -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f * 0.25f, 3.0f * 0.333333f
};

// Wierzcho�ki dla g�owy �wini, z odpowiednimi wsp�rz�dnymi tekstur.
// Zwr�� uwag� na niestandardowe przypisanie normalnych,
// kt�re s� u�ywane do okre�lenia, kt�ra tekstura powinna by� u�yta (g�owa czy bok).
GLfloat pigHeadVertices[] = {
    // Lewa �ciana (teraz jako "przednia" �ciana) - indeksy 0-5
    // Normalne (1,0,0) sugeruj�, �e ta �ciana b�dzie mapowana na tekstur� g�owy.
    -0.5f, -0.5f, -0.5f,  1, 0, 0,  0.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  1, 0, 0,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1, 0, 0,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  1, 0, 0,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  1, 0, 0,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  1, 0, 0,  0.0f, 0.0f,

    // Prawa �ciana (teraz jako "tylna" �ciana) - indeksy 6-11
    // Normalne (1,0,0) sugeruj�, �e ta �ciana b�dzie mapowana na tekstur� g�owy.
     0.5f, -0.5f, -0.5f,  1, 0, 0,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1, 0, 0,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1, 0, 0,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1, 0, 0,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1, 0, 0,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1, 0, 0,  0.0f, 0.0f,

     // Przednia �ciana (teraz jako "lewa" �ciana) - indeksy 12-17
     // Normalne (0,0,1) sugeruj�, �e ta �ciana b�dzie mapowana na tekstur� boku.
     -0.5f, -0.5f,  0.5f,  0, 0, 1,  0.0f, 0.0f,
      0.5f, -0.5f,  0.5f,  0, 0, 1,  1.0f, 0.0f,
      0.5f,  0.5f,  0.5f,  0, 0, 1,  1.0f, 1.0f,
      0.5f,  0.5f,  0.5f,  0, 0, 1,  1.0f, 1.0f,
     -0.5f,  0.5f,  0.5f,  0, 0, 1,  0.0f, 1.0f,
     -0.5f, -0.5f,  0.5f,  0, 0, 1,  0.0f, 0.0f,

     // Tylna �ciana (teraz jako "prawa" �ciana) - indeksy 18-23
     // Normalne (0,0,1) sugeruj�, �e ta �ciana b�dzie mapowana na tekstur� boku.
     -0.5f, -0.5f, -0.5f,  0, 0, 1,  0.0f, 0.0f,
      0.5f, -0.5f, -0.5f,  0, 0, 1,  1.0f, 0.0f,
      0.5f,  0.5f, -0.5f,  0, 0, 1,  1.0f, 1.0f,
      0.5f,  0.5f, -0.5f,  0, 0, 1,  1.0f, 1.0f,
     -0.5f,  0.5f, -0.5f,  0, 0, 1,  0.0f, 1.0f,
     -0.5f, -0.5f, -0.5f,  0, 0, 1,  0.0f, 0.0f,

     // Dolna �ciana - indeksy 24-29
     // Normalne (0,1,0) sugeruj�, �e ta �ciana b�dzie mapowana na tekstur� boku/g�ry.
     -0.5f, -0.5f, -0.5f,  0, 1, 0,  0.0f, 1.0f,
      0.5f, -0.5f, -0.5f,  0, 1, 0,  1.0f, 1.0f,
      0.5f, -0.5f,  0.5f,  0, 1, 0,  1.0f, 0.0f,
      0.5f, -0.5f,  0.5f,  0, 1, 0,  1.0f, 0.0f,
     -0.5f, -0.5f,  0.5f,  0, 1, 0,  0.0f, 0.0f,
     -0.5f, -0.5f, -0.5f,  0, 1, 0,  0.0f, 1.0f,

     // G�rna �ciana - indeksy 30-35
     // Normalne (0,1,0) sugeruj�, �e ta �ciana b�dzie mapowana na tekstur� boku/g�ry.
     -0.5f,  0.5f, -0.5f,  0, 1, 0,  0.0f, 1.0f,
      0.5f,  0.5f, -0.5f,  0, 1, 0,  1.0f, 1.0f,
      0.5f,  0.5f,  0.5f,  0, 1, 0,  1.0f, 0.0f,
      0.5f,  0.5f,  0.5f,  0, 1, 0,  1.0f, 0.0f,
     -0.5f,  0.5f,  0.5f,  0, 1, 0,  0.0f, 0.0f,
     -0.5f,  0.5f, -0.5f,  0, 1, 0,  0.0f, 1.0f
};

// Zmienne kamery
glm::vec3 cameraPos = glm::vec3(0.0f, 2.0f, 5.0f);   // Pozycja kamery
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f); // Kierunek, w kt�rym patrzy kamera
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);     // Wektor "w g�r�" dla kamery

// Timing
float deltaTime = 0.0f; // Czas mi�dzy bie��c� a poprzedni� klatk�
float lastFrame = 0.0f; // Czas ostatniej klatki

// Zmienne myszy
bool firstMouse = true;   // Flaga do obs�ugi pierwszego ruchu mysz�
float lastX = width / 2.0f; // Poprzednia pozycja X myszy
float lastY = height / 2.0f; // Poprzednia pozycja Y myszy
float yaw = -90.0f;       // Obr�t kamery wok� osi Y (pocz�tkowo skierowana w stron� -Z)
float pitch = 0.0f;       // Obr�t kamery wok� osi X

// Pozycja i ruch creepera
glm::vec3 creeperPos = glm::vec3(3.0f, 0.0f, 3.0f);    // Pocz�tkowa pozycja creepera (prawo-prz�d od domu)
glm::vec3 creeperFront = glm::vec3(0.0f, 0.0f, -1.0f); // Pocz�tkowy kierunek, w kt�rym creeper jest zwr�cony

// Pozycja �wiat�a (s�o�ca)
glm::vec3 lightPos = glm::vec3(5.0f, 5.0f, 5.0f); // Pocz�tkowa pozycja �r�d�a �wiat�a
float lightAngle = 0.0f;                         // K�t obrotu �wiat�a (symulacja ruchu s�o�ca)
GLfloat lightSpeed = 1.0f;                       // Pr�dko�� obrotu �wiat�a

// Zmienne dla g�owy �wini
glm::vec3 pigHeadPos = glm::vec3(7.0f, 2.5f, 7.0f); // Pozycja g�owy �wini
glm::vec3 pigHeadScale = glm::vec3(2.5f);        // Pocz�tkowa skala g�owy �wini


// Prototypy funkcji
/**
 * @brief Callback do zmiany rozmiaru framebuffer'a.
 * @param window Wska�nik na okno GLFW.
 * @param width Nowa szeroko�� okna.
 * @param height Nowa wysoko�� okna.
 */
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

/**
 * @brief Przetwarza dane wej�ciowe z klawiatury.
 * @param window Wska�nik na okno GLFW.
 */
void processInput(GLFWwindow* window);

/**
 * @brief Callback do obs�ugi ruchu myszy.
 * @param window Wska�nik na okno GLFW.
 * @param xpos Bie��ca pozycja X kursora.
 * @param ypos Bie��ca pozycja Y kursora.
 */
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

/**
 * @brief Renderuje pojedynczy sze�cian.
 * @param shader Obiekt shadera do u�ycia.
 * @param texture Obiekt tekstury do na�o�enia na sze�cian.
 * @param position Pozycja sze�cianu w �wiecie.
 * @param scale Skala sze�cianu.
 */
void renderCube(Shader& shader, Texture& texture, glm::vec3 position, glm::vec3 scale = glm::vec3(1.0f));

/**
 * @brief Renderuje SkyBox.
 * @param shader Obiekt shadera do u�ycia.
 * @param skyBoxTex Obiekt tekstury dla SkyBoxa.
 */
void renderSkyBox(Shader& shader, Texture& skyBoxTex);

/**
 * @brief Renderuje drzewo sk�adaj�ce si� z blok�w.
 * @param shader Obiekt shadera do u�ycia.
 * @param woodTex Obiekt tekstury drewna.
 * @param leavesTex Obiekt tekstury li�ci.
 */
void renderTree(Shader& shader, Texture& woodTex, Texture& leavesTex);

/**
 * @brief Renderuje prosty dom sk�adaj�cy si� z blok�w.
 * @param shader Obiekt shadera do u�ycia.
 * @param houseTex Obiekt tekstury domu.
 */
void renderHouse(Shader& shader, Texture& houseTex);

/**
 * @brief Renderuje creepera sk�adaj�cego si� z blok�w.
 * @param shader Obiekt shadera do u�ycia.
 * @param creeperTex Obiekt tekstury creepera.
 */
void renderCreeper(Shader& shader, Texture& creeperTex);

/**
 * @brief Renderuje g�ow� �wini, wykorzystuj�c dwie r�ne tekstury dla r�nych �cian.
 * @param shader Obiekt shadera do u�ycia.
 * @param headTex Obiekt tekstury dla "przedniej" i "tylnej" �ciany g�owy (np. z pyskiem).
 * @param sideTex Obiekt tekstury dla bocznych, g�rnej i dolnej �ciany g�owy.
 * @param position Pozycja g�owy �wini w �wiecie.
 * @param scale Skala g�owy �wini.
 */
void renderPigHead(Shader& shader, Texture& headTex, Texture& sideTex, glm::vec3 position, glm::vec3 scale);

/**
 * @brief Aktualizuje pozycj� i kierunek creepera na podstawie danych wej�ciowych.
 * @param deltaTime Czas, jaki up�yn�� od ostatniej klatki.
 * @param window Wska�nik na okno GLFW (do sprawdzania stanu klawiszy).
 */
void updateCreeper(float deltaTime, GLFWwindow* window);

bool blurEnabled = true; // Flaga okre�laj�ca, czy efekt rozmycia jest w��czony (domy�lnie w��czony)

int main()
{
    // Inicjalizacja GLFW
    glfwInit();
    // Ustawienie wersji OpenGL na 3.3 Core Profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Tworzenie okna
    GLFWwindow* window = glfwCreateWindow(width, height, "Maincamp - Projekt", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); // Ustawienie kontekstu OpenGL dla bie��cego okna
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // Rejestracja callbacka dla zmiany rozmiaru okna
    glfwSetCursorPosCallback(window, mouse_callback);               // Rejestracja callbacka dla ruchu myszy
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);    // Ukrycie i zablokowanie kursora myszy

    // �adowanie GLAD (zarz�dzanie wska�nikami funkcji OpenGL)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Konfiguracja globalnego stanu OpenGL
    glEnable(GL_DEPTH_TEST); // W��czenie testu g��bi dla prawid�owego renderowania 3D

    // Generowanie i bindowanie framebuffer'a (FBO) do renderowania poza ekranem
    unsigned int framebuffer;
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    // Generowanie i do��czanie tekstury kolor�w do FBO
    unsigned int textureColorbuffer;
    glGenTextures(1, &textureColorbuffer);
    glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
    // Przydzielenie pami�ci dla tekstury bez inicjalizacji danych
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    // Ustawienie filtr�w tekstury
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Do��czenie tekstury do FBO jako za��cznik kolor�w
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);

    // Generowanie i do��czanie renderbuffer'a (dla g��bi i stencilu) do FBO
    unsigned int rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    // Przydzielenie pami�ci dla renderbuffer'a
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    // Do��czenie renderbuffer'a do FBO jako za��cznik g��bi i stencilu
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    // Sprawdzenie kompletno�ci framebuffer'a
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0); // Odwi�zanie FBO, aby renderowa� z powrotem na domy�lny framebuffer

    // Budowanie i kompilacja shader�w
    Shader defaultShader("default.vert", "default.frag");     // Shader dla wi�kszo�ci obiekt�w w scenie
    Shader lightCubeShader("lightCube.vert", "lightCube.frag"); // Shader dla obiektu reprezentuj�cego �wiat�o
    Shader skyBoxShader("skyBox.vert", "skyBox.frag");       // Shader dla SkyBoxa
    Shader blurShader("Framebuffer.vert", "Framebuffer.frag"); // Shader do efektu rozmycia (post-processing)
    Shader defaultScreenShader("defaultScreen.vert", "defaultScreen.frag"); // Shader do renderowania tekstury na pe�nym ekranie bez efekt�w

    // �adowanie tekstur
    Texture woodTex("tree.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture leavesTex("leaves.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture houseTex("house.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture creeperTex("creeper.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture groundTex("grass.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture skyTex("skyBox.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture pigHeadTex("pig_head.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture pigSideTex("pig_side.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

    // Konfiguracja Vertex Array Object (VAO) dla sze�cianu
    VAO cubeVAO;
    cubeVAO.Bind();
    VBO cubeVBO(vertices, sizeof(vertices)); // Tworzenie Vertex Buffer Object (VBO) z danymi wierzcho�k�w
    // ��czenie atrybut�w wierzcho�k�w (pozycja, normalne, wsp�rz�dne tekstury) z VAO
    cubeVAO.LinkAttrib(cubeVBO, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    cubeVAO.LinkAttrib(cubeVBO, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    cubeVAO.LinkAttrib(cubeVBO, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    cubeVAO.Unbind(); // Odwi�zanie VAO
    cubeVBO.Unbind(); // Odwi�zanie VBO

    // Konfiguracja VAO dla SkyBoxa
    VAO skyVAO;
    skyVAO.Bind();
    VBO skyVBO(skyBoxVertices, sizeof(skyBoxVertices));
    skyVAO.LinkAttrib(skyVBO, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    skyVAO.LinkAttrib(skyVBO, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    skyVAO.LinkAttrib(skyVBO, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    skyVAO.Unbind();
    skyVBO.Unbind();

    // Konfiguracja VAO dla g�owy �wini
    VAO pigHeadVAO;
    pigHeadVAO.Bind();
    VBO pigHeadVBO(pigHeadVertices, sizeof(pigHeadVertices));
    pigHeadVAO.LinkAttrib(pigHeadVBO, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    pigHeadVAO.LinkAttrib(pigHeadVBO, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    pigHeadVAO.LinkAttrib(pigHeadVBO, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    pigHeadVAO.Unbind();
    pigHeadVBO.Unbind();

    // Kolory nieba i �wiat�a w zale�no�ci od pory dnia
    glm::vec4 defaultSkyColor = glm::vec4(0.53f, 0.81f, 0.92f, 1.0f); // Kolor nieba w dzie�
    glm::vec4 nightColor = glm::vec4(0.13f, 0.31f, 0.42f, 1.0f);     // Kolor nieba w nocy

    // Wierzcho�ki dla pe�noekranowego kwadratu (do post-processingu)
    float quadVertices[] = {
        // pozycje   // wsp�rz�dne tekstury
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };
    unsigned int quadVAO, quadVBO;
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    // G��wna p�tla renderowania
    while (!glfwWindowShouldClose(window))
    {
        // Logika czasu na klatk�
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Przetwarzanie danych wej�ciowych
        processInput(window);

        // --- Aktualizacja pozycji �wiat�a (ruch s�o�ca) ---
        lightAngle += lightSpeed * deltaTime; // Zwi�kszanie k�ta obrotu �wiat�a
        if (lightAngle > 360.0f) lightAngle -= 360.0f; // Resetowanie k�ta po pe�nym obrocie
        // Obliczanie pozycji �wiat�a na okr�gu
        lightPos.x = 30.0f * cos(lightAngle);
        lightPos.y = 30.0f * sin(lightAngle);

        // Aktualizacja pozycji creepera
        updateCreeper(deltaTime, window);

        // --- 1. RENDEROWANIE SCENY DO FRAMEBUFFERA ---
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer); // Bindowanie FBO do renderowania do tekstury
        glEnable(GL_DEPTH_TEST); // W��czenie testu g��bi

        // Interpolacja koloru nieba w zale�no�ci od k�ta �wiat�a (symulacja dnia/nocy)
        glm::vec4 skyColor = glm::mix(nightColor, defaultSkyColor, sin(lightAngle));
        glClearColor(skyColor.x, skyColor.y, skyColor.z, skyColor.w); // Ustawienie koloru t�a
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);           // Czyszczenie bufor�w koloru i g��bi

        defaultShader.Activate(); // Aktywacja g��wnego shadera

        // Interpolacja koloru �wiat�a w zale�no�ci od k�ta �wiat�a (symulacja dnia/nocy)
        glm::vec4 defaultLightColor = glm::vec4(1.0f, 1.0f, 0.9f, 1.0f); // Kolor �wiat�a w dzie�
        glm::vec3 lightColor = glm::mix(nightColor, defaultLightColor, sin(lightAngle));
        // Ustawienie uniform�w shadera dla o�wietlenia
        glUniform3f(glGetUniformLocation(defaultShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z);
        glUniform3f(glGetUniformLocation(defaultShader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
        glUniform3f(glGetUniformLocation(defaultShader.ID, "viewPos"), cameraPos.x, cameraPos.y, cameraPos.z);
        glUniform1f(glGetUniformLocation(defaultShader.ID, "material.shininess"), 32.0f);

        // Tworzenie macierzy projekcji i widoku
        glm::mat4 projection = glm::perspective(glm::radians(100.0f), (float)width / (float)height, 0.1f, 200.0f);
        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        // Przekazanie macierzy do shadera
        glUniformMatrix4fv(glGetUniformLocation(defaultShader.ID, "projection"), 1, GL_FALSE, &projection[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(defaultShader.ID, "view"), 1, GL_FALSE, &view[0][0]);

        // Renderowanie pod�o�a
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
        model = glm::scale(model, glm::vec3(50.0f, 1.0f, 50.0f));
        glUniformMatrix4fv(glGetUniformLocation(defaultShader.ID, "model"), 1, GL_FALSE, &model[0][0]);
        groundTex.Bind(); // Aktywacja tekstury pod�o�a
        cubeVAO.Bind();   // Bindowanie VAO dla sze�cianu
        glDrawArrays(GL_TRIANGLES, 0, 36); // Rysowanie sze�cianu

        // Renderowanie obiekt�w sceny
        renderTree(defaultShader, woodTex, leavesTex);      // Renderowanie drzewa
        renderHouse(defaultShader, houseTex);               // Renderowanie domu
        renderCreeper(defaultShader, creeperTex);           // Renderowanie creepera
        renderPigHead(defaultShader, pigHeadTex, pigSideTex, pigHeadPos, pigHeadScale); // Renderowanie g�owy �wini

        // Skybox
        skyVAO.Bind();           // Bindowanie VAO dla SkyBoxa
        skyBoxShader.Activate(); // Aktywacja shadera SkyBoxa

        // Przekazanie koloru �wiat�a do shadera SkyBoxa
        GLuint skyBoxLightColorLoc = glGetUniformLocation(skyBoxShader.ID, "lightColor");
        glm::vec3 skyBoxlightColor = glm::mix(nightColor, defaultLightColor, sin(lightAngle));
        glUniform3f(skyBoxLightColorLoc, skyBoxlightColor.x, skyBoxlightColor.y, skyBoxlightColor.z);

        // Przekazanie macierzy projekcji i widoku do shadera SkyBoxa
        GLuint skyProjectionLoc = glGetUniformLocation(skyBoxShader.ID, "projection");
        glUniformMatrix4fv(skyProjectionLoc, 1, GL_FALSE, &projection[0][0]);
        GLuint skyViewLoc = glGetUniformLocation(skyBoxShader.ID, "view");
        glUniformMatrix4fv(skyViewLoc, 1, GL_FALSE, &view[0][0]);

        renderSkyBox(skyBoxShader, skyTex); // Renderowanie SkyBoxa

        // �wiat�o jako sze�cian
        lightCubeShader.Activate(); // Aktywacja shadera dla sze�cianu �wiat�a
        // Przekazanie macierzy projekcji i widoku
        glUniformMatrix4fv(glGetUniformLocation(lightCubeShader.ID, "projection"), 1, GL_FALSE, &projection[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(lightCubeShader.ID, "view"), 1, GL_FALSE, &view[0][0]);
        // Utworzenie macierzy modelu dla sze�cianu �wiat�a
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(5.0f)); // Skalowanie sze�cianu �wiat�a
        glUniformMatrix4fv(glGetUniformLocation(lightCubeShader.ID, "model"), 1, GL_FALSE, &model[0][0]);
        cubeVAO.Bind(); // Bindowanie VAO dla sze�cianu (do renderowania sze�cianu �wiat�a)
        glDrawArrays(GL_TRIANGLES, 0, 36); // Rysowanie sze�cianu �wiat�a

        // 2. Renderowanie pe�noekranowego kwadratu z efektem rozmycia (je�li w��czony) lub normalnie
        glBindFramebuffer(GL_FRAMEBUFFER, 0); // Powr�t do domy�lnego framebuffer'a (ekranu)
        glDisable(GL_DEPTH_TEST);             // Wy��czenie testu g��bi (niepotrzebne dla 2D kwadratu)
        glClear(GL_COLOR_BUFFER_BIT);         // Czyszczenie bufora koloru

        // Wyb�r shadera do post-processingu
        if (blurEnabled) {
            blurShader.Activate(); // Aktywacja shadera do rozmycia
        }
        else {
            defaultScreenShader.Activate(); // Aktywacja shadera do renderowania bez zmian
        }

        glBindVertexArray(quadVAO);               // Bindowanie VAO pe�noekranowego kwadratu
        glBindTexture(GL_TEXTURE_2D, textureColorbuffer); // Bindowanie tekstury z wyrenderowan� scen�
        glDrawArrays(GL_TRIANGLES, 0, 6);         // Rysowanie kwadratu

        // Zamiana bufor�w i przetwarzanie zdarze�
        glfwSwapBuffers(window); // Wymiana bufor�w (wy�wietlenie wyrenderowanej klatki)
        glfwPollEvents();        // Przetwarzanie zdarze� (np. wej�cie z klawiatury/myszy)
    }

    // Czyszczenie zasob�w OpenGL
    cubeVAO.Delete();
    cubeVBO.Delete();
    woodTex.Delete();
    leavesTex.Delete();
    houseTex.Delete();
    creeperTex.Delete();
    groundTex.Delete();
    defaultShader.Delete();
    lightCubeShader.Delete();
    pigSideTex.Delete(); // Usuni�cie tekstury boku �wini

    glfwTerminate(); // Zako�czenie pracy GLFW
    return 0;        // Pomy�lne zako�czenie programu
}

/**
 * @brief Aktualizuje pozycj� i kierunek creepera na podstawie danych wej�ciowych z klawiatury.
 * Creeper porusza si� w p�aszczy�nie XZ i ma ograniczone pole ruchu.
 * @param deltaTime Czas, jaki up�yn�� od ostatniej klatki, u�ywany do skalowania ruchu.
 * @param window Wska�nik na okno GLFW, u�ywany do sprawdzania stanu klawiszy strza�ek.
 */
void updateCreeper(float deltaTime, GLFWwindow* window) {
    const float moveSpeed = 3.0f * deltaTime; // Bazowa pr�dko�� ruchu creepera
    bool moved = false; // Flaga, czy creeper si� poruszy� w tej klatce

    // Obs�uga ruchu klawiszami strza�ek
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        creeperPos.z -= moveSpeed; // Ruch do przodu (wzgl�dem pocz�tkowego kierunku -Z)
        creeperFront = glm::vec3(0.0f, 0.0f, -1.0f); // Ustawienie kierunku przodem
        moved = true;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        creeperPos.z += moveSpeed; // Ruch do ty�u
        creeperFront = glm::vec3(0.0f, 0.0f, 1.0f);  // Ustawienie kierunku ty�em
        moved = true;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        creeperPos.x -= moveSpeed; // Ruch w lewo
        creeperFront = glm::vec3(-1.0f, 0.0f, 0.0f); // Ustawienie kierunku w lewo
        moved = true;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        creeperPos.x += moveSpeed; // Ruch w prawo
        creeperFront = glm::vec3(1.0f, 0.0f, 0.0f);  // Ustawienie kierunku w prawo
        moved = true;
    }

    // Ograniczenie pozycji creepera do okre�lonego zakresu na p�aszczy�nie XZ
    creeperPos.x = glm::clamp(creeperPos.x, -5.0f, 5.0f);
    creeperPos.z = glm::clamp(creeperPos.z, -5.0f, 5.0f);

    // Kierunek creepera jest aktualizowany tylko wtedy, gdy si� poruszy�,
    // w przeciwnym razie zachowuje poprzedni kierunek.
    if (!moved) {
        // Zachowaj bie��cy kierunek
    }
}

/**
 * @brief Renderuje pojedynczy sze�cian w scenie, stosuj�c transformacje modelu.
 * @param shader Obiekt shadera, kt�ry ma zosta� u�yty do renderowania sze�cianu.
 * @param texture Obiekt tekstury, kt�ra ma zosta� na�o�ona na sze�cian.
 * @param position Wektor glm::vec3 okre�laj�cy pozycj� sze�cianu w przestrzeni �wiata.
 * @param scale Wektor glm::vec3 okre�laj�cy skal� sze�cianu (domy�lnie glm::vec3(1.0f) - brak skalowania).
 */
void renderCube(Shader& shader, Texture& texture, glm::vec3 position, glm::vec3 scale)
{
    // Utworzenie macierzy modelu, inicjalizacja jako macierz jednostkowa.
    glm::mat4 model = glm::mat4(1.0f);
    // Przesuni�cie sze�cianu do okre�lonej pozycji.
    model = glm::translate(model, position);
    // Skalowanie sze�cianu.
    model = glm::scale(model, scale);

    // Pobranie lokalizacji uniformu "model" w shaderze.
    GLuint modelLoc = glGetUniformLocation(shader.ID, "model");
    // Ustawienie macierzy modelu w shaderze.
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);

    // Aktywacja i bindowanie tekstury.
    texture.Bind();
    // Rysowanie 36 wierzcho�k�w sze�cianu (dwana�cie tr�jk�t�w, ka�dy po 3 wierzcho�ki).
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

/**
 * @brief Renderuje SkyBox, kt�ry otacza ca�� scen�.
 * SkyBox jest skalowany na du�� warto��, aby zawsze znajdowa� si� poza zasi�giem widzenia.
 * @param shader Obiekt shadera SkyBoxa.
 * @param skyBoxTex Obiekt tekstury dla SkyBoxa.
 */
void renderSkyBox(Shader& shader, Texture& skyBoxTex)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(100.0f)); // Skalowanie SkyBoxa, aby by� bardzo du�y

    // Przekazanie macierzy modelu do shadera SkyBoxa
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, &model[0][0]);
    skyBoxTex.Bind(); // Aktywacja tekstury SkyBoxa
    glDrawArrays(GL_TRIANGLES, 0, 36); // Rysowanie SkyBoxa (sze�cianu)
}

/**
 * @brief Renderuje drzewo, sk�adaj�ce si� z kilku blok�w drewna i li�ci.
 * Wykorzystuje funkcj� `renderCube` do rysowania poszczeg�lnych blok�w.
 * @param shader Obiekt shadera do u�ycia.
 * @param woodTex Tekstura drewna.
 * @param leavesTex Tekstura li�ci.
 */
void renderTree(Shader& shader, Texture& woodTex, Texture& leavesTex)
{
    // Pie� (4 bloki wysoko�ci)
    for (int i = 0; i < 4; i++) {
        renderCube(shader, woodTex, glm::vec3(2.0f, 0.5f + i, 0.0f));
    }

    // Li�cie na g�rze
    renderCube(shader, leavesTex, glm::vec3(2.0f, 3.5f, 0.0f));
    renderCube(shader, leavesTex, glm::vec3(2.0f, 4.5f, 0.0f));
    renderCube(shader, leavesTex, glm::vec3(1.0f, 3.5f, 0.0f));
    renderCube(shader, leavesTex, glm::vec3(3.0f, 3.5f, 0.0f));
    renderCube(shader, leavesTex, glm::vec3(2.0f, 3.5f, 1.0f));
    renderCube(shader, leavesTex, glm::vec3(2.0f, 3.5f, -1.0f));
}

/**
 * @brief Renderuje prosty dom sk�adaj�cy si� z blok�w, z wyci�tymi drzwiami i oknami.
 * Wykorzystuje funkcj� `renderCube` do rysowania poszczeg�lnych blok�w.
 * @param shader Obiekt shadera do u�ycia.
 * @param houseTex Tekstura domu.
 */
void renderHouse(Shader& shader, Texture& houseTex)
{
    // Podstawa domu (4x4x4 bloki)
    for (int x = 0; x < 4; x++) {
        for (int z = 0; z < 4; z++) {
            for (int y = 0; y < 4; y++) {
                // Renderowanie tylko zewn�trznych �cian i dachu/pod�ogi, aby utworzy� pusty w �rodku dom
                if (y == 0 || y == 3 || x == 0 || x == 3 || z == 0 || z == 3) {
                    // Pomijanie blok�w dla drzwi i okien
                    if (!(y == 0 && x == 1 && z == 0)) { // Drzwi (na poziomie Y=0, X=1, Z=0)
                        // Okna (na poziomach Y=1 i Y=2, w okre�lonych miejscach XZ)
                        if (!((y == 1 || y == 2) && ((x == 1 && (z == 1 || z == 2)) || (z == 1 && (x == 1 || x == 2))))) {
                            renderCube(shader, houseTex, glm::vec3(-5.0f + x, 0.5f + y, -3.0f + z));
                        }
                    }
                }
            }
        }
    }
}

/**
 * @brief Renderuje posta� creepera, sk�adaj�c� si� z dw�ch blok�w i obracaj�c� si� w kierunku ruchu.
 * @param shader Obiekt shadera do u�ycia.
 * @param creeperTex Tekstura creepera.
 */
void renderCreeper(Shader& shader, Texture& creeperTex)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, creeperPos); // Przesuni�cie creepera do jego aktualnej pozycji
    // Obr�t creepera tak, aby by� zwr�cony w kierunku ruchu (na podstawie creeperFront)
    model = glm::rotate(model, atan2(creeperFront.x, creeperFront.z), glm::vec3(0.0f, 1.0f, 0.0f));

    // Dolny blok creepera
    glm::mat4 bottomModel = model;
    bottomModel = glm::translate(bottomModel, glm::vec3(0.0f, 0.5f, 0.0f)); // Przesuni�cie dolnego bloku
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, &bottomModel[0][0]);
    creeperTex.Bind(); // Aktywacja tekstury creepera
    glDrawArrays(GL_TRIANGLES, 0, 36); // Rysowanie dolnego bloku

    // G�rny blok creepera
    glm::mat4 topModel = model;
    topModel = glm::translate(topModel, glm::vec3(0.0f, 1.5f, 0.0f)); // Przesuni�cie g�rnego bloku
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, &topModel[0][0]);
    creeperTex.Bind(); // Aktywacja tekstury creepera
    glDrawArrays(GL_TRIANGLES, 0, 36); // Rysowanie g�rnego bloku
}

/**
 * @brief Renderuje g�ow� �wini z wykorzystaniem dw�ch r�nych tekstur dla poszczeg�lnych �cian.
 * Wierzcho�ki `pigHeadVertices` s� specjalnie zdefiniowane, aby umo�liwi� mapowanie tekstur na podstawie normalnych.
 * @param shader Obiekt shadera do u�ycia.
 * @param headTex Tekstura przeznaczona dla "przedniej" i "tylnej" �ciany g�owy (z pyszczkiem/twarz�).
 * @param sideTex Tekstura przeznaczona dla bocznych, g�rnej i dolnej �ciany g�owy.
 * @param position Pozycja g�owy �wini w �wiecie.
 * @param scale Skala g�owy �wini.
 */
void renderPigHead(Shader& shader, Texture& headTex, Texture& sideTex, glm::vec3 position, glm::vec3 scale)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position); // Przesuni�cie g�owy �wini do jej pozycji
    // Obr�t o 90 stopni wok� osi Y, aby tekstura pyszczka by�a na odpowiedniej �cianie
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, scale); // Skalowanie g�owy �wini

    GLuint modelLoc = glGetUniformLocation(shader.ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);

    // Renderowanie �cian z oryginalnymi indeksami, ale z odpowiedni� tekstur�
    // �ciany o normalnych (1,0,0) (czyli oryginalnie lewa i prawa, teraz przekr�cone na prz�d i ty�)
    headTex.Bind(); // Bindowanie tekstury g�owy (z pyszczkiem)
    glDrawArrays(GL_TRIANGLES, 0, 6); // Renderowanie "przedniej" �ciany (oryginalnie lewej)
    glDrawArrays(GL_TRIANGLES, 6, 6); // Renderowanie "tylnej" �ciany (oryginalnie prawej)

    // �ciany o normalnych (0,0,1) i (0,1,0) (czyli oryginalnie przednia, tylna, dolna i g�rna)
    sideTex.Bind(); // Bindowanie tekstury bocznej/g�rnej/dolnej
    glDrawArrays(GL_TRIANGLES, 12, 6); // Renderowanie "lewej" �ciany (oryginalnie przedniej)
    glDrawArrays(GL_TRIANGLES, 18, 6); // Renderowanie "prawej" �ciany (oryginalnie tylnej)
    glDrawArrays(GL_TRIANGLES, 24, 6); // Renderowanie dolnej �ciany
    glDrawArrays(GL_TRIANGLES, 30, 6); // Renderowanie g�rnej �ciany
}

/**
 * @brief Przetwarza dane wej�ciowe z klawiatury w celu sterowania kamer�, �wiat�em i efektem rozmycia.
 * @param window Wska�nik na okno GLFW.
 */
void processInput(GLFWwindow* window)
{
    // Zamkni�cie okna po naci�ni�ciu klawisza ESC
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // Pr�dko�� poruszania si� kamery, skalowana przez deltaTime
    float cameraSpeed = 5.0f * deltaTime;
    // Ruch kamery do przodu/ty�u (W/S)
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    // Ruch kamery w lewo/prawo (A/D)
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    // Ruch kamery w g�r�/d� (SPACE/LEFT_SHIFT)
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraUp;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraUp;
    // Zwi�kszenie/zmniejszenie pr�dko�ci �wiat�a (+/-)
    if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS)
        lightSpeed += 0.001f;
    if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS)
        if (lightSpeed > 0.05f) lightSpeed -= 0.001f;
    // Zwi�kszenie/zmniejszenie skali g�owy �wini (KP_ADD/KP_SUBTRACT)
    if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS) {
        pigHeadScale += glm::vec3(0.1f) * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS) {
        pigHeadScale -= glm::vec3(0.1f) * deltaTime;
        // Zabezpieczenie przed ujemn� skal�
        if (pigHeadScale.x < 0.1f) pigHeadScale = glm::vec3(0.1f);
    }

    // Statyczna flaga do obs�ugi pojedynczego wci�ni�cia klawisza 'B'
    static bool blurKeyPressed = false;
    // Prze��czanie efektu rozmycia po naci�ni�ciu klawisza 'B'
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
        if (!blurKeyPressed) { // Sprawdzenie, czy klawisz nie by� ju� wci�ni�ty w poprzedniej klatce
            blurEnabled = !blurEnabled; // Zmiana stanu w��czenia/wy��czenia rozmycia
            blurKeyPressed = true;      // Ustawienie flagi na true
        }
    }
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_RELEASE) {
        blurKeyPressed = false; // Resetowanie flagi po zwolnieniu klawisza
    }
}

/**
 * @brief Callback wywo�ywany, gdy rozmiar okna zostanie zmieniony.
 * Aktualizuje rozmiar viewportu OpenGL, aby dopasowa� go do nowego rozmiaru okna.
 * @param window Wska�nik na okno GLFW.
 * @param width Nowa szeroko�� okna.
 * @param height Nowa wysoko�� okna.
 */
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height); // Ustawienie nowego rozmiaru viewportu
}

/**
 * @brief Callback wywo�ywany, gdy kursor myszy zostanie przesuni�ty.
 * Oblicza przesuni�cie myszy i aktualizuje k�ty yaw i pitch kamery, a nast�pnie przelicza wektor cameraFront.
 * @param window Wska�nik na okno GLFW.
 * @param xpos Bie��ca pozycja X kursora.
 * @param ypos Bie��ca pozycja Y kursora.
 */
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    // Inicjalizacja pozycji myszy przy pierwszym wej�ciu
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    // Obliczenie przesuni�cia myszy od ostatniej klatki
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // Odwr�cone, poniewa� wsp�rz�dne Y OpenGL rosn� w g�r�, a Y ekranu w d�
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f; // Czu�o�� myszy
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    // Aktualizacja k�t�w yaw i pitch
    yaw += xoffset;
    pitch += yoffset;

    // Ograniczenie k�ta pitch, aby zapobiec "przewr�ceniu" kamery
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    // Obliczenie nowego wektora cameraFront na podstawie k�t�w yaw i pitch
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front); // Normalizacja wektora
}