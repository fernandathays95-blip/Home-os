// Arquivo: HomeOS/gui/native_calls.cpp (C++)

#include <iostream>

// Esta macro 'extern "C"' e 'DLLEXPORT' é crucial. 
// Ela garante que a função possa ser vista e chamada pelo C# (.NET).
#define DLLEXPORT extern "C" __attribute__((visibility("default")))

// Função nativa C++ que a Interface C# chamará
DLLEXPORT int NativeStartCameraApp() {
    std::cout << "C++ NATIVE: Recebido o chamado do C#. Preparando o driver da camera..." << std::endl;

    // *** Aqui é onde o C++ chamaria a função do Kernel/Driver ***
    
    // 1. Abre o dispositivo da câmera (geralmente um arquivo /dev/videoX no Linux)
    int camera_fd = open("/dev/video0", O_RDWR);
    if (camera_fd < 0) {
        std::cerr << "C++ NATIVE ERROR: Falha ao abrir o dispositivo da camera (/dev/video0)." << std::endl;
        return -1;
    }
    
    // 2. Chama uma função do driver do Kernel (ioctl) para ligar o streaming
    // (A função real seria muito mais complexa)
    ioctl(camera_fd, V4L2_CID_POWER_ON, 1);

    std::cout << "C++ NATIVE: Streaming de camera ativado. Driver pronto." << std::endl;
    close(camera_fd);
    return 0;
}
