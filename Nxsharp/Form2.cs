using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Resources;
using System.Threading;

namespace gui
{
    public partial class Form2 : Form
    {
        public Form2()
        {
            InitializeComponent();
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void label1_Click_1(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (NetworkInterfaceAvaliable.adapters_dict.ContainsKey(Cfg.device))
            {
                //Thread t = new Thread(new ThreadStart(NetworkInterfaceAvaliable.RefreshDHCP));
                NetworkInterfaceAvaliable.RefreshDHCP(NetworkInterfaceAvaliable.adapters_dict[Cfg.device]);
            }
            else
            {
                MessageBox.Show("你没有选择网卡！");
                this.Close();
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Cfg.CreateFile();
            MessageBox.Show("请重新打开程序！");
            System.Environment.Exit(0);
        }

        private void button3_Click(object sender, EventArgs e)
        {
            //TODO 
        }

        private void button4_Click(object sender, EventArgs e)
        {
            string path = Application.StartupPath + "/";
            string pcapFileName = "WinPcap_4_1_3.exe";
            FileStream fs = new FileStream(path + pcapFileName, FileMode.OpenOrCreate, FileAccess.Write);
            BinaryWriter bw = new BinaryWriter(fs);
            bw.Write(gui.Properties.Resources.WinPcap_4_1_3);
            bw.Close();
            fs.Close();
            MessageBox.Show("WinPcap安装文件已生成，请手动安装WinPcap后重启本程序！");
            return;
        }
    }
}
