// Arquivo: CameraView.cs (C# Interface)
// Uma nova janela/tela para o aplicativo "Ver Interior".

using System;
using System.Threading.Tasks;
using System.Timers;

// (Assumindo um Framework de UI como Avalonia ou similar)
public class CameraView : Window
{
    private Image videoFrame;
    private Label statusLabel;
    private System.Timers.Timer refreshTimer;

    public CameraView()
    {
        this.Title = "Visualizador de Conteúdo da Geladeira";
        this.IsFullScreen = true;
        this.BackgroundColor = Colors.Black; // Fundo preto para destaque do vídeo

        // 1. Label de Status
        statusLabel = new Label("Iniciando driver da Câmera (aguarde)...")
        {
            FontSize = 36,
            TextColor = Colors.Yellow,
            HorizontalAlignment = HAlignment.Center
        };
        this.Add(statusLabel);
        
        // 2. Componente Principal para exibir o vídeo
        videoFrame = new Image()
        {
            Source = null, // Inicialmente vazio
            Stretch = Stretch.Uniform
        };
        this.Add(videoFrame);

        // 3. Botão para Voltar para a Home
        var backButton = new Button("Voltar para Home")
        {
            OnClick = () => {
                StopCameraFeed(); // Garante que o stream C++ seja parado
                // (Lógica para fechar esta janela e voltar para a Main Window)
            }
        };
        this.Add(backButton);

        // Inicia o processo de carregamento quando a janela for exibida
        this.Loaded += OnViewLoaded;
    }

    private void OnViewLoaded()
    {
        // 1. Chama a função C++ para ligar o hardware da Câmera.
        int result = NativeCodeBridge.StartCameraApp(); 
        
        if (result == 0)
        {
            statusLabel.TextColor = Colors.Green;
            statusLabel.Text = "Câmera Ativa. Carregando imagem...";
            
            // 2. Inicia um timer para atualizar a imagem (simulando um stream)
            StartCameraFeed();
        }
        else
        {
            statusLabel.TextColor = Colors.Red;
            statusLabel.Text = $"ERRO: Falha ao ligar a câmera. Cod: {result}";
        }
    }

    private void StartCameraFeed()
    {
        // No HomeOS real, o C++ exporia uma função para pegar o Frame.
        refreshTimer = new System.Timers.Timer(1000); // Tenta atualizar a cada 1 segundo
        refreshTimer.Elapsed += async (sender, e) => {
            // Chama o C++ para obter o último frame da câmera
            var newFrameData = NativeCodeBridge.GetCameraFrame(); 
            
            // Simulação: se tiver dados, exibe
            if (newFrameData != null)
            {
                videoFrame.Source = ImageConverter.FromBytes(newFrameData);
                statusLabel.Text = "Último Conteúdo: " + DateTime.Now.ToString("HH:mm:ss");
            }
        };
        refreshTimer.Start();
    }
    
    private void StopCameraFeed()
    {
        if (refreshTimer != null)
        {
            refreshTimer.Stop();
        }
        NativeCodeBridge.StopCameraApp(); // Nova função C++ para desligar o driver
    }
}

// Nota: A classe NativeCodeBridge precisaria de novas declarações 'DllImport' 
// para GetCameraFrame() e StopCameraApp() para funcionar!
