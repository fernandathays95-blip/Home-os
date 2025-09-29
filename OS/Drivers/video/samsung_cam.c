/*
 * Arquivo: samsung_cam.c
 * Driver de Câmera para o HomeOS (Subsistema V4L2)
 * ----------------------------------------------------
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/videodev2.h> // Essencial para V4L2
#include <media/v4l2-device.h>
#include <media/v4l2-ioctl.h>
#include <linux/i2c.h>       // Protocolo comum para comunicação com chips de câmera

// Estrutura principal do dispositivo de vídeo
struct samsung_camera_device {
    struct v4l2_device v4l2_dev;
    struct video_device vdev;
    struct i2c_client *client;
    // ... buffers de memória para frames de imagem ...
};

// 1. Função que o Kernel usa para manipular o dispositivo (IOCTL)
// Esta é a função que o seu código C++ chama indiretamente (ioctl)
static const struct v4l2_ioctl_ops samsung_cam_ioctl_ops = {
    // Configuração e controles (Ex: ligar/desligar, mudar resolucao)
    .vidioc_querycap      = v4l2_querycap,
    .vidioc_g_fmt_vid_cap = v4l2_g_fmt_vid_cap, // Obter formato atual
    .vidioc_try_fmt_vid_cap = v4l2_try_fmt_vid_cap, // Tentar mudar formato
    .vidioc_s_fmt_vid_cap = v4l2_s_fmt_vid_cap, // Definir formato (Ex: 1080p)

    // Streaming de memória (o buffer que guarda a imagem)
    .vidioc_reqbufs       = v4l2_reqbufs,
    .vidioc_querybuf      = v4l2_querybuf,
    .vidioc_qbuf          = v4l2_qbuf,
    .vidioc_dqbuf         = v4l2_dqbuf,
    
    // Iniciar/Parar a captura de frames
    .vidioc_streamon      = v4l2_streamon,
    .vidioc_streamoff     = v4l2_streamoff,
    
    // ... outras operações ...
};

// 2. Função de Inicialização do Driver
int __init camera_driver_init(void)
{
    struct samsung_camera_device *cam_dev;
    int err;

    printk(KERN_INFO "HomeOS Camera: Inicializando driver de camera (V4L2).\n");

    // a. Aloca e inicializa a estrutura principal
    cam_dev = kzalloc(sizeof(*cam_dev), GFP_KERNEL);
    if (!cam_dev)
        return -ENOMEM;

    // b. Encontra o chip da câmera via I2C (Protocolo de comunicação)
    cam_dev->client = i2c_find_device("samsung_cam_id");
    if (!cam_dev->client) {
        printk(KERN_ERR "HomeOS Camera: Chip I2C da camera nao encontrado!\n");
        kfree(cam_dev);
        return -ENODEV;
    }

    // c. Inicializa o dispositivo de vídeo
    cam_dev->vdev.minor = -1;
    cam_dev->vdev.fops = &v4l2_fops; // Funções de arquivo (open, close, read)
    cam_dev->vdev.ioctl_ops = &samsung_cam_ioctl_ops; // Operações de IOCTL (as mais importantes)
    cam_dev->vdev.release = video_device_release;
    cam_dev->vdev.v4l2_dev = &cam_dev->v4l2_dev;
    strlcpy(cam_dev->vdev.name, "HomeOS_Cam", sizeof(cam_dev->vdev.name));

    // d. Registra o dispositivo no V4L2
    // É isso que cria o arquivo /dev/video0 (ou /dev/video1, etc.)
    err = video_register_device(&cam_dev->vdev, VFL_TYPE_GRABBER, -1);
    if (err) {
        printk(KERN_ERR "HomeOS Camera: Falha ao registrar dispositivo de video.\n");
        kfree(cam_dev);
        return err;
    }

    printk(KERN_INFO "HomeOS Camera: Driver ativo. Dispositivo /dev/%s criado.\n", video_device_node_name(&cam_dev->vdev));
    return 0;
}
