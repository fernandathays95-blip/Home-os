// Arquivo: main.cpp (C++ Host)
// Ponto de entrada da Interface Gráfica do HomeOS.
// Responsável por inicializar o ambiente .NET (C#).

#include <iostream>
#include <string>
#include <unistd.h>
#include <mono/jit/jit.h> // Se você usar o runtime Mono
#include <mono/metadata/assembly.h>
#include <mono/metadata/debug-helpers.h>

using namespace std;

// Definição da pasta onde o código C# compilado (.dll) está
#define APP_ASSEMBLY_PATH "./HomeOS.Interface.dll"
#define APP_DOMAIN_NAME "HomeOS.AppDomain"

int main(int argc, char* argv[]) 
{
    cout << "HomeOS UI: Iniciando ambiente C++ para carregar a UI em C#..." << endl;

    // 1. Inicializar o ambiente de runtime C# (Mono/NET)
    MonoDomain *domain = mono_jit_init(APP_DOMAIN_NAME);
    if (!domain) {
        cerr << "HomeOS UI ERROR: Falha ao iniciar o runtime C# (Mono/NET). O sistema será desligado." << endl;
        return 1;
    }

    // 2. Carregar o código C# compilado
    MonoAssembly *assembly = mono_domain_assembly_open(domain, APP_ASSEMBLY_PATH);
    if (!assembly) {
        cerr << "HomeOS UI ERROR: Nao foi possivel carregar a DLL da interface C# em: " << APP_ASSEMBLY_PATH << endl;
        mono_jit_cleanup(domain);
        return 1;
    }

    // 3. Executar o código C#
    // O Mono/NET executa a função Main() dentro da DLL HomeOS.Interface.dll.
    cout << "HomeOS UI: DLL carregada com sucesso. Transferindo controle para o C#..." << endl;
    
    // mono_jit_exec executa a função principal do seu C#
    int retval = mono_jit_exec(domain, assembly, argc, argv);

    // 4. Limpeza (se o C# retornar/fechar)
    mono_jit_cleanup(domain);
    cout << "HomeOS UI: Interface C# encerrada. Retornando valor: " << retval << endl;

    return retval;
}

