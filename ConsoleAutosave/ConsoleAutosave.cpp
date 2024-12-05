#include <windows.h>
#include <iostream>
#include <string>
#include <thread>

// Function to bring the window to the foreground and simulate Ctrl + S for saving
void AutoSaveProgram(const std::string& windowTitle) {
    // Convert the windowTitle string to a wide string (for FindWindow)
    std::wstring wideWindowTitle(windowTitle.begin(), windowTitle.end());

    // Find the target window
    HWND hwnd = FindWindow(NULL, wideWindowTitle.c_str());

    if (hwnd == NULL) {
        std::cerr << "Error: Window not found for \"" << windowTitle << "\"." << std::endl;
        return;
    }

    // Bring the window to the foreground
    SetForegroundWindow(hwnd);

    // Simulate pressing Ctrl + S
    INPUT inputs[4] = { 0 };

    // Press the Ctrl key down
    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = VK_CONTROL;

    // Press the S key down
    inputs[1].type = INPUT_KEYBOARD;
    inputs[1].ki.wVk = 'S';

    // Release the S key
    inputs[2].type = INPUT_KEYBOARD;
    inputs[2].ki.wVk = 'S';
    inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;

    // Release the Ctrl key
    inputs[3].type = INPUT_KEYBOARD;
    inputs[3].ki.wVk = VK_CONTROL;
    inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;

    // Send the input (simulate Ctrl + S)
    SendInput(4, inputs, sizeof(INPUT));

    std::cout << "Autosave triggered for: " << windowTitle << std::endl;
}

int main() {
    // Prompt user to enter the window title of the program to autosave
    std::string windowTitle;
    std::cout << "Enter the window title of the program you want to autosave: ";
    std::getline(std::cin, windowTitle);

    // Time interval (5 minutes = 300,000 milliseconds)
    const int interval = 5 * 60 * 1000;  // 5 minutes

    while (true) {
        AutoSaveProgram(windowTitle);

        // Wait for the next interval
        std::this_thread::sleep_for(std::chrono::milliseconds(interval));
    }

    return 0;
}
