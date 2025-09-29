// Arquivo: HomeOS/gui/HomeOS.Interface/NativeCodeBridge.cs (C#)

using System.Runtime.InteropServices;

public static class NativeCodeBridge
{
    // A tag [DllImport] diz ao C# onde a função nativa C++ está.
    // O nome da biblioteca que o C++ gerou (neste caso, uma lib simples)
    private const string NativeLib = "libnative_calls.so"; 

    // Declaração da função nativa C++
    [DllImport(NativeLib, EntryPoint = "NativeStartCameraApp")]
    public static extern int StartCameraApp();
    
    // ... e a interface C# chama essa função simples:
    public static void OpenCameraView() 
    {
        int result = StartCameraApp();
        if (result != 0)
        {
            // Trata o erro se o C++ não conseguiu iniciar a câmera
            Console.WriteLine($"Erro ao iniciar a câmera! Código: {result}");
        }
    }
}
