using System.Windows;

namespace SBGModLauncher.Views
{
    /// <summary>
    /// Interaction logic for ModBrowserWindow.xaml
    /// </summary>
    public partial class ModBrowserWindow : Window
    {
        public ModBrowserWindow(string gamePath)
        {
            InitializeComponent();
            DataContext = new ViewModels.ModBrowserViewModel(gamePath);
        }
    }
}
