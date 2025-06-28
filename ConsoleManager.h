#pragma once
#include <memory>
#include <vector> 
#include <unordered_map>
#include <Windows.h>
#include "AConsole.h"
#include "TypedefRepo.h"
#include "MainConsole.h"
#include "MarqueeConsole.h"
#include "ConsoleGlobals.h"
#include "Process.h"

const String MAIN_CONSOLE = "MAIN_CONSOLE";
const String MARQUEE_CONSOLE = "MARQUEE_CONSOLE";
const String SCHEDULING_CONSOLE = "SCHEDULING_CONSOLE";
const String MEMORY_CONSOLE = "MEMORY_CONSOLE";


class ConsoleManager {

public:
    /* Will contain the consoles/screens*/
    typedef std::unordered_map<String, std::shared_ptr<AConsole>> ConsoleTable;

    /*
    * @brief retreives the instance <sharedInstance> of the ConsoleManager
    *
    */
    static ConsoleManager* getInstance();


    /* @brief initializes the Console Manager
    *
    * This member function is the one used create the instance of Console Manager
    */
    static void initialize();

    /* @brief destroys the instance of the Console Managerl; only use once the program terminates
     *
     * This function destroys the console manager itself
     */
    static void destroy();

    /*
    * @brief Draws the screen of the current console from the <ConsoleTable>
    *
    */
    void drawConsole() const;

    /*
    * @brief shows the process of the current console
    *
    *
    */
    void process() const;

    /*
    * @brief Switches the <currentConsole>  to the next console
    */
    void switchConsole(String consoleName);
    //  volatile char* readLine();


    /*
    * @brief Goes back to <previousConsole> NOT YET IMPLEMENTED
    *
    */
    void returnToPreviousConsole();

    /*
    * @brief NOT YET IMPLEMENTED
    *
    */
    void exitApplication();

    /*
    * @brief NOT YET IMPLEMENTED
    *
    */
    void unregisterScreen();

    /*
    * @brief Checks if the <currentConsole> is still running
    *
    */
    bool isRunning() const;

    /*
    * @brief NOT YET IMPLEMENTED
    *
    */
    void setCursorPosition(int posX, int posY) const;

    /*
    * @brief Clears the screen
    */
    static void refresh();

    void stopRunning();



    bool findConsole(String consoleName);
    void addConsole(String newconsoleName);

    /*
    * @brief Removes the current console from the table and returns to the previous console 
    * ;Mainly used for screen consoles
    */
    void closeConsoleAndReturnToPrevious();

private:
    ConsoleManager();
    ~ConsoleManager() = default;
    ConsoleManager(ConsoleManager const&) = delete;             //Explicitly deletes the copy constructor for the ConsoleManager  ; prevents copying via constructor
    ConsoleManager& operator=(ConsoleManager const&) = delete; //Explicitly deletes copy assignment operator ; prevents assignment from another instance
    static ConsoleManager* sharedInstance;

    ConsoleTable consoleTable;

    std::shared_ptr<AConsole> currentConsole;
    std::shared_ptr<AConsole> previousConsole;
    std::shared_ptr<AConsole> tempConsole;

    bool running = true;

    //Cys variables
    /*int size;
    AConsole* mainMenu;
    AConsole* currentConsole;
    AConsole** allConsoles;
    bool* activeConsoles;*/

    //add console 
    //remove console 


};