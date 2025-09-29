/*
 * Arquivo: logo_homeos.c
 * Logo do HomeOS (Matriz de Pixels para o Kernel)
 * ----------------------------------------------------
 * IMPORTANTE: Este codigo é gerado por ferramentas de conversao 
 * e representa a imagem IMG_9989.png em formato que o Kernel entende.
 */

#include <linux/types.h>
#include <linux/stddef.h>

// 1. Dimensoes da imagem do pinguim
// (Estas dimensões são fixas e lidas pelo driver de vídeo)
const int homeos_logo_width = 180;  // Largura em pixels (exemplo)
const int homeos_logo_height = 200; // Altura em pixels (exemplo)
const int homeos_logo_clutsize = 0; // Nao usa paleta de cores

// 2. A matriz de pixels (Os dados brutos da imagem)
// Cada elemento representa uma cor RGB (Vermelho, Verde, Azul)
// O array é 'const' porque o kernel so precisa ler
const u32 homeos_logo_data[] = {
    // Linha 1: 
    0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0x000000, 0x000000, 0x000000, 0xFFFFFF, 0xFFFFFF, // ... e assim por diante
    // Este array continuaria por milhares de entradas (pixels)
    // que representam a sua imagem do pinguim (IMG_9989.png) em formato binario
    // 0x000000 = Preto (cor do corpo do pinguim)
    // 0xFFFFFF = Branco (cor do fundo/barriga)
    // 0xFFA500 = Laranja (cor dos pés e bico)
    
    // ... milhares de pixels da sua imagem ...
    0x000000, 0x000000, 0xFFFFFF, 0xFFA500, 0xFFA500, 0xFFFFFF, 0x000000, 0x000000,
    // ...
};

// 3. Estrutura que o kernel usa para encontrar seu logo
struct logo_homeos {
    const u32 *data;
    const int width;
    const int height;
};

// Variavel global que aponta para o seu logo
struct logo_homeos logo_homeos = {
    .data = homeos_logo_data,
    .width = homeos_logo_width,
    .height = homeos_logo_height,
};
