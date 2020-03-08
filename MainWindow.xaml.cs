using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Forms;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace MouseToJoystick2
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private MouseToJoystickHandler handler = null;

        public MainWindow()
        {
            InitializeComponent();
        }

        private void ToggleButton_Click(object sender, RoutedEventArgs e)
        {
            var model = (MainWindowModel)this.DataContext;

            if (model.ShouldRun == true)
            {
                uint deviceId = Convert.ToUInt32(model.DeviceId);
                int manualWidth = Convert.ToInt32(model.ScreenWidth);
                int manualHeight = Convert.ToInt32(model.ScreenHeight);
                try
                {
                    handler = new MouseToJoystickHandler(deviceId, model.InvertX, model.InvertY, model.AutoCenter, model.AutoScreenSize, manualWidth, manualHeight);
                    model.SettingsEnabled = false;
                }
                catch (Exception err)
                {
                    Console.WriteLine("Whoops!");
                    System.Windows.Forms.MessageBox.Show(err.Message);
                    model.ShouldRun = false;
                }
            }
            else
            {
                if (this.handler != null)
                {
                    this.handler.Dispose();
                    this.handler = null;
                }
                model.SettingsEnabled = true;
            }

            //var btn = (ToggleButton)sender;
            //bool isChecked = btn.IsChecked == true;

            //if (isChecked)
            //{
            //    try
            //    {
            //        handler = new MouseToJoystickHandler();
            //    }
            //    catch (Exception err)
            //    {

            //    }
            //}
        }
    }
}
