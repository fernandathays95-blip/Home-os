// Arquivo: HomeOS/kernel/panic.c

#include <linux/kernel.h>
#include <linux/panic.h>
#include "errors.h" // Inclui os seus códigos de erro

// Função que o kernel chama em caso de erro fatal específico do HomeOS
void homeos_panic_handler(int error_code, const char *msg_context)
{
    const char *error_message = NULL;
    
    // 1. Mapeamento do Código de Erro para a Mensagem (Mensagem exibida na tela)
    switch (error_code) {
        case HOMEOS_ERR_ROOTFS_NOT_FOUND:
            error_message = "ERRO 1: DIRETORIO HOMEOS AUSENTE. RESTAURACAO DE FABRICA NECESSARIA.";
            break;
        case HOMEOS_ERR_BASE_CRITICAL_FAIL:
            error_message = "ERRO 2: FALHA CRITICA NA BASE DO SISTEMA. HARDWARE INCOMPATIVEL OU CORROMPIDO.";
            break;
        default:
            error_message = "ERRO DESCONHECIDO. CONTATE O SUPORTE TECNICO.";
            break;
    }

    // 2. Chama a função panic() do Linux com a mensagem personalizada
    // Esta chamada executa o show_linux_logo() (seu pinguim) e congela o sistema.
    panic("HOMEOS PANIC (CODIGO: %d). Contexto: %s. Mensagem: %s", 
          error_code, 
          msg_context,
          error_message);
    
    // O kernel nunca deve retornar desta função.
}
