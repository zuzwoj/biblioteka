#include "application.h"

bool Application::initialize()
{
    // intialize GLWF window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
    window = glfwCreateWindow(1, 1, "Biblioteka", NULL, NULL);
    glfwSetWindowAttrib(window, GLFW_MAXIMIZED, GLFW_TRUE);
    if (window == NULL)
    {
        std::cout << "Cannot create window." << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);

    // verify GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Cannot initialize GLAD." << std::endl;
        return false;
    }

    // initialize imgui
    IMGUI_CHECKVERSION();
    ImGui::SetCurrentContext(ImGui::CreateContext());
    io = &ImGui::GetIO();
    io->Fonts->AddFontFromFileTTF(FONT_PATH, FONT_SIZE, nullptr, io->Fonts->GetGlyphRangesDefault());
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
    ImGui::StyleColorsLight();

    library = new Library();
    initializeDummyLibrary();
    guiRenderer = new GuiRenderer(*library);

    return true;
}

void Application::run()
{
    while (!glfwWindowShouldClose(window))
    {
        guiRenderer->render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Application::cleanup()
{
    delete guiRenderer;
    delete library;
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
}

void Application::initializeDummyLibrary()
{
    library->addShelf("1");
    library->addShelf("2");
    BookData b1 = BookData(
        "Lalka", 
        u8"Bolesław Prus", 
        1889, 
        480,
        1,
        u8"Powieść społeczno-obyczajowa publikowana w dzienniku Kurier Codzienny, wydana w Warszawie w wydawnictwie Gebethner i Wolff. Uznawana jest za jedną z najlepszych polskich powieści.");
    BookData b2 = BookData(
        "Wizja Lokalna", 
        u8"Stanisław Lem", 
        1982, 
        476, 
        1, 
        u8"Powieść opowiada o podróży Ijona Tichego na odległą planetę, Encję (co jest łacińskim tłumaczeniem nazwy własnej owego świata), w celu zbadania tamtejszej cywilizacji.");
    BookData b3 = BookData(
        u8"I nie było już nikogo", 
        "Agata Christie", 
        1939,
        224,
        2,
        u8"Tajemniczy pan Owen zaprasza na odciętą od świata wyspę dziesięciu gości, których pozornie nic ze sobą nie łączy. W dniu przyjazdu okazuje się, że gospodarz nie pojawi się na wyspie.");
    BookData b4 = BookData(
        "Proces", 
        "Franz Kafka", 
        1925, 
        208,
        2,
        u8"Głównym bohaterem powieści jest Józef K., kawaler, prokurent bankowy, mieszkający w mieście, określanym jako stolica. Pewnego dnia budzi się w swoim mieszkaniu i zostaje zaskoczony najściem urzędników, którzy oświadczają mu, że zostaje aresztowany, mimo iż nic złego nie popełnił.");
    std::vector<Shelf>& sfs = library->getShelves();
    sfs[0].addBook(b1);
    sfs[0].addBook(b2);
    sfs[1].addBook(b3);
    sfs[1].addBook(b4);
}
