/*
 * Arquivo: main.c
 * Kernel do HomeOS para Samsung Family Hub (Base ARMv7)
 * ----------------------------------------------------
 */

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/module.h>

// Definição da primeira função que o Kernel executa
void __init start_kernel(void)
{
    // 1. Inicialização do Subsistema de Memória
    // Configura a RAM, as páginas de memória e o gerenciamento de memória.
    printk(KERN_INFO "HomeOS: Inicializando gerenciamento de memória (MMU).\n");
    setup_memory();

    // 2. Inicialização do Scheduler (Agendador de Tarefas)
    // Começa a gerenciar as tarefas (processos) que vão rodar no sistema.
    sched_init();
    printk(KERN_INFO "HomeOS: Scheduler ativado. Processos prontos para rodar.\n");

    // 3. Inicialização dos Drivers de Hardware
    // Carrega os drivers essenciais para a geladeira.
    // O Buildroot garantirá que estes módulos estejam disponíveis.
    printk(KERN_INFO "HomeOS: Inicializando drivers criticos (ARMv7).\n");
    drivers_init();

    // 4. Inicialização do Driver de Tela Touchscreen
    // O driver da tela é crucial para a interface do Family Hub.
    touchscreen_driver_init();
    printk(KERN_INFO "HomeOS: Driver Touchscreen carregado com sucesso.\n");

    // 5. Inicialização do Driver da Câmera Interna
    // Permite que a HomeOS veja o que está dentro da geladeira.
    camera_driver_init();
    printk(KERN_INFO "HomeOS: Driver de Câmera (V4L2) carregado.\n");

    // 6. Montagem do Sistema de Arquivos Raiz (rootfs)
    // Onde estão os programas, bibliotecas e o seu Qt/QML compilado.
    rootfs_mount_init();
    printk(KERN_INFO "HomeOS: Sistema de Arquivos Raiz (rootfs) montado.\n");

    // 7. Início do Processo de Inicialização (PID 1)
    // O Kernel executa o primeiro programa do usuário (geralmente 'init' ou 'systemd').
    // Este programa inicia o ambiente gráfico (Qt/QML) e os apps da geladeira.
    printk(KERN_INFO "HomeOS: Iniciando o processo PID 1...\n");
    // O último passo no kernel é chamar a função que inicia o init/systemd
    run_init_process("/sbin/init");

    // Se o init falhar, o kernel entra em pânico.
    for (;;)
        cpu_relax();
}
