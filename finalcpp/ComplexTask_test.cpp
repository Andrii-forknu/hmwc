#include "ComplexTask.h"

// ==============================================================================
// MAIN MENU
// ==============================================================================
int main() {
    std::cout << "========================================================\n";
    std::cout << " WELCOME TO THE COMPLEX NUMBERS CALCULATION PROGRAM! \n";
    std::cout << "========================================================\n";
    std::cout << "Choose the program operation mode:\n";
    std::cout << "1 - Manual mode (you enter all data yourself)\n";
    std::cout << "2 - Automatic test (program will use prepared data)\n";
    std::cout << "3 - Performance Benchmark (Test FFT speed)\n";
    std::cout << "4 - FFT Formula Check & Matrix Visualization\n";
    std::cout << "5 - Verify FFT Correctness (Proof)\n";
    
    int mode_choice;
    while (true) {
        mode_choice = read_int("Your choice (1, 2, 3, 4, or 5): ");
        if (mode_choice >= 1 && mode_choice <= 5) break;
        std::cout << "[Error] Please enter 1, 2, 3, 4, or 5.\n";
    }

    bool auto_mode = (mode_choice == 2);

    if (mode_choice == 1 || mode_choice == 2) {
        if (auto_mode) {
            std::cout << "\n*** AUTOMATIC TEST LAUNCHED ***\n";
        } else {
            std::cout << "\n*** MANUAL MODE LAUNCHED ***\n";
        }
        demo_custom_class(auto_mode);
        demo_quadratic(auto_mode);
        demo_taylor(auto_mode);
        demo_cubic(auto_mode);
        demo_quartic(auto_mode);
        demo_fft(auto_mode);
    } 
    else if (mode_choice == 3) {
        std::cout << "\n*** BENCHMARK MODE LAUNCHED ***\n";
        run_benchmark();
    }
    else if (mode_choice == 4) {
        std::cout << "\n*** FFT VISUALIZATION LAUNCHED ***\n";
        visualize_fft_matrix();
    }
    else if (mode_choice == 5) {
        std::cout << "\n*** FFT CORRECTNESS PROOF LAUNCHED ***\n";
        verify_fft_correctness();
    }
    std::cout << "\nAll operations completed successfully.\n";
    return 0;
}